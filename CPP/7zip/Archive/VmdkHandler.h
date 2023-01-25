// VmdkHandler.h

#ifndef __VMDK_HANDLER_H
#define __VMDK_HANDLER_H

#include "../../Common/MyCom.h"
#include "../../Common/MyString.h"
#include "../../Common/MyVector.h"

namespace NArchive {
namespace NVmdk {

struct CHeader
{
  UInt32 flags;
  UInt32 version;

  UInt64 capacity;
  UInt64 grainSize;
  UInt64 descriptorOffset;
  UInt64 descriptorSize;

  UInt32 numGTEsPerGT;
  UInt16 algo;
  // Byte uncleanShutdown;
  // UInt64 rgdOffset;
  UInt64 gdOffset;
  UInt64 overHead;

  bool Is_NL()         const;
  bool Is_ZeroGrain()  const;
  bool Is_Compressed() const;
  bool Is_Marker()     const;

  bool Parse(const Byte *p);

  bool IsSameImageFor(const CHeader &h) const;
};

struct CMarker
{
  UInt64 NumSectors;
  UInt32 SpecSize; // = 0 for metadata sectors
  UInt32 Type;

  void Parse(const Byte *p);
};

struct CExtentInfo
{
  AString Access;    // RW, RDONLY, or NOACCESS
  UInt64 NumSectors; // 512 bytes sectors
  AString Type;      // FLAT, SPARSE, ZERO, VMFS, VMFSSPARSE, VMFSRDM, VMFSRAW
  AString FileName;
  UInt64 StartSector; // used for FLAT

  // for VMWare Player 9:
  // PartitionUUID
  // DeviceIdentifier

  bool IsType_ZERO() const;
  // bool IsType_FLAT() const;
  bool IsType_Flat() const;

  bool Parse(const char *s);
};

struct CDescriptor
{
  AString CID;
  AString parentCID;
  AString createType;
  // AString encoding; // UTF-8, windows-1252 - default is UTF-8

  CObjectVector<CExtentInfo> Extents;

  static void GetUnicodeName(const AString &s, UString &res);

  void Clear();

  bool IsThere_Parent() const;

  bool Parse(const Byte *p, size_t size);
};

struct CExtent
{
  bool IsOK;
  bool IsArc;
  bool NeedDeflate;
  bool Unsupported;
  bool IsZero;
  bool IsFlat;
  bool DescriptorOK;
  bool HeadersError;

  unsigned ClusterBits;
  UInt32 ZeroSector;

  CObjectVector<CByteBuffer> Tables;

  CMyComPtr<IInStream> Stream;
  UInt64 PosInArc;
  
  UInt64 PhySize;
  UInt64 VirtSize;     // from vmdk header of volume

  UInt64 StartOffset;  // virtual offset of this extent
  UInt64 NumBytes;     // from main descriptor, if multi-vol
  UInt64 FlatOffset;   // in Stream

  CByteBuffer DescriptorBuf;
  CDescriptor Descriptor;

  CHeader h;

  UInt64 GetEndOffset() const;

  bool IsVmdk() const;
  // if (IsOK && IsVmdk()), then VMDK header of this extent was read

  CExtent();

  HRESULT ReadForHeader(IInStream *stream, UInt64 sector, void *data, size_t numSectors);
  HRESULT Open3(IInStream *stream, IArchiveOpenCallback *openCallback,
        unsigned numVols, unsigned volIndex, UInt64 &complexity);
  HRESULT Seek(UInt64 offset);
  HRESULT InitAndSeek();
  HRESULT Read(void *data, size_t *size);
};

class CHandler: public CHandlerImg
{
  bool _isArc;
  bool _unsupported;
  bool _unsupportedSome;
  bool _headerError;
  bool _missingVol;
  bool _isMultiVol;
  bool _needDeflate;

  UInt64 _cacheCluster;
  unsigned _cacheExtent;
  CByteBuffer _cache;
  CByteBuffer _cacheCompressed;
  
  unsigned _clusterBitsMax;
  UInt64 _phySize;

  CObjectVector<CExtent> _extents;

  CBufInStream *_bufInStreamSpec;
  CMyComPtr<ISequentialInStream> _bufInStream;

  CBufPtrSeqOutStream *_bufOutStreamSpec;
  CMyComPtr<ISequentialOutStream> _bufOutStream;

  NCompress::NZlib::CDecoder *_zlibDecoderSpec;
  CMyComPtr<ICompressCoder> _zlibDecoder;

  CByteBuffer _descriptorBuf;
  CDescriptor _descriptor;

  UString _missingVolName;

  void InitAndSeekMain();

  virtual HRESULT Open2(IInStream *stream, IArchiveOpenCallback *openCallback);
  virtual void CloseAtError();
public:
  static void Register();

  INTERFACE_IInArchive_Img(;)

  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
  STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);
};

}}

#endif // __VMDK_HANDLER_H

// VhdxHandler.h

#ifndef __VHDX_HANDLER_H
#define __VHDX_HANDLER_H

#include "../../Common/MyCom.h"
#include "../../Common/MyString.h"
#include "../../Common/MyVector.h"

namespace NArchive {
namespace NVhdx {

struct CGuid
{
  Byte Data[16];

  bool IsZero() const;
  bool IsEqualTo(const Byte *a) const;
  bool IsEqualTo(const CGuid &g) const;
  void AddHexToString(UString &s) const;
  void SetFrom(const Byte *p);
  bool ParseFromFormatedHexString(const UString &s);
};

struct CHeader
{
  UInt64 SequenceNumber;
  // UInt16 LogVersion;
  // UInt16 Version;
  UInt32 LogLength;
  UInt64 LogOffset;
  CGuid Guids[3];

  bool Parse(Byte *p);
};

struct CRegionEntry
{
  // CGuid Guid;
  UInt64 Offset;
  UInt32 Len;
  UInt32 Required;

  UInt64 GetEndPos() const;
  bool Parse(const Byte *p);
};

struct CRegion
{
  bool Bat_Defined;
  bool Meta_Defined;
  UInt64 EndPos;
  UInt64 DataSize;

  CRegionEntry BatEntry;
  CRegionEntry MetaEntry;

  bool Parse(Byte *p);
};

struct CMetaEntry
{
  CGuid Guid;
  UInt32 Offset;
  UInt32 Len;
  UInt32 Flags0;
  // UInt32 Flags1;

  bool IsUser()        const;
  bool IsVirtualDisk() const;
  bool IsRequired()    const;

  bool CheckLimit(size_t regionSize) const;

  bool Parse(const Byte *p);
};

struct CParentPair
{
  UString Key;
  UString Value;
};

struct CMetaHeader
{
  // UInt16 EntryCount;
  bool Guid_Defined;
  bool VirtualDiskSize_Defined;
  bool Locator_Defined;

  unsigned BlockSize_Log;
  unsigned LogicalSectorSize_Log;
  unsigned PhysicalSectorSize_Log;

  UInt32 Flags;
  UInt64 VirtualDiskSize;
  CGuid Guid;
  // CGuid LocatorType;

  CObjectVector<CParentPair> ParentPairs;

  int FindParentKey(const char *name) const;

  bool Is_LeaveBlockAllocated() const;
  bool Is_HasParent() const;

  void Clear();
  bool Parse(const Byte *p, size_t size);
};

struct CBat
{
  CByteBuffer Data;

  void Clear();
  UInt64 GetItem(size_t n) const;
};

class CHandler: public CHandlerImg
{
  UInt64 _phySize;

  CBat Bat;
  CObjectVector<CByteBuffer> BitMaps;

  unsigned ChunkRatio_Log;
  size_t ChunkRatio;
  size_t TotalBatEntries;

  CMetaHeader Meta;
  CHeader Header;

  UInt32 NumUsedBlocks;
  UInt32 NumUsedBitMaps;
  UInt64 HeadersSize;

  UInt32 NumLevels;
  UInt64 PackSize_Total;

  /*
  UInt64 NumUsed_1MB_Blocks; // data and bitmaps
  bool NumUsed_1MB_Blocks_Defined;
  */

  CMyComPtr<IInStream> ParentStream;
  CHandler *Parent;
  UString _errorMessage;
  UString _Creator;

  bool _nonEmptyLog;
  bool _isDataContiguous;
  // bool _BatOverlap;

  CGuid _parentGuid;
  bool _parentGuid_IsDefined;
  UStringVector ParentNames;
  UString ParentName_Used;

  const CHandler *_child;
  unsigned _level;
  bool _isCyclic;
  bool _isCyclic_or_CyclicParent;

  void AddErrorMessage(const char *message);
  void AddErrorMessage(const char *message, const wchar_t *name);

  void UpdatePhySize(UInt64 value);

  HRESULT Seek2(UInt64 offset);
  HRESULT Read_FALSE(Byte *data, size_t size);
  HRESULT ReadToBuf_FALSE(CByteBuffer &buf, size_t size);
  
  void InitSeekPositions();
  HRESULT ReadPhy(UInt64 offset, void *data, UInt32 size, UInt32 &processed);

  bool IsDiff() const;

  void AddTypeString(AString &s) const;

  void AddComment(UString &s) const;

  UInt64 GetPackSize() const;

  UString GetParentSequence() const;

  bool AreParentsOK() const;

  // bool ParseLog(CByteBuffer &log);
  bool ParseBat();
  bool CheckBat();

  HRESULT Open3();
  HRESULT Open2(IInStream *stream, IArchiveOpenCallback *openArchiveCallback);
  HRESULT OpenParent(IArchiveOpenCallback *openArchiveCallback, bool &_parentFileWasOpen);
  virtual void CloseAtError();

public:
  static void Register();

  INTERFACE_IInArchive_Img(;)

  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
  STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);

  CHandler();
};

}}

#endif // __VHDX_HANDLER_H

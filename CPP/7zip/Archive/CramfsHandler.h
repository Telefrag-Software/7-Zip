// CramfsHandler.cpp

#ifndef __CRAMFS_HANDLER_H
#define __CRAMFS_HANDLER_H

#include "../../Common/MyCom.h"
#include "../../Common/MyString.h"
#include "../../Common/MyVector.h"
#include "../Common/StreamObjects.h"
#include "../Compress/ZlibDecoder.h"

namespace NArchive {
namespace NCramfs {

static const UInt32 kArcSizeMax = (256 + 16) << 20;
static const UInt32 kNumFilesMax = (1 << 19);
static const unsigned kNumDirLevelsMax = (1 << 8);

static const UInt32 kHeaderSize = 0x40;
static const unsigned kHeaderNameSize = 16;
static const UInt32 kNodeSize = 12;

static const UInt32 kFlag_FsVer2 = (1 << 0);

static const unsigned k_Flags_BlockSize_Shift = 11;
static const unsigned k_Flags_BlockSize_Mask = 7;
static const unsigned k_Flags_Method_Shift = 14;
static const unsigned k_Flags_Method_Mask = 3;

struct CItem
{
  UInt32 Offset;
  int Parent;
};

struct CHeader
{
  bool be;
  UInt32 Size;
  UInt32 Flags;
  // UInt32 Future;
  UInt32 Crc;
  // UInt32 Edition;
  UInt32 NumBlocks;
  UInt32 NumFiles;
  char Name[kHeaderNameSize];

  bool Parse(const Byte *p);

  bool IsVer2() const { return (Flags & kFlag_FsVer2) != 0; }
  unsigned GetBlockSizeShift() const { return (unsigned)(Flags >> k_Flags_BlockSize_Shift) & k_Flags_BlockSize_Mask; }
  unsigned GetMethod() const { return (unsigned)(Flags >> k_Flags_Method_Shift) & k_Flags_Method_Mask; }
};

class CHandler:
  public IInArchive,
  public IInArchiveGetStream,
  public CMyUnknownImp
{
  CRecordVector<CItem> _items;
  CMyComPtr<IInStream> _stream;
  Byte *_data;
  UInt32 _size;
  UInt32 _headersSize;

  UInt32 _errorFlags;
  bool _isArc;

  CHeader _h;
  UInt32 _phySize;

  unsigned _method;
  unsigned _blockSizeLog;

  // Current file

  NCompress::NZlib::CDecoder *_zlibDecoderSpec;
  CMyComPtr<ICompressCoder> _zlibDecoder;

  CBufInStream *_inStreamSpec;
  CMyComPtr<ISequentialInStream> _inStream;

  CBufPtrSeqOutStream *_outStreamSpec;
  CMyComPtr<ISequentialOutStream> _outStream;

  UInt32 _curBlocksOffset;
  UInt32 _curNumBlocks;

  HRESULT OpenDir(int parent, UInt32 baseOffsetBase, unsigned level);
  HRESULT Open2(IInStream *inStream);
  AString GetPath(int index) const;
  bool GetPackSize(int index, UInt32 &res) const;
  void Free();

  UInt32 GetNumBlocks(UInt32 size) const
  {
    return (size + ((UInt32)1 << _blockSizeLog) - 1) >> _blockSizeLog;
  }

  void UpdatePhySize(UInt32 s)
  {
    if (_phySize < s)
      _phySize = s;
  }

public:
  static void Register();

  CHandler(): _data(0) {}
  ~CHandler() { Free(); }
  MY_UNKNOWN_IMP2(IInArchive, IInArchiveGetStream)
  INTERFACE_IInArchive(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
  HRESULT ReadBlock(UInt64 blockIndex, Byte *dest, size_t blockSize);
};

}}

#endif // __CRAMFS_HANDLER_H

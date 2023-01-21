// SquashfsHandler.h

#ifndef __SQUASHFS__HANDLER_H
#define __SQUASHFS__HANDLER_H

#include "../../../C/Xz.h"
#include "../../Common/MyCom.h"
#include "../../Common/MyString.h"
#include "../../Common/MyVector.h"
#include "../Common/LimitedStreams.h"

namespace NArchive {
namespace NSquashfs {

struct CHeader
{
  bool be;
  bool SeveralMethods;
  Byte NumUids;
  Byte NumGids;

  UInt32 NumInodes;
  UInt32 CTime;
  UInt32 BlockSize;
  UInt32 NumFrags;
  UInt16 Method;
  UInt16 BlockSizeLog;
  UInt16 Flags;
  UInt16 NumIDs;
  UInt16 Major;
  UInt16 Minor;
  UInt64 RootInode;
  UInt64 Size;
  UInt64 UidTable;
  UInt64 GidTable;
  UInt64 XattrIdTable;
  UInt64 InodeTable;
  UInt64 DirTable;
  UInt64 FragTable;
  UInt64 LookupTable;

  void Parse3(const Byte *p);
  void Parse4(const Byte *p);
  bool Parse(const Byte *p);
  bool IsSupported() const;
  bool IsOldVersion() const;
  bool NeedCheckData() const;
  unsigned GetFileNameOffset() const;
  unsigned GetSymLinkOffset() const;
  unsigned GetSpecGuidIndex() const;
};

struct CNode
{
  UInt16 Type;
  UInt16 Mode;
  UInt16 Uid;
  UInt16 Gid;
  UInt32 Frag;
  UInt32 Offset;
  // UInt32 MTime;
  // UInt32 Number;
  // UInt32 NumLinks;
  // UInt32 RDev;
  // UInt32 Xattr;
  // UInt32 Parent;
  
  UInt64 FileSize;
  UInt64 StartBlock;
  // UInt64 Sparse;

  UInt32 Parse1(const Byte *p, UInt32 size, const CHeader &_h);
  UInt32 Parse2(const Byte *p, UInt32 size, const CHeader &_h);
  UInt32 Parse3(const Byte *p, UInt32 size, const CHeader &_h);
  UInt32 Parse4(const Byte *p, UInt32 size, const CHeader &_h);

  bool IsDir() const;
  bool IsLink() const;
  UInt64 GetSize() const;
  bool ThereAreFrags() const;
  UInt64 GetNumBlocks(const CHeader &_h) const;
};

struct CItem
{
  int Node;
  int Parent;
  UInt32 Ptr;

  CItem();
};

struct CData
{
  CByteBuffer Data;
  CRecordVector<UInt32> PackPos;
  CRecordVector<UInt32> UnpackPos; // additional item at the end contains TotalUnpackSize

  UInt32 GetNumBlocks() const;
  void Clear();
};

struct CFrag
{
  UInt64 StartBlock;
  UInt32 Size;
};

class CHandler:
  public IInArchive,
  public IInArchiveGetStream,
  public CMyUnknownImp
{
  CRecordVector<CItem> _items;
  CRecordVector<CNode> _nodes;
  CRecordVector<UInt32> _nodesPos;
  CRecordVector<UInt32> _blockToNode;
  CData _inodesData;
  CData _dirs;
  CRecordVector<CFrag> _frags;
  // CByteBuffer _uids;
  // CByteBuffer _gids;
  CHeader _h;
  bool _noPropsLZMA;
  bool _needCheckLzma;
  
  UInt32 _openCodePage;

  CMyComPtr<IInStream> _stream;
  UInt64 _sizeCalculated;

  IArchiveOpenCallback *_openCallback;

  int _nodeIndex;
  CRecordVector<bool> _blockCompressed;
  CRecordVector<UInt64> _blockOffsets;
  
  CByteBuffer _cachedBlock;
  UInt64 _cachedBlockStartPos;
  UInt32 _cachedPackBlockSize;
  UInt32 _cachedUnpackBlockSize;

  CLimitedSequentialInStream *_limitedInStreamSpec;
  CMyComPtr<ISequentialInStream> _limitedInStream;

  CBufPtrSeqOutStream *_outStreamSpec;
  CMyComPtr<ISequentialOutStream> _outStream;

  // NCompress::NLzma::CDecoder *_lzmaDecoderSpec;
  // CMyComPtr<ICompressCoder> _lzmaDecoder;

  NCompress::NZlib::CDecoder *_zlibDecoderSpec;
  CMyComPtr<ICompressCoder> _zlibDecoder;
  
  CXzUnpacker _xz;

  CByteBuffer _inputBuffer;

  CDynBufSeqOutStream *_dynOutStreamSpec;
  CMyComPtr<ISequentialOutStream> _dynOutStream;

  void ClearCache();

  HRESULT Decompress(ISequentialOutStream *outStream, Byte *outBuf, bool *outBufWasWritten, UInt32 *outBufWasWrittenSize,
      UInt32 inSize, UInt32 outSizeMax);
  HRESULT ReadMetadataBlock(UInt32 &packSize);
  HRESULT ReadData(CData &data, UInt64 start, UInt64 end);

  HRESULT OpenDir(int parent, UInt32 startBlock, UInt32 offset, unsigned level, int &nodeIndex);
  HRESULT ScanInodes(UInt64 ptr);
  // HRESULT ReadUids(UInt64 start, UInt32 num, CByteBuffer &ids);
  HRESULT Open2(IInStream *inStream);
  AString GetPath(int index) const;
  bool GetPackSize(int index, UInt64 &res, bool fillOffsets);

public:
  static void Register();

  CHandler();
  ~CHandler();

  MY_UNKNOWN_IMP2(IInArchive, IInArchiveGetStream)
  INTERFACE_IInArchive(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);

  HRESULT ReadBlock(UInt64 blockIndex, Byte *dest, size_t blockSize);
};

struct CTempItem
{
  UInt32 StartBlock;
  // UInt32 iNodeNumber1;
  UInt32 Offset;
  // UInt16 iNodeNumber2;
  UInt16 Type;
};

class CSquashfsInStream: public CCachedInStream
{
  HRESULT ReadBlock(UInt64 blockIndex, Byte *dest, size_t blockSize);
public:
  CHandler *Handler;
};

}}

#endif // __SQUASHFS__HANDLER_H

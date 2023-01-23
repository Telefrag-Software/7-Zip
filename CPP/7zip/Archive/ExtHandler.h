// ExtHandler.h

#ifndef __EXT_HANDLER_H
#define __EXT_HANDLER_H

#include "../../Common/MyCom.h"
#include "../../Common/MyString.h"
#include "../../Common/MyVector.h"

namespace NArchive {
namespace NExt {

enum
{
  k_Type_UNKNOWN,
  k_Type_REG_FILE,
  k_Type_DIR,
  k_Type_CHRDEV,
  k_Type_BLKDEV,
  k_Type_FIFO,
  k_Type_SOCK,
  k_Type_SYMLINK
};

static const unsigned kNumTreeLevelsMax = 6; // must be >= 3

static const unsigned kNodeBlockFieldSize = 60;

struct CHeader
{
  unsigned BlockBits;
  unsigned ClusterBits;

  UInt32 NumInodes;
  UInt64 NumBlocks;
  // UInt64 NumBlocksSuper;
  UInt64 NumFreeBlocks;
  UInt32 NumFreeInodes;
  // UInt32 FirstDataBlock;

  UInt32 BlocksPerGroup;
  UInt32 ClustersPerGroup;
  UInt32 InodesPerGroup;

  UInt32 MountTime;
  UInt32 WriteTime;

  // UInt16 NumMounts;
  // UInt16 NumMountsMax;
  
  // UInt16 State;
  // UInt16 Errors;
  // UInt16 MinorRevLevel;

  UInt32 LastCheckTime;
  // UInt32 CheckInterval;
  UInt32 CreatorOs;
  UInt32 RevLevel;

  // UInt16 DefResUid;
  // UInt16 DefResGid;

  UInt32 FirstInode;
  UInt16 InodeSize;
  UInt16 BlockGroupNr;
  UInt32 FeatureCompat;
  UInt32 FeatureIncompat;
  UInt32 FeatureRoCompat;
  Byte Uuid[16];
  char VolName[16];
  char LastMount[64];
  // UInt32 BitmapAlgo;

  UInt32 JournalInode;
  UInt16 GdSize; // = 64 if 64-bit();
  UInt32 CTime;
  UInt16 MinExtraISize;
  // UInt16 WantExtraISize;
  // UInt32 Flags;
  // Byte LogGroupsPerFlex;
  // Byte ChecksumType;

  UInt64 WrittenKB;

  bool IsOldRev() const;

  UInt64 GetNumGroups() const;
  UInt64 GetNumGroups2() const;

  bool IsThereFileType() const;
  bool Is64Bit() const;
  bool UseGdtChecksum() const;
  bool UseMetadataChecksum() const;

  bool Parse(const Byte *p);
};

struct CGroupDescriptor
{
  UInt64 BlockBitmap;
  UInt64 InodeBitmap;
  UInt64 InodeTable;
  UInt32 NumFreeBlocks;
  UInt32 NumFreeInodes;
  UInt32 DirCount;
  
  UInt16 Flags;
  
  UInt64 ExcludeBitmap;
  UInt32 BlockBitmap_Checksum;
  UInt32 InodeBitmap_Checksum;
  UInt32 UnusedCount;
  UInt16 Checksum;

  void Parse(const Byte *p, unsigned size);
};

struct CExtentTreeHeader
{
  UInt16 NumEntries;
  UInt16 MaxEntries;
  UInt16 Depth;
  // UInt32 Generation;

  bool Parse(const Byte *p);
};

struct CExtentIndexNode
{
  UInt32 VirtBlock;
  UInt64 PhyLeaf;

  void Parse(const Byte *p);
};

struct CExtent
{
  UInt32 VirtBlock;
  UInt16 Len;
  bool IsInited;
  UInt64 PhyStart;

  UInt32 GetVirtEnd() const { return VirtBlock + Len; }
  bool IsLenOK() const { return VirtBlock + Len >= VirtBlock; }

  void Parse(const Byte *p);
};

struct CExtTime
{
  UInt32 Val;
  UInt32 Extra;
};

struct CNode
{
  Int32 ParentNode;   // in _refs[], -1 if not dir
  int ItemIndex;      // in _items[]
  int SymLinkIndex;   // in _symLinks[]
  int DirIndex;       // in _dirs[]

  UInt16 Mode;
  UInt32 Uid; // fixed 21.02
  UInt32 Gid; // fixed 21.02
  // UInt16 Checksum;
  
  UInt64 FileSize;
  CExtTime MTime;
  CExtTime ATime;
  CExtTime CTime;
  // CExtTime InodeChangeTime;
  // CExtTime DTime;

  UInt64 NumBlocks;
  UInt32 NumLinks;
  UInt32 Flags;

  UInt32 NumLinksCalced;

  Byte Block[kNodeBlockFieldSize];
  
  CNode():
      ParentNode(-1),
      ItemIndex(-1),
      SymLinkIndex(-1),
      DirIndex(0),
      NumLinksCalced(0)
        {}

  bool IsFlags_HUGE()    const;
  bool IsFlags_EXTENTS() const;

  bool IsDir()     const;
  bool IsRegular() const;
  bool IsLink()    const;

  bool Parse(const Byte *p, const CHeader &_h);
};

struct CItem
{
  unsigned Node;        // in _refs[]
  int ParentNode;       // in _refs[]
  int SymLinkItemIndex; // in _items[], if the Node contains SymLink to existing dir
  Byte Type;

  AString Name;

  CItem():
      Node(0),
      ParentNode(-1),
      SymLinkItemIndex(-1),
      Type(k_Type_UNKNOWN)
        {}
  
  void Clear()
  {
    Node = 0;
    ParentNode = -1;
    SymLinkItemIndex = -1;
    Type = k_Type_UNKNOWN;
    Name.Empty();
  }

  bool IsDir() const { return Type == k_Type_DIR; }
  // bool IsNotDir() const { return Type != k_Type_DIR && Type != k_Type_UNKNOWN; }

};

class CHandler:
  public IInArchive,
  public IArchiveGetRawProps,
  public IInArchiveGetStream,
  public CMyUnknownImp
{
  CObjectVector<CItem> _items;
  CIntVector _refs;
  CRecordVector<CNode> _nodes;
  CObjectVector<CUIntVector> _dirs; // each CUIntVector contains indexes in _items[] only for dir items;
  AStringVector _symLinks;
  AStringVector _auxItems;
  int _auxSysIndex;
  int _auxUnknownIndex;

  CMyComPtr<IInStream> _stream;
  UInt64 _phySize;
  bool _isArc;
  bool _headersError;
  bool _headersWarning;
  bool _linksError;
  
  bool _isUTF;
  
  CHeader _h;

  IArchiveOpenCallback *_openCallback;
  UInt64 _totalRead;
  UInt64 _totalReadPrev;

  CByteBuffer _tempBufs[kNumTreeLevelsMax];

  HRESULT CheckProgress2()
  {
    const UInt64 numFiles = _items.Size();
    return _openCallback->SetCompleted(&numFiles, &_totalRead);
  }

  HRESULT CheckProgress()
  {
    HRESULT res = S_OK;
    if (_openCallback)
    {
      if (_totalRead - _totalReadPrev >= ((UInt32)1 << 20))
      {
        _totalReadPrev = _totalRead;
        res = CheckProgress2();
      }
    }
    return res;
  }

  int GetParentAux(const CItem &item) const
  {
    if (item.Node < _h.FirstInode && _auxSysIndex >= 0)
      return _auxSysIndex;
    return _auxUnknownIndex;
  }

  HRESULT SeekAndRead(IInStream *inStream, UInt64 block, Byte *data, size_t size);
  HRESULT ParseDir(const Byte *data, size_t size, unsigned iNodeDir);
  int FindTargetItem_for_SymLink(unsigned dirNode, const AString &path) const;

  HRESULT FillFileBlocks2(UInt32 block, unsigned level, unsigned numBlocks, CRecordVector<UInt32> &blocks);
  HRESULT FillFileBlocks(const Byte *p, unsigned numBlocks, CRecordVector<UInt32> &blocks);
  HRESULT FillExtents(const Byte *p, size_t size, CRecordVector<CExtent> &extents, int parentDepth);

  HRESULT GetStream_Node(unsigned nodeIndex, ISequentialInStream **stream);
  HRESULT ExtractNode(unsigned nodeIndex, CByteBuffer &data);

  void ClearRefs();
  HRESULT Open2(IInStream *inStream);

  void GetPath(unsigned index, AString &s) const;
  bool GetPackSize(unsigned index, UInt64 &res) const;

public:
  static void Register();

  CHandler() {}
  ~CHandler() {}

  MY_UNKNOWN_IMP3(IInArchive, IArchiveGetRawProps, IInArchiveGetStream)
  
  INTERFACE_IInArchive(;)
  INTERFACE_IArchiveGetRawProps(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
};

class CClusterInStream2:
  public IInStream,
  public CMyUnknownImp
{
  UInt64 _virtPos;
  UInt64 _physPos;
  UInt32 _curRem;
public:
  unsigned BlockBits;
  UInt64 Size;
  CMyComPtr<IInStream> Stream;
  CRecordVector<UInt32> Vector;

  HRESULT SeekToPhys() { return Stream->Seek(_physPos, STREAM_SEEK_SET, NULL); }

  HRESULT InitAndSeek()
  {
    _curRem = 0;
    _virtPos = 0;
    _physPos = 0;
    if (Vector.Size() > 0)
    {
      _physPos = (Vector[0] << BlockBits);
      return SeekToPhys();
    }
    return S_OK;
  }

  MY_UNKNOWN_IMP2(ISequentialInStream, IInStream)

  STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);
  STDMETHOD(Seek)(Int64 offset, UInt32 seekOrigin, UInt64 *newPosition);
};

class CExtInStream:
  public IInStream,
  public CMyUnknownImp
{
  UInt64 _virtPos;
  UInt64 _phyPos;
public:
  unsigned BlockBits;
  UInt64 Size;
  CMyComPtr<IInStream> Stream;
  CRecordVector<CExtent> Extents;

  CExtInStream() {}

  HRESULT StartSeek()
  {
    _virtPos = 0;
    _phyPos = 0;
    return Stream->Seek(_phyPos, STREAM_SEEK_SET, NULL);
  }

  MY_UNKNOWN_IMP2(ISequentialInStream, IInStream)
  STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);
  STDMETHOD(Seek)(Int64 offset, UInt32 seekOrigin, UInt64 *newPosition);
};

}}

#endif // __EXT_HANDLER_H
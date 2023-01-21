// HfsHandler.h

#ifndef __HFS_HANDLER_H
#define __HFS_HANDLER_H

#include "../../Common/MyCom.h"
#include "../../Common/MyVector.h"

namespace NArchive {
namespace NHfs {

struct CExtent
{
  UInt32 Pos;
  UInt32 NumBlocks;
};

struct CIdExtents
{
  UInt32 ID;
  UInt32 StartBlock;
  CRecordVector<CExtent> Extents;
};

struct CFork
{
  UInt64 Size;
  UInt32 NumBlocks;
  // UInt32 ClumpSize;
  CRecordVector<CExtent> Extents;

  CFork();

  void Parse(const Byte *p);

  bool IsEmpty() const;

  UInt32 Calc_NumBlocks_from_Extents() const;
  bool Check_NumBlocks() const;

  bool Check_Size_with_NumBlocks(unsigned blockSizeLog) const;

  bool IsOk(unsigned blockSizeLog) const;

  bool Upgrade(const CObjectVector<CIdExtents> &items, UInt32 id);
  bool UpgradeAndTest(const CObjectVector<CIdExtents> &items, UInt32 id, unsigned blockSizeLog);
};

struct CIdIndexPair
{
  UInt32 ID;
  int Index;

  int Compare(const CIdIndexPair &a) const;
};

struct CVolHeader
{
  Byte Header[2];
  UInt16 Version;
  // UInt32 Attr;
  // UInt32 LastMountedVersion;
  // UInt32 JournalInfoBlock;

  UInt32 CTime;
  UInt32 MTime;
  // UInt32 BackupTime;
  // UInt32 CheckedTime;
  
  UInt32 NumFiles;
  UInt32 NumFolders;
  unsigned BlockSizeLog;
  UInt32 NumBlocks;
  UInt32 NumFreeBlocks;

  // UInt32 WriteCount;
  // UInt32 FinderInfo[8];
  // UInt64 VolID;

  UInt64 GetPhySize() const;
  UInt64 GetFreeSize() const;
  bool IsHfsX() const;
};

enum ERecordType
{
  RECORD_TYPE_FOLDER = 1,
  RECORD_TYPE_FILE,
  RECORD_TYPE_FOLDER_THREAD,
  RECORD_TYPE_FILE_THREAD
};

struct CItem
{
  UString Name;
  
  UInt32 ParentID;

  UInt16 Type;
  UInt16 FileMode;
  // UInt16 Flags;
  // UInt32 Valence;
  UInt32 ID;
  UInt32 CTime;
  UInt32 MTime;
  // UInt32 AttrMTime;
  UInt32 ATime;
  // UInt32 BackupDate;

  /*
  UInt32 OwnerID;
  UInt32 GroupID;
  Byte AdminFlags;
  Byte OwnerFlags;
  union
  {
    UInt32  iNodeNum;
    UInt32  LinkCount;
    UInt32  RawDevice;
  } special;

  UInt32 FileType;
  UInt32 FileCreator;
  UInt16 FinderFlags;
  UInt16 Point[2];
  */

  CFork DataFork;
  CFork ResourceFork;

  // for compressed attribute
  UInt64 UnpackSize;
  size_t DataPos;
  UInt32 PackSize;
  unsigned Method;
  bool UseAttr;
  bool UseInlineData;

  CItem();
  bool IsDir() const;
  const CFork &GetFork(bool isResource) const;
};

struct CAttr
{
  UInt32 ID;
  UInt32 Size;
  size_t Pos;
  UString Name;
};

struct CRef
{
  unsigned ItemIndex;
  int AttrIndex;
  int Parent;
  bool IsResource;

  bool IsAltStream() const;
  CRef();
};

class CDatabase
{
  HRESULT ReadFile(const CFork &fork, CByteBuffer &buf, IInStream *inStream);
  HRESULT LoadExtentFile(const CFork &fork, IInStream *inStream, CObjectVector<CIdExtents> *overflowExtentsArray);
  HRESULT LoadAttrs(const CFork &fork, IInStream *inStream, IArchiveOpenCallback *progress);
  HRESULT LoadCatalog(const CFork &fork, const CObjectVector<CIdExtents> *overflowExtentsArray, IInStream *inStream, IArchiveOpenCallback *progress);
  bool Parse_decmpgfs(const CAttr &attr, CItem &item, bool &skip);
public:
  CRecordVector<CRef> Refs;
  CObjectVector<CItem> Items;
  CObjectVector<CAttr> Attrs;

  CByteBuffer AttrBuf;

  CVolHeader Header;
  bool HeadersError;
  bool ThereAreAltStreams;
  // bool CaseSensetive;
  UString ResFileName;

  UInt64 SpecOffset;
  UInt64 PhySize;
  UInt64 PhySize2;
  UInt64 ArcFileSize;

  void Clear()
  {
    SpecOffset = 0;
    PhySize = 0;
    PhySize2 = 0;
    ArcFileSize = 0;
    HeadersError = false;
    ThereAreAltStreams = false;
    // CaseSensetive = false;
    Refs.Clear();
    Items.Clear();
    Attrs.Clear();
    AttrBuf.Free();
  }

  UInt64 Get_UnpackSize_of_Ref(const CRef &ref) const;

  void GetItemPath(unsigned index, NWindows::NCOM::CPropVariant &path) const;
  HRESULT Open2(IInStream *inStream, IArchiveOpenCallback *progress);
};

enum
{
  kHfsID_Root                  = 1,
  kHfsID_RootFolder            = 2,
  kHfsID_ExtentsFile           = 3,
  kHfsID_CatalogFile           = 4,
  kHfsID_BadBlockFile          = 5,
  kHfsID_AllocationFile        = 6,
  kHfsID_StartupFile           = 7,
  kHfsID_AttributesFile        = 8,
  kHfsID_RepairCatalogFile     = 14,
  kHfsID_BogusExtentFile       = 15,
  kHfsID_FirstUserCatalogNode  = 16
};

struct CNodeDescriptor
{
  UInt32 fLink;
  // UInt32 bLink;
  Byte Kind;
  // Byte Height;
  unsigned NumRecords;

  bool Parse(const Byte *p, unsigned nodeSizeLog);
};

struct CHeaderRec
{
  // UInt16 TreeDepth;
  // UInt32 RootNode;
  // UInt32 LeafRecords;
  UInt32 FirstLeafNode;
  // UInt32 LastLeafNode;
  unsigned NodeSizeLog;
  // UInt16 MaxKeyLength;
  UInt32 TotalNodes;
  // UInt32 FreeNodes;
  // UInt16 Reserved1;
  // UInt32 ClumpSize;
  // Byte BtreeType;
  // Byte KeyCompareType;
  // UInt32 Attributes;
  // UInt32 Reserved3[16];
  
  HRESULT Parse2(const CByteBuffer &buf);
};

class CHandler:
  public IInArchive,
  public IArchiveGetRawProps,
  public IInArchiveGetStream,
  public CMyUnknownImp,
  public CDatabase
{
  CMyComPtr<IInStream> _stream;

  HRESULT GetForkStream(const CFork &fork, ISequentialInStream **stream);

  HRESULT ExtractZlibFile(
      ISequentialOutStream *realOutStream,
      const CItem &item,
      NCompress::NZlib::CDecoder *_zlibDecoderSpec,
      CByteBuffer &buf,
      UInt64 progressStart,
      IArchiveExtractCallback *extractCallback);
public:
  static void Register();

  MY_UNKNOWN_IMP3(IInArchive, IArchiveGetRawProps, IInArchiveGetStream)
  INTERFACE_IInArchive(;)
  INTERFACE_IArchiveGetRawProps(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
};

}}

#endif // __HFS_HANDLER_H

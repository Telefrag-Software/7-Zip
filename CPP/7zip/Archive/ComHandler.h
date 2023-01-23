// ComHandler.h

#ifndef __COM_HANDLER_H
#define __COM_HANDLER_H

namespace NArchive {
namespace NCom {

namespace NFatID
{
  // static const UInt32 kFree       = 0xFFFFFFFF;
  static const UInt32 kEndOfChain = 0xFFFFFFFE;
  // static const UInt32 kFatSector  = 0xFFFFFFFD;
  // static const UInt32 kMatSector  = 0xFFFFFFFC;
  static const UInt32 kMaxValue   = 0xFFFFFFFA;
}

namespace NItemType
{
  static const Byte kEmpty = 0;
  static const Byte kStorage = 1;
  // static const Byte kStream = 2;
  // static const Byte kLockBytes = 3;
  // static const Byte kProperty = 4;
  static const Byte kRootStorage = 5;
}

static const UInt32 kNameSizeMax = 64;

enum EType
{
  k_Type_Common,
  k_Type_Msi,
  k_Type_Msp,
  k_Type_Doc,
  k_Type_Ppt,
  k_Type_Xls
};

struct CItem
{
  Byte Name[kNameSizeMax];
  // UInt16 NameSize;
  // UInt32 Flags;
  FILETIME CTime;
  FILETIME MTime;
  UInt64 Size;
  UInt32 LeftDid;
  UInt32 RightDid;
  UInt32 SonDid;
  UInt32 Sid;
  Byte Type;

  bool IsEmpty() const { return Type == NItemType::kEmpty; }
  bool IsDir() const { return Type == NItemType::kStorage || Type == NItemType::kRootStorage; }

  void Parse(const Byte *p, bool mode64bit);
};

struct CRef
{
  int Parent;
  UInt32 Did;
};

class CDatabase
{
  UInt32 NumSectorsInMiniStream;
  CObjArray<UInt32> MiniSids;

  HRESULT AddNode(int parent, UInt32 did);
public:

  CObjArray<UInt32> Fat;
  UInt32 FatSize;
  
  CObjArray<UInt32> Mat;
  UInt32 MatSize;

  CObjectVector<CItem> Items;
  CRecordVector<CRef> Refs;

  UInt32 LongStreamMinSize;
  unsigned SectorSizeBits;
  unsigned MiniSectorSizeBits;

  Int32 MainSubfile;

  UInt64 PhySize;
  EType Type;

  bool IsNotArcType() const
  {
    return
      Type != k_Type_Msi &&
      Type != k_Type_Msp;
  }

  void UpdatePhySize(UInt64 val)
  {
    if (PhySize < val)
      PhySize = val;
  }
  HRESULT ReadSector(IInStream *inStream, Byte *buf, unsigned sectorSizeBits, UInt32 sid);
  HRESULT ReadIDs(IInStream *inStream, Byte *buf, unsigned sectorSizeBits, UInt32 sid, UInt32 *dest);

  HRESULT Update_PhySize_WithItem(unsigned index);

  void Clear();
  bool IsLargeStream(UInt64 size) const { return size >= LongStreamMinSize; }
  UString GetItemPath(UInt32 index) const;

  UInt64 GetItemPackSize(UInt64 size) const
  {
    UInt64 mask = ((UInt64)1 << (IsLargeStream(size) ? SectorSizeBits : MiniSectorSizeBits)) - 1;
    return (size + mask) & ~mask;
  }

  bool GetMiniCluster(UInt32 sid, UInt64 &res) const
  {
    unsigned subBits = SectorSizeBits - MiniSectorSizeBits;
    UInt32 fid = sid >> subBits;
    if (fid >= NumSectorsInMiniStream)
      return false;
    res = (((UInt64)MiniSids[fid] + 1) << subBits) + (sid & ((1 << subBits) - 1));
    return true;
  }

  HRESULT Open(IInStream *inStream);
};

class CHandler:
  public IInArchive,
  public IInArchiveGetStream,
  public CMyUnknownImp
{
  CMyComPtr<IInStream> _stream;
  CDatabase _db;
public:
  static void Register();

  MY_UNKNOWN_IMP2(IInArchive, IInArchiveGetStream)
  INTERFACE_IInArchive(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
};

}}

#endif // __COM_HANDLER_H

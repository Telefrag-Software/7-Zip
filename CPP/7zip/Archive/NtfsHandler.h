// NtfsHandler.h

#ifndef __NTFS_HANDLER_H
#define __NTFS_HANDLER_H

#include "../../Common/MyCom.h"
#include "../../Common/MyVector.h"
#include "../../Windows/PropVariant.h"

namespace NArchive {
namespace Ntfs {

static const unsigned kNumCacheChunksLog = 1;
static const size_t kNumCacheChunks = (size_t)1 << kNumCacheChunksLog;

struct CHeader
{
  unsigned SectorSizeLog;
  unsigned ClusterSizeLog;
  // Byte MediaType;
  UInt32 NumHiddenSectors;
  UInt64 NumSectors;
  UInt64 NumClusters;
  UInt64 MftCluster;
  UInt64 SerialNumber;
  UInt16 SectorsPerTrack;
  UInt16 NumHeads;

  UInt64 GetPhySize_Clusters() const;
  UInt64 GetPhySize_Max() const;
  UInt32 ClusterSize() const;
  bool Parse(const Byte *p);
};

struct CMftRef
{
  UInt64 Val;

  UInt64 GetIndex() const;
  UInt16 GetNumber() const;
  bool IsBaseItself() const;
};

struct CFileNameAttr
{
  CMftRef ParentDirRef;

  // Probably these timestamps don't contain some useful timestamps. So we don't use them
  // UInt64 CTime;
  // UInt64 MTime;
  // UInt64 ThisRecMTime;  // xp-64: the time of previous name change (not last name change. why?)
  // UInt64 ATime;
  // UInt64 AllocatedSize;
  // UInt64 DataSize;
  // UInt16 PackedEaSize;
  UString2 Name;
  UInt32 Attrib;
  Byte NameType;

  bool IsDos() const;
  bool IsWin32() const;

  bool Parse(const Byte *p, unsigned size);
};

struct CSiAttr
{
  UInt64 CTime;
  UInt64 MTime;
  // UInt64 ThisRecMTime;
  UInt64 ATime;
  UInt32 Attrib;

  /*
  UInt32 MaxVersions;
  UInt32 Version;
  UInt32 ClassId;
  UInt32 OwnerId;
  */
  UInt32 SecurityId; // SecurityId = 0 is possible ?
  // UInt64 QuotaCharged;

  bool Parse(const Byte *p, unsigned size);
};

struct CExtent
{
  UInt64 Virt;
  UInt64 Phy;

  bool IsEmpty() const;
};

struct CVolInfo
{
  Byte MajorVer;
  Byte MinorVer;
  // UInt16 Flags;

  bool Parse(const Byte *p, unsigned size);
};

struct CAttr
{
  UInt32 Type;

  Byte NonResident;

  // Non-Resident
  Byte CompressionUnit;

  // UInt32 Len;
  UString2 Name;
  // UInt16 Flags;
  // UInt16 Instance;
  CByteBuffer Data;

  // Non-Resident
  UInt64 LowVcn;
  UInt64 HighVcn;
  UInt64 AllocatedSize;
  UInt64 Size;
  UInt64 PackSize;
  UInt64 InitializedSize;

  // Resident
  // UInt16 ResidentFlags;

  bool IsCompressionUnitSupported() const;

  UInt32 Parse(const Byte *p, unsigned size);
  bool ParseFileName(CFileNameAttr &a) const;
  bool ParseSi(CSiAttr &a) const;
  bool ParseVolInfo(CVolInfo &a) const;
  bool ParseExtents(CRecordVector<CExtent> &extents, UInt64 numClustersMax, unsigned compressionUnit) const;
  UInt64 GetSize() const;
  UInt64 GetPackSize() const;
};

class CInStream:
  public IInStream,
  public CMyUnknownImp
{
  UInt64 _virtPos;
  UInt64 _physPos;
  UInt64 _curRem;
  bool _sparseMode;
  

  unsigned _chunkSizeLog;
  UInt64 _tags[kNumCacheChunks];
  CByteBuffer _inBuf;
  CByteBuffer _outBuf;
public:
  UInt64 Size;
  UInt64 InitializedSize;
  unsigned BlockSizeLog;
  unsigned CompressionUnit;
  CRecordVector<CExtent> Extents;
  bool InUse;
  CMyComPtr<IInStream> Stream;

  HRESULT SeekToPhys();

  UInt32 GetCuSize() const;
  HRESULT InitAndSeek(unsigned compressionUnit);

  MY_UNKNOWN_IMP1(IInStream)

  STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);
  STDMETHOD(Seek)(Int64 offset, UInt32 seekOrigin, UInt64 *newPosition);
};

struct CDataRef
{
  unsigned Start;
  unsigned Num;
};

struct CMftRec
{
  UInt32 Magic;
  // UInt64 Lsn;
  UInt16 SeqNumber;  // Number of times this mft record has been reused
  UInt16 Flags;
  // UInt16 LinkCount;
  // UInt16 NextAttrInstance;
  CMftRef BaseMftRef;
  // UInt32 ThisRecNumber;
  
  UInt32 MyNumNameLinks;
  int MyItemIndex; // index in Items[] of main item  for that record, or -1 if there is no item for that record

  CObjectVector<CAttr> DataAttrs;
  CObjectVector<CFileNameAttr> FileNames;
  CRecordVector<CDataRef> DataRefs;
  // CAttr SecurityAttr;

  CSiAttr SiAttr;
  
  CByteBuffer ReparseData;

  int FindWin32Name_for_DosName(unsigned dosNameIndex) const;

  int FindDosName(unsigned nameIndex) const;

  // bool IsAltStream(int dataIndex) const;

  void MoveAttrsFrom(CMftRec &src);

  UInt64 GetPackSize() const;

  bool Parse(Byte *p, unsigned sectorSizeLog, UInt32 numSectors, UInt32 recNumber, CObjectVector<CAttr> *attrs);

  bool IsEmpty() const;
  bool IsFILE() const;
  bool IsBAAD() const;

  bool InUse() const;
  bool IsDir() const;

  void ParseDataNames();
  HRESULT GetStream(IInStream *mainStream, int dataIndex,
      unsigned clusterSizeLog, UInt64 numPhysClusters, IInStream **stream) const;
  unsigned GetNumExtents(int dataIndex, unsigned clusterSizeLog, UInt64 numPhysClusters) const;

  UInt64 GetSize(unsigned dataIndex) const;

  CMftRec();
};

struct CItem
{
  unsigned RecIndex;  // index in Recs array
  unsigned NameIndex; // index in CMftRec::FileNames

  int DataIndex;      /* index in CMftRec::DataRefs
                         -1: file without unnamed data stream
                         -2: for directories */
                         
  int ParentFolder;   /* index in Items array
                         -1: for root items
                         -2: [LOST] folder
                         -3: [UNKNOWN] folder (deleted lost) */
  int ParentHost;     /* index in Items array, if it's AltStream
                         -1: if it's not AltStream */

  CItem();

  bool IsAltStream() const;
  bool IsDir() const;
        // check it !!!
        // probably NTFS for empty file still creates empty DATA_ATTRIBUTE
        // But it doesn't do it for $Secure:$SDS
};

struct CDatabase
{
  CRecordVector<CItem> Items;
  CObjectVector<CMftRec> Recs;
  CMyComPtr<IInStream> InStream;
  CHeader Header;
  unsigned RecSizeLog;
  UInt64 PhySize;

  IArchiveOpenCallback *OpenCallback;

  CByteBuffer ByteBuf;

  CObjectVector<CAttr> VolAttrs;

  CByteBuffer SecurData;
  CRecordVector<size_t> SecurOffsets;

  bool _showSystemFiles;
  bool _showDeletedFiles;
  CObjectVector<UString2> VirtFolderNames;
  UString EmptyString;

  int _systemFolderIndex;
  int _lostFolderIndex_Normal;
  int _lostFolderIndex_Deleted;

  // bool _headerWarning;

  bool ThereAreAltStreams;

  void InitProps();

  CDatabase();
  ~CDatabase();

  void Clear();
  void ClearAndClose();

  void GetItemPath(unsigned index, NWindows::NCOM::CPropVariant &path) const;
  HRESULT Open();

  HRESULT SeekToCluster(UInt64 cluster);

  int FindDirItemForMtfRec(UInt64 recIndex) const;

  bool FindSecurityDescritor(UInt32 id, UInt64 &offset, UInt32 &size) const;

  HRESULT ParseSecuritySDS_2();
  void ParseSecuritySDS();
};

class CHandler:
  public IInArchive,
  public IArchiveGetRawProps,
  public IInArchiveGetStream,
  public ISetProperties,
  public CMyUnknownImp,
  CDatabase
{
public:
  static void Register();

  MY_UNKNOWN_IMP4(
      IInArchive,
      IArchiveGetRawProps,
      IInArchiveGetStream,
      ISetProperties)
  INTERFACE_IInArchive(;)
  INTERFACE_IArchiveGetRawProps(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
  STDMETHOD(SetProperties)(const wchar_t * const *names, const PROPVARIANT *values, UInt32 numProps);
};

}}

#endif // __NTFS_HANDLER_H

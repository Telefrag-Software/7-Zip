// FatHandler.cpp

#ifndef __FAT_HANDLER_H
#define __FAT_HANDLER_H

#include "../../Common/MyCom.h"
#include "../../Common/MyVector.h"

namespace NArchive {
namespace NFat {

struct CHeader
{
  UInt32 NumSectors;
  UInt16 NumReservedSectors;
  Byte NumFats;
  UInt32 NumFatSectors;
  UInt32 RootDirSector;
  UInt32 NumRootDirSectors;
  UInt32 DataSector;

  UInt32 FatSize;
  UInt32 BadCluster;

  Byte NumFatBits;
  Byte SectorSizeLog;
  Byte SectorsPerClusterLog;
  Byte ClusterSizeLog;
  
  UInt16 SectorsPerTrack;
  UInt16 NumHeads;
  UInt32 NumHiddenSectors;

  bool VolFieldsDefined;

  UInt32 VolId;
  // Byte VolName[11];
  // Byte FileSys[8];

  // Byte OemName[5];
  Byte MediaType;

  // 32-bit FAT
  UInt16 Flags;
  UInt16 FsInfoSector;
  UInt32 RootCluster;

  bool IsFat32() const;
  UInt64 GetPhySize() const;
  UInt32 SectorSize() const;
  UInt32 ClusterSize() const;
  UInt32 ClusterToSector(UInt32 c) const;
  UInt32 IsEoc(UInt32 c) const;
  UInt32 IsEocAndUnused(UInt32 c) const;
  UInt32 IsValidCluster(UInt32 c) const;
  UInt32 SizeToSectors(UInt32 size) const;
  UInt32 CalcFatSizeInSectors() const;

  UInt32 GetFatSector() const;

  UInt64 GetFilePackSize(UInt32 unpackSize) const;

  UInt32 GetNumClusters(UInt32 size) const;

  bool Parse(const Byte *p);
};

struct CItem
{
  UString UName;
  char DosName[11];
  Byte CTime2;
  UInt32 CTime;
  UInt32 MTime;
  UInt16 ADate;
  Byte Attrib;
  Byte Flags;
  UInt32 Size;
  UInt32 Cluster;
  Int32 Parent;

  // NT uses Flags to store Low Case status
  bool NameIsLow() const;
  bool ExtIsLow() const;
  bool IsDir() const;
  UString GetShortName() const;
  UString GetName() const;
  UString GetVolName() const;
};

struct CDatabase
{
  CHeader Header;
  CObjectVector<CItem> Items;
  UInt32 *Fat;
  CMyComPtr<IInStream> InStream;
  IArchiveOpenCallback *OpenCallback;

  UInt32 NumFreeClusters;
  bool VolItemDefined;
  CItem VolItem;
  UInt32 NumDirClusters;
  CByteBuffer ByteBuf;
  UInt64 NumCurUsedBytes;

  UInt64 PhySize;

  CDatabase();
  ~CDatabase();

  void Clear();
  void ClearAndClose();
  HRESULT OpenProgressFat(bool changeTotal = true);
  HRESULT OpenProgress();

  UString GetItemPath(Int32 index) const;
  HRESULT Open();
  HRESULT ReadDir(Int32 parent, UInt32 cluster, unsigned level);

  UInt64 GetHeadersSize() const;
  HRESULT SeekToSector(UInt32 sector);
  HRESULT SeekToCluster(UInt32 cluster);
};

class CHandler:
  public IInArchive,
  public IInArchiveGetStream,
  public CMyUnknownImp,
  CDatabase
{
public:
  static void Register();

  MY_UNKNOWN_IMP2(IInArchive, IInArchiveGetStream)
  INTERFACE_IInArchive(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
};

}}

#endif // __FAT_HANDLER_H

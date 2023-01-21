// DmgHandler.h

#include "../../Common/MyCom.h"
#include "../../Common/MyString.h"
#include "../../Common/MyVector.h"

#ifndef __DMG_HANDLER_H
#define __DMG_HANDLER_H

namespace NArchive {
namespace NDmg {

static const UInt32  METHOD_ZERO_0  = 0;
static const UInt32  METHOD_COPY    = 1;
static const UInt32  METHOD_ZERO_2  = 2; // without file CRC calculation
static const UInt32  METHOD_ADC     = 0x80000004;
static const UInt32  METHOD_ZLIB    = 0x80000005;
static const UInt32  METHOD_BZIP2   = 0x80000006;
static const UInt32  METHOD_LZFSE   = 0x80000007;
static const UInt32  METHOD_COMMENT = 0x7FFFFFFE; // is used to comment "+beg" and "+end" in extra field.
static const UInt32  METHOD_END     = 0xFFFFFFFF;

static const UInt32 kCheckSumType_CRC = 2;

static const size_t kChecksumSize_Max = 0x80;

struct CBlock
{
  UInt32 Type;
  UInt64 UnpPos;
  UInt64 UnpSize;
  UInt64 PackPos;
  UInt64 PackSize;

  UInt64 GetNextPackOffset() const;
  UInt64 GetNextUnpPos() const;

  bool IsZeroMethod() const;
  bool ThereAreDataInBlock() const;
};

struct CChecksum
{
  UInt32 Type;
  UInt32 NumBits;
  Byte Data[kChecksumSize_Max];

  bool IsCrc32() const;
  UInt32 GetCrc32() const;
  void Parse(const Byte *p);
};

struct CFile
{
  UInt64 Size;
  UInt64 PackSize;
  UInt64 StartPos;
  AString Name;
  CRecordVector<CBlock> Blocks;
  CChecksum Checksum;
  bool FullFileChecksum;

  HRESULT Parse(const Byte *p, UInt32 size);
};

struct CForkPair
{
  UInt64 Offset;
  UInt64 Len;
  
  void Parse(const Byte *p);

  bool UpdateTop(UInt64 limit, UInt64 &top);
};

class CHandler:
  public IInArchive,
  public IInArchiveGetStream,
  public CMyUnknownImp
{
  CMyComPtr<IInStream> _inStream;
  CObjectVector<CFile> _files;
  bool _masterCrcError;
  bool _headersError;

  UInt32 _dataStartOffset;
  UInt64 _startPos;
  UInt64 _phySize;

  AString _name;
  
  #ifdef DMG_SHOW_RAW
  CObjectVector<CExtraFile> _extras;
  #endif

  HRESULT ReadData(IInStream *stream, const CForkPair &pair, CByteBuffer &buf);
  bool ParseBlob(const CByteBuffer &data);
  HRESULT Open2(IInStream *stream);
  HRESULT Extract(IInStream *stream);
public:
  static void Register();

  MY_UNKNOWN_IMP2(IInArchive, IInArchiveGetStream)
  INTERFACE_IInArchive(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
};

struct CAppleName
{
  bool IsFs;
  const char *Ext;
  const char *AppleName;
};

static const CAppleName k_Names[] =
{
  { true,  "hfs",  "Apple_HFS" },
  { true,  "hfsx", "Apple_HFSX" },
  { true,  "ufs",  "Apple_UFS" },
  { true,  "apfs", "Apple_APFS" },

  // efi_sys partition is FAT32, but it's not main file. So we use (IsFs = false)
  { false,  "efi_sys", "C12A7328-F81F-11D2-BA4B-00A0C93EC93B" },

  { false, "free", "Apple_Free" },
  { false, "ddm",  "DDM" },
  { false, NULL,   "Apple_partition_map" },
  { false, NULL,   " GPT " },
  { false, NULL,   "MBR" },
  { false, NULL,   "Driver" },
  { false, NULL,   "Patches" }
};

}}

#endif // __DMG_HANDLER_H

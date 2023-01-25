// PeHandler.h

#ifndef __PE_HANDLER_H
#define __PE_HANDLER_H

#include "../../Common/MyCom.h"
#include "../../Common/MyString.h"
#include "../../Common/MyVector.h"
#include "../../Windows/PropVariant.h"

namespace NArchive {

namespace NPe {

static const UInt32 kNumDirItemsMax = 16;

static const UInt32 kBmpHeaderSize = 14;
static const UInt32 kIconHeaderSize = 22;

static const unsigned kNameSize = 8;

struct CVersion
{
  UInt16 Major;
  UInt16 Minor;

  void Parse(const Byte *p);
  void ToProp(NWindows::NCOM::CPropVariant &prop);
};

struct CHeader
{
  UInt16 Machine;
  UInt16 NumSections;
  UInt32 Time;
  UInt32 PointerToSymbolTable;
  UInt32 NumSymbols;
  UInt16 OptHeaderSize;
  UInt16 Flags;

  void ParseBase(const Byte *p);
  bool ParseCoff(const Byte *p);
  bool ParsePe(const Byte *p);
  bool IsDll() const;
};

struct CDirLink
{
  UInt32 Va;
  UInt32 Size;

  CDirLink();
  void Parse(const Byte *p);
};

struct CDebugEntry
{
  UInt32 Flags;
  UInt32 Time;
  CVersion Ver;
  UInt32 Type;
  UInt32 Size;
  UInt32 Va;
  UInt32 Pa;

  void Parse(const Byte *p);
};

struct COptHeader
{
  UInt16 Magic;
  Byte LinkerVerMajor;
  Byte LinkerVerMinor;

  UInt32 CodeSize;
  UInt32 InitDataSize;
  UInt32 UninitDataSize;
  
  // UInt32 AddressOfEntryPoint;
  // UInt32 BaseOfCode;
  // UInt32 BaseOfData32;
  UInt64 ImageBase;

  UInt32 SectAlign;
  UInt32 FileAlign;

  CVersion OsVer;
  CVersion ImageVer;
  CVersion SubsysVer;

  UInt32 ImageSize;
  UInt32 HeadersSize;
  UInt32 CheckSum;
  UInt16 SubSystem;
  UInt16 DllCharacts;

  UInt64 StackReserve;
  UInt64 StackCommit;
  UInt64 HeapReserve;
  UInt64 HeapCommit;

  UInt32 NumDirItems;
  CDirLink DirItems[kNumDirItemsMax];

  bool Is64Bit() const;
  bool Parse(const Byte *p, UInt32 size);
  int GetNumFileAlignBits() const;
  bool IsSybSystem_EFI() const;
};

struct CSection
{
  AString Name;

  UInt32 VSize;
  UInt32 Va;
  UInt32 PSize;
  UInt32 Pa;
  UInt32 Flags;
  UInt32 Time;
  // UInt16 NumRelocs;
  bool IsRealSect;
  bool IsDebug;
  bool IsAdditionalSection;

  CSection();

  UInt32 GetSizeExtract() const;
  UInt32 GetSizeMin() const;

  void UpdateTotalSize(UInt32 &totalSize) const;
  void Parse(const Byte *p);
  int Compare(const CSection &s) const;
};

struct CTableItem
{
  UInt32 Offset;
  UInt32 ID;
};

struct CResItem
{
  UInt32 Type;
  UInt32 ID;
  UInt32 Lang;

  UInt32 Size;
  UInt32 Offset;

  UInt32 HeaderSize;
  Byte Header[kIconHeaderSize]; // it must be enough for max size header.
  bool Enabled;

  bool IsNameEqual(const CResItem &item) const;
  UInt32 GetSize() const;
  bool IsBmp() const;
  bool IsIcon() const;
  bool IsString() const;
  bool IsRcData() const;
  bool IsVersion() const;
  bool IsRcDataOrUnknown() const;
};

struct CTextFile
{
  CByteDynamicBuffer Buf;

  size_t FinalSize() const;

  void AddChar(Byte c);
  void AddWChar(UInt16 c);
  void AddWChar_Smart(UInt16 c);
  void NewLine();
  void AddString(const char *s);
  void AddSpaces(int num);
  void AddBytes(const Byte *p, size_t size);
  void OpenBlock(int num);
  void CloseBlock(int num);
};

struct CStringItem: public CTextFile
{
  UInt32 Lang;
};

struct CByteBuffer_WithLang: public CByteBuffer
{
  UInt32 Lang;
};

struct CMixItem
{
  int SectionIndex;
  int ResourceIndex;
  int StringIndex;
  int VersionIndex;

  CMixItem();
  bool IsSectionItem() const;
};

struct CUsedBitmap
{
  CByteBuffer Buf;
public:
  void Alloc(size_t size);
  void Free();
  bool SetRange(size_t from, unsigned size);
};

struct CStringKeyValue
{
  UString Key;
  UString Value;
};

class CHandler:
  public IInArchive,
  public IInArchiveGetStream,
  public IArchiveAllowTail,
  public CMyUnknownImp
{
  CMyComPtr<IInStream> _stream;
  CObjectVector<CSection> _sections;
  CHeader _header;
  UInt32 _totalSize;
  Int32 _mainSubfile;

  CRecordVector<CMixItem> _mixItems;
  CRecordVector<CResItem> _items;
  CObjectVector<CStringItem> _strings;
  CObjectVector<CByteBuffer_WithLang> _versionFiles;
  UString _versionFullString;
  UString _versionShortString;
  UString _originalFilename;
  CObjectVector<CStringKeyValue> _versionKeys;

  CByteBuffer _buf;
  bool _oneLang;
  UString _resourcesPrefix;
  CUsedBitmap _usedRes;
  // bool _parseResources;
  bool _checksumError;

  bool IsOpt() const;

  COptHeader _optHeader;

  bool _coffMode;
  bool _allowTail;

  HRESULT LoadDebugSections(IInStream *stream, bool &thereIsSection);
  HRESULT Open2(IInStream *stream, IArchiveOpenCallback *callback);

  void AddResNameToString(UString &s, UInt32 id) const;
  void AddLangPrefix(UString &s, UInt32 lang) const;
  HRESULT ReadString(UInt32 offset, UString &dest) const;
  HRESULT ReadTable(UInt32 offset, CRecordVector<CTableItem> &items);
  bool ParseStringRes(UInt32 id, UInt32 lang, const Byte *src, UInt32 size);
  HRESULT OpenResources(unsigned sectIndex, IInStream *stream, IArchiveOpenCallback *callback);
  void CloseResources();

  bool CheckItem(const CSection &sect, const CResItem &item, size_t offset) const;

public:
  static void Register();

  CHandler(bool coffMode = false);

  MY_UNKNOWN_IMP3(IInArchive, IInArchiveGetStream, IArchiveAllowTail)
  INTERFACE_IInArchive(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
  STDMETHOD(AllowTail)(Int32 allowTail);
};

// BITMAPINFOHEADER
struct CBitmapInfoHeader
{
  // UInt32 HeaderSize;
  UInt32 XSize;
  Int32 YSize;
  UInt16 Planes;
  UInt16 BitCount;
  UInt32 Compression;
  UInt32 SizeImage;

  bool Parse(const Byte *p, size_t size);
};

struct CMy_VS_FIXEDFILEINFO
{
  // UInt32 Signature;
  // UInt32 StrucVersion;
  UInt32 VersionMS;
  UInt32 VersionLS;
  UInt32 ProductVersionMS;
  UInt32 ProductVersionLS;
  UInt32 FlagsMask;
  UInt32 Flags;
  UInt32 OS;
  UInt32 Type;
  UInt32 Subtype;
  UInt32 DateMS;
  UInt32 DateLS;

  bool Parse(const Byte *p);
  void PrintToTextFile(CTextFile &f, CObjectVector<CStringKeyValue> &keys);
};

struct CVersionBlock
{
  UInt32 TotalLen;
  UInt32 ValueLen;
  bool IsTextValue;
  unsigned StrSize;

  bool Parse(const Byte *p, UInt32 size);
};

}

namespace NTe {

// Terse Executable (TE) image

struct CDataDir
{
  UInt32 Va;
  UInt32 Size;

  void Parse(const Byte *p);
};

struct CHeader
{
  UInt16 Machine;
  Byte NumSections;
  Byte SubSystem;
  UInt16 StrippedSize;
  /*
  UInt32 AddressOfEntryPoint;
  UInt32 BaseOfCode;
  UInt64 ImageBase;
  */
  CDataDir DataDir[2]; // base relocation and debug directory

  bool ConvertPa(UInt32 &pa) const;
  bool Parse(const Byte *p);
};

struct CSection
{
  Byte Name[NPe::kNameSize];

  UInt32 VSize;
  UInt32 Va;
  UInt32 PSize;
  UInt32 Pa;
  UInt32 Flags;
  // UInt16 NumRelocs;

  void Parse(const Byte *p);
  bool Check() const;
  void UpdateTotalSize(UInt32 &totalSize);
};

class CHandler:
  public IInArchive,
  public IInArchiveGetStream,
  public IArchiveAllowTail,
  public CMyUnknownImp
{
  CRecordVector<CSection> _items;
  CMyComPtr<IInStream> _stream;
  UInt32 _totalSize;
  bool _allowTail;
  CHeader _h;

  HRESULT Open2(IInStream *stream);
public:
  static void Register();

  MY_UNKNOWN_IMP3(IInArchive, IInArchiveGetStream, IArchiveAllowTail)
  INTERFACE_IInArchive(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
  STDMETHOD(AllowTail)(Int32 allowTail);
  CHandler();
};

}

}

#endif // __PE_HANDLER_H

// ElfHandler.cpp

#ifndef __ELF_HANDLER_H
#define __ELF_HANDLER_H

#include "../../Common/MyCom.h"
#include "../../Common/MyVector.h"
#include "../../Windows/PropVariant.h"

namespace NArchive {
namespace NElf {

struct CHeader
{
  bool Mode64;
  bool Be;
  Byte Os;
  Byte AbiVer;

  UInt16 Type;
  UInt16 Machine;
  // UInt32 Version;

  // UInt64 EntryVa;
  UInt64 ProgOffset;
  UInt64 SectOffset;
  UInt32 Flags;
  UInt16 HeaderSize;
  UInt16 SegmentEntrySize;
  UInt16 NumSegments;
  UInt16 SectionEntrySize;
  UInt16 NumSections;
  UInt16 NamesSectIndex;

  bool Parse(const Byte *buf);

  UInt64 GetHeadersSize() const { return (UInt64)HeaderSize +
      (UInt32)NumSegments * SegmentEntrySize +
      (UInt32)NumSections * SectionEntrySize; }
};

struct CSegment
{
  UInt32 Type;
  UInt32 Flags;
  UInt64 Offset;
  UInt64 Va;
  // UInt64 Pa;
  UInt64 Size;
  UInt64 VSize;
  UInt64 Align;

  void UpdateTotalSize(UInt64 &totalSize)
  {
    UInt64 t = Offset + Size;
    if (totalSize < t)
      totalSize = t;
  }
  void Parse(const Byte *p, bool mode64, bool be);
};

struct CSection
{
  UInt32 Name;
  UInt32 Type;
  UInt64 Flags;
  UInt64 Va;
  UInt64 Offset;
  UInt64 VSize;
  UInt32 Link;
  UInt32 Info;
  UInt64 AddrAlign;
  UInt64 EntSize;

  UInt64 GetSize() const;

  void UpdateTotalSize(UInt64 &totalSize)
  {
    UInt64 t = Offset + GetSize();
    if (totalSize < t)
      totalSize = t;
  }
  bool Parse(const Byte *p, bool mode64, bool be);
};

class CHandler:
  public IInArchive,
  public IArchiveAllowTail,
  public CMyUnknownImp
{
  CRecordVector<CSegment> _segments;
  CRecordVector<CSection> _sections;
  CByteBuffer _namesData;
  CMyComPtr<IInStream> _inStream;
  UInt64 _totalSize;
  CHeader _header;
  bool _headersError;
  bool _allowTail;

  void GetSectionName(UInt32 index, NWindows::NCOM::CPropVariant &prop, bool showNULL) const;
  HRESULT Open2(IInStream *stream);
public:
  static void Register();

  MY_UNKNOWN_IMP2(IInArchive, IArchiveAllowTail)
  INTERFACE_IInArchive(;)
  STDMETHOD(AllowTail)(Int32 allowTail);

  CHandler(): _allowTail(false) {}
};

}}

#endif // __ELF_HANDLER_H

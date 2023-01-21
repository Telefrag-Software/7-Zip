// MachoHandler.h

#ifndef __MACHO_HANDLER_H
#define __MACHO_HANDLER_H

#include "../../Common/MyCom.h"
#include "../../Common/MyVector.h"

namespace NArchive {
namespace NMacho {

static const unsigned kNameSize = 16;

enum EFileType
{
  kType_OBJECT = 1,
  kType_EXECUTE,
  kType_FVMLIB,
  kType_CORE,
  kType_PRELOAD,
  kType_DYLIB,
  kType_DYLINKER,
  kType_BUNDLE,
  kType_DYLIB_STUB,
  kType_DSYM
};

struct CSegment
{
  char Name[kNameSize];
};

struct CSection
{
  char Name[kNameSize];
  char SegName[kNameSize];
  UInt64 Va;
  UInt64 Pa;
  UInt64 VSize;
  UInt64 PSize;

  UInt32 Flags;
  int SegmentIndex;

  bool IsDummy;

  CSection();
  // UInt64 GetPackSize() const { return Flags == SECT_ATTR_ZEROFILL ? 0 : Size; }
  UInt64 GetPackSize() const;
};

class CHandler:
  public IInArchive,
  public IArchiveAllowTail,
  public CMyUnknownImp
{
  CMyComPtr<IInStream> _inStream;
  CObjectVector<CSegment> _segments;
  CObjectVector<CSection> _sections;
  bool _allowTail;
  bool _mode64;
  bool _be;
  UInt32 _cpuType;
  UInt32 _cpuSubType;
  UInt32 _type;
  UInt32 _flags;
  UInt32 _headersSize;
  UInt64 _totalSize;

  HRESULT Open2(ISequentialInStream *stream);
public:
  static void Register();

  MY_UNKNOWN_IMP2(IInArchive, IArchiveAllowTail)
  INTERFACE_IInArchive(;)
  STDMETHOD(AllowTail)(Int32 allowTail);
  CHandler();
};

}}

#endif // __MACHO_HANDLER_H

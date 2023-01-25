// VhdHandler.h

#ifndef __VHD_HANDLER_H
#define __VHD_HANDLER_H

#include "../../Common/MyString.h"
#include "../../Common/MyVector.h"

namespace NArchive {
namespace NVhd {

struct CFooter
{
  // UInt32 Features;
  // UInt32 FormatVersion;
  UInt64 DataOffset;
  UInt32 CTime;
  UInt32 CreatorApp;
  UInt32 CreatorVersion;
  UInt32 CreatorHostOS;
  // UInt64 OriginalSize;
  UInt64 CurrentSize;
  UInt32 DiskGeometry;
  UInt32 Type;
  Byte Id[16];
  Byte SavedState;

  bool IsFixed() const;
  bool ThereIsDynamic() const;
  // bool IsSupported() const;
  UInt32 NumCyls() const;
  UInt32 NumHeads() const;
  UInt32 NumSectorsPerTrack() const;
  void AddTypeString(AString &s) const;
  bool Parse(const Byte *p);
};

struct CParentLocatorEntry
{
  UInt32 Code;
  UInt32 DataSpace;
  UInt32 DataLen;
  UInt64 DataOffset;

  bool Parse(const Byte *p);
};

struct CDynHeader
{
  // UInt64 DataOffset;
  UInt64 TableOffset;
  // UInt32 HeaderVersion;
  UInt32 NumBlocks;
  unsigned BlockSizeLog;
  UInt32 ParentTime;
  Byte ParentId[16];
  bool RelativeNameWasUsed;
  UString ParentName;
  UString RelativeParentNameFromLocator;
  CParentLocatorEntry ParentLocators[8];

  bool Parse(const Byte *p);
  UInt32 NumBitMapSectors() const;
  void Clear();
};

class CHandler: public CHandlerImg
{
  UInt64 _posInArcLimit;
  UInt64 _startOffset;
  UInt64 _phySize;

  CFooter Footer;
  CDynHeader Dyn;
  CRecordVector<UInt32> Bat;
  CByteBuffer BitMap;
  UInt32 BitMapTag;
  UInt32 NumUsedBlocks;
  CMyComPtr<IInStream> ParentStream;
  CHandler *Parent;
  UInt64 NumLevels;
  UString _errorMessage;
  // bool _unexpectedEnd;

  void AddErrorMessage(const char *message, const wchar_t *name = NULL);
  void UpdatePhySize(UInt64 value);
  void Reset_PosInArc();
  HRESULT Seek2(UInt64 offset);
  HRESULT InitAndSeek();
  HRESULT ReadPhy(UInt64 offset, void *data, UInt32 size);

  bool NeedParent() const;
  UInt64 GetPackSize() const;

  UString GetParentSequence() const;

  bool AreParentsOK() const;

  HRESULT Open3();
  HRESULT Open2(IInStream *stream, CHandler *child, IArchiveOpenCallback *openArchiveCallback, unsigned level);
  HRESULT Open2(IInStream *stream, IArchiveOpenCallback *openArchiveCallback);
  void CloseAtError();

public:
  static void Register();

  INTERFACE_IInArchive_Img(;)

  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
  STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);
};


}}

#endif // __VHD_HANDLER_H

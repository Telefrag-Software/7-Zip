// UefiHandler.h

#ifndef __UEFI_HANDLER_H
#define __UEFI_HANDLER_H

#include "../../Common/MyString.h"
#include "../../Common/MyVector.h"

#ifdef SHOW_DEBUG_INFO
#define PRF(x) x
#else
#define PRF(x)
#endif

namespace NArchive {
namespace NUefi {

static const unsigned kGuidSize = 16;

struct CSigExtPair
{
  const char *ext;
  unsigned sigSize;
  Byte sig[16];
};

class CFfsFileHeader
{
PRF(public:)
  Byte CheckHeader;
  Byte CheckFile;
  Byte Attrib;
  Byte State;

  UInt16 GetTailReference() const;
  UInt32 GetTailSize() const;
  bool IsThereFileChecksum() const;
  bool IsThereTail() const;
public:
  Byte GuidName[kGuidSize];
  Byte Type;
  UInt32 Size;

  bool Parse(const Byte *p);

  UInt32 GetDataSize() const;
  UInt32 GetDataSize2(UInt32 rem) const;

  bool Check(const Byte *p, UInt32 size);
  AString GetCharacts() const;
};

struct CCapsuleHeader
{
  UInt32 HeaderSize;
  UInt32 Flags;
  UInt32 CapsuleImageSize;
  UInt32 SequenceNumber;
  // Guid InstanceId;
  UInt32 OffsetToSplitInformation;
  UInt32 OffsetToCapsuleBody;
  UInt32 OffsetToOemDefinedHeader;
  UInt32 OffsetToAuthorInformation;
  UInt32 OffsetToRevisionInformation;
  UInt32 OffsetToShortDescription;
  UInt32 OffsetToLongDescription;
  UInt32 OffsetToApplicableDevices;

  void Clear();
  bool Parse(const Byte *p);
};

struct CItem
{
  AString Name;
  AString Characts;
  int Parent;
  int Method;
  int NameIndex;
  int NumChilds;
  bool IsDir;
  bool Skip;
  bool ThereAreSubDirs;
  bool ThereIsUniqueName;
  bool KeepName;

  int BufIndex;
  UInt32 Offset;
  UInt32 Size;

  CItem();
  void SetGuid(const Byte *guidName, bool full = false);
  AString GetName(int numChildsInParent) const;
};

struct CItem2
{
  AString Name;
  AString Characts;
  int MainIndex;
  int Parent;

  CItem2();
};

class CHandler:
  public IInArchive,
  public IInArchiveGetStream,
  public CMyUnknownImp
{
  CObjectVector<CItem> _items;
  CObjectVector<CItem2> _items2;
  CObjectVector<CByteBuffer> _bufs;
  UString _comment;
  UInt32 _methodsMask;
  bool _capsuleMode;
  bool _headersError;

  size_t _totalBufsSize;
  CCapsuleHeader _h;
  UInt64 _phySize;

  void AddCommentString(const char *name, UInt32 pos);
  int AddItem(const CItem &item);
  int AddFileItemWithIndex(CItem &item);
  int AddDirItem(CItem &item);
  unsigned AddBuf(size_t size);

  HRESULT DecodeLzma(const Byte *data, size_t inputSize);

  HRESULT ParseSections(int bufIndex, UInt32 pos, UInt32 size, int parent, int method, unsigned level, bool &error);
  
  HRESULT ParseIntelMe(int bufIndex, UInt32 posBase,
      UInt32 exactSize, UInt32 limitSize,
      int parent, int method, unsigned level);

  HRESULT ParseVolume(int bufIndex, UInt32 posBase,
      UInt32 exactSize, UInt32 limitSize,
      int parent, int method, unsigned level);

  HRESULT OpenCapsule(IInStream *stream);
  HRESULT OpenFv(IInStream *stream, const UInt64 *maxCheckStartPosition, IArchiveOpenCallback *callback);
  HRESULT Open2(IInStream *stream, const UInt64 *maxCheckStartPosition, IArchiveOpenCallback *callback);
public:
  static void Register();

  CHandler(bool capsuleMode);
  MY_UNKNOWN_IMP2(IInArchive, IInArchiveGetStream)
  INTERFACE_IInArchive(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
};

struct CVolFfsHeader
{
  UInt32 HeaderLen;
  UInt64 VolSize;

  bool Parse(const Byte *p);
};

}}

#endif // __UEFI_HANDLER_H

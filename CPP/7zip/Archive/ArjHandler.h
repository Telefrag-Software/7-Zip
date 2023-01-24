// ArjHandler.h

#ifndef __ARJ_HANDLER_H
#define __ARJ_HANDLER_H

#include "../../Common/MyBuffer.h"
#include "../../Common/MyCom.h"
#include "../../Common/MyString.h"
#include "../../Common/MyVector.h"
#include "../../Windows/PropVariant.h"
#include "../Common/InBuffer.h"
#include "../Compress/BitmDecoder.h"
#include "../Compress/LzOutWindow.h"

namespace NCompress {
namespace NArj {
namespace NDecoder {

class CCoder:
  public ICompressCoder,
  public CMyUnknownImp
{
  CLzOutWindow _outWindow;
  NBitm::CDecoder<CInBuffer> _inBitStream;

  class CCoderReleaser
  {
    CCoder *_coder;
  public:
    CCoderReleaser(CCoder *coder);
    void Disable();
    ~CCoderReleaser();
  };
  friend class CCoderReleaser;

  HRESULT CodeReal(UInt64 outSize, ICompressProgressInfo *progress);
public:
  MY_UNKNOWN_IMP

  bool FinishMode;
  CCoder();

  STDMETHOD(Code)(ISequentialInStream *inStream, ISequentialOutStream *outStream,
      const UInt64 *inSize, const UInt64 *outSize, ICompressProgressInfo *progress);
  UInt64 GetInputProcessedSize() const;
};

}}}

namespace NArchive {
namespace NArj {

namespace NCompressionMethod
{
  enum
  {
    kStored = 0,
    kCompressed1a = 1,
    kCompressed1b = 2,
    kCompressed1c = 3,
    kCompressed2 = 4,
    kNoDataNoCRC = 8,
    kNoData = 9
  };
}

namespace NFileType
{
  enum
  {
    kBinary = 0,
    k7BitText,
    kArchiveHeader,
    kDirectory,
    kVolumeLablel,
    kChapterLabel
  };
}

namespace NFlags
{
  const Byte kGarbled  = 1 << 0;
  // const Byte kAnsiPage = 1 << 1; // or (OLD_SECURED_FLAG) obsolete
  const Byte kVolume   = 1 << 2;
  const Byte kExtFile  = 1 << 3;
  // const Byte kPathSym  = 1 << 4;
  // const Byte kBackup   = 1 << 5; // obsolete
  // const Byte kSecured  = 1 << 6;
  // const Byte kDualName = 1 << 7;
}

namespace NHostOS
{
  enum EEnum
  {
    kMSDOS = 0,  // MS-DOS, OS/2, Win32, pkarj 2.50 (FAT / VFAT / FAT32)
    kPRIMOS,
    kUnix,
    kAMIGA,
    kMac,
    kOS_2,
    kAPPLE_GS,
    kAtari_ST,
    kNext,
    kVAX_VMS,
    kWIN95
  };
}

struct CArcHeader
{
  // Byte ArchiverVersion;
  // Byte ExtractVersion;
  Byte HostOS;
  // Byte Flags;
  // Byte SecuryVersion;
  // Byte FileType;
  // Byte Reserved;
  UInt32 CTime;
  UInt32 MTime;
  UInt32 ArchiveSize;
  // UInt32 SecurPos;
  // UInt16 FilespecPosInFilename;
  UInt16 SecurSize;
  // Byte EncryptionVersion;
  // Byte LastChapter;
  AString Name;
  AString Comment;
  
  HRESULT Parse(const Byte *p, unsigned size);
};

struct CExtendedInfo
{
  UInt64 Size;
  bool CrcError;

  void Clear();
  void ParseToPropVar(NWindows::NCOM::CPropVariant &prop) const;
};

struct CItem
{
  AString Name;
  AString Comment;

  UInt32 MTime;
  UInt32 PackSize;
  UInt32 Size;
  UInt32 FileCRC;
  UInt32 SplitPos;

  Byte Version;
  Byte ExtractVersion;
  Byte HostOS;
  Byte Flags;
  Byte Method;
  Byte FileType;

  // UInt16 FilespecPosInFilename;
  UInt16 FileAccessMode;
  // Byte FirstChapter;
  // Byte LastChapter;
  
  UInt64 DataPosition;

  CExtendedInfo ExtendedInfo;

  bool IsEncrypted() const;
  bool IsDir() const;
  bool IsSplitAfter() const;
  bool IsSplitBefore() const;
  UInt32 GetWinAttrib() const;

  HRESULT Parse(const Byte *p, unsigned size);
};

enum EErrorType
{
  k_ErrorType_OK,
  k_ErrorType_Corrupted,
  k_ErrorType_UnexpectedEnd
};

class CArc
{
public:
  UInt64 Processed;
  EErrorType Error;
  bool IsArc;
  IInStream *Stream;
  IArchiveOpenCallback *Callback;
  UInt64 NumFiles;
  CArcHeader Header;

  CExtendedInfo ExtendedInfo;

  HRESULT Open();
  HRESULT GetNextItem(CItem &item, bool &filled);
  void Close();
private:
  unsigned _blockSize;
  CByteBuffer _block;

  HRESULT ReadBlock(bool &filled, CExtendedInfo *extendedInfo);
  HRESULT SkipExtendedHeaders(CExtendedInfo &extendedInfo);
  HRESULT Read(void *data, size_t *size);
};

class CHandler:
  public IInArchive,
  public CMyUnknownImp
{
  CObjectVector<CItem> _items;
  CMyComPtr<IInStream> _stream;
  UInt64 _phySize;
  CArc _arc;
public:
  static void Register();

  MY_UNKNOWN_IMP1(IInArchive)

  INTERFACE_IInArchive(;)

  HRESULT Open2(IInStream *inStream, IArchiveOpenCallback *callback);
};

}}

#endif // __ARJ_HANDLER_H

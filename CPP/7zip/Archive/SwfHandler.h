// SwfHandler.h

#ifndef __SWF_HANDLER_H
#define __SWF_HANDLER_H

// #define SWF_UPDATE

namespace NArchive {

namespace NSwfc {

static const unsigned kHeaderBaseSize = 8;
static const unsigned kHeaderLzmaSize = 17;

struct CItem
{
  Byte Buf[kHeaderLzmaSize];
  unsigned HeaderSize;

  UInt32 GetSize() const;
  UInt32 GetLzmaPackSize() const;
  UInt32 GetLzmaDicSize() const;

  bool IsSwf() const;
  bool IsUncompressed() const;
  bool IsZlib() const;
  bool IsLzma() const;

  void MakeUncompressed();
  void MakeZlib();
  void MakeLzma(UInt32 packSize);

  HRESULT ReadHeader(ISequentialInStream *stream);
  HRESULT WriteHeader(ISequentialOutStream *stream);
};

class CHandler:
  public IInArchive,
  public IArchiveOpenSeq,
 #ifdef SWF_UPDATE
  public IOutArchive,
  public ISetProperties,
 #endif
  public CMyUnknownImp
{
  CItem _item;
  UInt64 _packSize;
  bool _packSizeDefined;
  CMyComPtr<ISequentialInStream> _seqStream;
  CMyComPtr<IInStream> _stream;

 #ifdef SWF_UPDATE
  CSingleMethodProps _props;
  bool _lzmaMode;
  #endif

public:
  static void Register();

 #ifdef SWF_UPDATE
  MY_UNKNOWN_IMP4(IInArchive, IArchiveOpenSeq, IOutArchive, ISetProperties)
  CHandler();
  INTERFACE_IOutArchive(;)
  STDMETHOD(SetProperties)(const wchar_t * const *names, const PROPVARIANT *values, UInt32 numProps);
 #else
  MY_UNKNOWN_IMP2(IInArchive, IArchiveOpenSeq)
 #endif
  INTERFACE_IInArchive(;)
  STDMETHOD(OpenSeq)(ISequentialInStream *stream);
};

class CCompressProgressInfoImp:
  public ICompressProgressInfo,
  public CMyUnknownImp
{
  CMyComPtr<IArchiveOpenCallback> Callback;
public:
  UInt64 Offset;
  MY_UNKNOWN_IMP1(ICompressProgressInfo)
  STDMETHOD(SetRatioInfo)(const UInt64 *inSize, const UInt64 *outSize);
  void Init(IArchiveOpenCallback *callback);
};

}

namespace NSwf {

struct CTag
{
  UInt32 Type;
  CByteBuffer Buf;
};

class CHandler:
  public IInArchive,
  public IArchiveOpenSeq,
  public CMyUnknownImp
{
  CObjectVector<CTag> _tags;
  NSwfc::CItem _item;
  UInt64 _phySize;

  HRESULT OpenSeq3(ISequentialInStream *stream, IArchiveOpenCallback *callback);
  HRESULT OpenSeq2(ISequentialInStream *stream, IArchiveOpenCallback *callback);
public:
  static void Register();

  MY_UNKNOWN_IMP2(IInArchive, IArchiveOpenSeq)
  INTERFACE_IInArchive(;)

  STDMETHOD(OpenSeq)(ISequentialInStream *stream);
};

struct CBitReader
{
  CInBuffer *stream;
  unsigned NumBits;
  Byte Val;

  CBitReader();

  UInt32 ReadBits(unsigned numBits);
};

}

}

#endif // __SWF_HANDLER_H

// GzHandler.h

#ifndef __GZ_HANDLER_H
#define __GZ_HANDLER_H

#include "../../Common/MyCom.h"
#include "../../Common/MyString.h"
#include "../../7zip/Compress/DeflateDecoder.h"
#include "../../7zip/Compress/DeflateEncoder.h"

namespace NArchive {
namespace NGz {

class CItem
{
  bool TestFlag(Byte flag) const;
public:
  Byte Flags;
  Byte ExtraFlags;
  Byte HostOS;
  UInt32 Time;
  UInt32 Crc;
  UInt32 Size32;

  AString Name;
  AString Comment;
  // CByteBuffer Extra;

  CItem();

  void Clear();

  void CopyMetaPropsFrom(const CItem &a);

  void CopyDataPropsFrom(const CItem &a);
  
  // bool IsText() const;
  bool HeaderCrcIsPresent() const;
  bool ExtraFieldIsPresent() const;
  bool NameIsPresent() const;
  bool CommentIsPresent() const;
  bool IsSupported() const;

  HRESULT ReadHeader(NCompress::NDeflate::NDecoder::CCOMCoder *stream);
  HRESULT ReadFooter1(NCompress::NDeflate::NDecoder::CCOMCoder *stream);
  HRESULT ReadFooter2(ISequentialInStream *stream);

  HRESULT WriteHeader(ISequentialOutStream *stream);
  HRESULT WriteFooter(ISequentialOutStream *stream);
};

class CHandler:
  public IInArchive,
  public IArchiveOpenSeq,
  public IOutArchive,
  public ISetProperties,
  public CMyUnknownImp
{
  CItem _item;

  bool _isArc;
  bool _needSeekToStart;
  bool _dataAfterEnd;
  bool _needMoreInput;

  bool _packSize_Defined;
  bool _unpackSize_Defined;
  bool _numStreams_Defined;

  UInt64 _packSize;
  UInt64 _unpackSize; // real unpack size (NOT from footer)
  UInt64 _numStreams;
  UInt64 _headerSize; // only start header (without footer)

  CMyComPtr<IInStream> _stream;
  CMyComPtr<ICompressCoder> _decoder;
  NCompress::NDeflate::NDecoder::CCOMCoder *_decoderSpec;

  CSingleMethodProps _props;

public:
  static void Register();

  MY_UNKNOWN_IMP4(
      IInArchive,
      IArchiveOpenSeq,
      IOutArchive,
      ISetProperties)
  INTERFACE_IInArchive(;)
  INTERFACE_IOutArchive(;)
  STDMETHOD(OpenSeq)(ISequentialInStream *stream);
  STDMETHOD(SetProperties)(const wchar_t * const *names, const PROPVARIANT *values, UInt32 numProps);

  CHandler();
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

}}

#endif // __GZ_HANDLER_H

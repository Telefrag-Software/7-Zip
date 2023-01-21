// LzmaHandler.h

#ifndef __LZMA_HANDLER_H
#define __LZMA_HANDLER_H

#include "../../Common/MyCom.h"
#include "../../Windows/PropVariant.h"
#include "../Common/FilterCoder.h"
#include "../Compress/LzmaDecoder.h"

namespace NArchive {
namespace NLzma {

struct CHeader
{
  UInt64 Size;
  Byte FilterID;
  Byte LzmaProps[5];

  Byte GetProp() const;
  UInt32 GetDicSize() const;
  bool HasSize() const;
  bool Parse(const Byte *buf, bool isThereFilter);
};

class CDecoder
{
  CMyComPtr<ISequentialOutStream> _bcjStream;
  CFilterCoder *_filterCoder;
  CMyComPtr<ICompressCoder> _lzmaDecoder;
public:
  NCompress::NLzma::CDecoder *_lzmaDecoderSpec;

  ~CDecoder();
  HRESULT Create(bool filtered, ISequentialInStream *inStream);

  HRESULT Code(const CHeader &header, ISequentialOutStream *outStream, ICompressProgressInfo *progress);

  UInt64 GetInputProcessedSize() const;

  void ReleaseInStream();

  HRESULT ReadInput(Byte *data, UInt32 size, UInt32 *processedSize);
};

class CHandler:
  public IInArchive,
  public IArchiveOpenSeq,
  public CMyUnknownImp
{
  CHeader _header;
  bool _lzma86;
  CMyComPtr<IInStream> _stream;
  CMyComPtr<ISequentialInStream> _seqStream;

  bool _isArc;
  bool _needSeekToStart;
  bool _dataAfterEnd;
  bool _needMoreInput;

  bool _packSize_Defined;
  bool _unpackSize_Defined;
  bool _numStreams_Defined;

  bool _unsupported;
  bool _dataError;

  UInt64 _packSize;
  UInt64 _unpackSize;
  UInt64 _numStreams;

  void GetMethod(NWindows::NCOM::CPropVariant &prop);

public:
  static void Register();

  MY_UNKNOWN_IMP2(IInArchive, IArchiveOpenSeq)

  INTERFACE_IInArchive(;)
  STDMETHOD(OpenSeq)(ISequentialInStream *stream);

  CHandler(bool lzma86);

  unsigned GetHeaderSize() const;
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

#endif // __LZMA_HANDLER_H

// QcowHandler.h

#ifndef __QCOW_HANDLER_H
#define __QCOW_HANDLER_H

namespace NArchive {
namespace NQcow {

class CHandler: public CHandlerImg
{
  unsigned _clusterBits;
  unsigned _numMidBits;
  UInt64 _compressedFlag;

  CObjArray2<UInt32> _dir;
  CAlignedBuffer _table;
  UInt64 _cacheCluster;
  CByteBuffer _cache;
  CByteBuffer _cacheCompressed;

  UInt64 _comprPos;
  size_t _comprSize;

  UInt64 _phySize;

  CBufInStream *_bufInStreamSpec;
  CMyComPtr<ISequentialInStream> _bufInStream;

  CBufPtrSeqOutStream *_bufOutStreamSpec;
  CMyComPtr<ISequentialOutStream> _bufOutStream;

  NCompress::NDeflate::NDecoder::CCOMCoder *_deflateDecoderSpec;
  CMyComPtr<ICompressCoder> _deflateDecoder;

  bool _needDeflate;
  bool _isArc;
  bool _unsupported;

  UInt32 _version;
  UInt32 _cryptMethod;
  
  HRESULT Seek2(UInt64 offset);

  HRESULT InitAndSeek();

  HRESULT Open2(IInStream *stream, IArchiveOpenCallback *openCallback);

public:
  static void Register();

  INTERFACE_IInArchive_Img(;)

  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
  STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);
};


}}

#endif // __QCOW_HANDLER_H

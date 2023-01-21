// XzHandler.h

#ifndef __XZ_HANDLER_H
#define __XZ_HANDLER_H

#include "../Compress/XzDecoder.h"
#include "../Compress/XzEncoder.h"
#include "../../Common/MyCom.h"
#include "../../Common/MyString.h"

namespace NArchive {
namespace NXz {

struct CBlockInfo
{
  unsigned StreamFlags;
  UInt64 PackPos;
  UInt64 PackSize; // pure value from Index record, it doesn't include pad zeros
  UInt64 UnpackPos;
};

class CHandler:
  public IInArchive,
  public IArchiveOpenSeq,
  public IInArchiveGetStream,
  public ISetProperties,

  #ifndef EXTRACT_ONLY
  public IOutArchive,
  #endif

  public CMyUnknownImp,

  #ifndef EXTRACT_ONLY
    public CMultiMethodProps
  #else
    public CCommonMethodProps
  #endif
{
  CXzStatInfo _stat;    // it's stat from backward parsing
  CXzStatInfo _stat2;   // it's data from forward parsing, if the decoder was called
  SRes _stat2_decode_SRes;
  bool _stat_defined;
  bool _stat2_defined;

  const CXzStatInfo *GetStat() const;

  bool _isArc;
  bool _needSeekToStart;
  bool _firstBlockWasRead;

  AString _methodsString;

  #ifndef EXTRACT_ONLY

  UInt32 _filterId;
  UInt64 _numSolidBytes;

  void InitXz();

  #endif

  void Init();

  HRESULT SetProperty(const wchar_t *name, const PROPVARIANT &value);

  HRESULT Open2(IInStream *inStream, /* UInt32 flags, */ IArchiveOpenCallback *callback);

  HRESULT Decode(NCompress::NXz::CDecoder &decoder,
      ISequentialInStream *seqInStream,
      ISequentialOutStream *outStream,
      ICompressProgressInfo *progress);

public:
  static void Register();

  MY_QUERYINTERFACE_BEGIN2(IInArchive)
  MY_QUERYINTERFACE_ENTRY(IArchiveOpenSeq)
  MY_QUERYINTERFACE_ENTRY(IInArchiveGetStream)
  MY_QUERYINTERFACE_ENTRY(ISetProperties)
  #ifndef EXTRACT_ONLY
  MY_QUERYINTERFACE_ENTRY(IOutArchive)
  #endif
  MY_QUERYINTERFACE_END
  MY_ADDREF_RELEASE

  INTERFACE_IInArchive(;)
  STDMETHOD(OpenSeq)(ISequentialInStream *stream);
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
  STDMETHOD(SetProperties)(const wchar_t * const *names, const PROPVARIANT *values, UInt32 numProps);

  #ifndef EXTRACT_ONLY
  INTERFACE_IOutArchive(;)
  #endif

  CBlockInfo *_blocks;
  size_t _blocksArraySize;
  UInt64 _maxBlocksSize;
  CMyComPtr<IInStream> _stream;
  CMyComPtr<ISequentialInStream> _seqStream;

  CXzBlock _firstBlock;

  CHandler();
  ~CHandler();

  HRESULT SeekToPackPos(UInt64 pos);
};

struct CMethodNamePair
{
  UInt32 Id;
  const char *Name;
};

struct COpenCallbackWrap
{
  ICompressProgress vt;
  IArchiveOpenCallback *OpenCallback;
  HRESULT Res;
  
  // new clang shows "non-POD" warning for offsetof(), if we use constructor instead of Init()
  void Init(IArchiveOpenCallback *progress);
};

struct CXzsCPP
{
  CXzs p;
  CXzsCPP();
  ~CXzsCPP();
};

struct CLookToRead2_CPP: public CLookToRead2
{
  CLookToRead2_CPP();
  void Alloc(size_t allocSize);
  ~CLookToRead2_CPP();
};

struct CXzUnpackerCPP2
{
  Byte *InBuf;
  // Byte *OutBuf;
  CXzUnpacker p;
  
  CXzUnpackerCPP2();
  ~CXzUnpackerCPP2();
};

class CInStream:
  public IInStream,
  public CMyUnknownImp
{
public:
  UInt64 _virtPos;
  UInt64 Size;
  UInt64 _cacheStartPos;
  size_t _cacheSize;
  CByteBuffer _cache;
  // UInt64 _startPos;
  CXzUnpackerCPP2 xz;

  void InitAndSeek();

  CHandler *_handlerSpec;
  CMyComPtr<IUnknown> _handler;

  MY_UNKNOWN_IMP1(IInStream)

  STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);
  STDMETHOD(Seek)(Int64 offset, UInt32 seekOrigin, UInt64 *newPosition);

  ~CInStream();
};

}}

#endif // __XZ_HANDLER_H

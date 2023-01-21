// FlvHandler.cpp

#ifndef __FLV_HANDLER_H
#define __FLV_HANDLER_H

#include "../../Common/MyCom.h"
#include "../../Common/MyString.h"
#include "../../Common/MyVector.h"

namespace NArchive {
namespace NFlv {

struct CItem
{
  CByteBuffer Data;
  Byte Type;
};

struct CItem2
{
  Byte Type;
  Byte SubType;
  Byte Props;
  bool SameSubTypes;
  unsigned NumChunks;
  size_t Size;

  CReferenceBuf *BufSpec;
  CMyComPtr<IUnknown> RefBuf;

  bool IsAudio() const;
};

class CHandler:
  public IInArchive,
  public IInArchiveGetStream,
  public CMyUnknownImp
{
  CMyComPtr<IInStream> _stream;
  CObjectVector<CItem2> _items2;
  CByteBuffer _metadata;
  bool _isRaw;
  UInt64 _phySize;

  HRESULT Open2(IInStream *stream, IArchiveOpenCallback *callback);
  // AString GetComment();
public:
  static void Register();

  MY_UNKNOWN_IMP2(IInArchive, IInArchiveGetStream)
  INTERFACE_IInArchive(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
};

}}

#endif // __FLV_HANDLER_H

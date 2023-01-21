// VdiHandler.h

#ifndef __VDI_HANDLER_H
#define __VDI_HANDLER_H

#include "../../Common/MyBuffer.h"

namespace NArchive {
namespace NVdi {

static const unsigned kNumGuids = 4;

class CHandler: public CHandlerImg
{
  UInt32 _dataOffset;
  CByteBuffer _table;
  UInt64 _phySize;
  UInt32 _imageType;
  bool _isArc;
  bool _unsupported;

  Byte Guids[kNumGuids][16];

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

#endif // __VDI_HANDLER_H

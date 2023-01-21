// Compress/DeltaFilter.h

#ifndef __DELTA_FILTER_H
#define __DELTA_FILTER_H

#include "../../../C/Delta.h"
#include "../../Common/MyCom.h"
#include "../ICoder.h"

namespace NCompress {
namespace NDelta {

struct CDelta
{
  unsigned _delta;
  Byte _state[DELTA_STATE_SIZE];

  CDelta(): _delta(1) {}
  void DeltaInit() { Delta_Init(_state); }
};

#ifndef EXTRACT_ONLY

class CEncoder:
  public ICompressFilter,
  public ICompressSetCoderProperties,
  public ICompressWriteCoderProperties,
  CDelta,
  public CMyUnknownImp
{
public:
  MY_UNKNOWN_IMP3(ICompressFilter, ICompressSetCoderProperties, ICompressWriteCoderProperties)
  INTERFACE_ICompressFilter(;)
  STDMETHOD(SetCoderProperties)(const PROPID *propIDs, const PROPVARIANT *props, UInt32 numProps);
  STDMETHOD(WriteCoderProperties)(ISequentialOutStream *outStream);
};

#endif // EXTRACT_ONLY

class CDecoder:
  public ICompressFilter,
  public ICompressSetDecoderProperties2,
  CDelta,
  public CMyUnknownImp
{
public:
  static void Register();

  MY_UNKNOWN_IMP2(ICompressFilter, ICompressSetDecoderProperties2)
  INTERFACE_ICompressFilter(;)
  STDMETHOD(SetDecoderProperties2)(const Byte *data, UInt32 size);
};

}}

#endif // __DELTA_FILTER_H

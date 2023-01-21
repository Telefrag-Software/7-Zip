// Compress/DeltaFilter.cpp

#include "DeltaFilter.h"

namespace NCompress {
namespace NDelta {

#ifndef EXTRACT_ONLY

STDMETHODIMP CEncoder::Init()
{
  DeltaInit();
  return S_OK;
}

STDMETHODIMP_(UInt32) CEncoder::Filter(Byte *data, UInt32 size)
{
  Delta_Encode(_state, _delta, data, size);
  return size;
}

STDMETHODIMP CEncoder::SetCoderProperties(const PROPID *propIDs, const PROPVARIANT *props, UInt32 numProps)
{
  UInt32 delta = _delta;
  for (UInt32 i = 0; i < numProps; i++)
  {
    const PROPVARIANT &prop = props[i];
    PROPID propID = propIDs[i];
    if (propID >= NCoderPropID::kReduceSize)
      continue;
    if (prop.vt != VT_UI4)
      return E_INVALIDARG;
    switch (propID)
    {
      case NCoderPropID::kDefaultProp:
        delta = (UInt32)prop.ulVal;
        if (delta < 1 || delta > 256)
          return E_INVALIDARG;
        break;
      case NCoderPropID::kNumThreads: break;
      case NCoderPropID::kLevel: break;
      default: return E_INVALIDARG;
    }
  }
  _delta = delta;
  return S_OK;
}

STDMETHODIMP CEncoder::WriteCoderProperties(ISequentialOutStream *outStream)
{
  Byte prop = (Byte)(_delta - 1);
  return outStream->Write(&prop, 1, NULL);
}

#endif // EXTRACT_ONLY

STDMETHODIMP CDecoder::Init()
{
  DeltaInit();
  return S_OK;
}

STDMETHODIMP_(UInt32) CDecoder::Filter(Byte *data, UInt32 size)
{
  Delta_Decode(_state, _delta, data, size);
  return size;
}

STDMETHODIMP CDecoder::SetDecoderProperties2(const Byte *props, UInt32 size)
{
  if (size != 1)
    return E_INVALIDARG;
  _delta = (unsigned)props[0] + 1;
  return S_OK;
}

}}

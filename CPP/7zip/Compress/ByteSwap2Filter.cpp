// Compress/ByteSwap2Filter.cpp

#include "ByteSwap2Filter.h"

namespace NCompress {
namespace NByteSwap {

STDMETHODIMP CByteSwap2::Init() { return S_OK; }

STDMETHODIMP_(UInt32) CByteSwap2::Filter(Byte *data, UInt32 size)
{
  const UInt32 kStep = 2;
  if (size < kStep)
    return 0;
  size &= ~(kStep - 1);
  
  const Byte *end = data + (size_t)size;
  
  do
  {
    Byte b0 = data[0];
    data[0] = data[1];
    data[1] = b0;
    data += kStep;
  }
  while (data != end);

  return size;
}

}}

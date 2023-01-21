// Compress/ByteSwap4Filter.cpp

#include "ByteSwap4Filter.h"

namespace NCompress {
namespace NByteSwap {

STDMETHODIMP CByteSwap4::Init() { return S_OK; }

STDMETHODIMP_(UInt32) CByteSwap4::Filter(Byte *data, UInt32 size)
{
  const UInt32 kStep = 4;
  if (size < kStep)
    return 0;
  size &= ~(kStep - 1);
  
  const Byte *end = data + (size_t)size;
  
  do
  {
    Byte b0 = data[0];
    Byte b1 = data[1];
    data[0] = data[3];
    data[1] = data[2];
    data[2] = b1;
    data[3] = b0;
    data += kStep;
  }
  while (data != end);

  return size;
}

}}

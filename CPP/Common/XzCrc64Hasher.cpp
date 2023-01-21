// Common/XzCrc64Hasher.h

#include "XzCrc64Hasher.h"

namespace NHash {

STDMETHODIMP_(void) CXzCrc64Hasher::Init() throw()
{
  _crc = CRC64_INIT_VAL;
}

STDMETHODIMP_(void) CXzCrc64Hasher::Update(const void *data, UInt32 size) throw()
{
  _crc = Crc64Update(_crc, data, size);
}

STDMETHODIMP_(void) CXzCrc64Hasher::Final(Byte *digest) throw()
{
  UInt64 val = CRC64_GET_DIGEST(_crc);
  SetUi64(digest, val);
}

}

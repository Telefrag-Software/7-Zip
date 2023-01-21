// Common/CksumHasher.cpp

#include "CksumHasher.h"

namespace NHash {

STDMETHODIMP_(void) CCksumHasher::Init() throw()
{
  _crc.Init(0);
  _size = 0;
}

STDMETHODIMP_(void) CCksumHasher::Update(const void *data, UInt32 size) throw()
{
  _size += size;
  CBZip2Crc crc = _crc;
  for (UInt32 i = 0; i < size; i++)
    crc.UpdateByte(((const Byte *)data)[i]);
  _crc = crc;
}

STDMETHODIMP_(void) CCksumHasher::Final(Byte *digest) throw()
{
  UInt64 size = _size;
  CBZip2Crc crc = _crc;
  while (size)
  {
    crc.UpdateByte((Byte)size);
    size >>= 8;
  }
  const UInt32 val = crc.GetDigest();
  SetUi32(digest, val);
}

}

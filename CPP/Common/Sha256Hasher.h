// Common/Sha256Hasher.h

#ifndef __SHA256_HASHER_H
#define __SHA256_HASHER_H

#include "../../C/Sha256.h"
#include "../7zip/ICoder.h"
#include "../Common/MyBuffer2.h"
#include "../Common/MyCom.h"

namespace NHash {

class CSha256Hasher:
  public IHasher,
  public ICompressSetCoderProperties,
  public CMyUnknownImp
{
  CAlignedBuffer _buf;
  Byte mtDummy[1 << 7];

  CSha256 *Sha() { return (CSha256 *)(void *)(Byte *)_buf; }
public:
  static void Prepare();
  static void Register();

  CSha256Hasher():
    _buf(sizeof(CSha256))
  {
    Sha256_SetFunction(Sha(), 0);
    Sha256_InitState(Sha());
  }

  MY_UNKNOWN_IMP2(IHasher, ICompressSetCoderProperties)
  INTERFACE_IHasher(;)
  STDMETHOD(SetCoderProperties)(const PROPID *propIDs, const PROPVARIANT *props, UInt32 numProps);
};

}

#endif // __SHA256_HASHER_H

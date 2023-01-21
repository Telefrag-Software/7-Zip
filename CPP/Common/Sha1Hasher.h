// Common/Sha1Hasher.h

#ifndef __SHA1_HASHER_H
#define __SHA1_HASHER_H

#include "../../C/Sha1.h"
#include "../7zip/ICoder.h"
#include "../Common/MyBuffer2.h"
#include "../Common/MyCom.h"

namespace NHash {

class CSha1Hasher:
  public IHasher,
  public ICompressSetCoderProperties,
  public CMyUnknownImp
{
  CAlignedBuffer _buf;
  Byte mtDummy[1 << 7];
  
  CSha1 *Sha() { return (CSha1 *)(void *)(Byte *)_buf; }
public:
  static void Prepare();
  static void Register();

  CSha1Hasher():
    _buf(sizeof(CSha1))
  {
    Sha1_SetFunction(Sha(), 0);
    Sha1_InitState(Sha());
  }

  MY_UNKNOWN_IMP2(IHasher, ICompressSetCoderProperties)
  INTERFACE_IHasher(;)
  STDMETHOD(SetCoderProperties)(const PROPID *propIDs, const PROPVARIANT *props, UInt32 numProps);
};

}

#endif // __SHA1_HASHER_H

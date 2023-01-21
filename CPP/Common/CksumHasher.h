// Common/CksumHasher.h

#ifndef __CKSUM_HASHER_H
#define __CKSUM_HASHER_H

#include "../../C/CpuArch.h"
#include "../7zip/ICoder.h"
#include "../Common/MyCom.h"
#include "../7zip/Compress/BZip2Crc.h"

namespace NHash {

class CCksumHasher:
  public IHasher,
  public CMyUnknownImp
{
  CBZip2Crc _crc;
  UInt64 _size;
  Byte mtDummy[1 << 7];
  
public:
  static void Register();

  CCksumHasher()
  {
    _crc.Init(0);
    _size = 0;
  }

  MY_UNKNOWN_IMP1(IHasher)
  INTERFACE_IHasher(;)
};

}

#endif // __CKSUM_HASHER_H
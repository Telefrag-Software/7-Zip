// Common/XzCrc64Hasher.h

#ifndef __XZ_CRC64_HASHER_H
#define __XZ_CRC64_HASHER_H

#include "../../C/CpuArch.h"
#include "../../C/XzCrc64.h"
#include "../7zip/ICoder.h"
#include "../7zip/Common/MethodId.h"
#include "../Common/MyCom.h"

namespace NHash {

class CXzCrc64Hasher:
  public IHasher,
  public CMyUnknownImp
{
  UInt64 _crc;
  Byte mtDummy[1 << 7];

public:
  static void Initialize();
  static void Register();

  CXzCrc64Hasher(): _crc(CRC64_INIT_VAL) {}

  MY_UNKNOWN_IMP1(IHasher)
  INTERFACE_IHasher(;)
};

}

#endif // __XZ_CRC64_HASHER_H

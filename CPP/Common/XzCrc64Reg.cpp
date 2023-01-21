// XzCrc64Reg.cpp

#include "StdAfx.h"

#include "../7zip/Common/RegisterCodec.h"

#include "XzCrc64Hasher.h"

namespace NHash {

UInt32 __stdcall CXzCrc64Hasher::GetDigestSize() throw() {
  return 8;
}

static IHasher * CreateHasherSpecXzCrc64() {
  return new CXzCrc64Hasher();
}

static const CHasherInfo s_hasherInfo_XzCrc64 = {
  CreateHasherSpecXzCrc64,
  0x4,
  "CRC64",
  8
};

void CXzCrc64Hasher::Register() {
  static bool s_registered;

  Initialize();

  if(!s_registered) {
    RegisterHasher(&s_hasherInfo_XzCrc64);
    s_registered = true;
  }
}

}

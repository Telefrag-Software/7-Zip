// Sha256Reg.cpp

#include "StdAfx.h"

#include "../7zip/Common/RegisterCodec.h"
#include "Sha256Hasher.h"

namespace NHash {

UInt32 __stdcall CSha256Hasher::GetDigestSize() throw() {
  return SHA256_DIGEST_SIZE;
}

static IHasher * CreateHasherSpecSha256() {
  return new CSha256Hasher();
}

static const CHasherInfo s_hasherInfo_Sha256 = {
  CreateHasherSpecSha256,
  0xA,
  "SHA256",
  SHA256_DIGEST_SIZE
};

void CSha256Hasher::Register() {
  static bool s_registered;

  Prepare();

  if(!s_registered) {
    RegisterHasher(&s_hasherInfo_Sha256);
    s_registered = true;
  }
}

}

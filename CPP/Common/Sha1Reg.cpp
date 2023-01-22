// Sha1Reg.cpp

#include "StdAfx.h"

#include "../7zip/Common/RegisterCodec.h"

#include "Sha1Hasher.h"

namespace NHash {

UInt32 __stdcall CSha1Hasher::GetDigestSize() throw() {
  return SHA1_DIGEST_SIZE;
}

static IHasher * CreateHasherSpec() {
  return new CSha1Hasher();
}

static const CHasherInfo s_hasherInfo_Sha1 = {
  CreateHasherSpec,
  0x201,
  "SHA1",
  SHA1_DIGEST_SIZE
};

void CSha1Hasher::Register() {
  static bool s_registered;

  Prepare();

  if(!s_registered) {
    RegisterHasher(&s_hasherInfo_Sha1);
    s_registered = true;
  }
}


}

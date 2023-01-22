// CksumReg.cpp

#include "StdAfx.h"

#include "../7zip/Common/RegisterCodec.h"

#include "CksumHasher.h"

namespace NHash {

UInt32 __stdcall CCksumHasher::GetDigestSize() throw() {
  return 4;
}

static IHasher * CreateHasherSpecCksum() {
  return new CCksumHasher();
}

static const CHasherInfo s_hasherInfo_Cksum = {
  CreateHasherSpecCksum,
  0,
  "CKSUM",
  4
};

void CCksumHasher::Register() {
  static bool s_registered;

  if(!s_registered) {
    RegisterHasher(&s_hasherInfo_Cksum);
    s_registered = true;
  }
}

}

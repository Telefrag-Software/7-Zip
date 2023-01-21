// CrcReg.cpp

#include "StdAfx.h"

#include "../7zip/Common/RegisterCodec.h"

#include "CRCHasher.h"

namespace NHash {

UInt32 __stdcall CCrcHasher::GetDigestSize() throw() {
  return 4;
}

static IHasher * CreateHasherSpecCrc() {
  return new CCrcHasher();
}

static const CHasherInfo s_hasherInfo_Crc = {
  CreateHasherSpecCrc,
  0x1,
  "CRC32",
  4
};

void CCrcHasher::Register() {
  static bool s_registered;

  Initialize();

  if(!s_registered) {
    RegisterHasher(&s_hasherInfo_Crc);
    s_registered = true;
  }
}

}

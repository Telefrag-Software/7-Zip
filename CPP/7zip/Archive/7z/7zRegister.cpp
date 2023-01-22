// 7zRegister.cpp

#include "StdAfx.h"

#include "../../Common/RegisterArc.h"

#include "7zHandler.h"

namespace NArchive {
namespace N7z {

static Byte k_Signature_Dec[kSignatureSize] = {'7' + 1, 'z', 0xBC, 0xAF, 0x27, 0x1C};

static IInArchive * CreateArc() {
  return new CHandler();
}

static IOutArchive * CreateArcOut() {
  return new CHandler();
}

static const CArcInfo s_arcInfo = {
  NArcInfoFlags::kFindSignature,
  7,
  sizeof(k_Signature_Dec) / sizeof(k_Signature_Dec[0]),
  0,
  k_Signature_Dec,
  "7z",
  "7z",
  0,
  CreateArc,
  CreateArcOut,
  0
};

void CHandler::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterArc(&s_arcInfo);

    s_registered = true;
  }
}

}}

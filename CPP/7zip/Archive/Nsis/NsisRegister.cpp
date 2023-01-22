// NsisRegister.cpp

#include "StdAfx.h"

#include "../../Common/RegisterArc.h"

#include "NsisHandler.h"

namespace NArchive {
namespace NNsis {

static IInArchive * CreateArc() {
  return new CHandler();
}

static const CArcInfo s_arcInfo = {
  NArcInfoFlags::kFindSignature | NArcInfoFlags::kUseGlobalOffset,
  0x9,
  sizeof(kSignature) / sizeof(kSignature[0]),
  4,
  kSignature,
  "Nsis",
  "nsis",
  0,
  CreateArc,
  0,
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

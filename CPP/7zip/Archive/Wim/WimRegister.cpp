// WimRegister.cpp

#include "StdAfx.h"

#include "../../Common/RegisterArc.h"

#include "WimHandler.h"

namespace NArchive {
namespace NWim {

static IInArchive * CreateArc() {
  return new CHandler();
}

static IOutArchive * CreateArcOut() {
  return new CHandler();
}

static const CArcInfo s_arcInfo = {
  NArcInfoFlags::kAltStreams | NArcInfoFlags::kNtSecure | NArcInfoFlags::kSymLinks | NArcInfoFlags::kHardLinks,
  0xE6,
  sizeof(kSignature) / sizeof(kSignature[0]),
  0,
  kSignature,
  "wim",
  "wim swm esd ppkg",
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

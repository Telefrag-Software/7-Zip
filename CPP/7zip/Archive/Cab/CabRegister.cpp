// CabRegister.cpp

#include "StdAfx.h"

#include "../../Common/RegisterArc.h"

#include "CabHandler.h"

namespace NArchive {
namespace NCab {

static IInArchive * CreateArc() {
  return new CHandler();
}

static const CArcInfo s_arcInfo = {
  NArcInfoFlags::kFindSignature,
  8,
  (sizeof(NHeader::kMarker) / sizeof(NHeader::kMarker[0])),
  0,
  NHeader::kMarker,
  "Cab",
  "cab",
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

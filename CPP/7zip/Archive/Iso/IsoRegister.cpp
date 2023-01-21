// IsoRegister.cpp

#include "StdAfx.h"

#include "../../Common/RegisterArc.h"

#include "IsoHandler.h"

namespace NArchive {
namespace NIso {

static const Byte k_Signature[] = { 'C', 'D', '0', '0', '1' };

static IInArchive * CreateArc() {
  return new CHandler();
}

static const CArcInfo s_arcInfo = {
  0,
  0xE7,
  (sizeof(k_Signature) / sizeof(k_Signature[0])),
  kStartPos + 1,
  k_Signature,
  "Iso",
  "iso img",
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

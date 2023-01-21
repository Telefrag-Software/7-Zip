// TarRegister.cpp

#include "StdAfx.h"

#include "../../Common/RegisterArc.h"

#include "TarHandler.h"

namespace NArchive {
namespace NTar {

static const Byte k_Signature[] = { 'u', 's', 't', 'a', 'r' };

static IInArchive * CreateArc() {
  return new CHandler();
}

static IOutArchive * CreateArcOut() {
  return new CHandler();
}

static const CArcInfo s_arcInfo = {
  NArcInfoFlags::kStartOpen | NArcInfoFlags::kSymLinks | NArcInfoFlags::kHardLinks,
  0xEE,
  sizeof(k_Signature) / sizeof(k_Signature[0]),
  NFileHeader::kUstarMagic_Offset,
  k_Signature,
  "tar",
  "tar ova",
  0,
  CreateArc,
  CreateArcOut,
  IsArc_Tar
};

void CHandler::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterArc(&s_arcInfo);

    s_registered = true;
  }
}

}}

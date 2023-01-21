// PpmdRegister.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "PpmdDecoder.h"

#ifndef EXTRACT_ONLY
#include "PpmdEncoder.h"
#endif

namespace NCompress {
namespace NPpmd {

static void * PPMD_CreateDec() {
  return (void *)(ICompressFilter *)(new CDecoder());
}

static void * PPMD_CreateEnc() {
  return (void *)(ICompressFilter *)(new CEncoder());
}

static const CCodecInfo s_codecInfo_PPMD = {
  PPMD_CreateDec,
  PPMD_CreateEnc,
  0x30401,
  "PPMD",
  1,
  false
};

void CDecoder::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_PPMD);
    s_registered = true;
  }
}

}}

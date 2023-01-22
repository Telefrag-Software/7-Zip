// DeltaFilter.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"
#include "DeltaFilter.h"

namespace NCompress {
namespace NDelta {

static void * Delta_CreateDec() {
  return (void *)(ICompressFilter *)(new CDecoder());
}

static void * Delta_CreateEnc() {
  return (void *)(ICompressFilter *)(new CEncoder());
}

static const CCodecInfo s_codecInfo_Delta = {
  Delta_CreateDec,
  Delta_CreateEnc,
  3,
  "Delta",
  1,
  true
};

void CDecoder::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_Delta);
    s_registered = true;
  }
}

}}

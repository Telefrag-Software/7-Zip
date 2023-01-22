// BcjRegister.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "BcjCoder.h"

namespace NCompress {
namespace NBcj {

static void * BCJ_CreateDec() {
  return (void *)(ICompressFilter *)(new CCoder(false));
}

static void * BCJ_CreateEnc() {
  return (void *)(ICompressFilter *)(new CCoder(true));
}

static const CCodecInfo s_codecInfo_BCJ = {
  BCJ_CreateDec,
  BCJ_CreateEnc,
  0x3030103,
  "BCJ",
  1,
  true
};

void CCoder::Register() {
  static bool s_registered = false;
  
  if(!s_registered) {
    RegisterCodec(&s_codecInfo_BCJ);
    s_registered = true;
  }
}

}}

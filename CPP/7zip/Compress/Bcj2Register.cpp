// Bcj2Register.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "Bcj2Coder.h"

namespace NCompress {
namespace NBcj2 {

static void * CreateCodec() {
  return (void *)(ICompressCoder2 *)(new CDecoder());
}

#ifndef EXTRACT_ONLY

static void * CreateCodecOut() {
  return (void *)(ICompressCoder2 *)(new CEncoder());
}

#else
#define CreateCodecOut NULL
#endif

static const CCodecInfo s_codecInfo_BCJ2 = {
  CreateCodec,
  CreateCodecOut,
  0x303011B,
  "BCJ2",
  4,
  false
};

void CEncoder::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_BCJ2);
    s_registered = true;
  }
}

}}

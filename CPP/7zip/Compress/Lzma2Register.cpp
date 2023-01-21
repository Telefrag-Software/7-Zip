// Lzma2Register.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "Lzma2Decoder.h"

#ifndef EXTRACT_ONLY
#include "Lzma2Encoder.h"
#endif

namespace NCompress {
namespace NLzma2 {

static void * LZMA2_CreateDec() {
  return (void *)(ICompressFilter *)(new CDecoder());
}

static void * LZMA2_CreateEnc() {
  return (void *)(ICompressFilter *)(new CEncoder());
}

static const CCodecInfo s_codecInfo_LZMA2 = {
  LZMA2_CreateDec,
  LZMA2_CreateEnc,
  0x21,
  "LZMA2",
  1,
  false
};

void CDecoder::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_LZMA2);
    s_registered = true;
  }
}

}}

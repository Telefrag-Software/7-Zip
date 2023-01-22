// LzmaRegister.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "LzmaDecoder.h"

#ifndef EXTRACT_ONLY
#include "LzmaEncoder.h"
#endif

namespace NCompress {
namespace NLzma {

static void * LZMA_CreateDec() {
  return (void *)(ICompressFilter *)(new CDecoder());
}

static void * LZMA_CreateEnc() {
  return (void *)(ICompressFilter *)(new CEncoder());
}

static const CCodecInfo s_codecInfo_LZMA = {
  LZMA_CreateDec,
  LZMA_CreateEnc,
  0x30101,
  "LZMA",
  1,
  false
};

void CDecoder::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_LZMA);
    s_registered = true;
  }
}


}}

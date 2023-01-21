// Deflate64Register.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "DeflateDecoder.h"

#if !defined(EXTRACT_ONLY) && !defined(DEFLATE_EXTRACT_ONLY)
#include "DeflateEncoder.h"
#endif

namespace NCompress {
namespace NDeflate {

static void * CreateDec() {
  return (void *)(ICompressCoder *)(new NDecoder::CCOMCoder64());
}

#if !defined(EXTRACT_ONLY) && !defined(DEFLATE_EXTRACT_ONLY)

static void * CreateEnc() {
  return (void *)(ICompressCoder *)(new NDecoder::CCOMCoder64());
}

#else
#define CreateEnc NULL
#endif

static const CCodecInfo s_codecInfo_Deflate = {
  CreateDec,
  CreateEnc,
  0x40109,
  "Deflate64",
  1,
  false
};

void NDecoder::CCOMCoder64::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_Deflate);
    s_registered = true;
  }
}

}}

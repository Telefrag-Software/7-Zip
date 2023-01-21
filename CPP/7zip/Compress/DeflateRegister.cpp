// DeflateRegister.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "DeflateDecoder.h"
#if !defined(EXTRACT_ONLY) && !defined(DEFLATE_EXTRACT_ONLY)
#include "DeflateEncoder.h"
#endif

namespace NCompress {
namespace NDeflate {

static void * CreateDec() {
  return (void *)(ICompressCoder *)(new NDecoder::CCOMCoder);
}

#if !defined(EXTRACT_ONLY) && !defined(DEFLATE_EXTRACT_ONLY)

static void * CreateEnc() {
  return (void *)(ICompressCoder *)(new NDecoder::CCOMCoder);
}

#else
#define CreateEnc NULL
#endif

static const CCodecInfo s_codecInfo_Deflate = {
  CreateDec,
  CreateEnc,
  0x40108,
  "Deflate",
  1,
  false
};

void NDecoder::CCOMCoder::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_Deflate);
    s_registered = true;
  }
}

}}

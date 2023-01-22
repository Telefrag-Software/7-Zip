// BZip2Register.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "BZip2Decoder.h"
#if !defined(EXTRACT_ONLY) && !defined(BZIP2_EXTRACT_ONLY)
#include "BZip2Encoder.h"
#endif

namespace NCompress {
namespace NBZip2 {

static void * CreateDec() {
  return (void *)(ICompressCoder *)(new CDecoder);
}

#if !defined(EXTRACT_ONLY) && !defined(BZIP2_EXTRACT_ONLY)

static void * CreateEnc() {
  return (void *)(ICompressCoder *)(new CEncoder);
}

#else
#define CreateEnc NULL
#endif

static const CCodecInfo s_codecInfo_BZip2 = {
  CreateDec,
  CreateEnc,
  0x40202,
  "BZip2",
  1,
  false
};

void CDecoder::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_BZip2);
    s_registered = true;
  }
}

}}

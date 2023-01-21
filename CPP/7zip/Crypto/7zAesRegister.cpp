// 7zAesRegister.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "7zAes.h"

namespace NCrypto {
namespace N7z {

static void * _7zAES_CreateDec() {
  return (void *)(ICompressFilter *)(new CDecoder);
}

static void * _7zAES_CreateEnc() {
  return (void *)(ICompressFilter *)(new CEncoder);
}

static const CCodecInfo s_codecInfo_7zAES = {
  _7zAES_CreateDec,
  _7zAES_CreateEnc,
  0x6F10701,
  "7zAES",
  1,
  true
};

void CDecoder::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_7zAES);
    s_registered = true;
  }
}

}}

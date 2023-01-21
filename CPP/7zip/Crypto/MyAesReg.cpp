// MyAesReg.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "MyAes.h"

namespace NCrypto {

#ifndef _SFX

static void * AES256CBC_CreateDec() {
  return (void *)(ICompressFilter *)(new CAesCoder(false, 32, false));
}

static void * AES256CBC_CreateEnc() {
  return (void *)(ICompressFilter *)(new CAesCoder(true, 32, false));
}

static const CCodecInfo s_codecInfo_AES256CBC = {
  AES256CBC_CreateDec,
  AES256CBC_CreateEnc,
  0x6F00100 | ((32 - 16) * 8) | 4,
  "AES256CBC",
  1,
  true
};

void CAesCoder::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_AES256CBC);
    s_registered = true;
  }
}

#endif

}

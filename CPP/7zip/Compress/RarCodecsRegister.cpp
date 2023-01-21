// RarCodecsRegister.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "Rar1Decoder.h"
#include "Rar2Decoder.h"
#include "Rar3Decoder.h"
#include "Rar5Decoder.h"

namespace NCompress {

static void * CreateCodec1() {
  return (void *)(ICompressFilter *)(new NRar1::CDecoder());
}

static void * CreateCodec2() {
  return (void *)(ICompressFilter *)(new NRar2::CDecoder());
}

static void * CreateCodec3() {
  return (void *)(ICompressFilter *)(new NRar3::CDecoder());
}

static void * CreateCodec5() {
  return (void *)(ICompressFilter *)(new NRar5::CDecoder());
}

static const CCodecInfo s_codecInfo_RAR1 = {
  CreateCodec1,
  nullptr,
  0x40301,
  "Rar",
  1,
  false
};

static const CCodecInfo s_codecInfo_RAR2 = {
  CreateCodec2,
  nullptr,
  0x40302,
  "Rar",
  1,
  false
};

static const CCodecInfo s_codecInfo_RAR3 = {
  CreateCodec3,
  nullptr,
  0x40303,
  "Rar",
  1,
  false
};

static const CCodecInfo s_codecInfo_RAR5 = {
  CreateCodec5,
  nullptr,
  0x40304,
  "Rar",
  1,
  false
};

void NRar1::CDecoder::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_RAR1);
    s_registered = true;
  }
}

void NRar2::CDecoder::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_RAR2);
    s_registered = true;
  }
}

void NRar3::CDecoder::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_RAR3);
    s_registered = true;
  }
}

void NRar5::CDecoder::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_RAR5);
    s_registered = true;
  }
}

}

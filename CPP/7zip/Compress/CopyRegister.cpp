// CopyRegister.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "CopyCoder.h"

namespace NCompress {

static void * CreateCodec() {
  return (void *)(ICompressCoder *)(new CCopyCoder());
}

static const CCodecInfo s_codecInfo_Copy = {
  CreateCodec,
  CreateCodec,
  0,
  "Copy",
  1,
  false
};

void CCopyCoder::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_Copy);
    s_registered = true;
  }
}

}

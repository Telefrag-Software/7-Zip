// ByteSwap.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "ByteSwap2Filter.h"
#include "ByteSwap4Filter.h"

namespace NCompress {
namespace NByteSwap {

static void * CreateFilter2() {
  return (void *)(ICompressFilter *)(new CByteSwap2());
}

static void * CreateFilter4() {
  return (void *)(ICompressFilter *)(new CByteSwap4());
}

static const CCodecInfo s_codecInfo_ByteSwap2 {
  CreateFilter2,
  CreateFilter2,
  0x20302,
  "Swap2",
  1,
  true
};

static const CCodecInfo s_codecInfo_ByteSwap4 {
  CreateFilter4,
  CreateFilter4,
  0x20304,
  "Swap4",
  1,
  true
};

void CByteSwap2::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_ByteSwap2);
    s_registered = true;
  }
}

void CByteSwap4::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_ByteSwap4);
    s_registered = true;
  }
}

}}

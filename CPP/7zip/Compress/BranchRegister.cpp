// BranchRegister.cpp

#include "StdAfx.h"

#include "../../../C/Bra.h"

#include "../Common/RegisterCodec.h"

#include "BranchMisc.h"

namespace NCompress {
namespace NBranch {

static void * CreateBra_Decoder_PPC() {
  return (void *)(ICompressFilter *)(new CCoder(PPC_Convert, false));
}

static void * CreateBra_Encoder_PPC() {
  return (void *)(ICompressFilter *)(new CCoder(PPC_Convert, true));
}

static void * CreateBra_Decoder_IA64() {
  return (void *)(ICompressFilter *)(new CCoder(IA64_Convert, false));
}

static void * CreateBra_Encoder_IA64() {
  return (void *)(ICompressFilter *)(new CCoder(IA64_Convert, true));
}

static void * CreateBra_Decoder_ARM() {
  return (void *)(ICompressFilter *)(new CCoder(ARM_Convert, false));
}

static void * CreateBra_Encoder_ARM() {
  return (void *)(ICompressFilter *)(new CCoder(ARM_Convert, true));
}

static void * CreateBra_Decoder_ARMT() {
  return (void *)(ICompressFilter *)(new CCoder(ARMT_Convert, false));
}

static void * CreateBra_Encoder_ARMT() {
  return (void *)(ICompressFilter *)(new CCoder(ARMT_Convert, true));
}

static void * CreateBra_Decoder_SPARC() {
  return (void *)(ICompressFilter *)(new CCoder(SPARC_Convert, false));
}

static void * CreateBra_Encoder_SPARC() {
  return (void *)(ICompressFilter *)(new CCoder(SPARC_Convert, true));
}

static const CCodecInfo s_codecInfo_PPC = {
  CreateBra_Decoder_PPC,
  CreateBra_Encoder_PPC,
  0x3030000 + 0x205,
  "PPC",
  1,
  true
};

static const CCodecInfo s_codecInfo_IA64 = {
  CreateBra_Decoder_IA64,
  CreateBra_Encoder_IA64,
  0x3030000 + 0x401,
  "IA64",
  1,
  true
};

static const CCodecInfo s_codecInfo_ARM = {
  CreateBra_Decoder_ARM,
  CreateBra_Encoder_ARM,
  0x3030000 + 0x501,
  "ARM",
  1,
  true
};

static const CCodecInfo s_codecInfo_ARMT = {
  CreateBra_Decoder_ARMT,
  CreateBra_Encoder_ARMT,
  0x3030000 + 0x701,
  "ARMT",
  1,
  true
};

static const CCodecInfo s_codecInfo_SPARC = {
  CreateBra_Decoder_SPARC,
  CreateBra_Encoder_SPARC,
  0x3030000 + 0x805,
  "SPARC",
  1,
  true
};

void CCoder::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterCodec(&s_codecInfo_PPC);
    RegisterCodec(&s_codecInfo_IA64);
    RegisterCodec(&s_codecInfo_ARM);
    RegisterCodec(&s_codecInfo_ARMT);
    RegisterCodec(&s_codecInfo_SPARC);
    s_registered = true;
  }
}

}}

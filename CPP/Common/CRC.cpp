// Common/CRC.cpp

#include "StdAfx.h"

#include "CRCHasher.h"

namespace NHash {

void CCrcHasher::Initialize() {
  static bool s_initialized = false;

  if(!s_initialized) {
    CrcGenerateTable();
    s_initialized = true;
  }
}

}

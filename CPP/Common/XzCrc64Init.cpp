// XzCrc64Init.cpp

#include "StdAfx.h"

#include "XzCrc64Hasher.h"

namespace NHash {

void CXzCrc64Hasher::Initialize() {
  static bool s_initialized = false;

  if(!s_initialized) {
    Crc64GenerateTable();
    s_initialized = true;
  }
}

}

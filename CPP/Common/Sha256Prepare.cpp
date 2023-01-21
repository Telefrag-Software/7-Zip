// Sha256Prepare.cpp

#include "StdAfx.h"

#include "Sha256Hasher.h"

namespace NHash {

void CSha256Hasher::Prepare() {
  static bool s_prepared = false;

  if(!s_prepared) {
    Sha256Prepare();
    s_prepared = true;
  }
}

}

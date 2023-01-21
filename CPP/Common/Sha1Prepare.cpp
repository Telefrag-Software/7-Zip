// Sha1Prepare.cpp

#include "StdAfx.h"

#include "Sha1Hasher.h"

namespace NHash {

void CSha1Hasher::Prepare() {
  static bool s_prepared = false;

  if(!s_prepared) {
    Sha1Prepare();
    s_prepared = true;
  }
}

}

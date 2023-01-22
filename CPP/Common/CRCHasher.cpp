// Common/CRCHasher.cpp

#include "CRCHasher.h"

namespace NHash {

bool CCrcHasher::SetFunctions(UInt32 tSize)
{
  CRC_FUNC f = NULL;
       if (tSize ==  0) f = g_CrcUpdate;
  else if (tSize ==  1) f = CrcUpdateT1;
  else if (tSize ==  4) f = g_CrcUpdateT4;
  else if (tSize ==  8) f = g_CrcUpdateT8;
  else if (tSize == 32) f = g_CrcUpdateT0_32;
  else if (tSize == 64) f = g_CrcUpdateT0_64;
  
  if (!f)
  {
    _updateFunc = g_CrcUpdate;
    return false;
  }
  _updateFunc = f;
  return true;
}

STDMETHODIMP CCrcHasher::SetCoderProperties(const PROPID *propIDs, const PROPVARIANT *coderProps, UInt32 numProps)
{
  for (UInt32 i = 0; i < numProps; i++)
  {
    const PROPVARIANT &prop = coderProps[i];
    if (propIDs[i] == NCoderPropID::kDefaultProp)
    {
      if (prop.vt != VT_UI4)
        return E_INVALIDARG;
      if (!SetFunctions(prop.ulVal))
        return E_NOTIMPL;
    }
  }
  return S_OK;
}

STDMETHODIMP_(void) CCrcHasher::Init() throw()
{
  _crc = CRC_INIT_VAL;
}

STDMETHODIMP_(void) CCrcHasher::Update(const void *data, UInt32 size) throw()
{
  _crc = _updateFunc(_crc, data, size, g_CrcTable);
}

STDMETHODIMP_(void) CCrcHasher::Final(Byte *digest) throw()
{
  UInt32 val = CRC_GET_DIGEST(_crc);
  SetUi32(digest, val);
}

}

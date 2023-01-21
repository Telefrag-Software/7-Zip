// Common/Sha256Hasher.cpp

#include "Sha256Hasher.h"

namespace NHash {

STDMETHODIMP_(void) CSha256Hasher::Init() throw()
{
  Sha256_InitState(Sha());
}

STDMETHODIMP_(void) CSha256Hasher::Update(const void *data, UInt32 size) throw()
{
  Sha256_Update(Sha(), (const Byte *)data, size);
}

STDMETHODIMP_(void) CSha256Hasher::Final(Byte *digest) throw()
{
  Sha256_Final(Sha(), digest);
}

STDMETHODIMP CSha256Hasher::SetCoderProperties(const PROPID *propIDs, const PROPVARIANT *coderProps, UInt32 numProps)
{
  unsigned algo = 0;
  for (UInt32 i = 0; i < numProps; i++)
  {
    const PROPVARIANT &prop = coderProps[i];
    if (propIDs[i] == NCoderPropID::kDefaultProp)
    {
      if (prop.vt != VT_UI4)
        return E_INVALIDARG;
      if (prop.ulVal > 2)
        return E_NOTIMPL;
      algo = (unsigned)prop.ulVal;
    }
  }
  if (!Sha256_SetFunction(Sha(), algo))
    return E_NOTIMPL;
  return S_OK;
}

}

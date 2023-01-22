// Common/Sha1Hasher.cpp

#include "Sha1Hasher.h"

namespace NHash {

STDMETHODIMP_(void) CSha1Hasher::Init() throw()
{
  Sha1_InitState(Sha());
}

STDMETHODIMP_(void) CSha1Hasher::Update(const void *data, UInt32 size) throw()
{
  Sha1_Update(Sha(), (const Byte *)data, size);
}

STDMETHODIMP_(void) CSha1Hasher::Final(Byte *digest) throw()
{
  Sha1_Final(Sha(), digest);
}


STDMETHODIMP CSha1Hasher::SetCoderProperties(const PROPID *propIDs, const PROPVARIANT *coderProps, UInt32 numProps)
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
  if (!Sha1_SetFunction(Sha(), algo))
    return E_NOTIMPL;
  return S_OK;
}

}

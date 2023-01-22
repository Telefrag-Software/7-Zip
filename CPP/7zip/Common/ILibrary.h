// ILibrary.h

#include "../../Windows/PropVariant.h"

#include "RegisterArc.h"

namespace SevenZip {

void RegisterFormats();
HRESULT CreateArchiver(const GUID *clsid, const GUID *iid, void **outObject);
HRESULT GetHandlerProperty2(UInt32 formatIndex, PROPID propID, PROPVARIANT *value);
HRESULT GetHandlerProperty(PROPID propID, PROPVARIANT *value);
HRESULT GetNumberOfFormats(UINT32 *numFormats);
HRESULT GetIsArc(UInt32 formatIndex, Func_IsArc *isArc);
HRESULT CreateObject(const GUID *clsid, const GUID *iid, void **outObject);
HRESULT SetLargePageMode();
HRESULT SetCaseSensitive(Int32 caseSensitive);

}

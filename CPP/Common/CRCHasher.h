// Common/CRCHasher.h

#ifndef __CRC_HASHER_H
#define __CRC_HASHER_H

#include "../../C/7zCrc.h"
#include "../../C/CpuArch.h"
#include "../7zip/ICoder.h"
#include "../Common/MyCom.h"

namespace NHash {

EXTERN_C_BEGIN

typedef UInt32 (MY_FAST_CALL *CRC_FUNC)(UInt32 v, const void *data, size_t size, const UInt32 *table);

UInt32 MY_FAST_CALL CrcUpdateT1(UInt32 v, const void *data, size_t size, const UInt32 *table);

extern CRC_FUNC g_CrcUpdate;
extern CRC_FUNC g_CrcUpdateT4;
extern CRC_FUNC g_CrcUpdateT8;
extern CRC_FUNC g_CrcUpdateT0_32;
extern CRC_FUNC g_CrcUpdateT0_64;

EXTERN_C_END

class CCrcHasher:
  public IHasher,
  public ICompressSetCoderProperties,
  public CMyUnknownImp
{
  UInt32 _crc;
  CRC_FUNC _updateFunc;
  Byte mtDummy[1 << 7];
  
  bool SetFunctions(UInt32 tSize);
public:
  static void Initialize();
  static void Register();

  CCrcHasher(): _crc(CRC_INIT_VAL) { SetFunctions(0); }

  MY_UNKNOWN_IMP2(IHasher, ICompressSetCoderProperties)
  INTERFACE_IHasher(;)
  STDMETHOD(SetCoderProperties)(const PROPID *propIDs, const PROPVARIANT *props, UInt32 numProps);
};

}

#endif // __CRC_HASHER_H

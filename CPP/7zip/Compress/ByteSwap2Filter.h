// Compress/ByteSwap2Filter.h

#ifndef __BYTE_SWAP_2_FILTER_H
#define __BYTE_SWAP_2_FILTER_H

#include "../../Common/MyCom.h"
#include "../ICoder.h"

namespace NCompress {
namespace NByteSwap {

class CByteSwap2:
  public ICompressFilter,
  public CMyUnknownImp
{
public:
  static void Register();

  MY_UNKNOWN_IMP1(ICompressFilter);
  INTERFACE_ICompressFilter(;)
};

}}

#endif // __BYTE_SWAP_2_FILTER_H

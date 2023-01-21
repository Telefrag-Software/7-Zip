// IhexHandler.h

#ifndef __IHEX_HANDLER_H
#define __IHEX_HANDLER_H

#include "../../Common/MyVector.h"
#include "../../Common/DynamicBuffer.h"

namespace NArchive {
namespace NIhex {

/* We still don't support files with custom record types: 20, 22: used by Samsung */

struct CBlock
{
  CByteDynamicBuffer Data;
  UInt32 Offset;
};

class CHandler:
  public IInArchive,
  public CMyUnknownImp
{
  bool _isArc;
  bool _needMoreInput;
  bool _dataError;
  
  UInt64 _phySize;

  CObjectVector<CBlock> _blocks;
public:
  static void Register();

  MY_UNKNOWN_IMP1(IInArchive)
  INTERFACE_IInArchive(;)
};

}}

#endif // __IHEX_HANDLER_H

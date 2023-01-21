// Base64Handler.h

#ifndef __BASE_64_HANDLER_H
#define __BASE_64_HANDLER_H

#include "../../Common/MyBuffer.h"

enum EBase64Res
{
  k_Base64_RES_MaybeFinished,
  k_Base64_RES_Finished,
  k_Base64_RES_NeedMoreInput,
  k_Base64_RES_UnexpectedChar
};

namespace NArchive {
namespace NBase64 {

class CHandler:
  public IInArchive,
  public CMyUnknownImp
{
  bool _isArc;
  UInt64 _phySize;
  size_t _size;
  EBase64Res _sres;
  CByteBuffer _data;
public:
  static void Register();

  MY_UNKNOWN_IMP1(IInArchive)
  INTERFACE_IInArchive(;)
};

}}

#endif // __BASE_64_HANDLER_H

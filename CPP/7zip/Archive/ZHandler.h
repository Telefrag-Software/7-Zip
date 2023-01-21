// ZHandler.h

#ifndef __Z_HANDLER_H
#define __Z_HANDLER_H

#include "../../Common/MyCom.h"

namespace NArchive {
namespace NZ {

class CHandler:
  public IInArchive,
  public CMyUnknownImp
{
  CMyComPtr<IInStream> _stream;
  UInt64 _packSize;
  // UInt64 _unpackSize;
  // bool _unpackSize_Defined;
public:
  static void Register();

  MY_UNKNOWN_IMP1(IInArchive)
  INTERFACE_IInArchive(;)
};

/*
class CCompressProgressInfoImp:
  public ICompressProgressInfo,
  public CMyUnknownImp
{
  CMyComPtr<IArchiveOpenCallback> Callback;
public:
  MY_UNKNOWN_IMP1(ICompressProgressInfo)
  STDMETHOD(SetRatioInfo)(const UInt64 *inSize, const UInt64 *outSize);
  void Init(IArchiveOpenCallback *callback);
};
*/

}}

#endif // __Z_HANDLER_H

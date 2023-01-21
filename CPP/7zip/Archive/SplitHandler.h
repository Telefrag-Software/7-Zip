// SplitHandler.h

#ifndef __SPLIT_HANDLER_H
#define __SPLIT_HANDLER_H

#include "../../Common/MyVector.h"

namespace NArchive {
namespace NSplit {

class CHandler:
  public IInArchive,
  public IInArchiveGetStream,
  public CMyUnknownImp
{
  CObjectVector<CMyComPtr<IInStream> > _streams;
  CRecordVector<UInt64> _sizes;
  UString _subName;
  UInt64 _totalSize;

  HRESULT Open2(IInStream *stream, IArchiveOpenCallback *callback);
public:
  static void Register();

  MY_UNKNOWN_IMP2(IInArchive, IInArchiveGetStream)
  INTERFACE_IInArchive(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
};

struct CSeqName
{
  UString _unchangedPart;
  UString _changedPart;
  bool _splitStyle;

  bool GetNextName(UString &s);
};

}}

#endif // __SPLIT_HANDLER_H

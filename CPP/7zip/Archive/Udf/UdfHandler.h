// UdfHandler.h

#ifndef __UDF_HANDLER_H
#define __UDF_HANDLER_H

#include "../../../Common/MyCom.h"

#include "../IArchive.h"

#include "UdfIn.h"

namespace NArchive {
namespace NUdf {

struct CRef2
{
  unsigned Vol;
  unsigned Fs;
  unsigned Ref;
};

class CHandler:
  public IInArchive,
  public IInArchiveGetStream,
  public CMyUnknownImp
{
  CMyComPtr<IInStream> _inStream;
  CInArchive _archive;
  CRecordVector<CRef2> _refs2;
public:
  static void Register();

  MY_UNKNOWN_IMP2(IInArchive, IInArchiveGetStream)
  INTERFACE_IInArchive(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
};

class CProgressImp: public CProgressVirt
{
  CMyComPtr<IArchiveOpenCallback> _callback;
  UInt64 _numFiles;
  UInt64 _numBytes;
public:
  HRESULT SetTotal(UInt64 numBytes);
  HRESULT SetCompleted(UInt64 numFiles, UInt64 numBytes);
  HRESULT SetCompleted();
  CProgressImp(IArchiveOpenCallback *callback);
};

}}

#endif // __UDF_HANDLER_H

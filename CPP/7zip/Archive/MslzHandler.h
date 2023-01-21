// MslzHandler.h

#ifndef __MSLZ_HANDLER_H
#define __MSLZ_HANDLER_H

#include "../../Common/MyCom.h"

namespace NArchive {
namespace NMslz {

class CHandler:
  public IInArchive,
  public IArchiveOpenSeq,
  public CMyUnknownImp
{
  CMyComPtr<IInStream> _inStream;
  CMyComPtr<ISequentialInStream> _seqStream;

  bool _isArc;
  bool _needSeekToStart;
  bool _dataAfterEnd;
  bool _needMoreInput;

  bool _packSize_Defined;
  bool _unpackSize_Defined;

  UInt32 _unpackSize;
  UInt64 _packSize;
  UInt64 _originalFileSize;
  UString _name;

  void ParseName(Byte replaceByte, IArchiveOpenCallback *callback);
public:
  static void Register();

  MY_UNKNOWN_IMP2(IInArchive, IArchiveOpenSeq)
  INTERFACE_IInArchive(;)
  STDMETHOD(OpenSeq)(ISequentialInStream *stream);
};



}}

#endif // __MSLZ_HANDLER_H

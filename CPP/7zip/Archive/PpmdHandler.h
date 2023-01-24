// PpmdHandler.h

#ifndef __PPMD_HANDLER_H
#define __PPMD_HANDLER_H

#include "../../../C/Ppmd7.h"
#include "../../../C/Ppmd8.h"
#include "../../Common/MyCom.h"
#include "../../Common/MyString.h"
#include "../../Windows/PropVariant.h"
#include "../Common/CWrappers.h"

namespace NArchive {
namespace NPpmd {

struct CBuf
{
  Byte *Buf;

  CBuf();
  ~CBuf();
  bool Alloc();
};

struct CItem
{
  UInt32 Attrib;
  UInt32 Time;
  AString Name;

  unsigned Order;
  unsigned MemInMB;
  unsigned Ver;
  unsigned Restor;

  HRESULT ReadHeader(ISequentialInStream *s, UInt32 &headerSize);
  bool IsSupported() const;
};

class CHandler:
  public IInArchive,
  public IArchiveOpenSeq,
  public CMyUnknownImp
{
  CItem _item;
  UInt32 _headerSize;
  bool _packSize_Defined;
  UInt64 _packSize;
  CMyComPtr<ISequentialInStream> _stream;

  void GetVersion(NWindows::NCOM::CPropVariant &prop);

public:
  static void Register();

  MY_UNKNOWN_IMP2(IInArchive, IArchiveOpenSeq)
  INTERFACE_IInArchive(;)
  STDMETHOD(OpenSeq)(ISequentialInStream *stream);
};

struct CPpmdCpp
{
  unsigned Ver;
  CPpmd7 _ppmd7;
  CPpmd8 _ppmd8;

  CPpmdCpp(unsigned version);
  ~CPpmdCpp();

  bool Alloc(UInt32 memInMB);
  void Init(unsigned order, unsigned restor);
  bool InitRc(CByteInBufWrap *inStream);
  bool IsFinishedOK();
};

}}

#endif // __PPMD_HANDLER_H

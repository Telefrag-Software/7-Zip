// CpioHandler.h

#ifndef __CPIO_HANDLER_H
#define __CPIO_HANDLER_H

#include "../../Common/MyCom.h"
#include "../../Common/MyLinux.h"
#include "../../Common/MyString.h"
#include "../../Common/MyVector.h"

namespace NArchive {
namespace NCpio {

static const char * const kName_TRAILER = "TRAILER!!!";

enum EType
{
  k_Type_BinLe,
  k_Type_BinBe,
  k_Type_Oct,
  k_Type_Hex,
  k_Type_HexCrc
};

struct CItem
{
  AString Name;
  UInt32 inode;
  UInt32 Mode;
  UInt32 UID;
  UInt32 GID;
  UInt64 Size;
  UInt32 MTime;

  UInt32 NumLinks;
  UInt32 DevMajor;
  UInt32 DevMinor;
  UInt32 RDevMajor;
  UInt32 RDevMinor;
  UInt32 ChkSum;

  UInt32 Align;
  EType Type;

  UInt32 HeaderSize;
  UInt64 HeaderPos;

  bool IsBin() const { return Type == k_Type_BinLe || Type == k_Type_BinBe; }
  bool IsCrcFormat() const { return Type == k_Type_HexCrc; }
  bool IsDir() const { return MY_LIN_S_ISDIR(Mode); }
  bool IsTrailer() const { return strcmp(Name, kName_TRAILER) == 0; }
  UInt64 GetDataPosition() const { return HeaderPos + HeaderSize; }
};

enum EErrorType
{
  k_ErrorType_OK,
  k_ErrorType_Corrupted,
  k_ErrorType_UnexpectedEnd
};

struct CInArchive
{
  ISequentialInStream *Stream;
  UInt64 Processed;

  HRESULT Read(void *data, size_t *size);
  HRESULT GetNextItem(CItem &item, EErrorType &errorType);
};

class CHandler:
  public IInArchive,
  public IInArchiveGetStream,
  public CMyUnknownImp
{
  CObjectVector<CItem> _items;
  CMyComPtr<IInStream> _stream;
  UInt64 _phySize;
  EType _Type;
  EErrorType _error;
  bool _isArc;
public:
  static void Register();

  MY_UNKNOWN_IMP2(IInArchive, IInArchiveGetStream)
  INTERFACE_IInArchive(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
};

}}

#endif // __CPIO_HANDLER_H

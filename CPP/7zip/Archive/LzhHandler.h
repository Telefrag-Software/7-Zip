// LzhHandler.h

#ifndef __LZH_HANDLER_H
#define __LZH_HANDLER_H

#include "../../Common/MyCom.h"
#include "../../Common/MyString.h"
#include "../../Common/MyVector.h"

namespace NArchive {
namespace NLzh{

const unsigned kMethodIdSize = 5;

struct CExtension
{
  Byte Type;
  CByteBuffer Data;
  
  AString GetString() const;
};

struct CItem
{
  AString Name;
  Byte Method[kMethodIdSize];
  Byte Attributes;
  Byte Level;
  Byte OsId;
  UInt32 PackSize;
  UInt32 Size;
  UInt32 ModifiedTime;
  UInt16 CRC;
  CObjectVector<CExtension> Extensions;

  bool IsValidMethod() const;
  bool IsLhMethod() const;
  bool IsDir() const;

  bool IsCopyMethod() const;

  bool IsLh1GroupMethod() const;

  bool IsLh4GroupMethod() const;

  unsigned GetNumDictBits() const;

  int FindExt(Byte type) const;

  bool GetUnixTime(UInt32 &value) const;

  AString GetDirName() const;

  AString GetFileName() const;

  AString GetName() const;
};

class COutStreamWithCRC:
  public ISequentialOutStream,
  public CMyUnknownImp
{
public:
  MY_UNKNOWN_IMP

  STDMETHOD(Write)(const void *data, UInt32 size, UInt32 *processedSize);
private:
  UInt32 _crc;
  CMyComPtr<ISequentialOutStream> _stream;
public:
  void Init(ISequentialOutStream *stream);
  void ReleaseStream();
  UInt32 GetCRC() const;
};

struct CItemEx: public CItem
{
  UInt64 DataPosition;
};

class CHandler:
  public IInArchive,
  public CMyUnknownImp
{
  CObjectVector<CItemEx> _items;
  CMyComPtr<IInStream> _stream;
  UInt64 _phySize;
  UInt32 _errorFlags;
  bool _isArc;
public:
  static void Register();

  MY_UNKNOWN_IMP1(IInArchive)
  INTERFACE_IInArchive(;)
  CHandler();
};

}}

#endif // __LZH_HANDLER_H

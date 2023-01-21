// GptHandler.cpp

#ifndef __GPT_HANDLER_H
#define __GPT_HANDLER_H

#include "../../Common/MyVector.h"

namespace NArchive {
namespace NGpt {

static const unsigned kNameLen = 36;

struct CPartition
{
  Byte Type[16];
  Byte Id[16];
  UInt64 FirstLba;
  UInt64 LastLba;
  UInt64 Flags;
  Byte Name[kNameLen * 2];

  bool IsUnused() const;

  UInt64 GetSize() const;
  UInt64 GetPos() const;
  UInt64 GetEnd() const;

  void Parse(const Byte *p);
};

struct CPartType
{
  UInt32 Id;
  const char *Ext;
  const char *Type;
};

class CHandler: public CHandlerCont
{
  CRecordVector<CPartition> _items;
  UInt64 _totalSize;
  Byte Guid[16];

  CByteBuffer _buffer;

  HRESULT Open2(IInStream *stream);

  virtual int GetItem_ExtractInfo(UInt32 index, UInt64 &pos, UInt64 &size) const;

public:
  static void Register();

  INTERFACE_IInArchive_Cont(;)
};

}}

#endif // __GPT_HANDLER_H

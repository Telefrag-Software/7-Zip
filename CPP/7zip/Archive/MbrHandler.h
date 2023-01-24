// MbrHandler.h

#ifndef __MBR_HANDLER_H
#define __MBR_HANDLER_H

#include "../../Common/MyBuffer.h"
#include "../../Common/MyVector.h"
#include "../../Windows/PropVariant.h"

namespace NArchive {
namespace NMbr {

struct CChs
{
  Byte Head;
  Byte SectCyl;
  Byte Cyl8;

  UInt32 GetSector() const;
  UInt32 GetCyl() const;
  void ToString(NWindows::NCOM::CPropVariant &prop) const;

  void Parse(const Byte *p);
  bool Check() const;
};

struct CPartition
{
  Byte Status;
  CChs BeginChs;
  Byte Type;
  CChs EndChs;
  UInt32 Lba;
  UInt32 NumBlocks;

  CPartition();

  bool IsEmpty() const;
  bool IsExtended() const;
  UInt32 GetLimit() const;
  // bool IsActive() const;
  UInt64 GetPos() const;
  UInt64 GetSize() const;

  bool CheckLbaLimits() const;
  bool Parse(const Byte *p);

  #ifdef SHOW_DEBUG_INFO
  void Print() const;
  #endif
};

struct CPartType
{
  UInt32 Id;
  const char *Ext;
  const char *Name;
};

struct CItem
{
  bool IsReal;
  bool IsPrim;
  UInt64 Size;
  CPartition Part;
};

class CHandler: public CHandlerCont
{
  CObjectVector<CItem> _items;
  UInt64 _totalSize;
  CByteBuffer _buffer;

  virtual int GetItem_ExtractInfo(UInt32 index, UInt64 &pos, UInt64 &size) const;

  HRESULT ReadTables(IInStream *stream, UInt32 baseLba, UInt32 lba, unsigned level);
public:
  static void Register();

  INTERFACE_IInArchive_Cont(;)
};


}}

#endif // __MBR_HANDLER_H

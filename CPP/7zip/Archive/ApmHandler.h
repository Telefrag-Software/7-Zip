// ApmHandler.h

#ifndef __APM_HANDLER_H_
#define __APM_HANDLER_H_

#include "../../Common/MyVector.h"
#include "HandlerCont.h"

namespace NArchive {
namespace NApm {

struct CItem
{
  UInt32 StartBlock;
  UInt32 NumBlocks;
  char Name[32];
  char Type[32];
  /*
  UInt32 DataStartBlock;
  UInt32 NumDataBlocks;
  UInt32 Status;
  UInt32 BootStartBlock;
  UInt32 BootSize;
  UInt32 BootAddr;
  UInt32 BootEntry;
  UInt32 BootChecksum;
  char Processor[16];
  */

  bool Parse(const Byte *p, UInt32 &numBlocksInMap);
};

class CHandler: public CHandlerCont
{
  CRecordVector<CItem> _items;
  unsigned _blockSizeLog;
  UInt32 _numBlocks;
  UInt64 _phySize;
  bool _isArc;

  HRESULT ReadTables(IInStream *stream);
  UInt64 BlocksToBytes(UInt32 i) const { return (UInt64)i << _blockSizeLog; }

  virtual int GetItem_ExtractInfo(UInt32 index, UInt64 &pos, UInt64 &size) const
  {
    const CItem &item = _items[index];
    pos = BlocksToBytes(item.StartBlock);
    size = BlocksToBytes(item.NumBlocks);
    return NExtract::NOperationResult::kOK;
  }

public:
  static void Register();

  INTERFACE_IInArchive_Cont(;)
};

}}

#endif // __APM_HANDLER_H_

// MubHandler.h

#ifndef __MUBHANDLER_H
#define __MUBHANDLER_H

namespace NArchive {
namespace NMub {

struct CItem
{
  UInt32 Type;
  UInt32 SubType;
  UInt32 Offset;
  UInt32 Size;
  // UInt32 Align;
};

static const UInt32 kNumFilesMax = 10;

class CHandler: public CHandlerCont
{
  // UInt64 _startPos;
  UInt64 _phySize;
  UInt32 _numItems;
  bool _bigEndian;
  CItem _items[kNumFilesMax];

  HRESULT Open2(IInStream *stream);

  virtual int GetItem_ExtractInfo(UInt32 index, UInt64 &pos, UInt64 &size) const;

public:
  static void Register();

  INTERFACE_IInArchive_Cont(;)
};


}}

#endif // __MUBHANDLER_H

// ArHandler.h

#ifndef __AR_HANDLER_H
#define __AR_HANDLER_H

#include "../../Common/MyCom.h"
#include "../../Common/MyString.h"

namespace NArchive {
namespace NAr {

enum EType
{
  kType_Ar,
  kType_ALib,
  kType_Deb,
  kType_Lib
};

enum ESubType
{
  kSubType_None,
  kSubType_BSD
};

/*
struct CHeader
{
  char Name[kNameSize];
  char MTime[kTimeSize];
  char User[kUserSize];
  char Group[kUserSize];
  char Mode[kModeSize];
  char Size[kSizeSize];
  char Quote;
  char NewLine;
};
*/

struct CItem
{
  AString Name;
  UInt64 Size;
  UInt32 MTime;
  UInt32 User;
  UInt32 Group;
  UInt32 Mode;
  
  UInt64 HeaderPos;
  UInt64 HeaderSize;

  int TextFileIndex;
  int SameNameIndex;

  CItem();
  UInt64 GetDataPos() const;
};

class CInArchive
{
  CMyComPtr<IInStream> m_Stream;
 
public:
  UInt64 Position;
  ESubType SubType;
 
  HRESULT GetNextItem(CItem &itemInfo, bool &filled);
  HRESULT Open(IInStream *inStream);
  HRESULT SkipData(UInt64 dataSize);
};

class CHandler:
  public IInArchive,
  public IInArchiveGetStream,
  public CMyUnknownImp
{
  CObjectVector<CItem> _items;
  CMyComPtr<IInStream> _stream;
  Int32 _mainSubfile;
  UInt64 _phySize;

  EType _type;
  ESubType _subType;
  int _longNames_FileIndex;
  AString _libFiles[2];
  unsigned _numLibFiles;
  AString _errorMessage;
  bool _isArc;
  

  void UpdateErrorMessage(const char *s);
  
  HRESULT ParseLongNames(IInStream *stream);
  void ChangeDuplicateNames();
  int FindItem(UInt32 offset) const;
  HRESULT AddFunc(UInt32 offset, const Byte *data, size_t size, size_t &pos);
  HRESULT ParseLibSymbols(IInStream *stream, unsigned fileIndex);
public:
  static void Register();

  MY_UNKNOWN_IMP2(IInArchive, IInArchiveGetStream)
  INTERFACE_IInArchive(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
};

}}

#endif __AR_HANDLER_H

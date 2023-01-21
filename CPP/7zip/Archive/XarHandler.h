// XarHandler.h

#ifndef __XAR_HANDLER_H
#define __XAR_HANDLER_H

#include "../../Common/MyCom.h"
#include "../../Common/MyString.h"
#include "../../Common/MyVector.h"

namespace NArchive {
namespace NXar {

struct CFile
{
  AString Name;
  AString Method;
  UInt64 Size;
  UInt64 PackSize;
  UInt64 Offset;

  UInt64 CTime;
  UInt64 MTime;
  UInt64 ATime;
  UInt32 Mode;

  AString User;
  AString Group;

  bool IsDir;
  bool HasData;
  bool ModeDefined;
  bool Sha1IsDefined;
  // bool packSha1IsDefined;

  Byte Sha1[SHA1_DIGEST_SIZE];
  // Byte packSha1[SHA1_DIGEST_SIZE];

  int Parent;

  CFile();

  bool IsCopyMethod() const;

  void UpdateTotalPackSize(UInt64 &totalSize) const;
};

class CHandler:
  public IInArchive,
  public IInArchiveGetStream,
  public CMyUnknownImp
{
  UInt64 _dataStartPos;
  CMyComPtr<IInStream> _inStream;
  CByteArr _xml;
  size_t _xmlLen;
  CObjectVector<CFile> _files;
  // UInt32 _checkSumAlgo;
  UInt64 _phySize;
  Int32 _mainSubfile;
  bool _is_pkg;

  HRESULT Open2(IInStream *stream);
  HRESULT Extract(IInStream *stream);
public:
  static void Register();

  MY_UNKNOWN_IMP2(IInArchive, IInArchiveGetStream)
  INTERFACE_IInArchive(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
};

}}

#endif // __XAR_HANDLER_H

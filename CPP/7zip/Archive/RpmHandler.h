// RpmHandler.h

#ifndef __RPM_HANDLER_H
#define __RPM_HANDLER_H

#include "../../Common/MyString.h"
#include "../../Common/MyVector.h"
#include "../../Windows/PropVariant.h"

namespace NArchive {
namespace NRpm {

static const unsigned kNameSize = 66;
static const unsigned kLeadSize = kNameSize + 30;
static const unsigned k_HeaderSig_Size = 16;
static const unsigned k_Entry_Size = 16;

struct CLead
{
  unsigned char Major;
  unsigned char Minor;
  UInt16 Type;
  UInt16 Cpu;
  UInt16 Os;
  UInt16 SignatureType;
  char Name[kNameSize];
  // char Reserved[16];

  void Parse(const Byte *p);

  bool IsSupported() const;
};

struct CEntry
{
  UInt32 Tag;
  UInt32 Type;
  UInt32 Offset;
  UInt32 Count;

  void Parse(const Byte *p);
};


#ifdef _SHOW_RPM_METADATA
struct CMetaFile
{
  UInt32 Tag;
  UInt32 Offset;
  UInt32 Size;
};
#endif

class CHandler: public CHandlerCont
{
  UInt64 _headersSize; // is equal to start offset of payload data
  UInt64 _payloadSize;
  UInt64 _size;
    // _size = _payloadSize, if (_payloadSize_Defined)
    // _size = (fileSize - _headersSize), if (!_payloadSize_Defined)
  UInt64 _phySize; // _headersSize + _payloadSize, if (_phySize_Defined)
  UInt32 _headerPlusPayload_Size;
  UInt32 _buildTime;
  
  bool _payloadSize_Defined;
  bool _phySize_Defined;
  bool _headerPlusPayload_Size_Defined;
  bool _time_Defined;

  Byte _payloadSig[6]; // start data of payload

  AString _name;    // p7zip
  AString _version; // 9.20.1
  AString _release; // 8.1.1
  AString _arch;    // x86_64
  AString _os;      // linux
  
  AString _format;      // cpio
  AString _compressor;  // xz, gzip, bzip2

  CLead _lead;

  #ifdef _SHOW_RPM_METADATA
  AString _metadata;
  CRecordVector<CMetaFile> _metaFiles;
  #endif

  void SetTime(NWindows::NCOM::CPropVariant &prop) const;

  void SetStringProp(const AString &s, NWindows::NCOM::CPropVariant &prop) const;

  void AddCPU(AString &s) const;
  AString GetBaseName() const;
  void AddSubFileExtension(AString &res) const;

  HRESULT ReadHeader(ISequentialInStream *stream, bool isMainHeader);
  HRESULT Open2(ISequentialInStream *stream);

  virtual int GetItem_ExtractInfo(UInt32 /* index */, UInt64 &pos, UInt64 &size) const;

public:
  static void Register();

  INTERFACE_IInArchive_Cont(;)
};

}}

#endif // __RPM_HANDLER_H

// ILibrary.cpp

#include "../../Windows/NtCheck.h"
#include "../../Common/CksumHasher.h"
#include "../../Common/CRCHasher.h"
#include "../../Common/Sha1Hasher.h"
#include "../../Common/Sha256Hasher.h"
#include "../../Common/XzCrc64Hasher.h"
#include "../Archive/ApmHandler.h"
#include "../Archive/ArHandler.h"
#include "../Archive/ArjHandler.h"
#include "../Archive/Base64Handler.h"
#include "../Archive/Bz2Handler.h"
#include "../Archive/ComHandler.h"
#include "../Archive/CpioHandler.h"
#include "../Archive/CramfsHandler.h"
#include "../Archive/DmgHandler.h"
#include "../Archive/ElfHandler.h"
#include "../Archive/ExtHandler.h"
#include "../Archive/FatHandler.h"
#include "../Archive/FlvHandler.h"
#include "../Archive/GptHandler.h"
#include "../Archive/GzHandler.h"
#include "../Archive/HfsHandler.h"
#include "../Archive/IhexHandler.h"
#include "../Archive/LzhHandler.h"
#include "../Archive/LzmaHandler.h"
#include "../Archive/MachoHandler.h"
#include "../Archive/MbrHandler.h"
#include "../Archive/MslzHandler.h"
#include "../Archive/MubHandler.h"
#include "../Archive/NtfsHandler.h"
#include "../Archive/PpmdHandler.h"
#include "../Archive/QcowHandler.h"
#include "../Archive/7z/7zHandler.h"
#include "../Archive/Cab/CabHandler.h"
#include "../Archive/Iso/IsoHandler.h"
#include "../Archive/Nsis/NsisHandler.h"
#include "../Archive/Tar/TarHandler.h"
#include "../Archive/Wim/WimHandler.h"
#include "../Archive/Zip/ZipHandler.h"
#include "../Compress/BcjCoder.h"
#include "../Compress/Bcj2Coder.h"
#include "../Compress/BranchMisc.h"
#include "../Compress/ByteSwap2Filter.h"
#include "../Compress/ByteSwap4Filter.h"
#include "../Compress/BZip2Decoder.h"
#include "../Compress/CopyCoder.h"
#include "../Compress/DeltaFilter.h"
#include "../Compress/DeflateDecoder.h"
#include "../Compress/LzmaDecoder.h"
#include "../Compress/Lzma2Decoder.h"
#include "../Compress/PpmdDecoder.h"
#include "../Compress/Rar1Decoder.h"
#include "../Compress/Rar2Decoder.h"
#include "../Compress/Rar3Decoder.h"
#include "../Compress/Rar5Decoder.h"
#include "../Crypto/7zAes.h"
#include "../Crypto/MyAes.h"

#include "ILibrary.h"
#include "RegisterArc.h"
#include "RegisterCodec.h"

static const unsigned kNumArcsMax = 64;
static unsigned g_NumArcs = 0;
static unsigned g_DefaultArcIndex = 0;
static const CArcInfo *g_Arcs[kNumArcsMax];

extern bool g_CaseSensitive;

void RegisterArc(const CArcInfo *arcInfo) throw()
{
  if (g_NumArcs < kNumArcsMax)
  {
    const char *p = arcInfo->Name;
    if (p[0] == '7' && p[1] == 'z' && p[2] == 0)
      g_DefaultArcIndex = g_NumArcs;
    g_Arcs[g_NumArcs++] = arcInfo;
  }
}

DEFINE_GUID(CLSID_CArchiveHandler,
    k_7zip_GUID_Data1,
    k_7zip_GUID_Data2,
    k_7zip_GUID_Data3_Common,
    0x10, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00);

#define CLS_ARC_ID_ITEM(cls) ((cls).Data4[5])

static inline HRESULT SetPropStrFromBin(const char *s, unsigned size, PROPVARIANT *value)
{
  if ((value->bstrVal = ::SysAllocStringByteLen(s, size)) != 0)
    value->vt = VT_BSTR;
  return S_OK;
}

static inline HRESULT SetPropGUID(const GUID &guid, PROPVARIANT *value)
{
  return SetPropStrFromBin((const char *)&guid, sizeof(guid), value);
}

int FindFormatCalssId(const GUID *clsid)
{
  GUID cls = *clsid;
  CLS_ARC_ID_ITEM(cls) = 0;
  if (cls != CLSID_CArchiveHandler)
    return -1;
  Byte id = CLS_ARC_ID_ITEM(*clsid);
  for (unsigned i = 0; i < g_NumArcs; i++)
    if (g_Arcs[i]->Id == id)
      return (int)i;
  return -1;
}

namespace SevenZip {

void Initialize() {
  static bool s_initialized = false;

  if(s_initialized) {
    return;
  }

  // Register Filters
  NCompress::NBcj::CCoder::Register();
  NCompress::NByteSwap::CByteSwap2::Register();
  NCompress::NByteSwap::CByteSwap4::Register();
  NCompress::NDelta::CDecoder::Register();
  NCrypto::N7z::CDecoder::Register();
  NCrypto::CAesCoder::Register();

  // Register Hashers
  NHash::CCksumHasher::Register();
  NHash::CCrcHasher::Register();
  NHash::CSha1Hasher::Register();
  NHash::CSha256Hasher::Register();
  NHash::CXzCrc64Hasher::Register();

  // Register Decoders & Encoders
  NCompress::NBcj2::CEncoder::Register();
  NCompress::NBranch::CCoder::Register();
  NCompress::NBZip2::CDecoder::Register();
  NCompress::CCopyCoder::Register();
  NCompress::NDeflate::NDecoder::CCOMCoder::Register();
  NCompress::NDeflate::NDecoder::CCOMCoder64::Register();
  NCompress::NLzma::CDecoder::Register();
  NCompress::NLzma2::CDecoder::Register();
  NCompress::NPpmd::CDecoder::Register();
  NCompress::NRar1::CDecoder::Register();
  NCompress::NRar2::CDecoder::Register();
  NCompress::NRar3::CDecoder::Register();
  NCompress::NRar5::CDecoder::Register();

  // Register Archives
  NArchive::N7z::CHandler::Register();
  NArchive::NApm::CHandler::Register();
  NArchive::NAr::CHandler::Register();
  NArchive::NArj::CHandler::Register();
  NArchive::NBase64::CHandler::Register();
  NArchive::NBz2::CHandler::Register();
  NArchive::NCab::CHandler::Register();
  NArchive::NCom::CHandler::Register();
  NArchive::NCpio::CHandler::Register();
  NArchive::NCramfs::CHandler::Register();
  NArchive::NDmg::CHandler::Register();
  NArchive::NElf::CHandler::Register();
  NArchive::NExt::CHandler::Register();
  NArchive::NFat::CHandler::Register();
  NArchive::NFlv::CHandler::Register();
  NArchive::NGpt::CHandler::Register();
  NArchive::NGz::CHandler::Register();
  NArchive::NHfs::CHandler::Register();
  NArchive::NIhex::CHandler::Register();
  NArchive::NIso::CHandler::Register();
  NArchive::NLzh::CHandler::Register();
  NArchive::NLzma::CHandler::Register();
  NArchive::NMacho::CHandler::Register();
  NArchive::NMbr::CHandler::Register();
  NArchive::NMslz::CHandler::Register();
  NArchive::NMub::CHandler::Register();
  NArchive::NNsis::CHandler::Register();
  NArchive::Ntfs::CHandler::Register();
  NArchive::NPpmd::CHandler::Register();
  NArchive::NQcow::CHandler::Register();
  NArchive::NTar::CHandler::Register();
  NArchive::NWim::CHandler::Register();
  NArchive::NZip::CHandler::Register();

  s_initialized = true;
}

HRESULT CreateArchiver(const GUID *clsid, const GUID *iid, void **outObject)
{
  Initialize();

  int needIn = (*iid == IID_IInArchive);
  int needOut = (*iid == IID_IOutArchive);
  if (!needIn && !needOut)
    return E_NOINTERFACE;
  int formatIndex = FindFormatCalssId(clsid);
  if (formatIndex < 0)
    return CLASS_E_CLASSNOTAVAILABLE;

  const CArcInfo &arc = *g_Arcs[formatIndex];
  if (needIn)
  {
    *outObject = arc.CreateInArchive();
    ((IInArchive *)*outObject)->AddRef();
  }
  else
  {
    if (!arc.CreateOutArchive)
      return CLASS_E_CLASSNOTAVAILABLE;
    *outObject = arc.CreateOutArchive();
    ((IOutArchive *)*outObject)->AddRef();
  }

  return S_OK;
}

HRESULT GetHandlerProperty2(UInt32 formatIndex, PROPID propID, PROPVARIANT *value)
{
  Initialize();

  NWindows::NCOM::PropVariant_Clear(value);
  if (formatIndex >= g_NumArcs)
    return E_INVALIDARG;
  const CArcInfo &arc = *g_Arcs[formatIndex];
  NWindows::NCOM::CPropVariant prop;
  switch (propID)
  {
    case NArchive::NHandlerPropID::kName: prop = arc.Name; break;
    case NArchive::NHandlerPropID::kClassID:
    {
      GUID clsId = CLSID_CArchiveHandler;
      CLS_ARC_ID_ITEM(clsId) = arc.Id;
      return SetPropGUID(clsId, value);
    }
    case NArchive::NHandlerPropID::kExtension: if (arc.Ext) prop = arc.Ext; break;
    case NArchive::NHandlerPropID::kAddExtension: if (arc.AddExt) prop = arc.AddExt; break;
    case NArchive::NHandlerPropID::kUpdate: prop = (bool)(arc.CreateOutArchive != NULL); break;
    case NArchive::NHandlerPropID::kKeepName:   prop = ((arc.Flags & NArcInfoFlags::kKeepName) != 0); break;
    case NArchive::NHandlerPropID::kAltStreams: prop = ((arc.Flags & NArcInfoFlags::kAltStreams) != 0); break;
    case NArchive::NHandlerPropID::kNtSecure:   prop = ((arc.Flags & NArcInfoFlags::kNtSecure) != 0); break;
    case NArchive::NHandlerPropID::kFlags: prop = (UInt32)arc.Flags; break;
    case NArchive::NHandlerPropID::kSignatureOffset: prop = (UInt32)arc.SignatureOffset; break;
    // case NArchive::NHandlerPropID::kVersion: prop = (UInt32)MY_VER_MIX; break;

    case NArchive::NHandlerPropID::kSignature:
      if (arc.SignatureSize != 0 && !arc.IsMultiSignature())
        return SetPropStrFromBin((const char *)arc.Signature, arc.SignatureSize, value);
      break;
    case NArchive::NHandlerPropID::kMultiSignature:
      if (arc.SignatureSize != 0 && arc.IsMultiSignature())
        return SetPropStrFromBin((const char *)arc.Signature, arc.SignatureSize, value);
      break;
  }
  prop.Detach(value);
  return S_OK;
}

HRESULT GetHandlerProperty(PROPID propID, PROPVARIANT *value)
{
  Initialize();

  return GetHandlerProperty2(g_DefaultArcIndex, propID, value);
}

HRESULT GetNumberOfFormats(UINT32 *numFormats)
{
  Initialize();

  *numFormats = g_NumArcs;
  return S_OK;
}

HRESULT GetIsArc(UInt32 formatIndex, Func_IsArc *isArc)
{
  Initialize();

  *isArc = NULL;
  if (formatIndex >= g_NumArcs)
    return E_INVALIDARG;
  *isArc = g_Arcs[formatIndex]->IsArc;
  return S_OK;
}

HRESULT CreateObject(const GUID *clsid, const GUID *iid, void **outObject)
{
  Initialize();

  return CreateArchiver(clsid, iid, outObject);
}

HRESULT SetLargePageMode()
{
  Initialize();

  #if defined(_7ZIP_LARGE_PAGES)
  SetLargePageSize();
  #endif
  return S_OK;
}

HRESULT SetCaseSensitive(Int32 caseSensitive)
{
  Initialize();

  g_CaseSensitive = (caseSensitive != 0);
  return S_OK;
}

}

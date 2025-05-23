// ApmHandler.cpp

#include "StdAfx.h"

#include "../../../C/CpuArch.h"

#include "../../Common/ComTry.h"
#include "../../Common/Defs.h"

#include "../../Windows/PropVariant.h"

#include "../Common/RegisterArc.h"
#include "../Common/StreamUtils.h"

#include "ApmHandler.h"

#define Get16(p) GetBe16(p)
#define Get32(p) GetBe32(p)

using namespace NWindows;

namespace NArchive {
namespace NApm {

static const Byte kSig0 = 'E';
static const Byte kSig1 = 'R';
static const UInt32 kSectorSize = 512;

bool CItem::Parse(const Byte *p, UInt32 &numBlocksInMap) {
  numBlocksInMap = Get32(p + 4);
  StartBlock = Get32(p + 8);
  NumBlocks = Get32(p + 0xC);
  memcpy(Name, p + 0x10, 32);
  memcpy(Type, p + 0x30, 32);
  if (p[0] != 0x50 || p[1] != 0x4D || p[2] != 0 || p[3] != 0)
    return false;
  /*
  DataStartBlock = Get32(p + 0x50);
  NumDataBlocks = Get32(p + 0x54);
  Status = Get32(p + 0x58);
  BootStartBlock = Get32(p + 0x5C);
  BootSize = Get32(p + 0x60);
  BootAddr = Get32(p + 0x64);
  if (Get32(p + 0x68) != 0)
    return false;
  BootEntry = Get32(p + 0x6C);
  if (Get32(p + 0x70) != 0)
    return false;
  BootChecksum = Get32(p + 0x74);
  memcpy(Processor, p + 0x78, 16);
  */
  return true;
}

API_FUNC_static_IsArc IsArc_Apm(const Byte *p, size_t size)
{
  if (size < kSectorSize)
    return k_IsArc_Res_NEED_MORE;
  if (p[0] != kSig0 || p[1] != kSig1)
    return k_IsArc_Res_NO;
  unsigned i;
  for (i = 8; i < 16; i++)
    if (p[i] != 0)
      return k_IsArc_Res_NO;
  UInt32 blockSize = Get16(p + 2);
  for (i = 9; ((UInt32)1 << i) != blockSize; i++)
    if (i >= 12)
      return k_IsArc_Res_NO;
  return k_IsArc_Res_YES;
}
}

HRESULT CHandler::ReadTables(IInStream *stream)
{
  Byte buf[kSectorSize];
  {
    RINOK(ReadStream_FALSE(stream, buf, kSectorSize));
    if (buf[0] != kSig0 || buf[1] != kSig1)
      return S_FALSE;
    UInt32 blockSize = Get16(buf + 2);
    unsigned i;
    for (i = 9; ((UInt32)1 << i) != blockSize; i++)
      if (i >= 12)
        return S_FALSE;
    _blockSizeLog = i;
    _numBlocks = Get32(buf + 4);
    for (i = 8; i < 16; i++)
      if (buf[i] != 0)
        return S_FALSE;
  }

  unsigned numSkips = (unsigned)1 << (_blockSizeLog - 9);
  for (unsigned j = 1; j < numSkips; j++)
  {
    RINOK(ReadStream_FALSE(stream, buf, kSectorSize));
  }

  UInt32 numBlocksInMap = 0;
  
  for (unsigned i = 0;;)
  {
    RINOK(ReadStream_FALSE(stream, buf, kSectorSize));
 
    CItem item;
    
    UInt32 numBlocksInMap2 = 0;
    if (!item.Parse(buf, numBlocksInMap2))
      return S_FALSE;
    if (i == 0)
    {
      numBlocksInMap = numBlocksInMap2;
      if (numBlocksInMap > (1 << 8))
        return S_FALSE;
    }
    else if (numBlocksInMap2 != numBlocksInMap)
      return S_FALSE;

    UInt32 finish = item.StartBlock + item.NumBlocks;
    if (finish < item.StartBlock)
      return S_FALSE;
    _numBlocks = MyMax(_numBlocks, finish);
    
    _items.Add(item);
    for (unsigned j = 1; j < numSkips; j++)
    {
      RINOK(ReadStream_FALSE(stream, buf, kSectorSize));
    }
    if (++i == numBlocksInMap)
      break;
  }
  
  _phySize = BlocksToBytes(_numBlocks);
  _isArc = true;
  return S_OK;
}

UInt64 CHandler::BlocksToBytes(UInt32 i) const { return (UInt64)i << _blockSizeLog; }

int CHandler::GetItem_ExtractInfo(UInt32 index, UInt64 &pos, UInt64 &size) const
{
  const CItem &item = _items[index];
  pos = BlocksToBytes(item.StartBlock);
  size = BlocksToBytes(item.NumBlocks);
  return NExtract::NOperationResult::kOK;
}

STDMETHODIMP CHandler::Open(IInStream *stream, const UInt64 *, IArchiveOpenCallback * /* callback */)
{
  COM_TRY_BEGIN
  Close();
  RINOK(ReadTables(stream));
  _stream = stream;
  return S_OK;
  COM_TRY_END
}

STDMETHODIMP CHandler::Close()
{
  _isArc = false;
  _phySize = 0;
  _items.Clear();
  _stream.Release();
  return S_OK;
}

static const Byte kProps[] =
{
  kpidPath,
  kpidSize,
  kpidOffset
};

static const Byte kArcProps[] =
{
  kpidClusterSize
};

IMP_IInArchive_Props
IMP_IInArchive_ArcProps

static AString GetString(const char *s)
{
  AString res;
  for (unsigned i = 0; i < 32 && s[i] != 0; i++)
    res += s[i];
  return res;
}

STDMETHODIMP CHandler::GetArchiveProperty(PROPID propID, PROPVARIANT *value)
{
  COM_TRY_BEGIN
  NCOM::CPropVariant prop;
  switch (propID)
  {
    case kpidMainSubfile:
    {
      int mainIndex = -1;
      FOR_VECTOR (i, _items)
      {
        AString s (GetString(_items[i].Type));
        if (s != "Apple_Free" &&
            s != "Apple_partition_map")
        {
          if (mainIndex >= 0)
          {
            mainIndex = -1;
            break;
          }
          mainIndex = (int)i;
        }
      }
      if (mainIndex >= 0)
        prop = (UInt32)mainIndex;
      break;
    }
    case kpidClusterSize: prop = (UInt32)1 << _blockSizeLog; break;
    case kpidPhySize: prop = _phySize; break;

    case kpidErrorFlags:
    {
      UInt32 v = 0;
      if (!_isArc) v |= kpv_ErrorFlags_IsNotArc;
      prop = v;
      break;
    }
  }
  prop.Detach(value);
  return S_OK;
  COM_TRY_END
}

STDMETHODIMP CHandler::GetNumberOfItems(UInt32 *numItems)
{
  *numItems = _items.Size();
  return S_OK;
}

STDMETHODIMP CHandler::GetProperty(UInt32 index, PROPID propID, PROPVARIANT *value)
{
  COM_TRY_BEGIN
  NCOM::CPropVariant prop;
  const CItem &item = _items[index];
  switch (propID)
  {
    case kpidPath:
    {
      AString s (GetString(item.Name));
      if (s.IsEmpty())
        s.Add_UInt32(index);
      AString type (GetString(item.Type));
      if (type == "Apple_HFS")
        type = "hfs";
      if (!type.IsEmpty())
      {
        s += '.';
        s += type;
      }
      prop = s;
      break;
    }
    case kpidSize:
    case kpidPackSize:
      prop = BlocksToBytes(item.NumBlocks);
      break;
    case kpidOffset: prop = BlocksToBytes(item.StartBlock); break;
  }
  prop.Detach(value);
  return S_OK;
  COM_TRY_END
}

static const Byte k_Signature[] = { kSig0, kSig1 };

static IInArchive * CreateArc() {
  return new CHandler();
}

static const CArcInfo s_arcInfo = {
  0,
  0xD4,
  sizeof(k_Signature) / sizeof(k_Signature[0]),
  0,
  k_Signature,
  "APM",
  "apm",
  0,
  CreateArc,
  0,
  IsArc_Apm
};

void CHandler::Register() {
  static bool s_registered = false;

  if(!s_registered) {
    RegisterArc(&s_arcInfo);

    s_registered = true;
  }
}

}}

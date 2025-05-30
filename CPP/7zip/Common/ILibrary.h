// ILibrary.h

#ifndef __I_LIBRARY_H
#define __I_LIBRARY_H

#include "../..//Common/MyInitGuid.h"
#include "../../Windows/PropVariant.h"

#include "RegisterArc.h"

// IProgress.h
DEFINE_GUID(IID_IProgress, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00);

// IFolderArchive.h
DEFINE_GUID(IID_IFolderArchiveExtractCallback, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x01, 0x00, 0x07, 0x00, 0x00);
DEFINE_GUID(IID_IFolderArchiveExtractCallback2, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x00);
DEFINE_GUID(IID_IFolderArchiveUpdateCallback, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0B, 0x00, 0x00);
DEFINE_GUID(IID_IArchiveFolderInternal, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0C, 0x00, 0x00);
DEFINE_GUID(IID_IArchiveFolder, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0D, 0x00, 0x00);
DEFINE_GUID(IID_IInFolderArchive, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00, 0x00);
DEFINE_GUID(IID_IOutFolderArchive, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0F, 0x00, 0x00);
DEFINE_GUID(IID_IFolderArchiveUpdateCallback2, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x00, 0x00);
DEFINE_GUID(IID_IFolderScanProgress, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x01, 0x00, 0x11, 0x00, 0x00);
DEFINE_GUID(IID_IGetProp, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00, 0x00);
DEFINE_GUID(IID_IFolderExtractToStreamCallback, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x01, 0x00, 0x31, 0x00, 0x00);

// IStream.h
DEFINE_GUID(IID_ISequentialInStream, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00);
DEFINE_GUID(IID_ISequentialOutStream, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x03, 0x00, 0x02, 0x00, 0x00);
DEFINE_GUID(IID_IInStream, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00);
DEFINE_GUID(IID_IOutStream, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x03, 0x00, 0x04, 0x00, 0x00);
DEFINE_GUID(IID_IStreamGetSize, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x03, 0x00, 0x06, 0x00, 0x00);
DEFINE_GUID(IID_IOutStreamFinish, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x03, 0x00, 0x07, 0x00, 0x00);
DEFINE_GUID(IID_IStreamGetProps, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x03, 0x00, 0x08, 0x00, 0x00);
DEFINE_GUID(IID_IStreamGetProps2, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x03, 0x00, 0x09, 0x00, 0x00);

// ICoder.h
DEFINE_GUID(IID_ICompressProgressInfo, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00);
DEFINE_GUID(IID_ICompressCoder, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x00);
DEFINE_GUID(IID_ICompressCoder2, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00);
DEFINE_GUID(IID_ICompressSetCoderPropertiesOpt, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x1F, 0x00, 0x00);
DEFINE_GUID(IID_ICompressSetCoderProperties, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x20, 0x00, 0x00);
DEFINE_GUID(IID_ICompressSetDecoderProperties, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x21, 0x00, 0x00);
DEFINE_GUID(IID_ICompressSetDecoderProperties2, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x22, 0x00, 0x00);
DEFINE_GUID(IID_ICompressWriteCoderProperties, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x23, 0x00, 0x00);
DEFINE_GUID(IID_ICompressGetInStreamProcessedSize, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x24, 0x00, 0x00);
DEFINE_GUID(IID_ICompressSetCoderMt, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x25, 0x00, 0x00);
DEFINE_GUID(IID_ICompressSetFinishMode, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x26, 0x00, 0x00);
DEFINE_GUID(IID_ICompressGetInStreamProcessedSize2, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x27, 0x00, 0x00);
DEFINE_GUID(IID_ICompressSetMemLimit, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x28, 0x00, 0x00);
DEFINE_GUID(IID_ICompressReadUnusedFromInBuf, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x29, 0x00, 0x00);
DEFINE_GUID(IID_ICompressGetSubStreamSize, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x30, 0x00, 0x00);
DEFINE_GUID(IID_ICompressSetInStream, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x31, 0x00, 0x00);
DEFINE_GUID(IID_ICompressSetOutStream, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x32, 0x00, 0x00);
DEFINE_GUID(IID_ICompressSetOutStreamSize, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x34, 0x00, 0x00);
DEFINE_GUID(IID_ICompressSetBufSize, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x35, 0x00, 0x00);
DEFINE_GUID(IID_ICompressInitEncoder, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x36, 0x00, 0x00);
DEFINE_GUID(IID_ICompressSetInStream2, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x37, 0x00, 0x00);
DEFINE_GUID(IID_ICompressFilter, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x40, 0x00, 0x00);
DEFINE_GUID(IID_ICompressCodecsInfo, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x60, 0x00, 0x00);
DEFINE_GUID(IID_ISetCompressCodecsInfo, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x61, 0x00, 0x00);
DEFINE_GUID(IID_ICryptoProperties, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x80, 0x00, 0x00);
DEFINE_GUID(IID_ICryptoResetSalt, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x88, 0x00, 0x00);
DEFINE_GUID(IID_ICryptoResetInitVector, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x8C, 0x00, 0x00);
DEFINE_GUID(IID_ICryptoSetCRC, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0xA0, 0x00, 0x00);
DEFINE_GUID(IID_ICryptoSetPassword, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x90, 0x00, 0x00);
DEFINE_GUID(IID_IHasher, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0xC0, 0x00, 0x00);
DEFINE_GUID(IID_IHashers, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0xC1, 0x00, 0x00);

// IPassword.h
DEFINE_GUID(IID_ICryptoGetTextPassword, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x10, 0x00, 0x00);
DEFINE_GUID(IID_ICryptoGetTextPassword2, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x05, 0x00, 0x11, 0x00, 0x00);

// IArchive.h
DEFINE_GUID(IID_ISetProperties, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0x03, 0x00, 0x00);
DEFINE_GUID(IID_IArchiveKeepModeForNextOpen, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0x04, 0x00, 0x00);
DEFINE_GUID(IID_IArchiveAllowTail, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0x05, 0x00, 0x00);
DEFINE_GUID(IID_IArchiveOpenCallback, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0x10, 0x00, 0x00);
DEFINE_GUID(IID_IArchiveExtractCallback, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0x20, 0x00, 0x00);
DEFINE_GUID(IID_IArchiveExtractCallbackMessage, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0x21, 0x00, 0x00);
DEFINE_GUID(IID_IArchiveOpenVolumeCallback, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0x30, 0x00, 0x00);
DEFINE_GUID(IID_IInArchiveGetStream, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0x40, 0x00, 0x00);
DEFINE_GUID(IID_IArchiveOpenSetSubArchiveName, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0x50, 0x00, 0x00);
DEFINE_GUID(IID_IInArchive, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0x60, 0x00, 0x00);
DEFINE_GUID(IID_IArchiveOpenSeq, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0x61, 0x00, 0x00);
DEFINE_GUID(IID_IArchiveGetRawProps, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0x70, 0x00, 0x00);
DEFINE_GUID(IID_IArchiveGetRootProps, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0x71, 0x00, 0x00);
DEFINE_GUID(IID_IArchiveUpdateCallback, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0x80, 0x00, 0x00);
DEFINE_GUID(IID_IArchiveUpdateCallback2, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0x82, 0x00, 0x00);
DEFINE_GUID(IID_IArchiveUpdateCallbackFile, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0x83, 0x00, 0x00);
DEFINE_GUID(IID_IArchiveGetDiskProperty, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0x84, 0x00, 0x00);
DEFINE_GUID(IID_IOutArchive, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x06, 0x00, 0xA0, 0x00, 0x00);

// IFolder.h
DEFINE_GUID(IID_IFolderFolder, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00);
DEFINE_GUID(IID_IEnumProperties, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x01, 0x00, 0x00);
DEFINE_GUID(IID_IFolderGetTypeID, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00);
DEFINE_GUID(IID_IFolderGetPath, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x03, 0x00, 0x00);
DEFINE_GUID(IID_IFolderWasChanged, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x04, 0x00, 0x00);
DEFINE_GUID(IID_IFolderGetSystemIconIndex, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x00, 0x00);
DEFINE_GUID(IID_IFolderGetItemFullSize, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x08, 0x00, 0x00);
DEFINE_GUID(IID_IFolderClone, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x09, 0x00, 0x00);
DEFINE_GUID(IID_IFolderSetFlatMode, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0A, 0x00, 0x00);
DEFINE_GUID(IID_IFolderOperationsExtractCallback, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0B, 0x00, 0x00);
DEFINE_GUID(IID_IFolderProperties, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0E, 0x00, 0x00);
DEFINE_GUID(IID_IFolderArcProps, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x10, 0x00, 0x00);
DEFINE_GUID(IID_IGetFolderArcProps, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x11, 0x00, 0x00);
DEFINE_GUID(IID_IFolderOperations, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x13, 0x00, 0x00);
DEFINE_GUID(IID_IFolderCalcItemFullSize, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x14, 0x00, 0x00);
DEFINE_GUID(IID_IFolderCompare, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x15, 0x00, 0x00);
DEFINE_GUID(IID_IFolderGetItemName, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x16, 0x00, 0x00);
DEFINE_GUID(IID_IFolderAltStreams, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x08, 0x00, 0x17, 0x00, 0x00);
DEFINE_GUID(IID_IInitContextMenu, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x09, 0x00, 0x0, 0x00, 0x00);
DEFINE_GUID(IID_IPluginOptionsCallback, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x09, 0x00, 0x1, 0x00, 0x00);
DEFINE_GUID(IID_IPluginOptions, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x09, 0x00, 0x2, 0x00, 0x00);
DEFINE_GUID(IID_IFolderManager, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x00, 0x00, 0x00, 0x09, 0x00, 0x5, 0x00, 0x00);

// Handler GUIDs
DEFINE_GUID(CLSID_CFormatZip, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0x01, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatBZip2, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0x02, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatRar, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0x03, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatArj, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0x04, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatZ, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0x05, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatLzh, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0x06, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormat7z, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0x07, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatCab, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0x08, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatNsis, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0x09, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatLzma, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0x0A, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatLzma86, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0x0B, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatXz, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0x0C, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatPpmd, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0x0D, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatVhdx, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xC4, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatBase64, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xC5, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatCOFF, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xC6, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatExt, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xC7, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatVMDK, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xC8, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatVDI, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xC9, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatQcow, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xCA, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatGPT, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xCB, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatRar5, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xCC, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatIHex, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xCD, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatHxs, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xCE, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatTE, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xCF, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatUEFIc, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xD0, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatUEFIs, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xD1, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatSquashFS, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xD2, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatCramFS, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xD3, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatAPM, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xD4, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatMslz, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xD5, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatFlv, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xD6, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatSwf, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xD7, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatSwfc, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xD8, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatNtfs, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xD9, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatFat, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xDA, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatMbr, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xDB, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatVhd, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xDC, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatPe, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xDD, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatElf, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xDE, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatMachO, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xDF, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatUdf, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xE0, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatXar, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xE1, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatMub, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xE2, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatHfs, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xE3, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatDmg, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xE4, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatCompound, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xE5, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatWim, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xE6, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatIso, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xE7, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatChm, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xE9, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatSplit, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xEA, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatRpm, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xEB, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatDeb, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xEC, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatCpio, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xED, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatTar, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xEE, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatGZip, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0x10, 0x00, 0x00, 0x01, 0x10, 0xEF, 0x00, 0x00);

namespace SevenZip {

HRESULT CreateArchiver(const GUID *clsid, const GUID *iid, void **outObject);
HRESULT GetHandlerProperty2(UInt32 formatIndex, PROPID propID, PROPVARIANT *value);
HRESULT GetHandlerProperty(PROPID propID, PROPVARIANT *value);
HRESULT GetNumberOfFormats(UINT32 *numFormats);
HRESULT GetIsArc(UInt32 formatIndex, Func_IsArc *isArc);
HRESULT CreateObject(const GUID *clsid, const GUID *iid, void **outObject);
HRESULT SetLargePageMode();
HRESULT SetCaseSensitive(Int32 caseSensitive);

}

#endif // __I_LIBRARY_H

set(SEVEN_ZIP_C_SOURCE_FILES
	7z.h
	7zBuf.h
	7zDec.c
	7zTypes.h
	AesOpt.c
	Bcj2Enc.c
	Bra86.c
	CpuArch.c
	DllSecur.h
	LzFindMt.c
	Lzma2Dec.h
	Lzma86.h
	LzmaEnc.c
	MtCoder.h
	Ppmd7.h
	Ppmd8.h
	Sha1.c
	Sha256Opt.c
	Xz.h
	XzEnc.c
	7zAlloc.c
	7zBuf2.c
	7zFile.c
	7zVersion.h
	Alloc.c
	Blake2.h
	BraIA64.c
	CpuArch.h
	HuffEnc.c
	LzFindMt.h
	Lzma2DecMt.c
	Lzma86Dec.c
	LzmaEnc.h
	MtDec.c
	Ppmd7aDec.c
	Ppmd8Dec.c
	Sha1.h
	Sort.c
	XzCrc64.c
	XzEnc.h
	7zAlloc.h
	7zCrc.c
	7zFile.h
	Alloc.h
	Blake2s.c
	BwtSort.c
	Delta.c
	HuffEnc.h
	LzFindOpt.c
	Lzma2DecMt.h
	Lzma86Enc.c
	LzmaLib.c
	MtDec.h
	Ppmd7Dec.c
	Ppmd8Enc.c
	Sha1Opt.c
	Sort.h
	XzCrc64.h
	XzIn.c
	7zArcIn.c
	7zCrc.h
	Aes.c
	Bcj2.c
	Bra.c
	BwtSort.h
	Delta.h
	LzFind.c
	LzHash.h
	Lzma2Enc.c
	LzmaDec.c
	LzmaLib.h
	Ppmd.h
	Ppmd7Enc.c
	Precomp.h
	Sha256.c
	Threads.c
	XzCrc64Opt.c
	7zBuf.c
	7zCrcOpt.c
	7zStream.c
	Aes.h
	Bcj2.h
	Bra.h
	Compiler.h
	DllSecur.c
	LzFind.h
	Lzma2Dec.c
	Lzma2Enc.h
	LzmaDec.h
	MtCoder.c
	Ppmd7.c
	Ppmd8.c
	RotateDefs.h
	Sha256.h
	Threads.h
	Xz.c
	XzDec.c
)

set(SEVEN_ZIP_CPP_SOURCE_FILES
	7zip/ICoder.h
	7zip/IDecl.h
	7zip/IPassword.h
	7zip/IProgress.h
	7zip/IStream.h
	7zip/PropID.h
	7zip/Archive/Bz2Handler.cpp
	7zip/Archive/Bz2Handler.h
	7zip/Archive/DeflateProps.h
	7zip/Archive/ElfHandler.cpp
	7zip/Archive/ElfHandler.h
	7zip/Archive/GptHandler.cpp
	7zip/Archive/GptHandler.h
	7zip/Archive/HfsHandler.cpp
	7zip/Archive/makefile
	7zip/Archive/QcowHandler.cpp
	7zip/Archive/SquashfsHandler.cpp
	7zip/Archive/VhdxHandler.cpp
	7zip/Archive/XzHandler.cpp
	7zip/Archive/ApmHandler.cpp
	7zip/Archive/ApmHandler.h
	7zip/Archive/ArHandler.cpp
	7zip/Archive/ArHandler.h
	7zip/Archive/CpioHandler.cpp
	7zip/Archive/CpioHandler.h
	7zip/Archive/ExtHandler.cpp
	7zip/Archive/ExtHandler.h
	7zip/Archive/GzHandler.cpp
	7zip/Archive/IArchive.h
	7zip/Archive/LzhHandler.cpp
	7zip/Archive/MbrHandler.cpp
	7zip/Archive/NtfsHandler.cpp
	7zip/Archive/StdAfx.h
	7zip/Archive/UefiHandler.cpp
	7zip/Archive/VmdkHandler.cpp
	7zip/Archive/XzHandler.h
	7zip/Archive/ArjHandler.cpp
	7zip/Archive/CramfsHandler.cpp
	7zip/Archive/CramfsHandler.h
	7zip/Archive/FatHandler.cpp
	7zip/Archive/FatHandler.h
	7zip/Archive/HandlerCont.cpp
	7zip/Archive/LzmaHandler.cpp
	7zip/Archive/MslzHandler.cpp
	7zip/Archive/PeHandler.cpp
	7zip/Archive/RpmHandler.cpp
	7zip/Archive/SwfHandler.cpp
	7zip/Archive/VdiHandler.cpp
	7zip/Archive/ZHandler.cpp
	7zip/Archive/Base64Handler.cpp
	7zip/Archive/Base64Handler.h
	7zip/Archive/ComHandler.cpp
	7zip/Archive/ComHandler.h
	7zip/Archive/DeflateProps.cpp
	7zip/Archive/DmgHandler.cpp
	7zip/Archive/DmgHandler.h
	7zip/Archive/FlvHandler.cpp
	7zip/Archive/FlvHandler.h
	7zip/Archive/HandlerCont.h
	7zip/Archive/IhexHandler.cpp
	7zip/Archive/MachoHandler.cpp
	7zip/Archive/MubHandler.cpp
	7zip/Archive/PpmdHandler.cpp
	7zip/Archive/SplitHandler.cpp
	7zip/Archive/VhdHandler.cpp
	7zip/Archive/XarHandler.cpp
	7zip/Archive/Common/CoderMixer2.cpp
	7zip/Archive/Common/DummyOutStream.cpp
	7zip/Archive/Common/FindSignature.cpp
	7zip/Archive/Common/HandlerOut.cpp
	7zip/Archive/Common/InStreamWithCRC.cpp
	7zip/Archive/Common/ItemNameUtils.cpp
	7zip/Archive/Common/MultiStream.cpp
	7zip/Archive/Common/OutStreamWithCRC.cpp
	7zip/Archive/Common/OutStreamWithSha1.cpp
	7zip/Archive/Common/ParseProperties.cpp
	7zip/Archive/Common/StdAfx.h
	7zip/Archive/Common/CoderMixer2.h
	7zip/Archive/Common/DummyOutStream.h
	7zip/Archive/Common/FindSignature.h
	7zip/Archive/Common/HandlerOut.h
	7zip/Archive/Common/InStreamWithCRC.h
	7zip/Archive/Common/ItemNameUtils.h
	7zip/Archive/Common/MultiStream.h
	7zip/Archive/Common/OutStreamWithCRC.h
	7zip/Archive/Common/OutStreamWithSha1.h
	7zip/Archive/Common/ParseProperties.h
	7zip/Archive/7z/7zCompressionMode.cpp
	7zip/Archive/7z/7zDecode.cpp
	7zip/Archive/7z/7zEncode.cpp
	7zip/Archive/7z/7zExtract.cpp
	7zip/Archive/7z/7zFolderInStream.h
	7zip/Archive/7z/7zHandler.h
	7zip/Archive/7z/7zHeader.cpp
	7zip/Archive/7z/7zIn.cpp
	7zip/Archive/7z/7zItem.h
	7zip/Archive/7z/7zOut.h
	7zip/Archive/7z/7zProperties.h
	7zip/Archive/7z/7zSpecStream.cpp
	7zip/Archive/7z/7zUpdate.cpp
	7zip/Archive/7z/makefile
	7zip/Archive/7z/StdAfx.cpp
	7zip/Archive/7z/7zCompressionMode.h
	7zip/Archive/7z/7zDecode.h
	7zip/Archive/7z/7zEncode.h
	7zip/Archive/7z/7zFolderInStream.cpp
	7zip/Archive/7z/7zHandler.cpp
	7zip/Archive/7z/7zHandlerOut.cpp
	7zip/Archive/7z/7zHeader.h
	7zip/Archive/7z/7zIn.h
	7zip/Archive/7z/7zOut.cpp
	7zip/Archive/7z/7zProperties.cpp
	7zip/Archive/7z/7zRegister.cpp
	7zip/Archive/7z/7zSpecStream.h
	7zip/Archive/7z/7zUpdate.h
	7zip/Archive/7z/StdAfx.h
	7zip/Archive/Cab/CabBlockInStream.cpp
	7zip/Archive/Cab/CabBlockInStream.h
	7zip/Archive/Cab/CabHandler.cpp
	7zip/Archive/Cab/CabHandler.h
	7zip/Archive/Cab/CabHeader.cpp
	7zip/Archive/Cab/CabHeader.h
	7zip/Archive/Cab/CabIn.cpp
	7zip/Archive/Cab/CabIn.h
	7zip/Archive/Cab/CabItem.h
	7zip/Archive/Cab/CabRegister.cpp
	7zip/Archive/Cab/StdAfx.h
	7zip/Archive/Chm/ChmHandler.cpp
	7zip/Archive/Chm/ChmHandler.h
	7zip/Archive/Chm/ChmIn.cpp
	7zip/Archive/Chm/ChmIn.h
	7zip/Archive/Chm/StdAfx.h
	7zip/Archive/Iso/IsoHandler.cpp
	7zip/Archive/Iso/IsoHandler.h
	7zip/Archive/Iso/IsoHeader.cpp
	7zip/Archive/Iso/IsoHeader.h
	7zip/Archive/Iso/IsoIn.cpp
	7zip/Archive/Iso/IsoIn.h
	7zip/Archive/Iso/IsoItem.h
	7zip/Archive/Iso/IsoRegister.cpp
	7zip/Archive/Iso/StdAfx.h
	7zip/Archive/Nsis/NsisDecode.cpp
	7zip/Archive/Nsis/NsisDecode.h
	7zip/Archive/Nsis/NsisHandler.cpp
	7zip/Archive/Nsis/NsisHandler.h
	7zip/Archive/Nsis/NsisIn.cpp
	7zip/Archive/Nsis/NsisIn.h
	7zip/Archive/Nsis/NsisRegister.cpp
	7zip/Archive/Nsis/StdAfx.h
	7zip/Archive/Rar/Rar5Handler.cpp
	7zip/Archive/Rar/Rar5Handler.h
	7zip/Archive/Rar/RarHandler.cpp
	7zip/Archive/Rar/RarHandler.h
	7zip/Archive/Rar/RarHeader.h
	7zip/Archive/Rar/RarItem.h
	7zip/Archive/Rar/RarVol.h
	7zip/Archive/Rar/StdAfx.cpp
	7zip/Archive/Rar/StdAfx.h
	7zip/Archive/Tar/StdAfx.h
	7zip/Archive/Tar/TarHandler.cpp
	7zip/Archive/Tar/TarHandler.h
	7zip/Archive/Tar/TarHandlerOut.cpp
	7zip/Archive/Tar/TarHeader.cpp
	7zip/Archive/Tar/TarHeader.h
	7zip/Archive/Tar/TarIn.cpp
	7zip/Archive/Tar/TarIn.h
	7zip/Archive/Tar/TarItem.h
	7zip/Archive/Tar/TarOut.cpp
	7zip/Archive/Tar/TarOut.h
	7zip/Archive/Tar/TarRegister.cpp
	7zip/Archive/Tar/TarUpdate.cpp
	7zip/Archive/Tar/TarUpdate.h
	7zip/Archive/Udf/StdAfx.h
	7zip/Archive/Udf/UdfHandler.cpp
	7zip/Archive/Udf/UdfHandler.h
	7zip/Archive/Udf/UdfIn.cpp
	7zip/Archive/Udf/UdfIn.h
	7zip/Archive/Wim/StdAfx.h
	7zip/Archive/Wim/WimHandler.cpp
	7zip/Archive/Wim/WimHandler.h
	7zip/Archive/Wim/WimHandlerOut.cpp
	7zip/Archive/Wim/WimIn.cpp
	7zip/Archive/Wim/WimIn.h
	7zip/Archive/Wim/WimRegister.cpp
	7zip/Archive/Zip/StdAfx.h
	7zip/Archive/Zip/ZipAddCommon.cpp
	7zip/Archive/Zip/ZipAddCommon.h
	7zip/Archive/Zip/ZipCompressionMode.h
	7zip/Archive/Zip/ZipHandler.cpp
	7zip/Archive/Zip/ZipHandler.h
	7zip/Archive/Zip/ZipHandlerOut.cpp
	7zip/Archive/Zip/ZipHeader.h
	7zip/Archive/Zip/ZipIn.cpp
	7zip/Archive/Zip/ZipIn.h
	7zip/Archive/Zip/ZipItem.cpp
	7zip/Archive/Zip/ZipItem.h
	7zip/Archive/Zip/ZipOut.cpp
	7zip/Archive/Zip/ZipOut.h
	7zip/Archive/Zip/ZipRegister.cpp
	7zip/Archive/Zip/ZipUpdate.cpp
	7zip/Archive/Zip/ZipUpdate.h
	7zip/Common/CreateCoder.cpp
	7zip/Common/CWrappers.h
	7zip/Common/FileStreams.cpp
	7zip/Common/FilterCoder.h
	7zip/Common/InOutTempBuffer.cpp
	7zip/Common/LimitedStreams.h
	7zip/Common/MemBlocks.cpp
	7zip/Common/MethodId.h
	7zip/Common/OffsetStream.cpp
	7zip/Common/OutBuffer.h
	7zip/Common/ProgressMt.cpp
	7zip/Common/ProgressUtils.h
	7zip/Common/RegisterCodec.h
	7zip/Common/StreamBinder.h
	7zip/Common/StreamUtils.cpp
	7zip/Common/UniqBlocks.h
	7zip/Common/CreateCoder.h
	7zip/Common/FilePathAutoRename.cpp
	7zip/Common/FileStreams.h
	7zip/Common/ILibrary.cpp
	7zip/Common/ILibrary.h
	7zip/Common/InBuffer.cpp
	7zip/Common/InOutTempBuffer.h
	7zip/Common/LockedStream.cpp
	7zip/Common/MemBlocks.h
	7zip/Common/MethodProps.cpp
	7zip/Common/OffsetStream.h
	7zip/Common/OutMemStream.cpp
	7zip/Common/ProgressMt.h
	7zip/Common/PropId.cpp
	7zip/Common/StdAfx.h
	7zip/Common/StreamObjects.cpp
	7zip/Common/StreamUtils.h
	7zip/Common/VirtThread.cpp
	7zip/Common/CWrappers.cpp
	7zip/Common/FilePathAutoRename.h
	7zip/Common/FilterCoder.cpp
	7zip/Common/InBuffer.h
	7zip/Common/LimitedStreams.cpp
	7zip/Common/LockedStream.h
	7zip/Common/MethodId.cpp
	7zip/Common/MethodProps.h
	7zip/Common/OutBuffer.cpp
	7zip/Common/OutMemStream.h
	7zip/Common/ProgressUtils.cpp
	7zip/Common/RegisterArc.h
	7zip/Common/StreamBinder.cpp
	7zip/Common/StreamObjects.h
	7zip/Common/UniqBlocks.cpp
	7zip/Common/VirtThread.h
	7zip/Compress/Bcj2Coder.cpp
	7zip/Compress/BitlDecoder.h
	7zip/Compress/ByteSwap.cpp
	7zip/Compress/ByteSwap2Filter.cpp
	7zip/Compress/ByteSwap2Filter.h
	7zip/Compress/ByteSwap4Filter.cpp
	7zip/Compress/ByteSwap4Filter.h
	7zip/Compress/BZip2Encoder.h
	7zip/Compress/Deflate64Register.cpp
	7zip/Compress/DeltaFilter.cpp
	7zip/Compress/DeltaFilter.h
	7zip/Compress/DeltaFilterReg.cpp
	7zip/Compress/ImplodeHuffmanDecoder.h
	7zip/Compress/Lzma2Encoder.cpp
	7zip/Compress/LzmaRegister.cpp
	7zip/Compress/LzxDecoder.h
	7zip/Compress/PpmdRegister.cpp
	7zip/Compress/Rar2Decoder.cpp
	7zip/Compress/Rar5Decoder.h
	7zip/Compress/XzDecoder.cpp
	7zip/Compress/ZlibDecoder.h
	7zip/Compress/Bcj2Coder.h
	7zip/Compress/BitlEncoder.h
	7zip/Compress/BZip2Const.h
	7zip/Compress/BZip2Register.cpp
	7zip/Compress/DeflateConst.h
	7zip/Compress/LzfseDecoder.cpp
	7zip/Compress/Lzma2Encoder.h
	7zip/Compress/LzmsDecoder.cpp
	7zip/Compress/makefile
	7zip/Compress/PpmdZip.cpp
	7zip/Compress/Rar2Decoder.h
	7zip/Compress/RarCodecsRegister.cpp
	7zip/Compress/XzDecoder.h
	7zip/Compress/ZlibEncoder.cpp
	7zip/Compress/Bcj2Register.cpp
	7zip/Compress/BitmDecoder.h
	7zip/Compress/BZip2Crc.cpp
	7zip/Compress/DeflateDecoder.cpp
	7zip/Compress/LzfseDecoder.h
	7zip/Compress/Lzma2Register.cpp
	7zip/Compress/LzmsDecoder.h
	7zip/Compress/Mtf8.h
	7zip/Compress/PpmdZip.h
	7zip/Compress/Rar3Decoder.cpp
	7zip/Compress/ShrinkDecoder.cpp
	7zip/Compress/XzEncoder.cpp
	7zip/Compress/ZlibEncoder.h
	7zip/Compress/BcjCoder.cpp
	7zip/Compress/BitmEncoder.h
	7zip/Compress/BZip2Crc.h
	7zip/Compress/DeflateDecoder.h
	7zip/Compress/HuffmanDecoder.h
	7zip/Compress/LzhDecoder.cpp
	7zip/Compress/LzmaDecoder.cpp
	7zip/Compress/LzOutWindow.cpp
	7zip/Compress/PpmdDecoder.cpp
	7zip/Compress/QuantumDecoder.cpp
	7zip/Compress/Rar3Decoder.h
	7zip/Compress/ShrinkDecoder.h
	7zip/Compress/XzEncoder.h
	7zip/Compress/BcjCoder.h
	7zip/Compress/BranchMisc.cpp
	7zip/Compress/BZip2Decoder.cpp
	7zip/Compress/CopyCoder.cpp
	7zip/Compress/DeflateEncoder.cpp
	7zip/Compress/ImplodeDecoder.cpp
	7zip/Compress/LzhDecoder.h
	7zip/Compress/LzmaDecoder.h
	7zip/Compress/LzOutWindow.h
	7zip/Compress/PpmdDecoder.h
	7zip/Compress/QuantumDecoder.h
	7zip/Compress/Rar3Vm.cpp
	7zip/Compress/StdAfx.h
	7zip/Compress/ZDecoder.cpp
	7zip/Compress/BcjRegister.cpp
	7zip/Compress/BranchMisc.h
	7zip/Compress/BZip2Decoder.h
	7zip/Compress/CopyCoder.h
	7zip/Compress/DeflateEncoder.h
	7zip/Compress/ImplodeDecoder.h
	7zip/Compress/Lzma2Decoder.cpp
	7zip/Compress/LzmaEncoder.cpp
	7zip/Compress/Lzx.h
	7zip/Compress/PpmdEncoder.cpp
	7zip/Compress/Rar1Decoder.cpp
	7zip/Compress/Rar3Vm.h
	7zip/Compress/XpressDecoder.cpp
	7zip/Compress/ZDecoder.h
	7zip/Compress/BitlDecoder.cpp
	7zip/Compress/BranchRegister.cpp
	7zip/Compress/BZip2Encoder.cpp
	7zip/Compress/CopyRegister.cpp
	7zip/Compress/DeflateRegister.cpp
	7zip/Compress/ImplodeHuffmanDecoder.cpp
	7zip/Compress/Lzma2Decoder.h
	7zip/Compress/LzmaEncoder.h
	7zip/Compress/LzxDecoder.cpp
	7zip/Compress/PpmdEncoder.h
	7zip/Compress/Rar1Decoder.h
	7zip/Compress/Rar5Decoder.cpp
	7zip/Compress/XpressDecoder.h
	7zip/Compress/ZlibDecoder.cpp
	7zip/Crypto/7zAes.cpp
	7zip/Crypto/7zAesRegister.cpp
	7zip/Crypto/HmacSha1.cpp
	7zip/Crypto/HmacSha256.cpp
	7zip/Crypto/MyAes.cpp
	7zip/Crypto/MyAesReg.cpp
	7zip/Crypto/Pbkdf2HmacSha1.h
	7zip/Crypto/RandGen.h
	7zip/Crypto/Rar20Crypto.h
	7zip/Crypto/Rar5Aes.h
	7zip/Crypto/RarAes.h
	7zip/Crypto/StdAfx.h
	7zip/Crypto/WzAes.h
	7zip/Crypto/ZipCrypto.h
	7zip/Crypto/ZipStrong.h
	7zip/Crypto/7zAes.h
	7zip/Crypto/HmacSha1.h
	7zip/Crypto/HmacSha256.h
	7zip/Crypto/MyAes.h
	7zip/Crypto/Pbkdf2HmacSha1.cpp
	7zip/Crypto/RandGen.cpp
	7zip/Crypto/Rar20Crypto.cpp
	7zip/Crypto/Rar5Aes.cpp
	7zip/Crypto/RarAes.cpp
	7zip/Crypto/Sha1Cls.h
	7zip/Crypto/WzAes.cpp
	7zip/Crypto/ZipCrypto.cpp
	7zip/Crypto/ZipStrong.cpp
	Common/AutoPtr.h
	Common/CommandLineParser.cpp
	Common/CRC.cpp
	Common/CRCHasher.cpp
	Common/CRCHasher.h
	Common/CrcReg.cpp
	Common/DynLimBuf.cpp
	Common/Lang.cpp
	Common/LzFindPrepare.cpp
	Common/MyException.h
	Common/MyMap.cpp
	Common/MyTypes.h
	Common/MyWindows.cpp
	Common/NewHandler.cpp
	Common/StdAfx.h
	Common/StdOutStream.h
	Common/StringToInt.h
	Common/UTFConvert.h
	Common/C_FileIO.cpp
	Common/CommandLineParser.h
	Common/DynLimBuf.h
	Common/Lang.h
	Common/MyBuffer.h
	Common/MyGuidDef.h
	Common/MyMap.h
	Common/MyUnknown.h
	Common/MyWindows.h
	Common/NewHandler.h
	Common/Sha1Hasher.cpp
	Common/Sha1Hasher.h
	Common/Sha1Prepare.cpp
	Common/Sha1Reg.cpp
	Common/StdInStream.cpp
	Common/StringConvert.cpp
	Common/TextConfig.cpp
	Common/Wildcard.cpp
	Common/C_FileIO.h
	Common/Common.h
	Common/Defs.h
	Common/IntToString.cpp
	Common/ListFileUtils.cpp
	Common/MyBuffer2.h
	Common/MyInitGuid.h
	Common/MyString.cpp
	Common/MyVector.cpp
	Common/MyXml.cpp
	Common/Random.cpp
	Common/Sha256Hasher.cpp
	Common/Sha256Hasher.h
	Common/Sha256Prepare.cpp
	Common/Sha256Reg.cpp
	Common/StdInStream.h
	Common/StringConvert.h
	Common/TextConfig.h
	Common/Wildcard.h
	Common/CksumHasher.cpp
	Common/CksumHasher.h
	Common/CksumReg.cpp
	Common/ComTry.h
	Common/DynamicBuffer.h
	Common/IntToString.h
	Common/ListFileUtils.h
	Common/MyCom.h
	Common/MyLinux.h
	Common/MyString.h
	Common/MyVector.h
	Common/MyXml.h
	Common/Random.h
	Common/StdOutStream.cpp
	Common/StringToInt.cpp
	Common/UTFConvert.cpp
	Common/XzCrc64Hasher.cpp
	Common/XzCrc64Hasher.h
	Common/XzCrc64Init.cpp
	Common/XzCrc64Reg.cpp
	Windows/Clipboard.cpp
	Windows/CommonDialog.cpp
	Windows/ErrorMsg.cpp
	Windows/FileFind.cpp
	Windows/FileLink.cpp
	Windows/FileName.h
	Windows/MemoryGlobal.cpp
	Windows/Menu.cpp
	Windows/Net.cpp
	Windows/ProcessMessages.h
	Windows/PropVariant.h
	Windows/PropVariantUtils.h
	Windows/ResourceString.h
	Windows/Shell.h
	Windows/System.cpp
	Windows/Thread.h
	Windows/Window.h
	Windows/Clipboard.h
	Windows/CommonDialog.h
	Windows/Defs.h
	Windows/ErrorMsg.h
	Windows/FileFind.h
	Windows/FileMapping.cpp
	Windows/FileSystem.cpp
	Windows/MemoryGlobal.h
	Windows/Menu.h
	Windows/Net.h
	Windows/ProcessUtils.cpp
	Windows/PropVariantConv.cpp
	Windows/Registry.cpp
	Windows/SecurityUtils.cpp
	Windows/StdAfx.h
	Windows/System.h
	Windows/TimeUtils.cpp
	Windows/COM.cpp
	Windows/Console.cpp
	Windows/DLL.cpp
	Windows/FileDir.cpp
	Windows/FileIO.cpp
	Windows/FileMapping.h
	Windows/FileSystem.h
	Windows/MemoryLock.cpp
	Windows/NationalTime.cpp
	Windows/NtCheck.h
	Windows/ProcessUtils.h
	Windows/PropVariantConv.h
	Windows/Registry.h
	Windows/SecurityUtils.h
	Windows/Synchronization.cpp
	Windows/SystemInfo.cpp
	Windows/TimeUtils.h
	Windows/COM.h
	Windows/Console.h
	Windows/DLL.h
	Windows/FileDir.h
	Windows/FileIO.h
	Windows/FileName.cpp
	Windows/Handle.h
	Windows/MemoryLock.h
	Windows/NationalTime.h
	Windows/ProcessMessages.cpp
	Windows/PropVariant.cpp
	Windows/PropVariantUtils.cpp
	Windows/ResourceString.cpp
	Windows/Shell.cpp
	Windows/Synchronization.h
	Windows/SystemInfo.h
	Windows/Window.cpp
	Windows/Control/ComboBox.cpp
	Windows/Control/ComboBox.h
	Windows/Control/CommandBar.h
	Windows/Control/Dialog.cpp
	Windows/Control/Dialog.h
	Windows/Control/Edit.h
	Windows/Control/ImageList.cpp
	Windows/Control/ImageList.h
	Windows/Control/ListView.cpp
	Windows/Control/ListView.h
	Windows/Control/ProgressBar.h
	Windows/Control/PropertyPage.cpp
	Windows/Control/PropertyPage.h
	Windows/Control/ReBar.h
	Windows/Control/Static.h
	Windows/Control/StatusBar.h
	Windows/Control/StdAfx.h
	Windows/Control/ToolBar.h
	Windows/Control/Trackbar.h
	Windows/Control/Window2.cpp
	Windows/Control/Window2.h
)

list(TRANSFORM SEVEN_ZIP_C_SOURCE_FILES PREPEND "C/")
list(TRANSFORM SEVEN_ZIP_CPP_SOURCE_FILES PREPEND "CPP/")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SEVEN_ZIP_C_SOURCE_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SEVEN_ZIP_CPP_SOURCE_FILES})

// Copyright 2015-2018 Piperift. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/SaveGame.h>
#include <Misc/EngineVersion.h>
#include <Templates/SubclassOf.h>
#include <Serialization/CustomVersion.h>
#include <Serialization/ObjectAndNameAsStringProxyArchive.h>
#include <PlatformFeatures.h>

#include "ISaveExtension.h"


class USavePreset;
class FMemoryReader;
class FMemoryWriter;


/** Based on GameplayStatics to add multi-threading */
struct FSaveFileHeader
{
	FSaveFileHeader();
	FSaveFileHeader(TSubclassOf<USaveGame> ObjectType, bool bIsCompressed);

	void Empty();
	bool IsEmpty() const;

	void Read(FMemoryReader& MemoryReader);
	void Write(FMemoryWriter& MemoryWriter);

	int32 FileTypeTag;
	int32 SaveGameFileVersion;
	int32 PackageFileUE4Version;
	FEngineVersion SavedEngineVersion;
	int32 CustomVersionFormat;
	FCustomVersionContainer CustomVersions;
	FString SaveGameClassName;
	bool bIsCompressed;
};

/** Based on GameplayStatics to add multi-threading */
class FFileAdapter
{
public:

	static bool SaveFile(USaveGame* SaveGameObject, const FString& SlotName, const bool bUseCompression);

	static USaveGame* LoadFile(const FString& SlotName);

	static bool DeleteFile(const FString& SlotName);
	static bool DoesFileExist(const FString& SlotName);
};

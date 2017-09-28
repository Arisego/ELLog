// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Engine/EngineTypes.h"
#include "ElLogSettings.generated.h"

/**
 * Settings for ElLog Plugin
 */
UCLASS(config = ElLog, defaultconfig, meta = (DisplayName = "ElLog"))
class UElLogSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()
	
public:
	/** The path log file will use */
	UPROPERTY(config, EditAnywhere, Category = "Setting", meta = (DisplayName = "Logging path", RelativeToGameContentDir, RelativePath, defaultValue = "../../logs"))
	FDirectoryPath LoggingPath;

	/** Log file rotate size */
	UPROPERTY(config, EditAnywhere, Category = "Setting", meta = (DisplayName = "Log Rotate Size", defaultValue = 102400, ClampMin = 1024))
	int32 RotateSize;

	/**	Time of day log file should be keep	*/
	UPROPERTY(config, EditAnywhere, Category = "Setting", meta = (DisplayName = "Log Keep Days", defaultValue = 3.0f, ClampMin = 0.001f))
	float KeepLogDays;

};

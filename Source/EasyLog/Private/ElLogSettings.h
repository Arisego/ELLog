// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ElLogSettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Loading Screen"))
class UElLogSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()
	
public:
	/** The size of the tip before it's wrapped to the next line. */
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = Advice)
	float TipWrapAt;
	
	
};

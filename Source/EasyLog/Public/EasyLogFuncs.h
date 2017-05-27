// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "EasyLogFuncs.generated.h"

/**
 * EasyLog's Blueprint Function Lib
 */
UCLASS()
class EASYLOG_API UEasyLogFuncs : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Set the out put file name/path */
	UFUNCTION(BlueprintCallable, Category = "EasyLog")
		static void SetFileNames();

	/**
	 *	Log the string to file.
	 */
	UFUNCTION(BlueprintCallable, Category = "EasyLog")
		static void LogToFile(FString StringToLog);
};

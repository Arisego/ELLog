// Fill out your copyright notice in the Description page of Project Settings.

#include "EasyLog.h"
#include "ElLogSettings.h"

UElLogSettings::UElLogSettings(const FObjectInitializer& Initializer)
	: Super(Initializer)
{
	LoggingPath.Path = "../../logs";
	RotateSize = 102400;
}

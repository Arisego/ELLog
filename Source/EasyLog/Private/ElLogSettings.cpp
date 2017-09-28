// Fill out your copyright notice in the Description page of Project Settings.

#include "EasyLog.h"
#include "ElLogSettings.h"

UElLogSettings::UElLogSettings(const FObjectInitializer& Initializer)
	: Super(Initializer)
	, RotateSize(102400)
	, KeepLogDays(3.0f)
{
	LoggingPath.Path = "../../logs";
}

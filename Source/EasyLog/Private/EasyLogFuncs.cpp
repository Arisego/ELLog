// Fill out your copyright notice in the Description page of Project Settings.

#include "EasyLog.h"
#include "LogHolder.h"
#include "EasyLogFuncs.h"

void UEasyLogFuncs::SetFileNames()
{

}

void UEasyLogFuncs::LogToFile(FString StringToLog)
{
	LogHolder::getInstance().LogToFile(StringToLog);
}

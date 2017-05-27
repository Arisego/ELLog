// Fill out your copyright notice in the Description page of Project Settings.

#include "EasyLog.h"
#include "LogHolder.h"

#include "easyloggingpp/easylogging++.h"

INITIALIZE_EASYLOGGINGPP


LogHolder::LogHolder()
{
	el::Configurations defaultConf;
	defaultConf.setToDefault();
	// Values are always std::string
	defaultConf.set(el::Level::Global,
		el::ConfigurationType::Format, "%datetime %level %msg");
	defaultConf.set(el::Level::Global,
		el::ConfigurationType::Filename, "E:/log.log");

	// default logger uses default configurations
	el::Loggers::reconfigureLogger("default", defaultConf);

	LOG(INFO) << "[FEasyLogModule] StartupModule()";
	LOG(INFO) << "[FEasyLogModule] StartupModule() --- Begin";
	UE_LOG(LogTemp, Log, TEXT("[FEasyLogModule] StartupModule() - ue_log"));
}

LogHolder::~LogHolder()
{
}

void LogHolder::LogToFile(FString InString)
{
	UE_LOG(LogTemp, Log, TEXT("[LogHolder] LogToFile()"));
	LOG(INFO) << "[LogHolder] LogToFile()" << *InString;
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "EasyLog.h"
#include "LogHolder.h"

#include "Paths.h"
#include "PlatformFilemanager.h"
#include "GenericPlatformFile.h"

#include "AllowWindowsPlatformTypes.h"

#include "easyloggingpp/easylogging++.h"

#include "HideWindowsPlatformTypes.h"





INITIALIZE_EASYLOGGINGPP

namespace LogHolderNs
{
	el::base::SubsecondPrecision DefaultSubSecPre;
};


LogHolder::LogHolder()
{
	FString t_fsLogPath = FPaths::RootDir();
	t_fsLogPath += "logs/";
	//t_fsLogPath += "dlo/gs/";

	//UE_LOG(LogTemp, Log, TEXT("Parent path: %s"), *FPaths::GetPath(FPaths::GetPath(t_fsLogPath)));

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.DirectoryExists(*t_fsLogPath))
	{
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*t_fsLogPath);

		if (!PlatformFile.DirectoryExists(*t_fsLogPath))
		{
			t_fsLogPath = FPaths::RootDir();
			UE_LOG(LogTemp, Warning, TEXT("[LogHolder] LogHolder(): Unable to create log directory"));
		}
	}

	t_fsLogPath += el::base::utils::DateTime::getDateTime("%Y%M%d_%H_%m_%s", &LogHolderNs::DefaultSubSecPre).c_str();
	t_fsLogPath += ".log";

	el::Configurations defaultConf;
	defaultConf.setToDefault();
	// Values are always std::string
	defaultConf.set(el::Level::Global,
		el::ConfigurationType::Format, "%datetime %level %msg");
	defaultConf.set(el::Level::Global,
		el::ConfigurationType::Filename, TCHAR_TO_ANSI(*t_fsLogPath));

	// default logger uses default configurations
	el::Loggers::reconfigureLogger("default", defaultConf);

	LOG(INFO) << "[LogHolder] LogHolder(): Construct";
	UE_LOG(LogTemp, Log, TEXT("[LogHolder] LogHolder(): Construct with path: %s"), *t_fsLogPath);
}

LogHolder::~LogHolder()
{
	LOG(INFO) << "[LogHolder] LogHolder(): Destruct";
}

void LogHolder::LogToFile(FString InString)
{
	UE_LOG(LogTemp, Log, TEXT("[LogHolder] LogToFile()"));
	LOG(INFO) << "[LogHolder] LogToFile(): " << *InString;
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "EasyLog.h"
#include "LogHolder.h"

#include "EngineMinimal.h"
#include "Paths.h"
#include "PlatformFilemanager.h"

#include "AllowWindowsPlatformTypes.h"
#include "easyloggingpp/easylogging++.h"
#include "HideWindowsPlatformTypes.h"
#include "GenericPlatformFile.h"

INITIALIZE_EASYLOGGINGPP

namespace LogHolderNs
{
	el::base::SubsecondPrecision DefaultSubSecPre;

	void rolloutHandler(const char* filename, std::size_t size) {
		LogHolder::OnRotate(ANSI_TO_TCHAR(filename), size);
	}
};

/** Max size before the log file rotate */
#define MAXLOGSIZE	"102400"

FString LogHolder::LogPath = FPaths::GameDir()+ "logs/";
FString LogHolder::LogName = el::base::utils::DateTime::getDateTime("%Y%M%d_%H%m%s_%g", &LogHolderNs::DefaultSubSecPre).c_str();

LogHolder::LogHolder()
{
	ReGenLogPath();

	el::Configurations defaultConf;
	defaultConf.setToDefault();

	// Values are always std::string
	defaultConf.set(el::Level::Global,
		el::ConfigurationType::Format, "%datetime %level %msg");
	defaultConf.set(el::Level::Global,
		el::ConfigurationType::Filename, TCHAR_TO_ANSI(*(LogPath+ LogName + ".log")));
	defaultConf.set(el::Level::Global,
		el::ConfigurationType::MaxLogFileSize, MAXLOGSIZE);

	// default logger uses default configurations
	el::Loggers::reconfigureLogger("default", defaultConf);
	el::Loggers::addFlag(el::LoggingFlag::StrictLogFileSizeCheck);
	el::Helpers::installPreRollOutCallback(LogHolderNs::rolloutHandler);

	LOG(INFO) << "[LogHolder] LogHolder(): Construct";
	UE_LOG(LogTemp, Log, TEXT("[LogHolder] LogHolder(): Construct with path: %s£¬ %s"), *LogPath, *LogName);
}

LogHolder::~LogHolder()
{
	el::Helpers::uninstallPreRollOutCallback();
	LOG(INFO) << "[LogHolder] LogHolder(): Destruct";
}

void LogHolder::LogToFile(FString InString)
{
	UE_LOG(LogTemp, Log, TEXT("[LogHolder] LogToFile()"));
	LOG(INFO) << "[LogHolder] LogToFile(): " << *InString;
}

void LogHolder::OnRotate(const FString& OldFile, std::size_t FileSize)
{
	static int idx = 0;

	UE_LOG(LogTemp, Log, TEXT("[LogHolder] LogHolder(): Log file roll: %s, %d reached"), *OldFile, FileSize);
	FPlatformFileManager::Get().GetPlatformFile().MoveFile(*(LogPath + LogName + "_" + FString::FromInt(idx++) + "_.log"), *OldFile);
}

void LogHolder::ReGenLogPath()
{
	if (!FPaths::DirectoryExists(*LogPath)){
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*LogPath);

		if (!FPaths::DirectoryExists(*LogPath)){
			LogPath = FPaths::RootDir();
			UE_LOG(LogTemp, Warning, TEXT("[LogHolder] LogHolder(): Unable to create log directory and fall back to default"));
			return;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("[LogHolder] LogHolder(): Init log path %s"), *FPaths::GetPath(FPaths::GetPath(LogPath)));
}

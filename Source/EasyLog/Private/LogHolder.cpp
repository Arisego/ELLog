// Fill out your copyright notice in the Description page of Project Settings.

#include "EasyLog.h"
#include "LogHolder.h"

#include "EngineMinimal.h"
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

	void rolloutHandler(const char* filename, std::size_t size) {
		LogHolder::OnRotate(ANSI_TO_TCHAR(filename), size);
	}
};

FString LogHolder::LogPath = FPaths::ProjectDir()+ "logs/";
FString LogHolder::LogName = el::base::utils::DateTime::getDateTime("%Y%M%d_%H%m%s_%g", &LogHolderNs::DefaultSubSecPre).c_str();
float LogHolder::KeepLogDays = 3.0f;

LogHolder::LogHolder()
{
	const UElLogSettings* t_eSetting = GetDefault<UElLogSettings>();
	LogPath = t_eSetting->LoggingPath.Path;
	KeepLogDays = t_eSetting->KeepLogDays;

	ReGenLogPath();
	Clean_LogFile();

	el::Configurations defaultConf;
	defaultConf.setToDefault();

	// Values are always std::string
	defaultConf.set(el::Level::Global,
		el::ConfigurationType::Format, "%datetime %level %msg");
	defaultConf.set(el::Level::Global,
		el::ConfigurationType::Filename, TCHAR_TO_ANSI(*((LogPath / LogName) + ".log")));
	defaultConf.set(el::Level::Global,
		el::ConfigurationType::MaxLogFileSize, TCHAR_TO_ANSI(*FString::FromInt(t_eSetting->RotateSize)));

	// default logger uses default configurations
	el::Loggers::reconfigureLogger("default", defaultConf);
	el::Loggers::addFlag(el::LoggingFlag::StrictLogFileSizeCheck);
	el::Helpers::installPreRollOutCallback(LogHolderNs::rolloutHandler);

	LOG(INFO) << "[LogHolder] LogHolder(): Construct";
	UE_LOG(LogTemp, Log, TEXT("[LogHolder] LogHolder(): Construct with path: %s"), *(LogPath / LogName));
}

LogHolder::~LogHolder()
{
	el::Helpers::uninstallPreRollOutCallback();
	LOG(INFO) << "[LogHolder] LogHolder(): Destruct";
}

void LogHolder::LogToFile(FString InString)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *InString);
	LOG(INFO) << *InString;
}

void LogHolder::OnRotate(const FString& OldFile, std::size_t FileSize)
{
	static int idx = 0;

	UE_LOG(LogTemp, Log, TEXT("[LogHolder] LogHolder(): Log file roll: %s, %d reached"), *OldFile, FileSize);
	FPlatformFileManager::Get().GetPlatformFile().MoveFile(*((LogPath / LogName) + "_" + FString::FromInt(idx++) + "_.log"), *OldFile);
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

void LogHolder::Clean_LogFile()
{
	TArray<FString> t_arrstrDirToSkip;
	IPlatformFile &PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FLocalTimestampDirectoryVisitor Visitor(PlatformFile, t_arrstrDirToSkip, t_arrstrDirToSkip, false);
	PlatformFile.IterateDirectory(*LogPath, Visitor);

	TArray<FString> t_arrFiles;
	FDateTime t_dtNow = FDateTime::Now();

	for (TMap<FString, FDateTime>::TIterator TimestampIt(Visitor.FileTimes); TimestampIt; ++TimestampIt)
	{
		const FString filePath = TimestampIt.Key();
		const FString fileName = FPaths::GetCleanFilename(filePath);
		bool t_bShouldAddFile = true;

		FDateTime FileDateTime = TimestampIt.Value();
		FTimespan t_ftLength = t_dtNow - FileDateTime;

		if (t_ftLength < FTimespan::FromDays(KeepLogDays))
		{
			t_bShouldAddFile = false;
			UE_LOG(LogTemp, Log, TEXT("[LogHolder] LogHolder(): File not to delete %s"), *filePath);
		}

		if (t_bShouldAddFile)
		{
			t_arrFiles.Add(filePath);
		}
	}

	for (FString t_strFileName : t_arrFiles)
	{
		FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*t_strFileName);
		UE_LOG(LogTemp, Log, TEXT("[LogHolder] LogHolder(): Delete file %s"), *t_strFileName);
	}
}

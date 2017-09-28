// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define EL_LOG(Format, ...) { LogHolder::getInstance().LogToFile(FString::Printf(Format, ##__VA_ARGS__));	}

/**
 * SingleTon for Log
 */
class EASYLOG_API LogHolder
{
public:
	static LogHolder& getInstance()
	{
		static LogHolder instance;
		return instance;
	}

private:
	static FString LogPath;
	static FString LogName;

	/** <How long should log file should keep before deleted */
	static float KeepLogDays;

private:
	LogHolder();

	/** Check and Generate Log path */
	static void ReGenLogPath();

	/** Remove old log files */
	static void Clean_LogFile();

public:
	LogHolder(LogHolder const&) = delete;
	void operator=(LogHolder const&) = delete;

	~LogHolder();

public:
	void LogToFile(FString InString = "");

	static void OnRotate(const FString& OldFile, std::size_t FileSize);

};

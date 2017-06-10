// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

private:
	LogHolder();

	/** Check and Generate Log path */
	static void ReGenLogPath();

public:
	LogHolder(LogHolder const&) = delete;
	void operator=(LogHolder const&) = delete;

	~LogHolder();

public:
	void LogToFile(FString InString = "");

	static void OnRotate(const FString& OldFile, std::size_t FileSize);

};

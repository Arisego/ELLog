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
	LogHolder();

public:
	LogHolder(LogHolder const&) = delete;
	void operator=(LogHolder const&) = delete;

	~LogHolder();

public:
	void LogToFile(FString InString = "");
};

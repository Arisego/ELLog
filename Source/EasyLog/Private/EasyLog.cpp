// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "EasyLog.h"
#include "ISettingsModule.h"
#include "ElLogSettings.h"
#include "CoreDelegates.h"

#define LOCTEXT_NAMESPACE "FEasyLogModule"

namespace NS_ELLOG
{
	void RegisterSettings()
	{
		UE_LOG(LogTemp,Log,TEXT("[NS_ELLOG] RegisterSettings()"));
		if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		{
			SettingsModule->RegisterSettings("Project", "Plugins", "ELLog",
				LOCTEXT("TileSetEditorSettingsName", "EasyLog Settings"),
				LOCTEXT("TileSetEditorSettingsDescription", "Configure the setting of easylog plugin."),
				GetMutableDefault<UElLogSettings>());
			UE_LOG(LogTemp, Log, TEXT("[NS_ELLOG] RegisterSettings(): Stp"));
		}
	}

	void UnregisterSettings()
	{
		if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		{
			SettingsModule->UnregisterSettings("Project", "Plugins", "ELLog");
		}
	}
};
// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
void FEasyLogModule::StartupModule()
{
	//NS_ELLOG::RegisterSettings();
	FCoreDelegates::OnFEngineLoopInitComplete.AddStatic(&NS_ELLOG::RegisterSettings);
}

void FEasyLogModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	NS_ELLOG::UnregisterSettings();
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEasyLogModule, EasyLog)
# UE4 EasyLoggingpp Plugin
A wrap of easyloggingpp, so that you can use easyloggingpp in ue4.

Notice: This plugin works on UE4.16, you need to change build rules to make it work for early version.

Why not just use UE_LOG？Because we want to make things easy:

* No need to bother with enable log in shipping mode
* Take advantage of EasyLogging++
* Have more control on what to and not to log

This plugin is only tested under Windows 64bit and 32bit. It should work on other platforms cause Easyloggingpp is cross-platform.

You can get more infomations on [EasyLogging++](https://github.com/muflihun/easyloggingpp)

# Usage

Throw the plugin into your project plugin folder and enable it.

Then you can use "LogToFile" bpl functioin in blueprint.

If you want to use this in C++

1. add "EasyLog" to your PublicDependencyModulesNames in [project].build.cs
2. include "LogHolder.h"

Then you can log to file by

* EL_LOG(TEXT("[AShipIssueGameModeBase] LoadPakDelegate(): %s"), *PakPath);
* Use LogHolder singleton

This plugin is not well designed enough, you can modify it to fit your wish.

# Log Infos

Default Logging path is GameDir()/logs

Default logging rotate size is 102400(100KB)

They are defiend in LogHolder.cpp.


# Known Issue
* Logging in early phase plugin's class constructor will crash your COOKING with CDO CRT error.

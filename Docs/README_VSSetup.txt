Before going through any of these steps, first you need to get the project set up. 

1. Create a directory structure that suites you on your hard drive. 
2. In visual studio, create a project, and select it to load out of the folder of your choice. Use /Build
3. There are 2 ways to think about how the project will be. 
   A) The source files will be organized on the disc to match the fitler set up. When you want to add a new folder to the project, right click on the solution, and select "Add new Filter", then map the filter to the folder that you want on your hard drive. Additionally, when you want to add a file to the project, you have to select the folder where it will live.
   B) All of the source files and headers files will live in a single directory. Then, in the project you will organize the file to follow a structure, but on the disc it will not. 
   It is not hard to switch between the 2, but I prefer method B) at this point. 

Naming conventions: 
Header files will be called .h. 
Header files that are 100% inlined, meaning they contain the implemenation as well as the definition will be called .hpp
Implementation file will be called .cpp

Suggested Directory Structure: 
Assets [All texture and configuration Assets for the game]
Build [Will hold the project solution configuration files. On linux will hold the make file]
Docs [All related documents to the project]
Bin [All the binaries that the game builds. This will be oranized by Platform name / Configuration name
Headers [All headers will live in a single folder nested in this one (Project_name/*.h and *.hpp)]
Lib [All library dependancy files. (.lib, .dll, etc)]
Source [Where all the implementations files will be stored (.cpp)]
Temp [Object files, and other temporary logs will be stored here]


To configure this, you must edit the configuration for the project. Make sure that when you do this for the first time, you change the configuration you are changing to ALL. These changes should apply to both Debug and Release, but Release will vary later on, in custom ways that you can specify later.  

Note: The $(PlatformName) is for any project that is going to be supported by more than one system. If you are going to support only one Platform, IE, only windows, or only linux, then this can be excluded. 

Configutation Properties -> General

-> Output Directory: $(ProjectDir)..\..\Bin\$(PlatformName)_$(Configuration)\ 

-> Intermediate Directory: $(ProjectDir)..\..\Temp\$(ProjectName)_$(Configuration)\

-> Target Name: $(ProjectName)_$(PlatformName)_$(Configuration)

*Some of the following values may be set by default. 

-> Debugging -> Debugging Command : $(TargetPath) *usually set by default

-> Debugging-> Working Directory : $(ProjectDir)..\..\Bin\

C/C++ -> Precompiled Headers -> Precompiled Header File : $(IntDir)$(TargetName).pch *usually set by default


-> General -> Additional Include Directories : $(ProjectDir)..\..\Headers\
					       C:\boost

-> Output Files : $(IntDir) for Asm List Location, Object Filename and Program Database File, this is usually set by default.

Linker -> General -> Additional Dependancies: Killer1_Engine_Win32_Debug.lib   

Debug Settings -> Generate Program Database File : $(TargetDir)_$(TargetName).pdb

-> Debugging -> Map File : $(TargetDir)_$(TargetName).map [May have to enable the file to even be made]

->General -> Additional Library Directories: $(ProjectDir)..\..\Lib\

del $(ProjectDir)..\..\Lib\Killer1_Engine_Win32_Debug.lib /S /Q
del $(ProjectDir)..\..\Headers\Engine /S /Q
xcopy F:\Projects\Killer1_Engine\Bin\Win32Debug\Killer1_Engine_Win32_Debug.lib $(ProjectDir)..\..\Lib\ /s /i /y
xcopy F:\Projects\Killer1_Engine\Headers\* $(ProjectDir)..\..\Headers\ /s /i /y



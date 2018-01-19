##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=SummonMaster
ConfigurationName      :=Release
WorkspacePath          :="/home/anton/Рабочий стол/projects/LifeBased/LifeSystem"
ProjectPath            :="/home/anton/Рабочий стол/projects/SummonMaster"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Anton
Date                   :=11/01/18
CodeLitePath           :=/home/anton/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=./bin/Release/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="SummonMaster.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)november $(LibrarySwitch)curl $(LibrarySwitch)pthread $(LibrarySwitch)z 
ArLibs                 :=  "november" "curl" "pthread" "z" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -O2 -pedantic -std=c++14 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_CEventDispatcher.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Map_CMap.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Map_CHeightMap.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Map_CPathFinder.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Creatures_CCreature.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Creatures_CPlayer.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Creatures_CPawn.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Objects_CMovableObject.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_World_CGameRequestHandler.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_World_CWorld.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_World_CInstance.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Net_CSummonMasterCommandManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Net_CSummonMasterUser.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Net_CSummonMasterApp.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Net_cindexpage.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Net_csitepage.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Net_csuccesspage.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/src_CEventDispatcher.cpp$(ObjectSuffix): src/CEventDispatcher.cpp $(IntermediateDirectory)/src_CEventDispatcher.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/src/CEventDispatcher.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_CEventDispatcher.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_CEventDispatcher.cpp$(DependSuffix): src/CEventDispatcher.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_CEventDispatcher.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_CEventDispatcher.cpp$(DependSuffix) -MM src/CEventDispatcher.cpp

$(IntermediateDirectory)/src_CEventDispatcher.cpp$(PreprocessSuffix): src/CEventDispatcher.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_CEventDispatcher.cpp$(PreprocessSuffix) src/CEventDispatcher.cpp

$(IntermediateDirectory)/src_Map_CMap.cpp$(ObjectSuffix): src/Map/CMap.cpp $(IntermediateDirectory)/src_Map_CMap.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/src/Map/CMap.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Map_CMap.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Map_CMap.cpp$(DependSuffix): src/Map/CMap.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Map_CMap.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Map_CMap.cpp$(DependSuffix) -MM src/Map/CMap.cpp

$(IntermediateDirectory)/src_Map_CMap.cpp$(PreprocessSuffix): src/Map/CMap.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Map_CMap.cpp$(PreprocessSuffix) src/Map/CMap.cpp

$(IntermediateDirectory)/src_Map_CHeightMap.cpp$(ObjectSuffix): src/Map/CHeightMap.cpp $(IntermediateDirectory)/src_Map_CHeightMap.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/src/Map/CHeightMap.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Map_CHeightMap.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Map_CHeightMap.cpp$(DependSuffix): src/Map/CHeightMap.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Map_CHeightMap.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Map_CHeightMap.cpp$(DependSuffix) -MM src/Map/CHeightMap.cpp

$(IntermediateDirectory)/src_Map_CHeightMap.cpp$(PreprocessSuffix): src/Map/CHeightMap.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Map_CHeightMap.cpp$(PreprocessSuffix) src/Map/CHeightMap.cpp

$(IntermediateDirectory)/src_Map_CPathFinder.cpp$(ObjectSuffix): src/Map/CPathFinder.cpp $(IntermediateDirectory)/src_Map_CPathFinder.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/src/Map/CPathFinder.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Map_CPathFinder.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Map_CPathFinder.cpp$(DependSuffix): src/Map/CPathFinder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Map_CPathFinder.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Map_CPathFinder.cpp$(DependSuffix) -MM src/Map/CPathFinder.cpp

$(IntermediateDirectory)/src_Map_CPathFinder.cpp$(PreprocessSuffix): src/Map/CPathFinder.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Map_CPathFinder.cpp$(PreprocessSuffix) src/Map/CPathFinder.cpp

$(IntermediateDirectory)/src_Creatures_CCreature.cpp$(ObjectSuffix): src/Creatures/CCreature.cpp $(IntermediateDirectory)/src_Creatures_CCreature.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/src/Creatures/CCreature.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Creatures_CCreature.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Creatures_CCreature.cpp$(DependSuffix): src/Creatures/CCreature.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Creatures_CCreature.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Creatures_CCreature.cpp$(DependSuffix) -MM src/Creatures/CCreature.cpp

$(IntermediateDirectory)/src_Creatures_CCreature.cpp$(PreprocessSuffix): src/Creatures/CCreature.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Creatures_CCreature.cpp$(PreprocessSuffix) src/Creatures/CCreature.cpp

$(IntermediateDirectory)/src_Creatures_CPlayer.cpp$(ObjectSuffix): src/Creatures/CPlayer.cpp $(IntermediateDirectory)/src_Creatures_CPlayer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/src/Creatures/CPlayer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Creatures_CPlayer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Creatures_CPlayer.cpp$(DependSuffix): src/Creatures/CPlayer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Creatures_CPlayer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Creatures_CPlayer.cpp$(DependSuffix) -MM src/Creatures/CPlayer.cpp

$(IntermediateDirectory)/src_Creatures_CPlayer.cpp$(PreprocessSuffix): src/Creatures/CPlayer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Creatures_CPlayer.cpp$(PreprocessSuffix) src/Creatures/CPlayer.cpp

$(IntermediateDirectory)/src_Creatures_CPawn.cpp$(ObjectSuffix): src/Creatures/CPawn.cpp $(IntermediateDirectory)/src_Creatures_CPawn.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/src/Creatures/CPawn.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Creatures_CPawn.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Creatures_CPawn.cpp$(DependSuffix): src/Creatures/CPawn.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Creatures_CPawn.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Creatures_CPawn.cpp$(DependSuffix) -MM src/Creatures/CPawn.cpp

$(IntermediateDirectory)/src_Creatures_CPawn.cpp$(PreprocessSuffix): src/Creatures/CPawn.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Creatures_CPawn.cpp$(PreprocessSuffix) src/Creatures/CPawn.cpp

$(IntermediateDirectory)/src_Objects_CMovableObject.cpp$(ObjectSuffix): src/Objects/CMovableObject.cpp $(IntermediateDirectory)/src_Objects_CMovableObject.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/src/Objects/CMovableObject.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Objects_CMovableObject.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Objects_CMovableObject.cpp$(DependSuffix): src/Objects/CMovableObject.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Objects_CMovableObject.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Objects_CMovableObject.cpp$(DependSuffix) -MM src/Objects/CMovableObject.cpp

$(IntermediateDirectory)/src_Objects_CMovableObject.cpp$(PreprocessSuffix): src/Objects/CMovableObject.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Objects_CMovableObject.cpp$(PreprocessSuffix) src/Objects/CMovableObject.cpp

$(IntermediateDirectory)/src_World_CGameRequestHandler.cpp$(ObjectSuffix): src/World/CGameRequestHandler.cpp $(IntermediateDirectory)/src_World_CGameRequestHandler.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/src/World/CGameRequestHandler.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_World_CGameRequestHandler.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_World_CGameRequestHandler.cpp$(DependSuffix): src/World/CGameRequestHandler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_World_CGameRequestHandler.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_World_CGameRequestHandler.cpp$(DependSuffix) -MM src/World/CGameRequestHandler.cpp

$(IntermediateDirectory)/src_World_CGameRequestHandler.cpp$(PreprocessSuffix): src/World/CGameRequestHandler.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_World_CGameRequestHandler.cpp$(PreprocessSuffix) src/World/CGameRequestHandler.cpp

$(IntermediateDirectory)/src_World_CWorld.cpp$(ObjectSuffix): src/World/CWorld.cpp $(IntermediateDirectory)/src_World_CWorld.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/src/World/CWorld.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_World_CWorld.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_World_CWorld.cpp$(DependSuffix): src/World/CWorld.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_World_CWorld.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_World_CWorld.cpp$(DependSuffix) -MM src/World/CWorld.cpp

$(IntermediateDirectory)/src_World_CWorld.cpp$(PreprocessSuffix): src/World/CWorld.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_World_CWorld.cpp$(PreprocessSuffix) src/World/CWorld.cpp

$(IntermediateDirectory)/src_World_CInstance.cpp$(ObjectSuffix): src/World/CInstance.cpp $(IntermediateDirectory)/src_World_CInstance.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/src/World/CInstance.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_World_CInstance.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_World_CInstance.cpp$(DependSuffix): src/World/CInstance.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_World_CInstance.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_World_CInstance.cpp$(DependSuffix) -MM src/World/CInstance.cpp

$(IntermediateDirectory)/src_World_CInstance.cpp$(PreprocessSuffix): src/World/CInstance.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_World_CInstance.cpp$(PreprocessSuffix) src/World/CInstance.cpp

$(IntermediateDirectory)/src_Net_CSummonMasterCommandManager.cpp$(ObjectSuffix): src/Net/CSummonMasterCommandManager.cpp $(IntermediateDirectory)/src_Net_CSummonMasterCommandManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/src/Net/CSummonMasterCommandManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Net_CSummonMasterCommandManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Net_CSummonMasterCommandManager.cpp$(DependSuffix): src/Net/CSummonMasterCommandManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Net_CSummonMasterCommandManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Net_CSummonMasterCommandManager.cpp$(DependSuffix) -MM src/Net/CSummonMasterCommandManager.cpp

$(IntermediateDirectory)/src_Net_CSummonMasterCommandManager.cpp$(PreprocessSuffix): src/Net/CSummonMasterCommandManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Net_CSummonMasterCommandManager.cpp$(PreprocessSuffix) src/Net/CSummonMasterCommandManager.cpp

$(IntermediateDirectory)/src_Net_CSummonMasterUser.cpp$(ObjectSuffix): src/Net/CSummonMasterUser.cpp $(IntermediateDirectory)/src_Net_CSummonMasterUser.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/src/Net/CSummonMasterUser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Net_CSummonMasterUser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Net_CSummonMasterUser.cpp$(DependSuffix): src/Net/CSummonMasterUser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Net_CSummonMasterUser.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Net_CSummonMasterUser.cpp$(DependSuffix) -MM src/Net/CSummonMasterUser.cpp

$(IntermediateDirectory)/src_Net_CSummonMasterUser.cpp$(PreprocessSuffix): src/Net/CSummonMasterUser.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Net_CSummonMasterUser.cpp$(PreprocessSuffix) src/Net/CSummonMasterUser.cpp

$(IntermediateDirectory)/src_Net_CSummonMasterApp.cpp$(ObjectSuffix): src/Net/CSummonMasterApp.cpp $(IntermediateDirectory)/src_Net_CSummonMasterApp.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/src/Net/CSummonMasterApp.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Net_CSummonMasterApp.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Net_CSummonMasterApp.cpp$(DependSuffix): src/Net/CSummonMasterApp.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Net_CSummonMasterApp.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Net_CSummonMasterApp.cpp$(DependSuffix) -MM src/Net/CSummonMasterApp.cpp

$(IntermediateDirectory)/src_Net_CSummonMasterApp.cpp$(PreprocessSuffix): src/Net/CSummonMasterApp.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Net_CSummonMasterApp.cpp$(PreprocessSuffix) src/Net/CSummonMasterApp.cpp

$(IntermediateDirectory)/src_Net_cindexpage.cpp$(ObjectSuffix): src/Net/cindexpage.cpp $(IntermediateDirectory)/src_Net_cindexpage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/src/Net/cindexpage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Net_cindexpage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Net_cindexpage.cpp$(DependSuffix): src/Net/cindexpage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Net_cindexpage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Net_cindexpage.cpp$(DependSuffix) -MM src/Net/cindexpage.cpp

$(IntermediateDirectory)/src_Net_cindexpage.cpp$(PreprocessSuffix): src/Net/cindexpage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Net_cindexpage.cpp$(PreprocessSuffix) src/Net/cindexpage.cpp

$(IntermediateDirectory)/src_Net_csitepage.cpp$(ObjectSuffix): src/Net/csitepage.cpp $(IntermediateDirectory)/src_Net_csitepage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/src/Net/csitepage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Net_csitepage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Net_csitepage.cpp$(DependSuffix): src/Net/csitepage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Net_csitepage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Net_csitepage.cpp$(DependSuffix) -MM src/Net/csitepage.cpp

$(IntermediateDirectory)/src_Net_csitepage.cpp$(PreprocessSuffix): src/Net/csitepage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Net_csitepage.cpp$(PreprocessSuffix) src/Net/csitepage.cpp

$(IntermediateDirectory)/src_Net_csuccesspage.cpp$(ObjectSuffix): src/Net/csuccesspage.cpp $(IntermediateDirectory)/src_Net_csuccesspage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/Рабочий стол/projects/SummonMaster/src/Net/csuccesspage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Net_csuccesspage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Net_csuccesspage.cpp$(DependSuffix): src/Net/csuccesspage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Net_csuccesspage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Net_csuccesspage.cpp$(DependSuffix) -MM src/Net/csuccesspage.cpp

$(IntermediateDirectory)/src_Net_csuccesspage.cpp$(PreprocessSuffix): src/Net/csuccesspage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Net_csuccesspage.cpp$(PreprocessSuffix) src/Net/csuccesspage.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/



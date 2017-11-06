##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=SummonMaster
ConfigurationName      :=Release
WorkspacePath          := "/home/anton/projects/LifeBased/LifeSystem"
ProjectPath            := "/home/anton/projects/SummonMaster"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Anton
Date                   :=06/11/17
CodeLitePath           :="/home/anton/.codelite"
LinkerName             :=/usr/bin/i686-linux-gnu-g++
SharedObjectLinkerName :=/usr/bin/i686-linux-gnu-g++ -shared -fPIC
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
AR       := /usr/bin/i686-linux-gnu-ar rcu
CXX      := /usr/bin/i686-linux-gnu-g++
CC       := /usr/bin/i686-linux-gnu-gcc
CXXFLAGS :=  -O2 -pedantic -std=c++14 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/i686-linux-gnu-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/CEventDispatcher.cpp$(ObjectSuffix) $(IntermediateDirectory)/Map_CMap.cpp$(ObjectSuffix) $(IntermediateDirectory)/Map_CHeightMap.cpp$(ObjectSuffix) $(IntermediateDirectory)/Creatures_CCreature.cpp$(ObjectSuffix) $(IntermediateDirectory)/World_CGameRequestHandler.cpp$(ObjectSuffix) $(IntermediateDirectory)/World_CWorld.cpp$(ObjectSuffix) $(IntermediateDirectory)/World_CInstance.cpp$(ObjectSuffix) $(IntermediateDirectory)/Net_CSummonMasterApp.cpp$(ObjectSuffix) $(IntermediateDirectory)/Net_CSummonMasterCommandManager.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/Net_CSummonMasterUser.cpp$(ObjectSuffix) $(IntermediateDirectory)/Net_cindexpage.cpp$(ObjectSuffix) $(IntermediateDirectory)/Net_csitepage.cpp$(ObjectSuffix) $(IntermediateDirectory)/Net_csuccesspage.cpp$(ObjectSuffix) 



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
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/projects/SummonMaster/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/CEventDispatcher.cpp$(ObjectSuffix): CEventDispatcher.cpp $(IntermediateDirectory)/CEventDispatcher.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/projects/SummonMaster/CEventDispatcher.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CEventDispatcher.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CEventDispatcher.cpp$(DependSuffix): CEventDispatcher.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CEventDispatcher.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CEventDispatcher.cpp$(DependSuffix) -MM "CEventDispatcher.cpp"

$(IntermediateDirectory)/CEventDispatcher.cpp$(PreprocessSuffix): CEventDispatcher.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CEventDispatcher.cpp$(PreprocessSuffix) "CEventDispatcher.cpp"

$(IntermediateDirectory)/Map_CMap.cpp$(ObjectSuffix): src/Map/CMap.cpp $(IntermediateDirectory)/Map_CMap.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/projects/SummonMaster/src/Map/CMap.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Map_CMap.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Map_CMap.cpp$(DependSuffix): src/Map/CMap.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Map_CMap.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Map_CMap.cpp$(DependSuffix) -MM "src/Map/CMap.cpp"

$(IntermediateDirectory)/Map_CMap.cpp$(PreprocessSuffix): src/Map/CMap.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Map_CMap.cpp$(PreprocessSuffix) "src/Map/CMap.cpp"

$(IntermediateDirectory)/Map_CHeightMap.cpp$(ObjectSuffix): src/Map/CHeightMap.cpp $(IntermediateDirectory)/Map_CHeightMap.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/projects/SummonMaster/src/Map/CHeightMap.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Map_CHeightMap.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Map_CHeightMap.cpp$(DependSuffix): src/Map/CHeightMap.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Map_CHeightMap.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Map_CHeightMap.cpp$(DependSuffix) -MM "src/Map/CHeightMap.cpp"

$(IntermediateDirectory)/Map_CHeightMap.cpp$(PreprocessSuffix): src/Map/CHeightMap.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Map_CHeightMap.cpp$(PreprocessSuffix) "src/Map/CHeightMap.cpp"

$(IntermediateDirectory)/Creatures_CCreature.cpp$(ObjectSuffix): src/Creatures/CCreature.cpp $(IntermediateDirectory)/Creatures_CCreature.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/projects/SummonMaster/src/Creatures/CCreature.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Creatures_CCreature.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Creatures_CCreature.cpp$(DependSuffix): src/Creatures/CCreature.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Creatures_CCreature.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Creatures_CCreature.cpp$(DependSuffix) -MM "src/Creatures/CCreature.cpp"

$(IntermediateDirectory)/Creatures_CCreature.cpp$(PreprocessSuffix): src/Creatures/CCreature.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Creatures_CCreature.cpp$(PreprocessSuffix) "src/Creatures/CCreature.cpp"

$(IntermediateDirectory)/World_CGameRequestHandler.cpp$(ObjectSuffix): src/World/CGameRequestHandler.cpp $(IntermediateDirectory)/World_CGameRequestHandler.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/projects/SummonMaster/src/World/CGameRequestHandler.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/World_CGameRequestHandler.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/World_CGameRequestHandler.cpp$(DependSuffix): src/World/CGameRequestHandler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/World_CGameRequestHandler.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/World_CGameRequestHandler.cpp$(DependSuffix) -MM "src/World/CGameRequestHandler.cpp"

$(IntermediateDirectory)/World_CGameRequestHandler.cpp$(PreprocessSuffix): src/World/CGameRequestHandler.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/World_CGameRequestHandler.cpp$(PreprocessSuffix) "src/World/CGameRequestHandler.cpp"

$(IntermediateDirectory)/World_CWorld.cpp$(ObjectSuffix): src/World/CWorld.cpp $(IntermediateDirectory)/World_CWorld.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/projects/SummonMaster/src/World/CWorld.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/World_CWorld.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/World_CWorld.cpp$(DependSuffix): src/World/CWorld.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/World_CWorld.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/World_CWorld.cpp$(DependSuffix) -MM "src/World/CWorld.cpp"

$(IntermediateDirectory)/World_CWorld.cpp$(PreprocessSuffix): src/World/CWorld.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/World_CWorld.cpp$(PreprocessSuffix) "src/World/CWorld.cpp"

$(IntermediateDirectory)/World_CInstance.cpp$(ObjectSuffix): src/World/CInstance.cpp $(IntermediateDirectory)/World_CInstance.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/projects/SummonMaster/src/World/CInstance.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/World_CInstance.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/World_CInstance.cpp$(DependSuffix): src/World/CInstance.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/World_CInstance.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/World_CInstance.cpp$(DependSuffix) -MM "src/World/CInstance.cpp"

$(IntermediateDirectory)/World_CInstance.cpp$(PreprocessSuffix): src/World/CInstance.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/World_CInstance.cpp$(PreprocessSuffix) "src/World/CInstance.cpp"

$(IntermediateDirectory)/Net_CSummonMasterApp.cpp$(ObjectSuffix): src/Net/CSummonMasterApp.cpp $(IntermediateDirectory)/Net_CSummonMasterApp.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/projects/SummonMaster/src/Net/CSummonMasterApp.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Net_CSummonMasterApp.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Net_CSummonMasterApp.cpp$(DependSuffix): src/Net/CSummonMasterApp.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Net_CSummonMasterApp.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Net_CSummonMasterApp.cpp$(DependSuffix) -MM "src/Net/CSummonMasterApp.cpp"

$(IntermediateDirectory)/Net_CSummonMasterApp.cpp$(PreprocessSuffix): src/Net/CSummonMasterApp.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Net_CSummonMasterApp.cpp$(PreprocessSuffix) "src/Net/CSummonMasterApp.cpp"

$(IntermediateDirectory)/Net_CSummonMasterCommandManager.cpp$(ObjectSuffix): src/Net/CSummonMasterCommandManager.cpp $(IntermediateDirectory)/Net_CSummonMasterCommandManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/projects/SummonMaster/src/Net/CSummonMasterCommandManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Net_CSummonMasterCommandManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Net_CSummonMasterCommandManager.cpp$(DependSuffix): src/Net/CSummonMasterCommandManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Net_CSummonMasterCommandManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Net_CSummonMasterCommandManager.cpp$(DependSuffix) -MM "src/Net/CSummonMasterCommandManager.cpp"

$(IntermediateDirectory)/Net_CSummonMasterCommandManager.cpp$(PreprocessSuffix): src/Net/CSummonMasterCommandManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Net_CSummonMasterCommandManager.cpp$(PreprocessSuffix) "src/Net/CSummonMasterCommandManager.cpp"

$(IntermediateDirectory)/Net_CSummonMasterUser.cpp$(ObjectSuffix): src/Net/CSummonMasterUser.cpp $(IntermediateDirectory)/Net_CSummonMasterUser.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/projects/SummonMaster/src/Net/CSummonMasterUser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Net_CSummonMasterUser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Net_CSummonMasterUser.cpp$(DependSuffix): src/Net/CSummonMasterUser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Net_CSummonMasterUser.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Net_CSummonMasterUser.cpp$(DependSuffix) -MM "src/Net/CSummonMasterUser.cpp"

$(IntermediateDirectory)/Net_CSummonMasterUser.cpp$(PreprocessSuffix): src/Net/CSummonMasterUser.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Net_CSummonMasterUser.cpp$(PreprocessSuffix) "src/Net/CSummonMasterUser.cpp"

$(IntermediateDirectory)/Net_cindexpage.cpp$(ObjectSuffix): src/Net/cindexpage.cpp $(IntermediateDirectory)/Net_cindexpage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/projects/SummonMaster/src/Net/cindexpage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Net_cindexpage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Net_cindexpage.cpp$(DependSuffix): src/Net/cindexpage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Net_cindexpage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Net_cindexpage.cpp$(DependSuffix) -MM "src/Net/cindexpage.cpp"

$(IntermediateDirectory)/Net_cindexpage.cpp$(PreprocessSuffix): src/Net/cindexpage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Net_cindexpage.cpp$(PreprocessSuffix) "src/Net/cindexpage.cpp"

$(IntermediateDirectory)/Net_csitepage.cpp$(ObjectSuffix): src/Net/csitepage.cpp $(IntermediateDirectory)/Net_csitepage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/projects/SummonMaster/src/Net/csitepage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Net_csitepage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Net_csitepage.cpp$(DependSuffix): src/Net/csitepage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Net_csitepage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Net_csitepage.cpp$(DependSuffix) -MM "src/Net/csitepage.cpp"

$(IntermediateDirectory)/Net_csitepage.cpp$(PreprocessSuffix): src/Net/csitepage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Net_csitepage.cpp$(PreprocessSuffix) "src/Net/csitepage.cpp"

$(IntermediateDirectory)/Net_csuccesspage.cpp$(ObjectSuffix): src/Net/csuccesspage.cpp $(IntermediateDirectory)/Net_csuccesspage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/anton/projects/SummonMaster/src/Net/csuccesspage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Net_csuccesspage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Net_csuccesspage.cpp$(DependSuffix): src/Net/csuccesspage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Net_csuccesspage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Net_csuccesspage.cpp$(DependSuffix) -MM "src/Net/csuccesspage.cpp"

$(IntermediateDirectory)/Net_csuccesspage.cpp$(PreprocessSuffix): src/Net/csuccesspage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Net_csuccesspage.cpp$(PreprocessSuffix) "src/Net/csuccesspage.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/



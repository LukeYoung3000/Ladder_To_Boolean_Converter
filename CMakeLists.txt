# CMakeList.txt : CMake project for Ladder_To_Boolean_Converter, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Ladder_To_Boolean_Converter")

# Add source to this project's executable.
add_executable (
	Ladder_To_Boolean_Converter
	"Ladder_To_Boolean_Converter.cpp"
	"Ladder_To_Boolean_Converter.h"
	"LadderLogicObjects.h"
	"LadderLogicConfig.h"
	"libs/pugixml/src/pugiconfig.hpp"
	"libs/pugixml/src/pugixml.hpp"
	"libs/pugixml/src/pugixml.cpp"
	"LadderLogicObjects.cpp"
	"TruthTableObjects.h"
	"TruthTableObjects.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Ladder_To_Boolean_Converter PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

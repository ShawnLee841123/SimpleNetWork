##-----------------------------------------------------------
##
##-----------------------------------------------------------

if(WIN32)
	add_definitions(-D_WIN_)
endif(WIN32)

#include(${CMAKE_SOURCE_DIR}/common.cmake)

set(APP_files_sources_files
	main.cpp
	WinConsole.h
	WinConsole.cpp
)



source_group("App" FILES ${APP_files_sources_files})

set(App_source_files ${APP_files_sources_files})

set(SOURCE_ ${APP_files_sources_files})


set(LINK_DIRECTORIES)
SET(ProjectName App)


ADD_EXECUTABLE(${ProjectName} ${SOURCE_})
ADD_DEPENDENCIES(${ProjectName} NetWorkCore)
#TARGET_LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../ThirdLib/SystemLib/Lib/Debug $<CONFIG:DEBUG>)
TARGET_LINK_LIBRARIES(${ProjectName} NetWorkCore)
TARGET_LINK_LIBRARIES(${ProjectName} ../../ThirdLib/SystemLib/Lib/Debug/SystemLib)

#if(WIN32)
##	if(CMAKE_CONFIGURATION_TYPE EQUAL Debug)
##	TARGET_LINK_LIBRARIES(${ProjectName} "../ThirdLib/SystemLib/Lib/Debug/SystemLib.lib")
##	elseif(CMAKE_CONFIGURATION_TYPE EQUAL Debug)
##		TARGET_LINK_LIBRARIES(${ProjectName} "../ThirdLib/SystemLib/Lib/Release/SystemLib.lib")
##	endif(CMAKE_CONFIGURATION_TYPE EQUAL Debug)
#	if(CMAKE_CONFIGURATION_TYPE EQUAL Debug)
		
#	elseif(CMAKE_CONFIGURATION_TYPE EQUAL Debug)
#		TARGET_LINK_LIBRARIES(${ProjectName} )
#	endif(CMAKE_CONFIGURATION_TYPE EQUAL Debug)
#elseif(WIN32)
#endif(WIN32)

#include(${CMAKE_SOURCE_DIR}/common.cmake)

SET_TARGET_PROPERTIES(${ProjectName} PROPERTIES FOLDER "App")

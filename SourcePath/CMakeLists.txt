cmake_minimum_required(VERSION 2.6)


if(WIN32)
	set_property(GLOBAL PROPERTY USE_FOLDERS On)
	set(CMAKE_VS_PLATFORM_TOOLSET "v140" CACHE STRING "Platform Toolset" FORCE)
elseif(WIN32)
	##-------------------------------
	##	网上找的那些什么 set(CMAKE_CXX_FLAGS "-std=c++ xxx")，一律不好使，千万不能加引号
	##-------------------------------
	#add_definitions(-std=c++11)	
	add_definitions(-fvisibility=hidden)
	add_definitions(-D_PORT_VERSION -Wno-deprecated -fPIC)
endif(WIN32)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../ThirdLib/SystemLib/Include ${CMAKE_SOURCE_DIR}/../ThirdLib/ThreadCore/Include)

PROJECT(NETWORK)
ADD_SUBDIRECTORY(App)
ADD_SUBDIRECTORY(NetWorkCore)

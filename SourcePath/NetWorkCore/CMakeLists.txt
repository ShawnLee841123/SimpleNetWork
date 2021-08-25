##-------------------------------------------------------------
##
##-------------------------------------------------------------

set(NetWork_System_files_Include_head_file
	Include/System/INetWorkCore.h
	Include/System/NetWorkCore.h
	Include/System/NetWorkCoreVariableDefines.h
)

source_group("NetWork\\Include\\System" FILES ${NetWork_System_files_Include_head_file})

set(NetWork_System_include_files ${NetWork_System_files_Include_head_file})

##-------------------------------------------------------------

set(NetWork_System_files_source_file
	Source/System/NetWorkCore.cpp
)

source_group("NetWork\\Source\\System" FILES ${NetWork_System_files_source_file})

set(NetWork_System_source_files ${NetWork_System_files_source_file})

##-------------------------------------------------------------
set(NetWork_Windows_files_Include_head_file
	Include/Windows/NetWorkCore_Windows.h
)

source_group("NetWork\\Include\\Windows" FILES ${NetWork_Windows_files_Include_head_file})

set(NetWork_Windows_include_files ${NetWork_Windows_files_Include_head_file})


##-------------------------------------------------------------
set(NetWork_Windows_files_source_file
	Source/Windows/NetWorkCore_Windows.cpp
)

source_group("NetWork\\Source\\Windows" FILES ${NetWork_Windows_files_source_file})

set(NetWork_Windows_source_files ${NetWork_Windows_files_source_file})
##-------------------------------------------------------------
set(NetWork_IOCP_files_include_file
	Include/Windows/IOCPCore/IOCPCore.h
	Include/Windows/IOCPcore/IOCPDefines.h
	Include/Windows/IOCPcore/IOCPWorker.h
)

source_group("NetWork\\Include\\Windows\\IOCPCore" FILES ${NetWork_IOCP_files_include_file})

set(NetWork_IOCP_include_files ${NetWork_IOCP_files_include_file})
##-------------------------------------------------------------
set(NetWork_IOCP_files_source_file
	Source/Windows/IOCPCore/IOCPCore.cpp
	Source/Windows/IOCPcore/IOCPDefines.cpp
	Source/Windows/IOCPcore/IOCPWorker.cpp
)

source_group("NetWork\\Source\\Windows\\IOCPCore" FILES ${NetWork_IOCP_files_source_file})

set(NetWork_IOCP_source_files ${NetWork_IOCP_files_source_file})
##-------------------------------------------------------------

if(WIN32)
	add_definitions(-D_WIN_)
	set(SOURCES_
		${NetWork_System_include_files}
		${NetWork_System_source_files}
		${NetWork_Windows_include_files}
		${NetWork_Windows_source_files}
		${NetWork_IOCP_include_files}
		${NetWork_IOCP_source_files}
	)
elseif(WIN32)
endif(WIN32)

SET(ProjectName NetWorkCore)
ADD_LIBRARY(${ProjectName} STATIC ${SOURCES_})
target_link_libraries(${ProjectName} ../../ThirdLib/SystemLib/Lib/Debug/SystemLib)
target_link_libraries(${ProjectName} ../../ThirdLib/ThreadCore/Lib/Debug/ThreadCore)
if(WIN32)
	target_link_libraries(${ProjectName} "ws2_32.lib")
elseif(WIN32)
endif(WIN32)

SET_TARGET_PROPERTIES(${ProjectName} PROPERTIES FOLDER "NetWorkCore")

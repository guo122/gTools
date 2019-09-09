
set(PROJECT_NAME sqlite3)

#set(CMAKE_C_COMPILER g++)
#add_compile_options(-std=c++1y)

#set(INCROOT ${CMAKE_ROOT_DIR}/include/gBase)
#set(SRCROOT ${CMAKE_ROOT_DIR})

set(DIR_SRCS 
	shell.c
	sqlite3.c
	sqlite3.h
	sqlite3ext.h
)

#set(INC_DIR 
    #${CMAKE_ROOT_DIR}/include/gBase
#)

#include_directories(${INC_DIR})

add_library_macro(
	${PROJECT_NAME} 
	SOURCES ${DIR_SRCS}
)

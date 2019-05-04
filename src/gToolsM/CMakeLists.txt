
set(PROJECT_NAME gToolsM)

set(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++1y)

set(INCROOT ${CMAKE_ROOT_DIR}/include/gToolsM)
set(SRCROOT ${CMAKE_ROOT_DIR}/src/gToolsM)

set(DIR_SRCS 
	${INCROOT}/gTimeM.h
	${SRCROOT}/gTimeM.cpp
	${INCROOT}/gToolsM.h
	${SRCROOT}/gToolsM.cpp
)

set(INC_DIR 
    ${CMAKE_ROOT_DIR}/3rd/gBase/include
    ${CMAKE_ROOT_DIR}/include
	${INCROOT}
)

include_directories(${INC_DIR})

set(LINK_LIBS
	gBase
)

link_libraries(${LINK_LIBS})
add_library_macro(
                ${PROJECT_NAME}
                #SOURCES ${DIR_SRCS} ${PLATFORM_SRC} ${BUNDLE_SRCS}
				SOURCES ${DIR_SRCS}
)

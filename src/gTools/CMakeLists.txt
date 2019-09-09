
set(PROJECT_NAME gTools)

set(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++1y)

set(SRCROOT ${CMAKE_ROOT_DIR}/src/gTools)
set(INCROOT ${CMAKE_ROOT_DIR}/include/gTools)

#set(DIR_SRCS 
#${SRCROOT}/main.mm
#)

if(${THE_PROJECT_PREFIX}_OS_IOS)
    set(PLATFORM_SRC
		${SRCROOT}/main.mm
		${INCROOT}/AppDelegate.h
		${SRCROOT}/AppDelegate.mm
		${INCROOT}/ViewController.h
		${SRCROOT}/ViewController.mm
		${INCROOT}/TimeAddViewController.h
		${SRCROOT}/TimeAddViewController.mm
		${INCROOT}/TimeListViewController.h
		${SRCROOT}/TimeListViewController.mm
    )
    source_group("ios" FILES ${PLATFORM_SRC})

	set(BUNDLE_SRCS
		${CMAKE_ROOT_DIR}/ios_resource/Assets.xcassets
		${CMAKE_ROOT_DIR}/ios_resource/Storyboard/LaunchScreen.storyboard
		${CMAKE_ROOT_DIR}/ios_resource/Storyboard/Main.storyboard
	)
elseif(${THE_PROJECT_PREFIX}_OS_WINDOWS)
	set(DIR_SRCS 
		${SRCROOT}/main.cpp
	)
endif()

set(INC_DIR 
    ${CMAKE_ROOT_DIR}/3rd/gBase/include
    ${CMAKE_ROOT_DIR}/include
	${CMAKE_ROOT_DIR}/3rd/sqlite3
	${INCROOT}
)

include_directories(${INC_DIR})

set(LINK_LIBS
	gBase
	gToolsM
	gToolsP
)

link_libraries(${LINK_LIBS})

link_libraries("sqlite3")

if(${THE_PROJECT_PREFIX}_OS_IOS)
link_libraries("-framework Foundation" "-framework UIKit" "-framework CoreGraphics" "-framework QuartzCore" "-framework CoreMotion" "-framework Metal" "-framework OpenGLES" "-framework OpenAL")

add_executable_macro(
                ${PROJECT_NAME}
                #SOURCES ${DIR_SRCS} ${PLATFORM_SRC} ${BUNDLE_SRCS}
                SOURCES ${PLATFORM_SRC} ${BUNDLE_SRCS}
)

set_target_properties(
	${PROJECT_NAME}
	PROPERTIES
	MACOSX_BUNDLE YES
	MACOSX_BUNDLE_INFO_PLIST "${CMAKE_ROOT_DIR}/ios_resource/Info.plist"
	RESOURCE "${BUNDLE_SRCS}"
)

set_target_properties(
	${PROJECT_NAME}
	PROPERTIES
	XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon"
	#XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_LAUNCHIMAGE_NAME "LaunchScreen.storyboard"
	XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
	XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1"
)
elseif(${THE_PROJECT_PREFIX}_OS_WINDOWS)
add_executable_macro(
                ${PROJECT_NAME}
                SOURCES ${DIR_SRCS} 
)
endif()

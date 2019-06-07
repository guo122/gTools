
set(PROJECTNAME gBrick)

#set(CMAKE_C_COMPILER g++)
#add_compile_options(-fno-objc-arc)

set(SRCROOT ${CMAKE_CURRENT_LIST_DIR})
set(INCROOT ${CMAKE_CURRENT_LIST_DIR})
set(RESROOT ${CMAKE_CURRENT_LIST_DIR}/../res)
set(COMMON_RESROOT ${CMAKE_CURRENT_LIST_DIR}/../../ios_resource)
set(BIN_DIR ${CMAKE_ROOT_DIR}/bin)

set(DIR_SRCS 
	${SRCROOT}/AppDelegate.h
	${SRCROOT}/AppDelegate.m
	${SRCROOT}/HomeViewController.h
	${SRCROOT}/HomeViewController.m
	${SRCROOT}/MapViewController.h
	${SRCROOT}/MapViewController.m
	${SRCROOT}/MapView.h
	${SRCROOT}/MapView.m
	${SRCROOT}/MtkController.h
	${SRCROOT}/MtkController.m
	${SRCROOT}/gShaderTypes.h
	${SRCROOT}/main.m
)

set(SHADERS_SRCS
	${SRCROOT}/../shaders/shaders.metal
)

set(BUNDLE_SRCS ${SHADERS_SRCS}
	${RESROOT}/Info.plist
	${COMMON_RESROOT}/Assets.xcassets
	${COMMON_RESROOT}/Storyboard/LaunchScreen.storyboard
	${COMMON_RESROOT}/Storyboard/JustMetal.storyboard
	${COMMON_RESROOT}/icn/icn_blue_add.png
)

SET(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})

add_executable(${PROJECTNAME} ${DIR_SRCS} ${BUNDLE_SRCS})

set_target_properties(
	${PROJECTNAME}
	PROPERTIES
	MACOSX_BUNDLE YES
	MACOSX_BUNDLE_INFO_PLIST "${RESROOT}/Info.plist"
	RESOURCE "${BUNDLE_SRCS}"
)
	
set_target_properties(
	${PROJECTNAME}
	PROPERTIES
	XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon"
	#XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_LAUNCHIMAGE_NAME "LaunchImage"
	XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
	XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1"
	XCODE_ATTRIBUTE_CLANG_ENABLE_MODULES "YES"
	XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "${BUNDLE_IDENT}"
)

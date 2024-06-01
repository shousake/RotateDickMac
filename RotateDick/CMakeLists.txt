cmake_minimum_required(VERSION 3.10)
project(RotateDick)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(SDL2 REQUIRED)


include_directories(/opt/homebrew/Cellar/sdl2/2.30.3/include)


add_executable(${PROJECT_NAME} main.cpp)


set(MACOSX_BUNDLE_ICON_FILE ${CMAKE_SOURCE_DIR}/Resources/Icon.icns)
set(MACOSX_BUNDLE_INFO_PLIST /opt/homebrew/share/cmake/Modules/MacOSXBundleInfo.plist.in)
set_target_properties(${PROJECT_NAME} PROPERTIES
  RESOURCE "${MACOSX_BUNDLE_ICON_FILE}"
  MACOSX_BUNDLE_ICON_FILE ${CMAKE_SOURCE_DIR}/Resources/Icon.icns
  MACOSX_BUNDLE 1  # Add this line
  MACOSX_BUNDLE_INFO_PLIST ${MACOSX_BUNDLE_INFO_PLIST}
  MACOSX_BUNDLE_BUNDLE_NAME RotateDick.app
  MACOSX_BUNDLE_BUNDLE_VERSION "5.20"
  MACOSX_BUNDLE_SHORT_VERSION_STRING "VersionString"
  MACOSX_BUNDLE_GUI_IDENTIFIER "com.Rotate.Dick"
  XCODE_ATTRIBUTE_ENABLE_HARDENED_RUNTIME YES
)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
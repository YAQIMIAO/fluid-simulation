# Install script for directory: /Users/yaqi/Academic/CS/184/hw/myq/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/yaqi/Academic/CS/184/hw/myq/fluid-simulator")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/yaqi/Academic/CS/184/hw/myq" TYPE EXECUTABLE FILES "/Users/yaqi/Academic/CS/184/hw/myq/build/fluid-simulator")
  if(EXISTS "$ENV{DESTDIR}/Users/yaqi/Academic/CS/184/hw/myq/fluid-simulator" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/yaqi/Academic/CS/184/hw/myq/fluid-simulator")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -change "@rpath/libglfw.3.dylib" "lib/libglfw.3.dylib"
      "$ENV{DESTDIR}/Users/yaqi/Academic/CS/184/hw/myq/fluid-simulator")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/yaqi/Academic/CS/184/hw/myq/build/ext/nanogui/ext_build/glfw/src"
      "$ENV{DESTDIR}/Users/yaqi/Academic/CS/184/hw/myq/fluid-simulator")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/yaqi/Academic/CS/184/hw/myq/build/ext/nanogui"
      "$ENV{DESTDIR}/Users/yaqi/Academic/CS/184/hw/myq/fluid-simulator")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}/Users/yaqi/Academic/CS/184/hw/myq/fluid-simulator")
    endif()
  endif()
endif()


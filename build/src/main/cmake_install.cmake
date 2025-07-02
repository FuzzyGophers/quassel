# Install script for directory: /Users/aaronbauman/repos/quassel/src/main

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/aaronbauman/repos/quassel/build/bundles")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Core" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/aaronbauman/repos/quassel/build/bundles/Quassel Core.app")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/aaronbauman/repos/quassel/build/bundles" TYPE DIRECTORY FILES "/Users/aaronbauman/repos/quassel/build/Quassel Core.app" USE_SOURCE_PERMISSIONS)
  if(EXISTS "$ENV{DESTDIR}/Users/aaronbauman/repos/quassel/build/bundles/Quassel Core.app/Contents/MacOS/Quassel Core" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/aaronbauman/repos/quassel/build/bundles/Quassel Core.app/Contents/MacOS/Quassel Core")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/aaronbauman/repos/quassel/build/bundles/lib"
      "$ENV{DESTDIR}/Users/aaronbauman/repos/quassel/build/bundles/Quassel Core.app/Contents/MacOS/Quassel Core")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Core" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/aaronbauman/repos/quassel/build/bundles/Quassel Core.app/Contents/Resources/qt.conf;/Users/aaronbauman/repos/quassel/build/bundles/Quassel Core.app/Contents/Resources/quassel.icns")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/aaronbauman/repos/quassel/build/bundles/Quassel Core.app/Contents/Resources" TYPE FILE FILES
    "/Users/aaronbauman/repos/quassel/data/qt.conf"
    "/Users/aaronbauman/repos/quassel/build/pics/quassel.icns"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Core" OR NOT CMAKE_INSTALL_COMPONENT)
  
                execute_process(
                    COMMAND /opt/homebrew/bin/cmake -P /Users/aaronbauman/repos/quassel/build/FinalizeBundle_Core.cmake
                    RESULT_VARIABLE result
                )
                if(NOT result EQUAL 0)
                    message(FATAL_ERROR "Finalizing bundle failed.")
                endif()
            
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Client" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/aaronbauman/repos/quassel/build/bundles/Quassel Client.app")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/aaronbauman/repos/quassel/build/bundles" TYPE DIRECTORY FILES "/Users/aaronbauman/repos/quassel/build/Quassel Client.app" USE_SOURCE_PERMISSIONS)
  if(EXISTS "$ENV{DESTDIR}/Users/aaronbauman/repos/quassel/build/bundles/Quassel Client.app/Contents/MacOS/Quassel Client" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/aaronbauman/repos/quassel/build/bundles/Quassel Client.app/Contents/MacOS/Quassel Client")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/aaronbauman/repos/quassel/build/bundles/lib"
      "$ENV{DESTDIR}/Users/aaronbauman/repos/quassel/build/bundles/Quassel Client.app/Contents/MacOS/Quassel Client")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Client" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/aaronbauman/repos/quassel/build/bundles/Quassel Client.app/Contents/Resources/qt.conf;/Users/aaronbauman/repos/quassel/build/bundles/Quassel Client.app/Contents/Resources/quassel.icns")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/aaronbauman/repos/quassel/build/bundles/Quassel Client.app/Contents/Resources" TYPE FILE FILES
    "/Users/aaronbauman/repos/quassel/data/qt.conf"
    "/Users/aaronbauman/repos/quassel/build/pics/quassel.icns"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Client" OR NOT CMAKE_INSTALL_COMPONENT)
  
                execute_process(
                    COMMAND /opt/homebrew/bin/cmake -P /Users/aaronbauman/repos/quassel/build/FinalizeBundle_Client.cmake
                    RESULT_VARIABLE result
                )
                if(NOT result EQUAL 0)
                    message(FATAL_ERROR "Finalizing bundle failed.")
                endif()
            
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Mono" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/aaronbauman/repos/quassel/build/bundles/Quassel.app")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/aaronbauman/repos/quassel/build/bundles" TYPE DIRECTORY FILES "/Users/aaronbauman/repos/quassel/build/Quassel.app" USE_SOURCE_PERMISSIONS)
  if(EXISTS "$ENV{DESTDIR}/Users/aaronbauman/repos/quassel/build/bundles/Quassel.app/Contents/MacOS/Quassel" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/aaronbauman/repos/quassel/build/bundles/Quassel.app/Contents/MacOS/Quassel")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/aaronbauman/repos/quassel/build/bundles/lib"
      "$ENV{DESTDIR}/Users/aaronbauman/repos/quassel/build/bundles/Quassel.app/Contents/MacOS/Quassel")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Mono" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/aaronbauman/repos/quassel/build/bundles/Quassel.app/Contents/Resources/qt.conf;/Users/aaronbauman/repos/quassel/build/bundles/Quassel.app/Contents/Resources/quassel.icns")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/aaronbauman/repos/quassel/build/bundles/Quassel.app/Contents/Resources" TYPE FILE FILES
    "/Users/aaronbauman/repos/quassel/data/qt.conf"
    "/Users/aaronbauman/repos/quassel/build/pics/quassel.icns"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Mono" OR NOT CMAKE_INSTALL_COMPONENT)
  
                execute_process(
                    COMMAND /opt/homebrew/bin/cmake -P /Users/aaronbauman/repos/quassel/build/FinalizeBundle_Mono.cmake
                    RESULT_VARIABLE result
                )
                if(NOT result EQUAL 0)
                    message(FATAL_ERROR "Finalizing bundle failed.")
                endif()
            
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/Users/aaronbauman/repos/quassel/build/src/main/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()

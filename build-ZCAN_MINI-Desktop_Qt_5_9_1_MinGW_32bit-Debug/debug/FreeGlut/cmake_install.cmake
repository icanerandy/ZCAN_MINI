# Install script for directory: C:/Users/icaner/Desktop/freeglut-3.4.0

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/freeglut")
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

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/lib/Debug/freeglutd.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/lib/Release/freeglut.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/lib/MinSizeRel/freeglut.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/lib/RelWithDebInfo/freeglut.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/bin/Debug/freeglutd.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/bin/Release/freeglut.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/bin/MinSizeRel/freeglut.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/bin/RelWithDebInfo/freeglut.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/bin/Debug/freeglutd.pdb")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/lib/Debug/freeglut_staticd.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/lib/Release/freeglut_static.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/lib/MinSizeRel/freeglut_static.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/lib/RelWithDebInfo/freeglut_static.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/GL" TYPE FILE FILES
    "C:/Users/icaner/Desktop/freeglut-3.4.0/include/GL/freeglut.h"
    "C:/Users/icaner/Desktop/freeglut-3.4.0/include/GL/freeglut_ucall.h"
    "C:/Users/icaner/Desktop/freeglut-3.4.0/include/GL/freeglut_ext.h"
    "C:/Users/icaner/Desktop/freeglut-3.4.0/include/GL/freeglut_std.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE RENAME "freeglut.pc" FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/freeglut.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT/FreeGLUTTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT/FreeGLUTTargets.cmake"
         "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/CMakeFiles/Export/6f3d6babffe806515ac5156322d25f7d/FreeGLUTTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT/FreeGLUTTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT/FreeGLUTTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT" TYPE FILE FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/CMakeFiles/Export/6f3d6babffe806515ac5156322d25f7d/FreeGLUTTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT" TYPE FILE FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/CMakeFiles/Export/6f3d6babffe806515ac5156322d25f7d/FreeGLUTTargets-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT" TYPE FILE FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/CMakeFiles/Export/6f3d6babffe806515ac5156322d25f7d/FreeGLUTTargets-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT" TYPE FILE FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/CMakeFiles/Export/6f3d6babffe806515ac5156322d25f7d/FreeGLUTTargets-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT" TYPE FILE FILES "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/CMakeFiles/Export/6f3d6babffe806515ac5156322d25f7d/FreeGLUTTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FreeGLUT" TYPE FILE FILES
    "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/FreeGLUT/FreeGLUTConfig.cmake"
    "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/FreeGLUT/FreeGLUTConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/Project/Qt5/ZCAN_MINI/build-ZCAN_MINI-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/FreeGlut/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
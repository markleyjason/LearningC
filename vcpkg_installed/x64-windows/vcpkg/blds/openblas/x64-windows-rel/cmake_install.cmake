# Install script for directory: C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/src/77a956eb52-3cc04fdab8.clean

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/pkgs/openblas_x64-windows")
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
  set(CMAKE_CROSSCOMPILING "OFF")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/getarch.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/getarch_2nd.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/lib/Release/openblas.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/lib/openblas.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openblas" TYPE FILE FILES "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/openblas_config.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openblas" TYPE FILE FILES "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/generated/cblas.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/openblas.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/OpenBLAS" TYPE FILE FILES "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/OpenBLASConfig.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/OpenBLAS" TYPE FILE RENAME "OpenBLASConfigVersion.cmake" FILES "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/OpenBLASConfigVersion.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/OpenBLAS/OpenBLASTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/OpenBLAS/OpenBLASTargets.cmake"
         "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/CMakeFiles/Export/a8c2ccb19d637ca60c41bd91c96a4ab5/OpenBLASTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/OpenBLAS/OpenBLASTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/OpenBLAS/OpenBLASTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/OpenBLAS" TYPE FILE FILES "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/CMakeFiles/Export/a8c2ccb19d637ca60c41bd91c96a4ab5/OpenBLASTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/OpenBLAS" TYPE FILE FILES "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/CMakeFiles/Export/a8c2ccb19d637ca60c41bd91c96a4ab5/OpenBLASTargets-release.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/interface/cmake_install.cmake")
  include("C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/driver/level2/cmake_install.cmake")
  include("C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/driver/level3/cmake_install.cmake")
  include("C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/driver/others/cmake_install.cmake")
  include("C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/kernel/cmake_install.cmake")
  include("C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/utest/cmake_install.cmake")
  include("C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/ctest/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
  file(WRITE "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/openblas/x64-windows-rel/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()

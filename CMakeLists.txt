cmake_minimum_required(VERSION 3.15)

# Project details
project(
  "fan_controller"
  VERSION 1.0.0
  LANGUAGES C
)



# build options: (configurable area)
option(${PROJECT_NAME}_BUILD_RELEASE "Build for release." OFF)
option(${PROJECT_NAME}_BUILD_WITH_APP_MOCK "Build the executable that simulates application level code" ON)
option(${PROJECT_NAME}_ENABLE_UNIT_TEST "Enable unit tests for fan_controller part" ON)
# end of build options


if(${CMAKE_HOST_UNIX})
  set(CMAKE_C_COMPILER /usr/bin/cc)
elseif(${CMAKE_HOST_WIN32})
  set(CMAKE_C_COMPILER mingw)
endif()

if(${PROJECT_NAME}_BUILD_RELEASE)
  set(CMAKE_BUILD_TYPE "Release")
else()
  set(CMAKE_BUILD_TYPE "Debug")
endif()

add_subdirectory(fan_controller)
if(${PROJECT_NAME}_BUILD_WITH_APP_MOCK)
  add_subdirectory(application_mock)
endif()
if(${PROJECT_NAME}_ENABLE_UNIT_TEST)
  enable_testing()
  add_subdirectory(test)
endif()
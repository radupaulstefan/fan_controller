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
# end of build options

if(${PROJECT_NAME}_BUILD_RELEASE)
  set(CMAKE_BUILD_TYPE "Release")
else()
  set(CMAKE_BUILD_TYPE "Debug")
endif()

add_subdirectory(fan_controller)
if(${PROJECT_NAME}_BUILD_WITH_APP_MOCK)
  add_subdirectory(application_mock)
endif()
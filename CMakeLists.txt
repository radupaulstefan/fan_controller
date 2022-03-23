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


# Add headears and sources for library
set(sources 
      src/fan_controller/simulated_register_area.c
      src/fan_controller/fan_driver.c
      src/fan_controller/fan_control_protocol.c)

set(headers
      include/fan_controller/simulated_register_area.h
      include/fan_controller/fan_driver.h
      include/fan_controller/registers.h
      include/fan_controller/fan_control_protocol.h)


add_library(${PROJECT_NAME} ${headers} ${sources})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    include/fan_controller
)

if(${PROJECT_NAME}_BUILD_WITH_APP_MOCK)
# Add sources for app mock
  set(mock_sources
        src/main.c
        src/wireless_receiver.c)
  add_executable(${PROJECT_NAME}_app_mock ${mock_sources})
endif()


message(INFO "sdafasdfasdfasdfasd ${CMAKE_SOURCE_DIR}")
# target_link_libraries(${PROJECT_NAME}_APP_MOCK_EXECUTABLE ${CMAKE_SOURCE_DIR}/build/fan_controller}


# Add pthread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
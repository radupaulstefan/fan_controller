cmake_minimum_required(VERSION 3.15)

project(
  "tests"
  VERSION 1.0.0
  LANGUAGES C
)

include(FetchContent)

FetchContent_Declare(
  cmocka
  GIT_REPOSITORY https://git.cryptomilk.org/projects/cmocka.git
  GIT_TAG        cmocka-1.1.5
  GIT_SHALLOW    1
)

set(WITH_STATIC_LIB ON CACHE BOOL "CMocka: Build with a static library" FORCE)
# set(WITH_CMOCKERY_SUPPORT OFF CACHE BOOL "CMocka: Install a cmockery header" FORCE)
# set(WITH_EXAMPLES OFF CACHE BOOL "CMocka: Build examples" FORCE)
# set(UNIT_TESTING OFF CACHE BOOL "CMocka: Build with unit testing" FORCE)
# set(PICKY_DEVELOPER OFF CACHE BOOL "CMocka: Build with picky developer flags" FORCE)

FetchContent_MakeAvailable(cmocka)

set(sources
      src/tests.c
      ${CMAKE_SOURCE_DIR}/fan_controller/src/simulated_register_area.c
      ${CMAKE_SOURCE_DIR}/fan_controller/src/fan_driver.c
      ${CMAKE_SOURCE_DIR}/fan_controller/src/fan_control_protocol.c)


add_executable(${PROJECT_NAME} ${sources})
target_compile_features(${PROJECT_NAME} PRIVATE c_std_99)
target_link_libraries(${PROJECT_NAME} PRIVATE cmocka-static)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/fan_controller/include ${CMAKE_SOURCE_DIR}/fan_controller/public)

enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
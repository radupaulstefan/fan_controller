
set(mock_sources
    src/main.c
    src/wireless_receiver.c)
add_executable(${PROJECT_NAME}_app_mock ${mock_sources})

target_include_directories(
${PROJECT_NAME}_app_mock
PUBLIC
include
include/fan_controller
)

target_link_libraries(${PROJECT_NAME}_app_mock LINK_PUBLIC fan_controller)


# Add pthread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
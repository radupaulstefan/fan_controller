# Add headears and sources for library
set(sources 
      src/simulated_register_area.c
      src/fan_driver.c
      src/fan_control_protocol.c)

set(headers
      include/simulated_register_area.h
      include/fan_driver.h
      include/registers.h
      public/fan_control_protocol.h)


add_library(${PROJECT_NAME} ${headers} ${sources})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    public
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    include
)
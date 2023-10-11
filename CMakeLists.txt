cmake_minimum_required(VERSION 3.5)
project(pedsim_original)

# #------------------ Configuration ------------------#
# option(SHALL_DEBUG "Enable debug features" OFF)
# option(SHALL_PROFILE "Enable the code profiling feature" OFF)
# option(CMAKE_VERBOSE_MAKEFILE "Full compiler output" ON)


# #----------------- Compiler Flags ------------------#
# add_definitions(-Wall -Wunused -std=c++0x -pipe)

# #debugging
# if(SHALL_DEBUG)
#   message("Debugging activated")
#   add_definitions(-O0 -DDEBUG -ggdb -g3 -rdynamic)
# else(SHALL_DEBUG)
#   message("Debugging deactivated")
#   add_definitions(-Os)
# endif(SHALL_DEBUG)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()
add_compile_options(-DCMAKE_BUILD_TYPE=Release)


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(Boost REQUIRED)

include_directories(
  include/${PROJECT_NAME}
  ${Boost_INCLUDE_DIRS}
)

# set(SOURCES
#   src/ped_agent.cpp
#   src/ped_angle.cpp
#   src/ped_obstacle.cpp
#   src/ped_scene.cpp
#   src/ped_tree.cpp
#   src/ped_vector.cpp
#   src/ped_waypoint.cpp
# )

add_library(${PROJECT_NAME} SHARED
  src/ped_agent.cpp
  src/ped_angle.cpp
  src/ped_obstacle.cpp
  src/ped_scene.cpp
  src/ped_tree.cpp
  src/ped_vector.cpp
  src/ped_waypoint.cpp
)
target_include_directories(${PROJECT_NAME}
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include/${PROJECT_NAME}>"
)
ament_target_dependencies(${PROJECT_NAME}
  rclcpp
)
target_link_libraries(${PROJECT_NAME} ${BOOST_LIBRARIES})

# INSTALL
install(TARGETS ${PROJECT_NAME}
  EXPORT "export_${PROJECT_NAME}"
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin # Was lib
  INCLUDES DESTINATION include
)

install(DIRECTORY include/
  DESTINATION include)

## FINALIZE PACKAGE ##
ament_export_include_directories(include/${PROJECT_NAME})
ament_export_dependencies(rclcpp)
ament_export_dependencies(Boost)
ament_export_targets("export_${PROJECT_NAME}")

ament_package()

cmake_minimum_required(VERSION 2.8.3)
project(gripper_control)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0")

SET(CMAKE_BUILD_TYPE Debug)

#==============================================================================
# Dependencies
#==============================================================================
find_package(catkin REQUIRED COMPONENTS roscpp controller_interface hardware_interface pluginlib ecl_geometry  )
catkin_package(CATKIN_DEPENDS message_runtime INCLUDE_DIRS include)

include_directories(
        include
        ${catkin_INCLUDE_DIRS}
)

#==============================================================================
# Libraries
#==============================================================================
add_executable(gripper_control src/gripper_control.cpp include/gripper_control/gripper_control.hpp)
target_link_libraries(gripper_control ${catkin_LIBRARIES})
#==============================================================================
# Installation
#==============================================================================
install(TARGETS
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        )

install(FILES
        package.xml
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
        )

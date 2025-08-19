cmake_minimum_required(VERSION 3.10)
project(movegroup)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 依赖包
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(image_transport REQUIRED)  
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(VISP REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(moveit_core REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(moveit_ros_planning REQUIRED)
find_package(service_interfaces REQUIRED)

add_executable(movegroup src/movegroup.cpp)

# 链接依赖库

ament_target_dependencies(
  movegroup
  rclcpp
  moveit_core
  moveit_ros_planning_interface
  moveit_ros_planning
  sensor_msgs
  std_srvs
  std_msgs
  service_interfaces
)

# 链接第三方库
target_link_libraries(movegroup
  ${OpenCV_LIBS}
  ${VISP_LIBRARIES}
  Eigen3::Eigen 
)

# 指定头文件搜索路径
target_include_directories(movegroup PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
# 安装目标
install(TARGETS
  movegroup
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

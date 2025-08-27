cmake_minimum_required(VERSION 3.10)
project(ik)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 依赖包
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED) 
find_package(Eigen3 REQUIRED)
find_package(std_srvs REQUIRED)
find_package(pinocchio REQUIRED)
add_executable(ik src/ik.cpp)

# 链接依赖库
ament_target_dependencies(
  ik
  rclcpp  
  sensor_msgs
  Eigen3
  std_srvs
  pinocchio 
)

# 链接第三方库
target_link_libraries(ik
  Eigen3::Eigen
  ${pinocchio_LIBRARIES} 
)

# 指定头文件搜索路径
target_include_directories(ik PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${pinocchio_INCLUDE_DIRS}
)

# 安装目标
install(TARGETS
  ik
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

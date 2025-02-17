cmake_minimum_required(VERSION 3.8)
project(calculator_2)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# 添加可执行文件
add_executable(calculator_publisher src/calculator_publisher.cpp)
ament_target_dependencies(calculator_publisher rclcpp std_msgs)

add_executable(calculator_subscriber src/calculator_subscriber.cpp)
ament_target_dependencies(calculator_subscriber rclcpp std_msgs)

# 安装可执行文件
install(TARGETS
  calculator_publisher
  calculator_subscriber
  DESTINATION lib/${PROJECT_NAME})

# 添加
install(DIRECTORY launch
    DESTINATION share/${PROJECT_NAME})

# 如果需要测试
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

#ifndef CALCULATOR_PUBLISHER_HPP
#define CALCULATOR_PUBLISHER_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"

class CalculatorPublisher : public rclcpp::Node
{
public:
  CalculatorPublisher();
  void run();

private:
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_num1_;
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_num2_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_op_;
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_command_;
};

#endif // CALCULATOR_PUBLISHER_HPP

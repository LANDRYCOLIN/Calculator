#ifndef CALCULATOR_SUBSCRIBER_HPP
#define CALCULATOR_SUBSCRIBER_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
#include <vector>
#include <optional>
#include <limits>
co
class CalculatorSubscriber : public rclcpp::Node
{
public:
  CalculatorSubscriber();

private:
  void num1_callback(const std_msgs::msg::Float64::SharedPtr msg);
  void num2_callback(const std_msgs::msg::Float64::SharedPtr msg);
  void operation_callback(const std_msgs::msg::String::SharedPtr msg);
  void command_callback(const std_msgs::msg::Int32::SharedPtr msg);

  double perform_calculation(double num1, double num2, const std::string &operation);
  void save_history(double result);
  void display_history();
  void clear_history();

  rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_num1_;
  rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_num2_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_op_;
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_command_;

  std::optional<double> num1_;
  std::optional<double> num2_;
  std::string operation_;
  std::vector<double> history_;
};

#endif // CALCULATOR_SUBSCRIBER_HPP

#include "calculator_subscriber.hpp"

CalculatorSubscriber::CalculatorSubscriber() : Node("calculator_subscriber")
{
  subscription_num1_ = this->create_subscription<std_msgs::msg::Float64>(
      "num1", 10, std::bind(&CalculatorSubscriber::num1_callback, this, std::placeholders::_1));
  subscription_num2_ = this->create_subscription<std_msgs::msg::Float64>(
      "num2", 10, std::bind(&CalculatorSubscriber::num2_callback, this, std::placeholders::_1));
  subscription_op_ = this->create_subscription<std_msgs::msg::String>(
      "operation", 10, std::bind(&CalculatorSubscriber::operation_callback, this, std::placeholders::_1));
  subscription_command_ = this->create_subscription<std_msgs::msg::Int32>(
      "command", 10, std::bind(&CalculatorSubscriber::command_callback, this, std::placeholders::_1));

  history_.reserve(5); // 保留前五次计算结果
}

void CalculatorSubscriber::num1_callback(const std_msgs::msg::Float64::SharedPtr msg)
{
  num1_ = msg->data;
}

void CalculatorSubscriber::num2_callback(const std_msgs::msg::Float64::SharedPtr msg)
{
  num2_ = msg->data;
}

void CalculatorSubscriber::operation_callback(const std_msgs::msg::String::SharedPtr msg)
{
  operation_ = msg->data;
}

void CalculatorSubscriber::command_callback(const std_msgs::msg::Int32::SharedPtr msg)
{
  int command = msg->data;
  if (command == 1 && num1_ && num2_ && !operation_.empty())
  {
    double result = perform_calculation(*num1_, *num2_, operation_);
    save_history(result);
    RCLCPP_INFO(this->get_logger(), "运算结果: %.2f", result);
  }
  else if (command == 2)
  {
    display_history();
  }
  else if (command == 3)
  {
    clear_history();
  }
  else
  {
    RCLCPP_WARN(this->get_logger(), "无效指令");
  }
}

double CalculatorSubscriber::perform_calculation(double num1, double num2, const std::string &operation)
{
  if (operation == "+")
    return num1 + num2;
  else if (operation == "-")
    return num1 - num2;
  else if (operation == "*")
    return num1 * num2;
  else if (operation == "/")
    return num2 != 0 ? num1 / num2 : std::numeric_limits<double>::infinity();
  else
    return 0.0;
}

void CalculatorSubscriber::save_history(double result)
{
  if (history_.size() >= 5)
  {
    history_.erase(history_.begin());
  }
  history_.push_back(result);
}

void CalculatorSubscriber::display_history()
{
  RCLCPP_INFO(this->get_logger(), "历史记录:");
  if (history_.empty())
  {
    RCLCPP_INFO(this->get_logger(), "无历史记录");
  }
  for (const auto &res : history_)
  {
    RCLCPP_INFO(this->get_logger(), "%.2f", res);
  }
}

void CalculatorSubscriber::clear_history()
{
  history_.clear();
  RCLCPP_INFO(this->get_logger(), "历史记录已清除");
}

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CalculatorSubscriber>());
  rclcpp::shutdown();
  return 0;
}

#include "calculator_publisher.hpp"

CalculatorPublisher::CalculatorPublisher() : Node("calculator_publisher")
{
  publisher_num1_ = this->create_publisher<std_msgs::msg::Float64>("num1", 10);
  publisher_num2_ = this->create_publisher<std_msgs::msg::Float64>("num2", 10);
  publisher_op_ = this->create_publisher<std_msgs::msg::String>("operation", 10);
  publisher_command_ = this->create_publisher<std_msgs::msg::Int32>("command", 10);
}

void CalculatorPublisher::run()
{
  while (rclcpp::ok())
  {
    int command;
    RCLCPP_INFO(this->get_logger(), "\n请输入操作：\n1 - 进行运算\n2 - 查看历史记录\n3 - 清除历史记录");

    // 检查是否有输入
    if (std::cin >> command)
    {
      auto msg_command = std_msgs::msg::Int32();
      msg_command.data = command;

      if (command == 1)
      {
        auto msg_num1 = std_msgs::msg::Float64();
        auto msg_num2 = std_msgs::msg::Float64();
        auto msg_op = std_msgs::msg::String();

        RCLCPP_INFO(this->get_logger(), "请输入两个数字和运算符(+, -, *, /):");
        std::cin >> msg_num1.data >> msg_num2.data >> msg_op.data;

        publisher_num1_->publish(msg_num1);
        publisher_num2_->publish(msg_num2);
        publisher_op_->publish(msg_op);
        RCLCPP_INFO(this->get_logger(), "发布: %.2f %s %.2f", msg_num1.data, msg_op.data.c_str(), msg_num2.data);
      }

      publisher_command_->publish(msg_command);
    }
    else
    {
      std::cin.clear(); // 清除错误标志
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略输入
    }

    rclcpp::spin_some(shared_from_this());  // 继续处理ROS的消息
  }
}



int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<CalculatorPublisher>();
  node->run();
  rclcpp::shutdown();
  return 0;
}

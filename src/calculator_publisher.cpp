#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"

class CalculatorPublisher : public rclcpp::Node
{
public:
  CalculatorPublisher() : Node("calculator_publisher")
  {
    publisher_num1_ = this->create_publisher<std_msgs::msg::Float64>("num1", 10);
    publisher_num2_ = this->create_publisher<std_msgs::msg::Float64>("num2", 10);
    publisher_op_ = this->create_publisher<std_msgs::msg::String>("operation", 10);
    publisher_command_ = this->create_publisher<std_msgs::msg::Int32>("command", 10);
  }

  void run()
  {
    while (rclcpp::ok())
    {
      int command;
      RCLCPP_INFO(this->get_logger(), "\n请输入操作：\n1 - 进行运算\n2 - 查看历史记录\n3 - 清除历史记录");
      std::cin >> command;

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
  }

private:
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_num1_;
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_num2_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_op_;
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_command_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<CalculatorPublisher>();
  node->run();
  rclcpp::shutdown();
  return 0;
}

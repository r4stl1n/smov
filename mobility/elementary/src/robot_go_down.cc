#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"

#include "front_board_msgs/msg/servo_array.hpp"
#include "front_board_msgs/msg/servo.hpp"

#include "back_board_msgs/msg/servo_array.hpp"
#include "back_board_msgs/msg/servo.hpp"

using namespace std::chrono_literals;

namespace smov {

class SMOVGoDown : public rclcpp::Node {
  public:
    SMOVGoDown()
    : Node("smov_go_down"), count(0) {
      RCLCPP_INFO(this->get_logger(), "The SMOV has decided to retreat after a long and perilous battle.");
      front_publisher = this->create_publisher<front_board_msgs::msg::ServoArray>("servos_absolute", 10);
      back_publisher = this->create_publisher<back_board_msgs::msg::ServoArray>("servos_absolute", 10);
      timer = this->create_wall_timer(500ms, std::bind(&SMOVGoDown::call, this));
    }

  private:
    void call() {
      call_front_board();
      call_back_board();
    }

    void call_front_board() {
      // Setting up the first servo on port 0.
      auto servo_0 = front_board_msgs::msg::Servo();
      servo_0.servo = 1;
      servo_0.value = 100;

      // Setting up the second servo on port 15.
      auto servo_15 = front_board_msgs::msg::Servo();
      servo_15.servo = 16;
      servo_15.value = 548;

      auto message = front_board_msgs::msg::ServoArray();

      // Pushing the servos to the array.
      message.servos.push_back(servo_0);
      message.servos.push_back(servo_15);

      front_publisher->publish(message);
    }

    void call_back_board() {
      // Setting up the first servo on port 0.
      auto servo_0 = back_board_msgs::msg::Servo();
      servo_0.servo = 1;
      servo_0.value = 100;

      // Setting up the second servo on port 15.
      auto servo_15 = back_board_msgs::msg::Servo();
      servo_15.servo = 16;
      servo_15.value = 548;

      auto message = back_board_msgs::msg::ServoArray();

      // Pushing the servos to the array.
      message.servos.push_back(servo_0);
      message.servos.push_back(servo_15);

      back_publisher->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer;
    rclcpp::Publisher<front_board_msgs::msg::ServoArray>::SharedPtr front_publisher;
    rclcpp::Publisher<back_board_msgs::msg::ServoArray>::SharedPtr back_publisher;
    size_t count;
};

}

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<smov::SMOVGoDown>());
  rclcpp::shutdown();
  return 0;
}

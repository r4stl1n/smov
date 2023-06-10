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

class SMOVWakeUp : public rclcpp::Node {
  public:
    SMOVWakeUp()
    : Node("smov_wake_up"), count(0) {
      RCLCPP_INFO(this->get_logger(), "The SMOV has awakened!");
      front_publisher = this->create_publisher<front_board_msgs::msg::ServoArray>("servos_absolute", 10);
      back_publisher = this->create_publisher<back_board_msgs::msg::ServoArray>("servos_absolute", 10);
      timer = this->create_wall_timer(500ms, std::bind(&SMOVWakeUp::call, this));
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
      servo_0.value = 420;

      // Setting up the second servo on port 15.
      auto servo_15 = front_board_msgs::msg::Servo();
      servo_15.servo = 16;
      servo_15.value = 240;

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
      servo_0.value = 420;

      // Setting up the second servo on port 15.
      auto servo_15 = back_board_msgs::msg::Servo();
      servo_15.servo = 16;
      servo_15.value = 240;

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
  rclcpp::spin(std::make_shared<smov::SMOVWakeUp>());
  rclcpp::shutdown();
  return 0;
}

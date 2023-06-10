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

class SMOVLockLegs : public rclcpp::Node {
  public:
    SMOVLockLegs()
    : Node("smov_lock_legs"), count(0) {
      RCLCPP_INFO(this->get_logger(), "Locked the servos on port 1,2,13,14 on both boards.");
      front_publisher = this->create_publisher<front_board_msgs::msg::ServoArray>("servos_absolute", 10);
      back_publisher = this->create_publisher<back_board_msgs::msg::ServoArray>("servos_absolute", 10);
      timer = this->create_wall_timer(500ms, std::bind(&SMOVLockLegs::call, this));
    }

  private:
    void call() {
      call_front_board();
      call_back_board();
    }

    void call_front_board() {
      // Setting up the servo on port 0.
      auto servo_0 = front_board_msgs::msg::Servo();
      servo_0.servo = 1;
      servo_0.value = 100;

      // Setting up the servo on port 15.
      auto servo_15 = front_board_msgs::msg::Servo();
      servo_15.servo = 16;
      servo_15.value = 548;

      // Setting up the servo on port 1.
      auto servo_1 = front_board_msgs::msg::Servo();
      servo_1.servo = 2;
      servo_1.value = 270;

      // Setting up the servo on port 14.
      auto servo_14 = front_board_msgs::msg::Servo();
      servo_14.servo = 15;
      servo_14.value = 320;

      // Setting up the servo on port 2.
      auto servo_2 = front_board_msgs::msg::Servo();
      servo_2.servo = 3;
      servo_2.value = 300;

      // Setting up the servo on port 13.
      auto servo_13 = front_board_msgs::msg::Servo();
      servo_13.servo = 14;
      servo_13.value = 350;

      auto message = front_board_msgs::msg::ServoArray();

      // Pushing the servos to the array.
      message.servos.push_back(servo_0);
      message.servos.push_back(servo_15);
      message.servos.push_back(servo_1);
      message.servos.push_back(servo_14);
      message.servos.push_back(servo_2);
      message.servos.push_back(servo_13);

      front_publisher->publish(message);
    }

    void call_back_board() {
      // Setting up the servo on port 0.
      auto servo_0 = back_board_msgs::msg::Servo();
      servo_0.servo = 1;
      servo_0.value = 100;

      // Setting up the servo on port 15.
      auto servo_15 = back_board_msgs::msg::Servo();
      servo_15.servo = 16;
      servo_15.value = 548;

      // Setting up the servo on port 1.
      auto servo_1 = back_board_msgs::msg::Servo();
      servo_1.servo = 2;
      servo_1.value = 270;

      // Setting up the servo on port 14.
      auto servo_14 = back_board_msgs::msg::Servo();
      servo_14.servo = 15;
      servo_14.value = 320;

      // Setting up the servo on port 2.
      auto servo_2 = back_board_msgs::msg::Servo();
      servo_2.servo = 3;
      servo_2.value = 300;

      // Setting up the servo on port 13.
      auto servo_13 = back_board_msgs::msg::Servo();
      servo_13.servo = 14;
      servo_13.value = 350;

      auto message = back_board_msgs::msg::ServoArray();

      // Pushing the servos to the array.
      message.servos.push_back(servo_0);
      message.servos.push_back(servo_15);
      message.servos.push_back(servo_1);
      message.servos.push_back(servo_14);
      message.servos.push_back(servo_2);
      message.servos.push_back(servo_13);

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
  rclcpp::spin(std::make_shared<smov::SMOVLockLegs>());
  rclcpp::shutdown();
  return 0;
}

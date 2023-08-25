#include <breath/breath.h>
#include <iostream>

namespace smov {

void BreathState::on_start() {
  trig.set_legs_distance_to(8); // 8 cm.

  for (int i = 0; i < SERVO_MAX_SIZE; i++) {
    std::cout << front_servos.value[i] << std::endl;
    std::cout << back_servos.value[i] << std::endl;
  }
}

void BreathState::on_loop() {
}

void BreathState::on_quit() {
}

}

// This macro creates the node and the main() input, which spins the node.
DECLARE_STATE_NODE_CLASS("smov_breath_state", smov::BreathState, 500ms)

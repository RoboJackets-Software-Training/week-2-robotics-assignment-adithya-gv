#include <iostream>  // Gives us access to std::cin and std::cout
#include <string>  // Gives us access to std::string and std::getline()

struct LightOutputs {
  bool red_ns;
  bool yellow_ns;
  bool green_ns;
  bool red_ew;
  bool yellow_ew;
  bool green_ew;
};

struct LightInputs {
  int time;
  bool car_sensor_n;
  bool car_sensor_s;
};

// TODO Define your light controller state machine class here
class LightController {
  public:
    LightOutputs update(const LightInputs &inputs) {
      switch(current_state_) {
        case RR:
          if (inputs.car_sensor_n || inputs.car_sensor_s) {
            current_state_ = RG;
            next_transition_time = inputs.time + 5;
          } else {
            current_state_ = GR;
            next_transition_time = inputs.time + 5;
          }
          break;
        case RG:
          if (inputs.time == 5) {
            current_state_ = RY;
            next_transition_time = inputs.time + 2;
          }
          break;
        case RY:
          if (inputs.time == 2) {
            current_state_ = RR;
          }
          break;
        case GR:
          if (inputs.time == 5) {
            current_state_ = YR;
            next_transition_time = inputs.time + 2;
          }
          break;
        case YR:
          if (inputs.time == 2) {
            current_state_ = RR;
          }
          break;
      }
      return status();

    
    }

    LightOutputs status() {
      switch(current_state_) {
        case RR:
          return {true, false, false, true, false, false};
          break;
        case RG:
          return {false, false, true, true, false, false};
          break;
        case RY:
          return {false, true, false, true, false, false};
          break;
        case GR:
          return {true, false, false, false, false, true};
          break;
        case YR:
          return {true, false, false, false, true, false};
          break;
      }
    }
  
  private:
    enum State {
      RR,
      YR,
      GR,
      RY,
      RG
    };

    State current_state_{RR};

    int next_transition_time = 0;
};

int main()
{
    // TODO Initialize your state machine class here
    while(true)
    {
        int time = 0;
        LightController controller;
        std::string input;
        std::getline(std::cin, input);
        if(input.size() != 2)
            break;

        // TODO Parse the input digits
        const LightInputs inputs{
            time,
            input[0] == '1',
            input[1] == '1'
        };


        // TODO Update your state machine based on input
        const auto output = controller.update(inputs);

        // TODO Output your state machine's light controls to std::cout
        std::cout << output.red_ns << output.yellow_ns << output.green_ns << output.red_ew << output.yellow_ew << output.green_ew << "\n";

        time++;
    }
    return 0;
}

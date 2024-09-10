#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
using std::cout, std::endl, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

bool ParameterIsInRange(float inputValue, float lowerLimit, float upperLimit) {
  if (inputValue<lowerLimit||inputValue>upperLimit) {
    return false;
  }
  return true;
}

void PrintMessage(const std::string& message) {
  cout << message << endl;
  for (int i = 0; i < 6; i++) {
    cout << "\r* " << flush;
    sleep_for(seconds(1));
    cout << "\r *" << flush;
    sleep_for(seconds(1));
  }
}

bool CheckBodyTemperature(float bodyTemperature) {
  if (!ParameterIsInRange(bodyTemperature,TEMPERATURE_LOWER_LIMIT,TEMPERATURE_UPPER_LIMIT)) {
    PrintMessage("Temperature is critical!");
    return false;
  }
  return true;
}

bool CheckPulseRate(float pulseRate) {
  if (!ParameterIsInRange(pulseRate,PULSERATE_LOWER_LIMIT,PULSERATE_UPPER_LIMIT)) {
    PrintMessage("Pulse Rate is out of range!");
    return false;
  }
  return true;
}

bool CheckSPO2(float spo2) {
  if (!ParameterIsInRange(spo2,SPO2_LOWER_LIMIT,SPO2_UPPER_LIMIT)) {
    PrintMessage("Oxygen Saturation out of range!");
    return false;
  }
  return true;
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
  return (CheckBodyTemperature(temperature) && CheckPulseRate(pulseRate) && CheckSPO2(spo2));
}

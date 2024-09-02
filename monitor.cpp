#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
using std::cout,std::endl, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

void PrintMessage(const string& message) {
  cout<<message<<endl;
  for (int i = 0; i < 6; i++) {
    cout << "\r* " << flush;
    sleep_for(seconds(1));
    cout << "\r *" << flush;
    sleep_for(seconds(1));
  }
}

int CheckBodyTemperature(float bodyTemperature) {
  if (bodyTemperature > 102 || bodyTemperature < 95) {
    PrintMessage("Temperature is critical!");
    return 0;
  }
  return 1;
}

int CheckPulseRate(float pulseRate) {
  if (pulseRate < 60 || pulseRate > 100) {
    PrintMessage("Pulse Rate is out of range!");
    return 0;
  }
  return 1;
}

int CheckSPO2(float spo2) {
  if (spo2 < 90) {
    PrintMessage("Oxygen Saturation out of range!");
    return 0;
  }
  return 1;
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
  return (CheckBodyTemperature(temperature) && CheckPulseRate(pulseRate) && CheckSPO2(spo2))
}
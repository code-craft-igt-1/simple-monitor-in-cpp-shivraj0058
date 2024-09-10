#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
using std::cout, std::endl, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

std::map<std::string, std::map<std::string, std::pair<std::string, std::string>>> 
        warningMessages = {{"English",
        {{"Temperature",
         {"Approaching hypothermia", "Approaching hyperthermia"}},
         {"PulseRate",
         {"Pulse rate approaching lower limit", "Pulse rate is approaching higher limit"}},
         {"SPO2",
         {"SPO2 is approaching lower limit", "SPO2 is approaching upper limit"}}
        }},
        {"German", 
        {{"Temperature",
        {"Annäherung an Unterkühlung", "Annäherung an Überhitzung"}},
         {"PulseRate",
         {"Pulsfrequenz nähert sich dem unteren Grenzwert", "Pulsfrequenz nähert sich dem oberen Grenzwert"}},
         {"SPO2",
         {"SPO2 nähert sich dem unteren Grenzwert", "SPO2 nähert sich dem oberen Grenzwert"}}
        }},
};

bool ParameterIsInRange(float inputValue, float lowerLimit, float upperLimit) {
  if (inputValue<lowerLimit || inputValue>upperLimit) {
    return false;
  }
  return true;
}

void PrintWarning(const std::string& message) {
  cout <<"Warning:"<< message << endl;
}

void CheckForTolerance(std::string parameter, float inputValue, float lowerLimit,
                       float upperLimit, float tolerance) {
  if (inputValue < (lowerLimit+tolerance)) {
    PrintWarning(warningMessages.at(language).at(parameter).first);
  } else if (inputValue > (upperLimit-tolerance)) {
    PrintWarning(warningMessages.at(language).at(parameter).second);
  }
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
  if (!ParameterIsInRange(bodyTemperature, TEMPERATURE_LOWER_LIMIT, TEMPERATURE_UPPER_LIMIT)) {
    PrintMessage("Temperature is critical!");
    return false;
  }
  CheckForTolerance("Temperature", bodyTemperature, TEMPERATURE_LOWER_LIMIT,
                    TEMPERATURE_UPPER_LIMIT, TEMPERATURE_TOLERANCE);
  return true;
}

bool CheckPulseRate(float pulseRate) {
  if (!ParameterIsInRange(pulseRate, PULSERATE_LOWER_LIMIT, PULSERATE_UPPER_LIMIT)) {
    PrintMessage("Pulse Rate is out of range!");
    return false;
  }
  CheckForTolerance("PulseRate", pulseRate, PULSERATE_LOWER_LIMIT,
                    PULSERATE_UPPER_LIMIT, PULSERATE_TOLERANCE);
  return true;
}

bool CheckSPO2(float spo2) {
  if (!ParameterIsInRange(spo2, SPO2_LOWER_LIMIT, SPO2_UPPER_LIMIT)) {
    PrintMessage("Oxygen Saturation out of range!");
    return false;
  }
  CheckForTolerance("SPO2", spo2, SPO2_LOWER_LIMIT, SPO2_UPPER_LIMIT, SPO2_TOLERANCE);
  return true;
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
  return (CheckBodyTemperature(temperature) && CheckPulseRate(pulseRate) && CheckSPO2(spo2));
}

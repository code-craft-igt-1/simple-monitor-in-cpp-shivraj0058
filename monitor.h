#pragma once

const float TEMPERATURE_UPPER_LIMIT = 102;
const float TEMPERATURE_LOWER_LIMIT = 96;
const float TEMPERATURE_TOLERANCE = (TEMPERATURE_UPPER_LIMIT*0.015);

const float PULSERATE_UPPER_LIMIT = 100;
const float PULSERATE_LOWER_LIMIT = 60;
const float PULSERATE_TOLERANCE = (PULSERATE_UPPER_LIMIT*0.015);

const float SPO2_UPPER_LIMIT = 100;
const float SPO2_LOWER_LIMIT = 60;
const float SPO2_TOLERANCE = (SPO2_UPPER_LIMIT*0.015);

int vitalsOk(float temperature, float pulseRate, float spo2);

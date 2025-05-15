const uint8_t sensorCount = 3; // Number of sensors
const uint8_t sensorPins[sensorCount] = {A0, A1, A2}; // Analog pins for sensors
const uint8_t ledPin = 13; // Pin for the LED

int sensorValues[sensorCount]; // Array to store sensor values
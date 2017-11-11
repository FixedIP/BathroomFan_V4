//==============================================================================================
void DTHsensor() {
  // Wait a few seconds between measurements.
  TimeClockDelayDHT();
  if (timeclockEND4 == 1)
  {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    Hum = dht.readHumidity();
    // Read temperature as Celsius (the default)
    Term = dht.readTemperature();
  }
}
//==============================================================================================


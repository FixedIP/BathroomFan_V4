//===============================================================================================
void FanOFF ()
{
  if (digitalRead(FanPin) == LOW)
  {
    digitalWrite(FanPin, HIGH);
     myOLED.clrScr();
     myOLED.setFont(RusFont);
      myOLED.print("Dtynbkznjh", CENTER, 20);
      myOLED.print("dsrk.xty", CENTER, 30);
      myOLED.update();
    starttime2 = millis();// Присваиваем значение точки отсчета.
   // starttime3 = millis();// Присваиваем значение точки отсчета.
  }
}

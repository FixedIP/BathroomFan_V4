//===============================================================================================
void FanON ()
{
  if (digitalRead(FanPin) == HIGH)
  {
    digitalWrite(FanPin, LOW);
   myOLED.clrScr();
     myOLED.setFont(RusFont);
      myOLED.print("Dtynbkznjh", CENTER, 20);
      myOLED.print("drk.xty", CENTER, 30);
      myOLED.update();
    timeclockEND = 0;

  }
}

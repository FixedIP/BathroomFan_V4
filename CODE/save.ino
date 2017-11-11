//=============================================================================
void save ()
{
  while (1)
  {
    TimeClockDelaySetting();


    myOLED.clrScr();
    myOLED.setFont(RusFont);
    myOLED.print("Cj[hfybnm bpvtytybz?", CENTER, 20);
    myOLED.print("LF (+)", RIGHT, 50);
    myOLED.print("YTN (-)", LEFT, 50);
    myOLED.update();
    delay(1000);

    if (digitalRead(PozitivButton) == HIGH && digitalRead(NegativButton) == LOW) //Сохраняем
    {
      delay(50);
      if (digitalRead(PozitivButton) == HIGH && digitalRead(NegativButton) == LOW)
      {
        starttime5 = millis();// Присваиваем значение точки отсчета

        if (EEPROM.read(1) != setTerm)
        {
          EEPROM.write(1, setTerm);//Записываем новые значения в память
        }
        if (EEPROM.read(2) != setTerm)
        {
          EEPROM.write(2, setHum);//Записываем новые значения в память
        }
        if (EEPROM.read(3) != setDelay)
        {
          EEPROM.write(3, setDelay);//Записываем новые значения в память
        }
        if (EEPROM.read(4) != setWork)
        {
          EEPROM.write(4, setWork);//Записываем новые значения в память
        }
        if (EEPROM.read(5) != setAuto)
        {
          EEPROM.write(5, setAuto);//Записываем новые значения в память
        }
        if (EEPROM.read(6) != setLight)
        {
          EEPROM.write(6, setLight);//Записываем новые значения в память
        }
       // if (EEPROM.read(7) != setAutoWork)
        {
         // EEPROM.write(7, setAutoWork);//Записываем новые значения в память
        }
        myOLED.clrScr();
        myOLED.print("Cj[hfyz.", CENTER, 30);
        myOLED.update();
        delay(1000);
        resetFunc(); //вызов

      }
    }
    if (digitalRead(PozitivButton) == LOW && digitalRead(NegativButton) == HIGH) // Не сохраняем
    {
      delay(50);
      if (digitalRead(PozitivButton) == LOW && digitalRead(NegativButton) == HIGH)
      {
        starttime5 = millis();// Присваиваем значение точки отсчета.
        myOLED.clrScr();
        myOLED.print("Yt cj[hfyz.", CENTER, 30);
        myOLED.update();
        delay(1000);
        resetFunc(); //вызов

      }
    }
  }
}

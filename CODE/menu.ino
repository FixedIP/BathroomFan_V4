void menu() {
  myOLED.clrScr();
  myOLED.setFont(MediumNumbers);
  while (1)
  {
    myOLED.invertText(false);
    // Прорисовка первой страницы меню
    if (mode < 6) {
      myOLED.setFont(RusFont);
      myOLED.print("Yfcnhjqrb 1-1", CENTER, 0);
      myOLED.print("Ntvgthfnehf", LEFT, 10);
      myOLED.printNumI(setTerm, RIGHT, 10);
      myOLED.print("Dkf;yjcnm", LEFT, 20);
      myOLED.printNumI(setHum, RIGHT, 20);
      myOLED.print("Pflth;rf yf DRK", LEFT, 30);
      myOLED.printNumI(setDelay, RIGHT, 30);
      myOLED.print("Pflth;rf yf DSRK", LEFT, 40);
      myOLED.printNumI(setWork, RIGHT, 40);
      myOLED.print("Ghjdtnhbdfybt DRK", LEFT, 50);
      myOLED.printNumI(setAuto, RIGHT, 50);
      myOLED.print("Jcdtotyyjcnm", LEFT, 60);
      myOLED.printNumI(setLight, RIGHT, 60);
    }
    // Прорисовка второй страницы меню
    if (mode > 5) {
      myOLED.print("Yfcnhjqrb 1-2", CENTER, 0);
      myOLED.print("Jcdtotyyjcnm", LEFT, 10);
      myOLED.printNumI(setLight, RIGHT, 10);
      myOLED.print("Flhtc ecnhjqcndf", LEFT, 20);
      myOLED.printNumI(Addr, RIGHT, 20);
    }
    if (mode == 1) {
      myOLED.invertText(true);
      myOLED.print("Ntvgthfnehf", LEFT, 10);
      myOLED.printNumI(setTerm, RIGHT, 10);
    }
    if (mode == 2) {
      myOLED.invertText(true);
      myOLED.print("Dkf;yjcnm", LEFT, 20);
      myOLED.printNumI(setHum, RIGHT, 20);
    }
    if (mode == 3) {
      myOLED.invertText(true);
      myOLED.print("Pflth;rf yf DRK", LEFT, 30);
      myOLED.printNumI(setDelay, RIGHT, 30);
    }
    if (mode == 4) {
      myOLED.invertText(true);
      myOLED.print("Pflth;rf yf DSRK", LEFT, 40);
      myOLED.printNumI(setWork, RIGHT, 40);
    }
    if (mode == 5) {
      myOLED.invertText(true);
      myOLED.print("Ghjdtnhbdfybt DRK", LEFT, 50);
      myOLED.printNumI(setAuto, RIGHT, 50);
    }
    if (mode == 6) {
      myOLED.invertText(true);
      myOLED.print("Jcdtotyyjcnm", LEFT, 10);
      myOLED.printNumI(setLight, RIGHT, 10);
    }
    if (mode == 7) {
      myOLED.invertText(true);
      myOLED.print("Flhtc ecnhjqcndf", LEFT, 20);
      myOLED.printNumI(Addr, RIGHT, 20);
    }
    myOLED.update();
    myOLED.clrScr();
    TimeClockDelaySetting();
    if (timeclockEND5 == 1)
    {
      resetFunc(); //вызов
    }
    if (digitalRead(PozitivButton) == HIGH && digitalRead(NegativButton) == HIGH)
    {
      delay(50);
      if (digitalRead(PozitivButton) == HIGH && digitalRead(NegativButton) == HIGH)
      {
        save ();
        delay(500);
      }
    }

    if (digitalRead(SetButton) == HIGH)
    {
      delay(50);
      if (digitalRead(SetButton) == HIGH)
      {
        starttime5 = millis();// Присваиваем значение точки отсчета.
        mode++;
        if (mode > 7)//
        {
          mode = 1;
        }
      }
    }
    if (mode == 1)//экран установки температуры
    {

      if (Pozitiv() == 1 )
      {
        starttime5 = millis();// Присваиваем значение точки отсчета.
        setTerm++;//увеличиваем температуру на 1 градус
        if (setTerm >= 100)
        {
          setTerm = 99;
        }

      }
      // меняем значение на экране

      if (Negativ () == 2)
      {
        starttime5 = millis();// Присваиваем значение точки отсчета.
        setTerm--;//уменьшаем температуру на 1 градус
        if (setTerm == 255)
        {
          setTerm = 0;
        }

      }
    }

    if (mode == 2)//экран установки влажности
    {
      if (Pozitiv() == 1 )
      {
        starttime5 = millis();// Присваиваем значение точки отсчета.
        setHum++;//увеличиваем влажность на 1%
        if (setHum >= 100)
        {
          setHum = 99;
        }
      }

      if (Negativ () == 2)
      {
        starttime5 = millis();// Присваиваем значение точки отсчета.
        setHum--;//уменьшаем влажность на 1%
        if (setHum == 255)
        {
          setHum = 0;
        }
      }
    }

    if (mode == 3)//экран установки задержки на включение вентилятора после включения света
    {
      if (Pozitiv() == 1 )
      {
        starttime5 = millis();// Присваиваем значение точки отсчета.
        setDelay++;//увеличиваем задержку на 1 минуту
        if (setDelay >= 100)
        {
          setDelay = 99;
        }
      }

      if (Negativ () == 2)
      {
        starttime5 = millis();// Присваиваем значение точки отсчета.
        setDelay--;//уменьшаем задержку на 1 минуту
        if (setDelay == 255)
        {
          setDelay = 0;
        }
      }
    }

    if (mode == 4)//экран установки работы вентилятора после выкл. света
    {

      if (Pozitiv() == 1 )
      {
        setWork++;//увеличиваем работу на 1 минуту
        if (setWork >= 100)
        {
          setWork = 99;
        }
      }

      if (Negativ () == 2)
      {
        starttime5 = millis();// Присваиваем значение точки отсчета.
        setWork--;//уменьшаем работу на 1 минуту
        if (setWork == 255)
        {
          setWork = 0;
        }
      }
    }



    if (mode == 5)//экран установки задержки на включение вентилятора в автоматическом режиме(проветривание)
    {
      if (Pozitiv() == 1 )
      {
        starttime5 = millis();// Присваиваем значение точки отсчета.
        setAuto++;//увеличиваем время на 1 минуту
        if (setAuto >= 100)
        {
          setAuto = 99;
        }
      }

      if (Negativ () == 2)
      {
        starttime5 = millis();// Присваиваем значение точки отсчета.
        setAuto--;//уменьшаем задержку на 1 минуту

        if (setAuto == 255)
        {
          setAuto = 0;
        }
      }
    }


    if (mode == 6)//экран установки включения света
    {
      Light = analogRead(LightPin);
      Light = map(Light, 0, 1023, 0, 255);
      setLight = Light;
    }
    if (mode == 7)//экран установки адреса устройства
    {
      if (Pozitiv() == 1 )
      {
        starttime5 = millis();// Присваиваем значение точки отсчета.
        Addr++;//увеличиваем время на 1 минуту
        if (Addr >= 100)
        {
          Addr = 99;
        }
      }

      if (Negativ () == 2)
      {
        starttime5 = millis();// Присваиваем значение точки отсчета.
        Addr--;//уменьшаем задержку на 1 минуту

        if (Addr == 255)
        {
          Addr = 0;
        }
      }

    }
  }
}

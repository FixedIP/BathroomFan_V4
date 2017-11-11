/* Внимание данный код выполнени в IDE 1.0.5-r2
  Контроллер вентилятора для ванной.
  В этой версии кода реализованны следующие режимы работы вентилятора:
  - Отображение на экране температуры, влажности и статус вентилятора
  - Установка всех параметров с помощью меню и записью новых данных в память МК
  - Автоматический выход из меню установки при бездействии больше 1 мин.
  - Режим "проветривания"(Auto)
  - Режим "забыл выключить свет" (LongWork)
  - Отключение режима при установке в 0
  - Меню установки:
  1. Задержка на включение вентилятора при вкл. света
  2. Задержка на выключение вентилятора при выкл. света
  3. Вкл. вентилятора при привышении влажности
  4. Вкл. вентилятора при привышении температуры
  5. Задержка на вкл. вентилятора (проветривание)
  6. Задержка на выкл. вентилятора (проветривание)


  Алгоритм работы:

*/
#include <OLED_I2C.h>
#include <OLED_StatusIcons.h>
#include <Wire.h>
#include <EEPROM.h>
#include "DHT.h"
OLED  myOLED(SDA, SCL, 8);
#define SetButton 4
#define PozitivButton 5
#define NegativButton 6
#define LightPin A0
#define FanPin 7// пин 3 для подключения реле
#define DHTPIN 2
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

void TimeClockAuto();
void menu();
void save ();
void TimeClockDelay();
void TimeClockWork();
void TimeClockAuto();
void TimeClockDelayDHT();
void TimeClockDelaySetting();
void TimeClockDelayLongWork();
void FanON ();
void FanOFF ();
void DTHsensor();
int Pozitiv ();
int Negativ ();

extern uint8_t SmallFont[];
extern uint8_t RusFont[]; // Русский шрифт
extern uint8_t MediumNumbers[];
//extern uint8_t BigNumbers[];
extern uint8_t MegaNumbers[];

unsigned long Delay ; //Задержка  перед повторной проверкой  на включение света
unsigned long Work;//Время работы вентилятора после выключения света
unsigned long Auto = 3600000; //Задержка  перед повторной проверкой  на включение света в часах
byte mode = 1;// Флаг перехода по меню
byte setTerm;// Пееременная для хранения максимальной температуры при которой происходит вкл. вентилятора
byte setHum;//Пееременная для хранения максимальной влажности при которой происходит вкл. вентилятора
byte setDelay;// Пееременная для хранения значения задержки на вкл. вентилятора после вкл. света
byte setWork;//Пееременная для хранения значения задержки на выкл. вентилятора после выкл. света
byte setAuto;//Пееременная для хранения значения задержки на вкл. вентилятора в режиме проветривания
byte Addr;//Пееременная для хранения значения адреса устройства
byte setLight;//Переменная для хранения значения освещенности при которой вкл. вентилятор(см. setDelay)
int Light;//Пееременная для хранения значения освещенности считанная с фоторезистора
byte Term;//Пееременная для хранения значения температуры считанная с датчика
byte Hum;//Пееременная для хранения значения влажности считанная с датчика

// Переменные таймера Dely
unsigned long starttime;// переменная для хранения значения точки отсчета.
byte timeclockSTART = 1;// Флаг задатчика значения точки отсчета.
byte timeclockEND = 0;// Флаг окончания работы таймера.
// Переменные таймера Work
unsigned long starttime1;// переменная для хранения значения точки отсчета.
byte timeclockSTART1 = 1;// Флаг задатчика значения точки отсчета.
byte timeclockEND1 = 0;// Флаг окончания работы таймера.
// Переменные таймера Auto
unsigned long starttime2;// переменная для хранения значения точки отсчета.
byte timeclockSTART2 = 1;// Флаг задатчика значения точки отсчета.
byte timeclockEND2 = 0;// Флаг окончания работы таймера.
// Переменные таймера DelyDHT
int starttime4;// переменная для хранения значения точки отсчета.
byte timeclockSTART4 = 1;// Флаг задатчика значения точки отсчета.
byte timeclockEND4 = 0;// Флаг окончания работы таймера.
// Переменные таймера DelySetting
unsigned long starttime5;// переменная для хранения значения точки отсчета.
byte timeclockSTART5 = 1;// Флаг задатчика значения точки отсчета.
byte timeclockEND5 = 0;// Флаг окончания работы таймера.
// Переменные таймера DelyLongWork
unsigned long starttime6;// переменная для хранения значения точки отсчета.
byte timeclockSTART6 = 1;// Флаг задатчика значения точки отсчета.
byte timeclockEND6 = 0;// Флаг окончания работы таймера.

byte workTerm = 0;//флаг работы по температуре 0 -вкл. 1-выкл.
byte workHum = 0;//флаг работы по влажности 0 - вкл. 1 -выкл.


void(* resetFunc) (void) = 0; // Reset MC function
//======================================================================================
void setup() {
  //Serial.begin(9600);
  dht.begin();
  // initialize the OLED
  myOLED.begin();
  myOLED.setFont(SmallFont);
  pinMode(PozitivButton, INPUT);
  //pinMode(PozitivButton, LOW);
  pinMode(NegativButton, INPUT);
  //pinMode(NegativButton, LOW);
  pinMode(SetButton, INPUT);
  //pinMode(SetButton, LOW);
  pinMode(FanPin, OUTPUT);
  digitalWrite(FanPin, HIGH);
  pinMode(LightPin, INPUT);
  // Turn on the blacklight and print a message.

  setTerm = EEPROM.read(1);//Читаем из памяти значение температуры
  setHum = EEPROM.read(2);//Читаем из памяти значение влажности
  setDelay = EEPROM.read(3);//Читаем из памяти значение задержки на включение
  setWork = EEPROM.read(4);//Читаем из памяти значение задержку на выключение
  setAuto = EEPROM.read(5);//Читаем из памяти значение задержку режима проветривания
  setLight = EEPROM.read(6);//Читаем из памяти значение освещенности
  // setAutoWork = EEPROM.read(7);//Читаем из памяти времени работы вентилятора в режиме проветривания
  Delay = setDelay * 60000;// Пререводим минуты в милисекунды
  Work = setWork * 60000;//Пререводим минуты в милисекунды
  setLight = setLight - 10;
  Auto = setAuto * Auto;
  //AutoWork = setAutoWork * AutoWork;
  myOLED.setFont(RusFont);
  myOLED.print("Fdnjh - ", LEFT, 10);
  myOLED.print("dthcbz rjlf - ", LEFT, 25);
  myOLED.print("dthcbz gkfns - ", LEFT, 40);
  myOLED.setFont(SmallFont);
  myOLED.print("FixedIP", RIGHT, 10);
  myOLED.print("1.0", RIGHT, 25);
  myOLED.print("1.0", RIGHT, 40);
  myOLED.update();
  delay (5000);
  myOLED.clrScr();
}
//==================================================================================
void loop() {

  TimeClockAuto();// Запускаем таймер режима "проветривания"
  Light = (analogRead(LightPin) / 4); //Считываем данные с фоторезистора
  //*************************************************************************************
  if (Light > setLight)// Если свет вкл. то сбрасываем таймер "проветривания" в исходную
  {
    timeclockSTART2 = 1;// Перевод флага задатчика значения точки отсчета в положение ВКЛ.
    // timeclockSTART3 = 1;// Перевод флага задатчика значения точки отсчета в положение ВКЛ.
  }
  //*************************************************************************************
  if (Light < setLight)// Если свет выключен то сбрасываем таймер "забыл выключить свет" в исходную
  {
    timeclockSTART6 = 1;// Перевод флага задатчика значения точки отсчета в положение ВКЛ.
    timeclockEND6 = 0; // Флаг окончания работы таймера ВЫКЛ.
  }
  //*************************************************************************************
  if (digitalRead(FanPin) == LOW)//Вкл. таймер "забыл выключить свет"
  {
    TimeClockDelayLongWork();
    if (timeclockEND6 == 1)
    {
      FanOFF ();
    }

  }
  //*************************************************************************************
  //Вывод на экран температуры и влажности с датчика
  myOLED.clrScr();
  DTHsensor();
  if (digitalRead(FanPin) == LOW) {
    myOLED.setFont(MegaNumbers);
    myOLED.printNumI(Term, LEFT, 0);
    myOLED.printNumI(Hum, 70, 25);
    myOLED.setFont(MediumNumbers);
    // myOLED.printNumI(Light, RIGHT, 2);
    myOLED. drawLine(20, 60, 100, 0);
    myOLED. drawCircle(52, 4, 2);
    myOLED.setFont(RusFont);
    myOLED.print("C", 56, 2);
    myOLED.print("%", 120, 27);
    myOLED.update();
    myOLED.clrScr();
  }
  //if (digitalRead(FanPin) == HIGH) {
  //*************************************************************************************
  //Вкл. и выкл. вентилятора по условию температуры
  if (setTerm != 0)//Если установка температура задана 0 то вкл. по температуре не используется
  {
    if (workTerm == 0)
    {
      if (Term > setTerm && Light < setLight)// Температура больше и свет выкл. то
      {
        FanON ();// Вкл. вентилятор
        workHum = 1;
      }
      if (Term < setTerm && Light < setLight)// Температура меньше и свет выкл. то
      {
        FanOFF ();// Выкл. вентилятор
        workHum = 0;
      }
    }
  }
  //*************************************************************************************
  //Вкл. и выкл. вентилятора по условию влажности
  if (setHum != 0)//Если установка влажности задана 0 то вкл. по влажности не используется
  {
    if (workHum == 0)
    {
      if (Hum > setHum && Light < setLight)// Влажность больше и свет выкл. то
      {
        FanON ();// Вкл. вентилятор
        workTerm = 1;
      }
      if (Hum < setHum && Light < setLight)//Влажность меньше и свет выкл. то
      {
        FanOFF ();// Выкл. вентилятор
        workTerm = 0;
      }
    }
  }

  //*************************************************************************************
  //Вкл. задержки на вкл. вентилятора по условию вкл. света :-)
  if (Light >= setLight && digitalRead(FanPin) == HIGH && timeclockEND6 == 0)
  {

    if (setDelay != 0)
    {
      TimeClockDelay();
      if (Light >= setLight && timeclockEND == 1 && digitalRead(FanPin) == HIGH)
      {
        FanON ();
      }
    }
    else FanON ();
  }

  //*************************************************************************************
  if (Light < setLight && digitalRead(FanPin) == HIGH && timeclockSTART == 0)
  {
    /*lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(4, 1);
      lcd.print("Fan OFF");
    */
    timeclockSTART = 1;// Перевод флага задатчика значения точки отсчета в положение ВКЛ.
  }
  //*************************************************************************************
  if (Light >= setLight && digitalRead(FanPin) == LOW && timeclockSTART1 == 0)// Если включили свет и задержка откл. еще не закончилась
  {
    /*lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(4, 1);
      lcd.print("Fan ON");
    */
    timeclockSTART1 = 1;// Перевод флага задатчика значения точки отсчета в положение ВКЛ.
  }
  //*************************************************************************************
  if (Light < setLight && digitalRead(FanPin) == LOW && timeclockEND2 == 0)
  {
    if (setWork != 0)//
    {
      TimeClockWork();
      workTerm = 1;
      workHum = 1;
      if (Light < setLight && timeclockEND1 == 1)
      {
        FanOFF ();
        workTerm = 0;
        workHum = 0;
      }
    }
    else
    {
      FanOFF ();
      workTerm = 0;
      workHum = 0;
    }
  }
  //*************************************************************************************
  if (setAuto != 0)
  {
    if (timeclockEND2 == 1)// Включение в режиме проветривания
    {

      FanON ();

      TimeClockWork();
      if (timeclockEND1 == 1)
      {
        FanOFF ();
        timeclockSTART2 = 1;// Перевод флага задатчика значения точки отсчета в положение ВКЛ.
        timeclockSTART1 = 1;// Перевод флага задатчика значения точки отсчета в положение ВКЛ.
        timeclockEND1 = 0;

      }
    }
  }
  //*************************************************************************************
  if (digitalRead(PozitivButton) == HIGH && digitalRead(NegativButton) == HIGH)
  {
    delay(100);
    if (digitalRead(PozitivButton) == HIGH && digitalRead(NegativButton) == HIGH)
    {
      delay(500);
      menu ();
    }
  }
}
//======================================================================================































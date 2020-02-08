#include "Keyboard.h"


/* Константы */

/* Аналоговые порты */
/* Большая педаль */
const int BIG_KEY_PIN = 0;    //76-930 диапазон значений
/* Малая педаль */
const int SMALL_KEY_PIN = 1;  //200-930 диапазон значений

/* Кнопки клавиатуры, которые имитируются по нажатию */
const char BIG_IMITATION_KEY = KEY_PAGE_DOWN;
const char SMALL_IMITATION_KEY = KEY_PAGE_UP;

/* Порог, с которого педаль считается нажатой. Импирически подобраны */
const int BIG_PRESSED_FRONTIER = 120;
const int SMALL_PRESSED_FRONTIER = 250;


/* Определения функций */

/* Функция получения значения с аналогового пина с отбросом 2 младших битов
 * @param   iPin  Номер аналогового порта, с которого считывается значение
 * @return  Значение в диапазоне 0 - 1023
 */
int GetAnalogValue(int iPin);

/* Проверка полного нажатия клавиши
 * @param   iFrontier  Пороговое значение, с которого педаль считается нажатой
 * @param   iValue     Значение считанное с аналогового порта
 * @return  Истина, если iValue <= iFrontier
 */
bool IsPressedKey(int iFrontier, int iValue);

/* Проверка полного нажатия клавиши
 * @param   iAnalogPin    Номер аналогового порта, с которого считывается значение
 * @param   iFrontier     Пороговое значение, с которого педаль считается нажатой
 * @param   cKey          Символ клавиши, нажатие которой имитируется
 * @param   bPressedFlag  Флаг произошедшего ранее нажатия на педаль
 */
void KeyHandler(int iAnalogPin, int iFrontier, char cKey, bool& bPressedFlag);


/* Глобальные переменные */

/* Флаги произошедшего события нажатия */
bool bWasPressSmall = false;
bool bWasPressBig = false;


/* Макросы */

#define SMALL_KEY_HANDLER() KeyHandler(SMALL_KEY_PIN, SMALL_PRESSED_FRONTIER, SMALL_IMITATION_KEY, bWasPressSmall)
#define BIG_KEY_HANDLER() KeyHandler(BIG_KEY_PIN, BIG_PRESSED_FRONTIER, BIG_IMITATION_KEY, bWasPressBig)


/* Тело программы */

void setup()
{
  
}

void loop()
{
  SMALL_KEY_HANDLER();
  BIG_KEY_HANDLER();

  delay(50);
}

int GetAnalogValue(int iPin)
{
  int iValue = analogRead(iPin);
  iValue &= 0x3FC;

  return iValue;
}

bool IsPressedKey(int iFrontier, int iValue)
{
  return iValue <= iFrontier;
}

void KeyHandler(int iAnalogPin, int iFrontier, char cKey, bool& bPressedFlag)
{
  const int iAnalogValue = GetAnalogValue(iAnalogPin);

  const bool bPress = IsPressedKey(iFrontier, iAnalogValue);

  if(bPress)
  {
    if(!bPressedFlag)
    {
      Keyboard.press(cKey);

      bPressedFlag = true;
    }
  }
  else
  {
    if(bPressedFlag)
    {
      bPressedFlag = false;
      
      Keyboard.release(cKey);
    }
  }
}

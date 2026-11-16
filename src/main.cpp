#include "main.h"

void setup()
{
  Serial.begin(9600);
  Serial.println("Serial connected");

#if ENABLE_WEB_SERVER
  init_web_server();
#endif
  init_KY040();
  led_controller_init();
}

void loop()
{
  uint8_t mode = get_mode();
  set_brightness(getEncoderPosition());

  // Kurzer Druck: naechster Modus (0..4, danach wieder 0)
  if (isButtonPressed())
  {
    set_mode(mode < 4 ? mode + 1 : 0);
  }

  // 3 s halten: direkt Regenbogen
  if (isButtonHeld3Seconds())
  {
    set_mode(4);
  }

  led_controller_do_work();
#if ENABLE_WEB_SERVER
  web_server_do_work();
#endif
}

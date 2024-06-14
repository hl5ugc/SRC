
#include "hw.h"


void hwInit(void)
{
  bspInit();
  timer0Init();
  ADCInit();
  At24c256Init();
  IplSioInit();
  HMI_SioInit();
  dwin_lcd_init();
}

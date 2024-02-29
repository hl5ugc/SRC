
#include "hw.h"


void hwInit(void)
{
  bspInit();
  cliInit();
  timer0Init();
  uartInit();
  At24c256Init();
  MemoryInit();
  MCP4822Init();
  PortWriteInit();
  PortReadInit();
  ADCInit();

  TempInit();
}

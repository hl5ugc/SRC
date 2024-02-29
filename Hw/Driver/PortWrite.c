/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ]  PortWrite.c
 * [ Version   ]  1.0
 * [ Created   ]
 * --------------------------------------------------------------------------
 * Revision History :
 * ------------------------------------------------------------------
 * 
 *  *.본소스 코드를 이용하는 것은 본 조항을 사용자가 암묵적으로
 *    동의 한것으로 간주 합니다.
 *  *.본 소스코드는 개인학습 및 연구 개발용으로 자유롭게 사용가능
 *    합니다.
 *  *.본소스를 사용하여 2차 저작을 하거나 재배포 할 시에는 반드시
 *    SAMJIN ELECTRONICS의 회사명을 반드시 명시하여야 합니다.
 *  *.본 소스코드의 판매 및 영리 활동을 금지합니다 .
 *  *.본 조항 및 원저자 표시의 수정 및 삭제를 금지합니다.
 *
 *------------------------------------------------------------------
 * --------------------------------------------------------------------------
 * Author         Date       Comments on this revision
 * --------------------------------------------------------------------------
 * Hagseong Kang  2024 02 26    First release of this file
 * --------------------------------------------------------------------------
 * Additional Notes:
 * **************************************************************************
 */
/**
* @brief
* @param
* @return
*/

/* Includes */
#include "PortWrite.h"
#include "timer0_int.h"
#ifdef _USE_HW_PORTWRITE

#include "cli.h"
#include "uart.h"
// ---------------------------------------------------------------------------
// Define Global define
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
// Define typedef
// ---------------------------------------------------------------------------
//
// typedef struct _data_bits
// {
//   uint8_t bit0  		: 1 ;
//   uint8_t bit1			: 1 ;
//   uint8_t bit2			: 1 ;
//   uint8_t bit3			: 1 ;
//   uint8_t bit4			: 1 ;
//   uint8_t bit5			: 1 ;
//   uint8_t bit6			: 1 ;
//   uint8_t bit7			: 1 ;	

// }	DATA_BITS ; 
// typedef union _IO_FLAG
// {
//   DATA_BITS bits ;
//   uint8_t   valus ;  
// } IO_FLAG_t ;

typedef struct 
{
  GPIO_Port     port ;
  uint8_t       pin ;
  GPIO_PinState onStatus ;
  GPIO_PinState offStatus ;
} portWrite_tbl_t ;
// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
portWrite_tbl_t portWrite_tbl[PORTWRITE_MAX_CH] =
{
  {GPIO_C,_DEF_PIN2,GPIO_PIN_SET,GPIO_PIN_RESET} ,  // OUT DRV1
  {GPIO_C,_DEF_PIN3,GPIO_PIN_SET,GPIO_PIN_RESET} ,  // OUT DRV2
  {GPIO_C,_DEF_PIN5,GPIO_PIN_SET,GPIO_PIN_RESET} ,  // SSR DRV1
  {GPIO_C,_DEF_PIN4,GPIO_PIN_SET,GPIO_PIN_RESET} ,  // SSR DRV2
  {GPIO_C,_DEF_PIN6,GPIO_PIN_SET,GPIO_PIN_RESET} ,  // OUT DRV3
  {GPIO_C,_DEF_PIN7,GPIO_PIN_SET,GPIO_PIN_RESET} ,  // OUT DRV4
  {GPIO_E,_DEF_PIN3,GPIO_PIN_SET,GPIO_PIN_RESET} ,  // OUT DRV5
  {GPIO_E,_DEF_PIN5,GPIO_PIN_SET,GPIO_PIN_RESET} ,  // OUT DRV6
  {GPIO_B,_DEF_PIN6,GPIO_PIN_RESET,GPIO_PIN_SET} ,  // TRG Control
  {GPIO_D,_DEF_PIN5,GPIO_PIN_SET,GPIO_PIN_RESET}    // Pluse Control
};
#ifdef PORTWRITE_MAX_CH  
static volatile IO_FLAG_t  portDataBuff[HW_P_WRITE_BUFF_MAX] = {0,} ;
#endif

static volatile uint8_t timerCbDisable = 0x00U ;
// ---------------------------------------------------------------------------
//  Macro Define .
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//
#ifdef _USE_HW_TIMER0

#define _USE_PORT_WRITE_CB_CH    HW_PORT_WRITE_CB1    
void cbPortWrite(void) ;
#endif

static void writeHWPortData(uint8_t u8ch,uint8_t u8Pin,GPIO_PinState status);
static GPIO_Port portSelect(uint8_t selectPort);
static void selectPortMsg(GPIO_Port SelectedPort);
//
static void cliPort(cli_args_t *args);
// ---------------------------------------------------------------------------
// Define Private function definitions.
// ---------------------------------------------------------------------------
//
void WriteHWPortCBDisable(void)
{
  timerCbDisable = 0x01U ;
}
void WriteHWPortCBEnable(void)
{
  timerCbDisable = 0x00U ;
}
void writeHWPortData(uint8_t u8ch,uint8_t u8Pin,GPIO_PinState status)
{
  switch(u8ch) 
  {
    case GPIO_A :
        if(status == GPIO_PIN_SET) { PORTA = PORTA | (1<<u8Pin); }
        else { PORTA = PORTA & (~(1<<u8Pin)) ; }
      break ;
    case GPIO_B :
      if(status == GPIO_PIN_SET) { PORTB = PORTB | (1<<u8Pin); }
      else { PORTB = PORTB & (~(1<<u8Pin)) ; }
      break ;
    case GPIO_C :
      if(status == GPIO_PIN_SET) { PORTC = PORTC | (1<<u8Pin); }
      else { PORTC = PORTC & (~(1<<u8Pin)) ; }
      break ;
    case GPIO_D :
      if(status == GPIO_PIN_SET) { PORTD = PORTD | (1<<u8Pin); }
      else { PORTD = PORTD & (~(1<<u8Pin)) ; }
      break ;
    case GPIO_E :
      if(status == GPIO_PIN_SET) { PORTE = PORTE | (1<<u8Pin); }
      else { PORTE = PORTE & (~(1<<u8Pin)) ; }
      break ;
    case GPIO_F :
      if(status == GPIO_PIN_SET) { PORTF = PORTF | (1<<u8Pin); }
      else { PORTF = PORTF & (~(1<<u8Pin)) ; }
      break ;
    case GPIO_G : // atmega128
      if(status == GPIO_PIN_SET) { PORTG = PORTG | (1<<u8Pin); }
      else { PORTG = PORTG & (~(1<<u8Pin)) ; }
      break ;
  }
 
}
// ---------------------------------------------------------------------------
// Define Private function definitions.
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
// Define  Global Function definitions.
// ---------------------------------------------------------------------------
//
 
/**
 * @brief Write Port Init (BSP.c port setting)
 * 
 * @return true 
 * @return false 
 */
bool PortWriteInit(void)
{ 
  bool bRet = true ;
  uint8_t i = 0 ;

  for(i = 0 ; i < PORTWRITE_MAX_CH ; i++)
  {
    writeHWPortData(portWrite_tbl[i].port,portWrite_tbl[i].pin,portWrite_tbl[i].offStatus);
  }
 
  #ifdef _USE_HW_TIMER0
  canSetTimer0Callback(_USE_PORT_WRITE_CB_CH,cbPortWrite) ;
  #endif

  cliAdd("PortW","A Data",cliPort);     
  return bRet ;
}
/**
 * @brief Get Write buffer byte data 
 * 
 * @param u8ch : Array Buffer Index
 * @return uint8_t : Data of Array Buffer [Index]
 */
uint8_t  GetwritePortBuffData(uint8_t u8Index)
{
  uint8_t u8Ret = 0 ;
  //
  if(u8Index < HW_P_WRITE_BUFF_MAX)
  {
    u8Ret =  portDataBuff[u8Index].valus ;
  }
  //
  return (u8Ret) ;
}
/**
 * @brief Write byte data to Write buffer  
 * 
 * @param u8index :  Write buffer  index
 * @param u8Bit   :  Write buffer  index . bit
 * @param status  :  Write buffer[index].bit Write set/reset
 */
bool  WritePortBuffData(uint8_t u8index,uint8_t u8Bit,GPIO_PinState status)
{
  bool bRet = false;

  if(u8index < HW_P_WRITE_BUFF_MAX)
  {
    if(status == GPIO_PIN_RESET) 
    {
      portDataBuff[u8index].valus = portDataBuff[u8index].valus  & (~(1<<u8Bit)) ;
    }
    else
    {
      portDataBuff[u8index].valus = portDataBuff[u8index].valus  | (1<<u8Bit) ; 
    }

    bRet = true ;
  }
  return bRet ;
}
/**
 * @brief Direct Port Data write to PORT
 * 
 * @param writePort  : Port
 * @param u8Data     : Write Byte Port Data
 */
bool WritePortData(GPIO_Port writePort,uint8_t u8Data)
{
  bool bRet = true ;

  switch(writePort) 
  {
    case GPIO_A :
      PORTA =  u8Data ;
      break ;
    case GPIO_B :
      PORTB =  u8Data ;
      break ;
    case GPIO_C :
      PORTC =  u8Data ;
      break ;
    case GPIO_D :
      PORTD=  u8Data ;
      break ;
    case GPIO_E :
      PORTE =  u8Data ;
      break ;
    case GPIO_F :
      PORTF =  u8Data ;
      break ;
    case GPIO_G :  
      PORTG =  u8Data ;
      break ;
  }
  return bRet ;
}
// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
#ifdef _USE_HW_TIMER0  
#ifdef     _USE_PORT_WRITE_CB_CH  
 
void cbPortWrite(void) 
{
  uint8_t i = 0 ;
  uint8_t u8OnOff = 0 ;

  if(timerCbDisable == 0x00U)
  {
    for(i = 0 ; i < PORTWRITE_MAX_CH ; i++)
    {
      u8OnOff = portDataBuff[0].valus >> i ;
      u8OnOff = u8OnOff & _DEF_MBIT0 ;

      if(u8OnOff == GPIO_PIN_RESET) 
      {
        writeHWPortData(portWrite_tbl[i].port,portWrite_tbl[i].pin,portWrite_tbl[i].offStatus);
      }
      else 
      {
        writeHWPortData(portWrite_tbl[i].port,portWrite_tbl[i].pin,portWrite_tbl[i].onStatus);
      }
    } 
  }
}
 
#endif // cb Function
#endif // HW Timer0

void cliPort(cli_args_t *args)
{
  uint8_t  *u8Command  = NULL ;
  uint8_t   u8Loop = 0x00U ;
  uint8_t   u8Data = 0x00U ;
  uint8_t   u8Mode = 0x00U ;
  GPIO_Port SelectedPort = GPIO_GG;

  timerCbDisable = 0x01U;

  if(args->argc >= 1)
  {
    u8Command = args->getStr(0);
    if((u8Command[0U] == 'T') || (u8Command[0U] == 't'))
    {
      SelectedPort = portSelect(u8Command[1U]);
      u8Mode = 0x01U ;
    }
    else
    {
      SelectedPort = portSelect(u8Command[0U]);
    }
    if(args->argc >= 2)
    {
      u8Data = (uint8_t)args->getData(1) ; // ASCII DECMAL & HEX Convert to binary
    }
    if(u8Mode == 0x00U) // Port Data Outpput
    {
      selectPortMsg(SelectedPort);
      uartMsgByte2Hex(_DEF_UART1," = 0x",u8Data); delay_ms(50);
      if(SelectedPort != GPIO_GG)
      {
        WritePortData(SelectedPort,u8Data);
      }
    }
    else // Test Mode
    {
      selectPortMsg(SelectedPort);
      uartMsgWrite(_DEF_UART1," Port Test \r\n");  delay_ms(200);
      u8Data = 0U ;
      while(cliKeepLoop())
      {
        u8Data = (1 << u8Loop) ; 
         WritePortData(SelectedPort,u8Data);
        uartMsgByte3ASC(_DEF_UART1,"\r\nLoop Count = ",u8Loop);
        u8Loop = (u8Loop + 1U) % 8 ;
        delay_ms(200);
      }
    }
  }
  else
  {
    uartMsgWrite(_DEF_UART1,"hl5ugc>> PortW [A//G]   Data\r\n");  delay_ms(50);
    uartMsgWrite(_DEF_UART1,"hl5ugc>> PortW T[A//G] (test) \r\n");      delay_ms(50);
  }
}
GPIO_Port portSelect(uint8_t selectPort)
{
  GPIO_Port selectedPort = GPIO_GG ;

    if((selectPort == 'a') || (selectPort == 'A'))
    {
      selectedPort = GPIO_A ;
    }
    else if((selectPort == 'b') || (selectPort == 'B'))
    {
      selectedPort = GPIO_B ;
    }
    else if((selectPort == 'c') || (selectPort == 'C'))
    {
      selectedPort = GPIO_C ;
    }
    else if((selectPort == 'd') || (selectPort == 'D'))
    {
      selectedPort = GPIO_D ;
    }
    else if((selectPort == 'e') || (selectPort == 'E'))
    {
      selectedPort = GPIO_E ;
    }
    else if((selectPort == 'f') || (selectPort == 'F'))
    {
      selectedPort = GPIO_F ;
    }
    else if((selectPort == 'g') || (selectPort == 'G'))
    {
      selectedPort = GPIO_G ;
    }
    else
    {
      selectedPort = GPIO_GG ;
    }
  return (selectedPort);    
}
//
void selectPortMsg(GPIO_Port SelectedPort)
{
  switch(SelectedPort)
  {
    case GPIO_A :
        uartMsgWrite(_DEF_UART1,"PortA");  
        break ;
    case GPIO_B :
        uartMsgWrite(_DEF_UART1,"PortB");  
        break ;  
    case GPIO_C :
        uartMsgWrite(_DEF_UART1,"PortC");  
        break ;
    case GPIO_D :
        uartMsgWrite(_DEF_UART1,"PortD");  
        break ;    
    case GPIO_E :
        uartMsgWrite(_DEF_UART1,"PortE");  
        break ;
    case GPIO_F :
        uartMsgWrite(_DEF_UART1,"PortF");  
        break ;      
    case GPIO_G :
        uartMsgWrite(_DEF_UART1,"PortG");  
        break ;    
    default:
        uartMsgWrite(_DEF_UART1,"Port Input Error!!\r\n");  
  }
  delay_ms(50);
}
#endif /* src/common/hw/include/portWrite.C End Of File !! Well Done */
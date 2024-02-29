/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ]  PortRead.c
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
 * Hagseong Kang  2024-02-26    First release of this file
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
#include "portRead.h"
#include "timer0_int.h"
#ifdef _USE_HW_PORTREAD

#include "cli.h"
#include "uart.h"
// ---------------------------------------------------------------------------
// Define Global define
// ---------------------------------------------------------------------------
//
#define PORT_READ_INTREVAL     10
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
} portRead_tbl_t ;

// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
portRead_tbl_t portRead_tbl[PORTREAD_MAX_CH] =
{
  {GPIO_A,_DEF_PIN0,GPIO_PIN_RESET} , // Cover Open
  {GPIO_A,_DEF_PIN1,GPIO_PIN_RESET} , // Run S/W
  {GPIO_A,_DEF_PIN2,GPIO_PIN_RESET} , // Hand OK
  {GPIO_A,_DEF_PIN3,GPIO_PIN_RESET} , // Filter
  {GPIO_A,_DEF_PIN4,GPIO_PIN_RESET} , // Spare1
  {GPIO_A,_DEF_PIN5,GPIO_PIN_RESET} , // Spare2
  {GPIO_A,_DEF_PIN6,GPIO_PIN_RESET} , // Water Flow
  {GPIO_C,_DEF_PIN0,GPIO_PIN_SET} ,   // Ld Connect 
  {GPIO_C,_DEF_PIN1,GPIO_PIN_RESET}   // Ld Alram
};

#ifdef PORTREAD_MAX_CH  
static volatile IO_FLAG_t  portDataBuffNew[HW_P_READ_BUFF_MAX] = {0,} ;
static volatile IO_FLAG_t  portDataBuffOld[HW_P_READ_BUFF_MAX] = {0,} ;
static volatile IO_FLAG_t  portDataBuff[HW_P_READ_BUFF_MAX] = {0,} ;
#endif

static volatile uint8_t timerCbDisable = 0x00U ;
static volatile uint8_t portReadInterval = 0 ;
// ---------------------------------------------------------------------------
//  Macro Define .
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//
#ifdef _USE_HW_TIMER0

#define _USE_PORT_READ_CB_CH    HW_PORT_READ_CB1    
void cbPortRead(void) ;
#endif

static bool    readPortPin(uint8_t index) ;
static uint8_t readHWPortData(GPIO_Port selectPort);

static void cliPort(cli_args_t *args);
static void PortBspTest(void);
static GPIO_Port portSelect(uint8_t selectPort);
static void selectPortMsg(GPIO_Port SelectedPort);
static void MsgOnOffOut(uint8_t onOff);
// ---------------------------------------------------------------------------
// Define Private function definitions.
// ---------------------------------------------------------------------------
//
uint8_t readHWPortData(GPIO_Port selectPort)
{
  uint8_t bRet = 0x00 ;

  switch(selectPort) 
  {
    case GPIO_A :
      bRet = PINA ;
      break ;
    case GPIO_B :
      bRet = PINB ;
      break ;
    case GPIO_C :
      bRet = PINC ;
      break ;
    case GPIO_D :
      bRet = PIND ;
      break ;
    case GPIO_E :
      bRet = PINE ;
      break ;
    case GPIO_F :
      bRet = PINF ;
      break ; 
    case GPIO_G : 
      bRet = PING ;
      break ;
  }
  return bRet ;
}
/**
 * @brief Read Port and Mask Pin 
 * 
 * @param index : Table Index 
 * @return true : Read Port and Mask Pin and Pin is Set
 */
bool readPortPin(uint8_t index) 
{
  bool bRet = false ;
  uint8_t u8Data = 0x00U ;
  // Read Port Data
  u8Data = readHWPortData(portRead_tbl[index].port) ;
  // Mask Port Pin
  u8Data = u8Data >> portRead_tbl[index].pin ;
  // 
  if((u8Data & _DEF_MBIT0) == portRead_tbl[index].onStatus)
  {
    bRet = true ;
  }

  return bRet ;
}
// ---------------------------------------------------------------------------
// Define  Global Function definitions.
// ---------------------------------------------------------------------------
//
bool PortReadInit(void)
{
  bool bRet = true ;
  uint8_t i = 0 ;

  for(i = 0 ; i < PORTREAD_MAX_CH ; i++)
  {
    #if(HW_P_READ_BUFF_MAX == 1)
      portDataBuff[0].valus = portDataBuff[0].valus << 1 ;
      portDataBuff[0].bits.bit0 = 0x00 ;
    #else
    if(i <  8) {
      portDataBuff[0].valus = portDataBuff[0].valus << 1 ;
      portDataBuff[0].bits.bit0 = 0x00 ;
    }
    else
    {
      portDataBuff[1].valus = portDataBuff[1].valus << 1 ;
      portDataBuff[1].bits.bit0 = 0x00 ;
    }
    #endif
  }
 
  #ifdef _USE_HW_TIMER0
  canSetTimer0Callback(_USE_PORT_READ_CB_CH,cbPortRead) ;
  #endif
  cliAdd("PortR","[A//G/T] Data",cliPort);  
  
  return bRet ;
}
/**
 * @brief read 8bits PORT DATA
 * 
 * @param ch        GPIO_A ~ GPIO_L 
 * @return uint8_t  8bits PORT DATA 
 */
uint8_t ReadPortData(GPIO_Port selectPort)
{
  uint8_t bRet = 0x00U ;

  bRet = readHWPortData(selectPort);

  return bRet ;
}
/**
 * @brief Read Input Port Buff data portDataBuff[index]
 * 
 * @param index : buffer pointer 
 * @return uint8_t 
 */
uint8_t ReadPortBuffData(uint8_t index)
{
  uint8_t bRet = 0x00U ;
  
  if(index < HW_P_READ_BUFF_MAX)
  {
    bRet = portDataBuff[index].valus ;
  }

  return bRet ;
} 
 
/**
 * @brief check pin of Port Buff data portDataBuff[index]
 *  (Check portDataBuff[index].selectBit is Trur : False)
 * @param   index     Read Input Port Buff data portDataBuff[index]
 * @param   selectBit .0 ~ .7  
 * @return  bool      PORT.PIN is Pressed is true  
 */
bool IsCheckPin(uint8_t index ,uint8_t selectBit)  
{
  bool bRet = false ;
  uint8_t u8Data;
  if(index < HW_P_READ_BUFF_MAX)
  {
    // cbTimer Reading Port data abd sabe portDataBuff[index]
    u8Data = portDataBuff[index].valus ;
    u8Data = u8Data >> selectBit ;

    if((u8Data & _DEF_MBIT0) == _DEF_MBIT0)
    {
      bRet = true ; 
    }
  }
  return bRet ;
}
/**
 * @param   GPIO_Port     GPIO_A ~ GPIO_L 
 * @param   pin           _DEF_PIN0 ~ _DEF_PIN7  
 * @return  GPIO_PinState GPIO_PIN_RESET, GPIO_PIN_SET
 */
GPIO_PinState IsCheckHWPin(GPIO_Port portCh ,uint8_t pin)  
{
  GPIO_PinState bRet = GPIO_PIN_RESET ;
  uint8_t u8Data ;

  u8Data = readHWPortData((uint8_t)portCh) ;
  u8Data = u8Data >> pin ;

  if((u8Data & _DEF_MBIT0) == GPIO_PIN_SET)
  {
    bRet = GPIO_PIN_SET ; 
  }
  return bRet ;
}
// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
#ifdef _USE_HW_TIMER0  
#ifdef     _USE_PORT_READ_CB_CH

void cbPortRead(void) 
{
  uint8_t i = 0 ;
  // Check Port read Interval xxmSec
  if(timerCbDisable == 0x00U)
  {
    if(++portReadInterval == PORT_READ_INTREVAL)
    {
      portReadInterval = 0x00U ;

      for(i = 0 ; i < PORTREAD_MAX_CH ; i++)
      {
        // Bit Data Clear
        portDataBuffNew[0].valus &= ~(1<<i);
        if(readPortPin(i) ==  true)
        {
          portDataBuffNew[0].valus |=  (1<<i);
        } 
      }
      // Compare the data read this time with the data read before.
      if(portDataBuffOld[0].valus != portDataBuffNew[0].valus )
      {
        portDataBuffOld[0].valus = portDataBuffNew[0].valus ;
      }
      else
      {
        portDataBuff[0].valus = portDataBuffOld[0].valus ;
      }
      //
    } 
  }
}
#endif
#endif
 
void PortBspTest(void)
{
  timerCbDisable = 0x00U;

  while(cliKeepLoop())
  {
    uartMsgByte7BASC(_DEF_UART1,"\r\n\r\n Read Port Data = 0b",portDataBuffNew[0].valus); delay_ms(10);
    uartMsgByte7BASC(_DEF_UART1,", 0b",portDataBuffNew[1].valus); delay_ms(10);
    //
    uartMsgWrite(_DEF_UART1,"\r\n Cover Open S/W Is ");
    MsgOnOffOut(portDataBuffNew[0].bits.bit0 );
    //
    uartMsgWrite(_DEF_UART1,"\r\n Run S/W Is ");
    MsgOnOffOut(portDataBuffNew[0].bits.bit1 );
    // 
    uartMsgWrite(_DEF_UART1,"\r\n Hand OK S/W Is ");
    MsgOnOffOut(portDataBuffNew[0].bits.bit2 );
    //
    uartMsgWrite(_DEF_UART1,"\r\n Filter S/W Is ");
    MsgOnOffOut(portDataBuffNew[0].bits.bit3 );
    //
    uartMsgWrite(_DEF_UART1,"\r\n Spare1 S/W Is ");
    MsgOnOffOut(portDataBuffNew[0].bits.bit4 );
    //
    uartMsgWrite(_DEF_UART1,"\r\n Spare2 S/W Is ");
    MsgOnOffOut(portDataBuffNew[0].bits.bit5 );
    //
    uartMsgWrite(_DEF_UART1,"\r\n Water Flow S/W Is ");
    MsgOnOffOut(portDataBuffNew[0].bits.bit6 );
    //
    uartMsgWrite(_DEF_UART1,"\r\n Ld Connect Is ");
    MsgOnOffOut(portDataBuffNew[0].bits.bit7 );
    //
    uartMsgWrite(_DEF_UART1,"\r\n Ld Alram Is ");
    MsgOnOffOut(portDataBuffNew[1].bits.bit0 );
    //
    delay_ms(300);
  }
}
void MsgOnOffOut(uint8_t onOff)
{
    if(onOff == 0x00U) { uartMsgWrite(_DEF_UART1,"Off"); }
    else { uartMsgWrite(_DEF_UART1,"On"); }
    delay_ms(10);
}
//
void cliPort(cli_args_t *args)
{
  uint8_t  *u8Command  = NULL ;
  uint8_t   u8Data = 0x00U ;
  GPIO_Port SelectedPort = GPIO_GG;

  if(args->argc == 1)
  {
    u8Command = args->getStr(0);
    if((u8Command[0U] == 'T') || (u8Command[0U] == 't'))
    {
      timerCbDisable = 0x00U;
      PortBspTest();
    }
    else
    {
      timerCbDisable = 0x01U;
      SelectedPort = portSelect(u8Command[0U]);
      selectPortMsg(SelectedPort);
      uartMsgWrite(_DEF_UART1," Read Start ....\r\n");  delay_ms(50);
      while(cliKeepLoop())
      {
        u8Data = readHWPortData(SelectedPort);
        selectPortMsg(SelectedPort);
        uartMsgByte7BASC(_DEF_UART1," Read Data = 0b",u8Data); delay_ms(200);
        uartMsgWrite(_DEF_UART1,"\r\n");  delay_ms(50);
      }
    }
  }
  else
  {
    uartMsgWrite(_DEF_UART1,"hl5ugc>> PortR [A//G/T] \r\n");  delay_ms(30);
    uartMsgWrite(_DEF_UART1,"hl5ugc>> PortR T (BSP Test) \r\n");  delay_ms(30);
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
#endif /* src/common/hw/include/portRead.C End Of File !! Well Done */
/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ]  uart.c
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
 * Hagseong Kang  Apr 20, 2023    First release of this file
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
#include "uart.h"

#ifdef _USE_HW_UART

#include "qbuffer.h"
#include "DataConvert.H"
// ---------------------------------------------------------------------------
// Define Global define
// ---------------------------------------------------------------------------
//
#define COM_BPS         38400
//
#ifdef _USE_ATMEGA8
#define DATA_REGISTER_EMPTY (1 << UDRE)
#define RX_COMPLETE (1 << RXC)
#define FRAMING_ERROR (1 << FE)
#define PARITY_ERROR (1 << UPE)
#define DATA_OVERRUN (1 << DOR)
#else
//
#define DATA_REGISTER_EMPTY (1 << UDRE0)
#define RX_COMPLETE (1 << RXC0)
#define FRAMING_ERROR (1 << FE0)
#define PARITY_ERROR (1 << UPE0)
#define DATA_OVERRUN (1 << DOR0)
#endif

#define _USE_UART1

#ifdef _USE_UART1
#define STX '@'
#define ETX '$'
#endif
// ---------------------------------------------------------------------------
// Define typedef
// ---------------------------------------------------------------------------
//
typedef struct
{
  void (*callBackUartRx)(uint8_t u8Data);
} uart_cb_tbl_t;

// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
#ifdef _USE_UART1
#define UARTA_TX_MAX_BUFF 64
#define UARTA_RX_MAX_BUFF 64
static volatile uint8_t tx_buff_a[UARTA_TX_MAX_BUFF];
static volatile uint8_t rx_buff_a[UARTA_RX_MAX_BUFF];
static volatile uint8_t useRxEvent = 0;
static volatile uint8_t useRx1Wait = 0;
static volatile uint8_t useTx1Wait = 0;

#ifdef _USE_ATMEGA8
#define UCSR0A UCSRA
#define UCSR0B UCSRB
#define UCSR0C UCSRC
#define UBRR0H UBRRL
#define UBRR0L UBRRH
#define UDR0 UDR
#define USART0_TXC USART_TXC
#define USART0_RXC USART_RXC
#endif

#endif

#ifdef _USE_UART2
#define UARTB_TX_MAX_BUFF 32
#define UARTB_RX_MAX_BUFF 32
static uint8_t tx_buff_b[UARTB_TX_MAX_BUFF];
static uint8_t rx_buff_b[UARTB_RX_MAX_BUFF];
#endif

#ifdef _USE_UART3
#define UARTC_TX_MAX_BUFF 32
#define UARTC_RX_MAX_BUFF 32
static uint8_t tx_buff_c[UARTC_TX_MAX_BUFF];
static uint8_t rx_buff_c[UARTC_RX_MAX_BUFF];
#endif

static bool is_open[UART_MAX_CH];
static qUartBuff_t qUartTxBuff[UART_MAX_CH];
static qUartBuff_t qUartRxBuff[UART_MAX_CH];
const uint8_t bps_Tbl[4] = {0x67, 0x33, 0x19, 0x19};

// ---------------------------------------------------------------------------
//  Macro Define .
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//
#ifdef _USE_HW_TIMER0

#define _DEF_UART_RX_CB_CH HW_TIMER0_CB1
#define _DEF_UART_TX_CB_CH HW_TIMER0_CB2
void cbUartRX0(void);
void cbUartTX0(void);
#endif

static void com_OutDelay(uint8_t len) ;
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// ---------------------------------------------------------------------------
//
bool uartInit(void)
{
  bool result = true;
  uint8_t i = 0;

  for (i = 0; i < UART_MAX_CH; i++)
  {
    is_open[i] = false;
  }

  // #ifdef _USE_HW_TIMER0
  // canSetTimer0Callback(_DEF_UART_RX_CB_CH,cbUartRX0) ;
  // canSetTimer0Callback(_DEF_UART_TX_CB_CH,cbUartTX0) ;
  // #endif

  return result;
}

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter int : On
// USART Mode: Asynchronous
//
bool uartOpen(uint8_t ch, UART_BPS bps)
{
  bool result = false;
  uint8_t *pRxd_buff;
  uint8_t *pTxd_buff;
  uint8_t u8TxLenth = 0;
  uint8_t u8RxLenth = 0;

  if (ch < UART_MAX_CH)
  {
    switch (ch)
    {
      case _DEF_UART1:

        UCSR0A = (0 << RXC0) | (0 << TXC0) | (0 << UDRE0) | (0 << FE0) | (0 << DOR0) | (0 << UPE0) | (0 << U2X0) | (0 << MPCM0);
        UCSR0B = (1 << RXCIE0) | (1 << TXCIE0) | (0 << UDRIE0) | (1 << RXEN0) | (1 << TXEN0) | (0 << UCSZ02) | (0 << RXB80) | (0 << TXB80);
        UCSR0C = (0 << UMSEL0) | (0 << UPM01) | (0 << UPM00) | (0 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00) | (0 << UCPOL0);
        UBRR0H = 0x00;
        // UBRR0L=bps_Tbl[bps] ;
        UBRR0H = 0x00;
        UBRR0L = 0x19;

        is_open[ch] = true;
        pRxd_buff = &rx_buff_a[0x00U];
        pTxd_buff = &tx_buff_a[0x00U];
        u8TxLenth = UARTA_TX_MAX_BUFF;
        u8RxLenth = UARTA_RX_MAX_BUFF;
        result = true;
        break;

      case _DEF_UART2:

        UCSR1A = (0 << RXC0) | (0 << TXC0) | (0 << UDRE0) | (0 << FE0) | (0 << DOR0) | (0 << UPE0) | (0 << U2X0) | (0 << MPCM0);
        UCSR1B = (1 << RXCIE0) | (1 << TXCIE0) | (0 << UDRIE0) | (1 << RXEN0) | (1 << TXEN0) | (0 << UCSZ02) | (0 << RXB80) | (0 << TXB80);
        UCSR1C = (0 << UMSEL0) | (0 << UPM01) | (0 << UPM00) | (0 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00) | (0 << UCPOL0);
        UBRR1H = 0x00;
        // UBRR0L=bps_Tbl[bps] ;
        UBRR1H = 0x00;
        UBRR1L = 0x19;

        is_open[ch] = true;
        pRxd_buff = &rx_buff_a[0x00U];
        pTxd_buff = &tx_buff_a[0x00U];
        u8TxLenth = UARTA_TX_MAX_BUFF;
        u8RxLenth = UARTA_RX_MAX_BUFF;
        result = true;
        break;
    }
    // buff init
    if (is_open[ch] == true)
    {
      qbufferCreate(&qUartTxBuff[ch], pTxd_buff, u8TxLenth);
      qbufferCreate(&qUartRxBuff[ch], pRxd_buff, u8RxLenth);
    }
  }

  return result;
}
/**
 * @brief  Function to read the number of data in the receive buff for communication
 *
 * @param ch        uart Channel
 * @return uint8_t  the number of data in the receive buff
 */
uint8_t uartRXAvailable(uint8_t ch)
{
  uint8_t result = 0;

  if (ch < UART_MAX_CH)
  {
    switch (ch)
    {
    case _DEF_UART1:
#ifdef _USE_UART1
      result = qbufferRxAvailable(&qUartRxBuff[ch]);
#endif
      break;
    default:
      break;
    }
  }
  //
  return result;
}
/**
 * @brief  Function to read the number of Available write data
 *         in the transmit buff for communication
 *
 * @param ch        uart Channel
 * @return uint8_t  the number of data in the receive buff
 */
uint8_t uartTXAvailable(uint8_t ch)
{
  uint8_t result = 0;

  if (ch < UART_MAX_CH)
  {
    switch (ch)
    {
    case _DEF_UART1:
#ifdef _USE_UART1
      result = qbufferTxAvailable(&qUartTxBuff[ch]);
#endif
      break;
    default:
      break;
    }
  }
  //
  return result;
}

/**
 * @brief   Function to read 1byte data of RX buffs for communication
 *
 * @param   ch        qUartRxBuff[ch]
 * @return  uint8_t   read buffer data 1 byte return
 */
uint8_t uartRead(uint8_t ch)
{
  uint8_t u8Result = 0;

  if (ch < UART_MAX_CH)
  {
    switch (ch)
    {
    case _DEF_UART1:
#ifdef _USE_UART1
      qbufferReadByte(&qUartRxBuff[ch], &u8Result);
#endif
      break;
    default:
      break;
    }
  }
  return u8Result;
}
/**
 * @brief Function to read bytes data of RX buffs for communication
 *
 * @param ch        uart channel
 * @param pMsg      read buff
 * @param u8Len     read data length
 * @return uint8_t  read bytes
 */
uint8_t uartReadMsg(uint8_t ch, uint8_t *pMsg, uint8_t u8Len)
{
  uint8_t u8Ret = 0;
  //
  if (ch < UART_MAX_CH)
  {
    switch (ch)
    {
    case _DEF_UART1:
#ifdef _USE_UART1
      if (u8Len <= qbufferRxAvailable(&qUartRxBuff[ch]))
      {
        qbufferRead(&qUartRxBuff[ch], pMsg, u8Len);
        u8Ret = u8Len;
      }
#endif
      break;
    default:
      break;
    }
  }
  //
  return u8Ret;
}
/**
 * @brief Function to Write bytes data of TX buffs for communication
 *
 * @param ch        uart channel
 * @param p_data    write buff
 * @param u8Len     write data bytes
 * @return uint8_t  write bytes
 */
uint8_t uartWrite(uint8_t ch, const uint8_t *p_data, uint8_t u8Len)
{
  uint8_t result = 0;
  uint8_t u8TxData;
  if (ch < UART_MAX_CH)
  {
    switch (ch)
    {
      case _DEF_UART1:
        while (qbufferEmpty(&qUartTxBuff[ch]) != true) ;
        if (qbufferEmpty(&qUartTxBuff[ch]) == true)
        {
          result = u8Len;
          if (u8Len > 1)
          {
            qbufferFlush(&qUartTxBuff[ch]);
            qbufferWrite(&qUartTxBuff[ch], (const uint8_t *)&p_data[0x01U], (uint8_t)(u8Len - 1));
            UDR0 = p_data[0x00U];
          }
          else
          {
            UDR0 = p_data[0x00U];
          }
        }
        else
        {
          qbufferWrite(&qUartTxBuff[ch], (const uint8_t *)&p_data, u8Len);
        }
        break;

      default:
        break;
    }
  }
  //
  return result;
}
/**
 * @brief MSG Send to uart and uint8_t Data Convert to 2bytes ASCII HEX
 *
 * @param ch      Uart Channel
 * @param pBuf    MSG string buffer pointer
 * @param u8Byte  Convert uint8_t Data to 2bytes ASCII HEX
 * @example (p_cli->ch,"\x1B[",line->cursor);
 */
void uartMsgByte2ASC(uint8_t ch, const uint8_t *pBuf, uint8_t u8Byte)
{
  uint8_t u8Msg[2];
  //
  uartWrite(ch, pBuf, strlen(pBuf));
  com_OutDelay(strlen(pBuf));
  cvtByte2DASC(u8Byte, &u8Msg[0x00U]);
  delay_ms(1);
  //
}
void uartByte2ASC(uint8_t ch, uint8_t u8Byte)
{
  uint8_t u8Msg[2];
  //
  cvtByte2DASC(u8Byte, &u8Msg[0x00U]);
  uartWrite(ch, u8Msg, 2);
  delay_ms(1);
  //
}
void uartMsgByte3ASC(uint8_t ch, const uint8_t *pBuf, uint8_t u8Byte)
{
  uint8_t u8Msg[3];
  //
  uartWrite(ch, pBuf, strlen(pBuf));
  com_OutDelay(strlen(pBuf));
  cvtByte3DASC(u8Byte, &u8Msg[0x00U]);
  uartWrite(ch, u8Msg, 3);
  delay_ms(1);
  //
}
void uartByte3ASC(uint8_t ch, uint8_t u8Byte)
{
  uint8_t u8Msg[3];
  //
  cvtByte3DASC(u8Byte, &u8Msg[0x00U]);
  uartWrite(ch, u8Msg, 3);
  delay_ms(1);
  //
}
void uartMsgWord3DASC(uint8_t ch, const uint8_t *pBuf, uint16_t u16Data)
{
  uint8_t u8Msg[3];
  //
  uartWrite(ch, pBuf, strlen(pBuf));
  com_OutDelay(strlen(pBuf));
  cvtWord3DASC(u16Data, &u8Msg[0x00U]);
  uartWrite(ch, u8Msg, 3);
  delay_ms(1);
}
void uartWord3DASC(uint8_t ch, uint16_t u16Data)
{
  uint8_t u8Msg[3];
  //
  cvtWord3DASC(u16Data,(uint8_t * const)&u8Msg[0x00U]);
  uartWrite(ch,  (const uint8_t *)u8Msg, 3U);
  delay_ms(1);
}
void uartMsgWord4DASC(uint8_t ch, const uint8_t *pBuf, uint16_t u16Data)
{
  uint8_t u8Msg[4];
  //
  uartWrite(ch, pBuf, strlen(pBuf));
  com_OutDelay(strlen(pBuf));
  cvtWord4DASC(u16Data, (uint8_t * const)&u8Msg[0x00U]);
  uartWrite(ch, (const uint8_t *)u8Msg, 4U);
  delay_ms(2);
}
void uartWord4DASC(uint8_t ch, uint16_t u16Data)
{
  uint8_t u8Msg[4];
  //
  cvtWord4DASC(u16Data,(uint8_t * const)&u8Msg[0x00U]);
  uartWrite(ch, (const uint8_t *)u8Msg, 4U);
  delay_ms(1);
}
void uartMsgWord5DASC(uint8_t ch, const uint8_t *pBuf, uint16_t u16Data)
{
  uint8_t u8Msg[5];
  //
  uartWrite(ch, pBuf, strlen(pBuf));
  com_OutDelay(strlen(pBuf));
  cvtWord5DASC(u16Data, (uint8_t * const)&u8Msg[0x00U]);
  uartWrite(ch, (const uint8_t *)u8Msg, 5U);
  delay_ms(2);
}
void uartWord5DASC(uint8_t ch, uint16_t u16Data)
{
  uint8_t u8Msg[5];
  //
  cvtWord5DASC(u16Data, (uint8_t * const)&u8Msg[0x00U]);
  uartWrite(ch,(const uint8_t *)u8Msg, 5U);
  delay_ms(2);
}

/**
 * @brief Msg & uint8_t Data Convert to 2bytes ASCII HEX and Send Uart
 *
 * @param ch      Uart Channel
 * @param pBuf    MSG Buffer Pointer
 * @param u8Data  Convert uint8_t Data to 2bytes ASCII HEX
 * @example
 */
void uartMsgByte2Hex(uint8_t ch, const uint8_t *pBuf, uint8_t u8Data)
{
  uint8_t u8Msg[2];
  //
  uartWrite(ch, pBuf, strlen(pBuf));
  com_OutDelay(strlen(pBuf));
  cvtByte2HEX(u8Data, &u8Msg[0x00U]);
  uartWrite(ch, u8Msg, 2);
  delay_ms(1);
}
/**
 * @brief uint8_t Data Convert to 2bytes ASCII HEX and Send Uart
 *
 * @param ch      Uart Channel
 * @param u8Data  Convert uint8_t Data to 2bytes ASCII HEX
 */
void uartByte2Hex(uint8_t ch, uint8_t u8Data)
{
  uint8_t u8Msg[2];
  //
  cvtByte2HEX(u8Data, &u8Msg[0x00U]);
  uartWrite(ch, u8Msg, 2);
  delay_ms(1);
}
/**
 * @brief   MSG & uint16_t Data Convert to 4bytes ASCII HEX and Send Uart
 *
 * @param ch      Uart Channel
 * @param pBuf    MSG Buffer Pointer
 * @param u16Data Convert uint16_t Data to 4bytes ASCII HEX
 */
void uartMsgWord4Hex(uint8_t ch, const uint8_t *pBuf, uint16_t u16Data)
{
  uint8_t u8Msg[4];
  //
  uartWrite(ch, pBuf, strlen(pBuf));
  com_OutDelay(strlen(pBuf));
  cvtWord4HEX(u16Data, &u8Msg[0x00U]);
  uartWrite(ch, u8Msg, 4);
  delay_ms(2);
  //
}
/**
 * @brief uint16_t Data Convert to 4bytes ASCII HEX and Send Uart
 *
 * @param ch      Uart Channel
 * @param u8Data  Convert uint16_t Data to 4bytes ASCII HEX
 */
void uartWord4Hex(uint8_t ch, uint16_t u16Data)
{
  uint8_t u8Msg[4];
  //
  cvtWord4HEX(u16Data, &u8Msg[0x00U]);
  uartWrite(ch, u8Msg, 4);
  delay_ms(2);
  //
}
/**
 * @brief   MSG & uint8_t Data Convert to 7bytes ASCII Binary and Send Uart
 *
 * @param ch
 * @param pBuf
 * @param u8Data
 */
void uartMsgByte7BASC(uint8_t ch, const uint8_t *pBuf, uint8_t u8Data)
{
  uint8_t u8Msg[8];
  //
  uartWrite(ch, pBuf, strlen(pBuf));
  com_OutDelay(strlen(pBuf));
  cvtByte7BASC(u8Data, &u8Msg[0x00U]);
  uartWrite(ch, u8Msg, 8);
  com_OutDelay(strlen(u8Msg));
}
void uartByte7BASC(uint8_t ch, uint8_t u8Data)
{
  uint8_t u8Msg[8];
  //
  cvtByte7BASC(u8Data, &u8Msg[0x00U]);
  uartWrite(ch, u8Msg, 8);
  com_OutDelay(strlen(u8Msg));
}
// ---------------------------------------------------------------------
uint8_t uartMsgWrite(uint8_t ch, const uint8_t *pBuf)
{
  uint8_t u8Ret = 0x00U;
  u8Ret = uartWrite(ch, (const uint8_t *)pBuf, strlen(pBuf));
  com_OutDelay(strlen(pBuf));
  return (u8Ret);
}
/**
 * @brief Cal_. Wait Delay time for long massages.
 * 
 * @param len :count  out bytes
 */
void com_OutDelay(uint8_t len)
{
  uint8_t u8Delay_time = 0x01U ;
  if(len > COM_OUT_DELAY ) 
  {
    u8Delay_time = len / COM_OUT_DELAY ;
    if( (len % COM_OUT_DELAY) != 0x00U )
    {
      u8Delay_time = u8Delay_time + 1U ;
    }
  }
  delay_ms(u8Delay_time);
}
uint8_t uartFlashWrite(uint8_t ch, flash uint8_t *pBuf)
{
  uint8_t u8Ret = 0x00U;
  uint8_t u8Msg[32] = {
      0x00U,
  };
  uint8_t u8Len = 0x00U;

  while (pBuf[u8Len] != 0x00U)
  {
    u8Msg[u8Len] = pBuf[u8Len];
    u8Len++;
  }
  u8Ret = uartWrite(ch, (const uint8_t *)u8Msg, u8Len);

  return (u8Ret);
}
uint8_t uartPrintf(uint8_t ch, uint8_t *pBuf, uint8_t u8Len)
{
  uint8_t u8Ret = 0x00U;
  u8Ret = uartWrite(ch, (uint8_t *)pBuf, u8Len);
  return (u8Ret);
}
/**
 * @brief max data 40bytes for printf
 * 
 * @param ch    : Com Port
 * @param fmt   : 
 * @param ... 
 * @return uint8_t : output length
 */
/*
      'i' - the function argument is a signed decimal integer;
      'd' - the function argument is a signed decimal integer;
      'u' - the function argument is an unsigned decimal integer;
      'e' - the function argument is a float, that will be outputted using the [-]d.dddddd e[±]dd format
      'E' - the function argument is a float, that will be outputted using the [-]d.dddddd E[±]dd format
      'f' - the function argument is a float, that will be outputted using the [-]ddd.dddddd  format
      'x' - the function argument is an unsigned hexadecimal integer, that will be outputted with lowercase characters;
      'X' - the function argument is an unsigned hexadecimal integer, that will be outputted with with uppercase characters;
      'c' - the function argument is a single character;
      's' - the function argument is a pointer to a null terminated char string located in RAM;
      'p' - the function argument is a pointer to a null terminated char string located in FLASH;
      '%' - the '%' character will be outputted.
*/
uint8_t uartflashPrintf(uint8_t ch, flash char *fmt, ...)
{
  uint8_t u8Ret = 0x00U;
  va_list ap;
  char buf[40];
  int rc;
  //
  va_start(ap, fmt);
  rc = vsprintf(buf, fmt, ap);
  va_end(ap);
  //
  u8Ret = uartWrite(ch, (uint8_t *)buf, strlen(&buf[0x00U]));
  com_OutDelay(u8Ret);
  //
  return (u8Ret);
}

// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
#ifdef _USE_HW_TIMER0
/**
 * @brief Uart RX control Callback Function
 *
 */
void cbUartRX0(void)
{
  // uint8_t i  = 0 ;
  // uint8_t u8RxLen = 0 ;
  // uint8_t u8Data  = 0 ;

  if (++useRx1Wait >= 0x04U)
  {
    if (useRxEvent != 0x00U)
    {
      useRxEvent = 0x00U;
    }
  }
}
/**
 * @brief Uart TX control Callback Function
 *
 */
void cbUartTX0(void)
{
  uint8_t u8Data = 0;

  // Can tx Interrput
  if (useTx1Wait == 0x00U)
  {
    if (qbufferEmpty(&qUartTxBuff[0x00U]) == false) //
    {
      qbufferReadByte(&qUartTxBuff[0x00U], &u8Data);
      UDR0 = u8Data;
      useTx1Wait = 0x01U;
    }
  }
}
#endif

// ---------------------------------------------------------------------------
// USART Receiver interrupt service routine
// ---------------------------------------------------------------------------
//
// #ifdef _USE_UART1
interrupt[USART0_RXC] void usart0_rx_isr(void)
{
  uint8_t u8Status = 0;
  uint8_t u8Data = 0;
  u8Status = UCSR0A;
  u8Data = UDR0;
  //
  // check flrame

  // if(u8Data == STX)
  // {
  //   qbufferFlush(&qUartRxBuff[0x00U]) ;
  //   useRxEvent = 0 ;
  // }
  // else if(u8Data == ETX)
  // {
  //   useRxEvent = 1 ;
  // }

  if ((u8Status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN)) == 0)
  {
    if (qbufferTxAvailable(&qUartRxBuff[0x00U]) > 0x00U)
    {
      qbufferWrite(&qUartRxBuff[0x00U], &u8Data, 1);
    }
    useRxEvent = 1;
  }
  else
  {
    UCSR0A = 0x00U;
  }
  //
  useRx1Wait = 0;
}
// --------------------------------------------------------------
//  USART0 Transmitter interrupt service routine
interrupt[USART0_TXC] void usart0_tx_isr(void)
{
  uint8_t u8Data = 0;
  //
  if (qbufferEmpty(&qUartTxBuff[0x00U]) == false)
  {
    qbufferReadByte(&qUartTxBuff[0x00U], &u8Data);
    UDR0 = u8Data;
    useTx1Wait = 1;
  }
  else
  {
    useTx1Wait = 0;
  }
}

// #endif

#endif /* src/common/hw/include/uart.h End Of File !! Well Done */
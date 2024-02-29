/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ]  uart.h
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

 
/* Mutiple includes protection */
#ifndef SRC_COMMON_HW_INCLUDE_UART_H_
#define SRC_COMMON_HW_INCLUDE_UART_H_
/* Includes */
#include "hw_def.h"

#ifdef _USE_HW_UART
// ---------------------------------------------------------------------------
// Define Global define
// ---------------------------------------------------------------------------
//
#define UART_MAX_CH         HW_UART_MAX_CH
#define COM_OUT_DELAY       HW_COM_OUT_DELAY    // Comm Data Out Delay Time
// ---------------------------------------------------------------------------
// Define typedef
// ---------------------------------------------------------------------------
//
// typedef enum
// {
//   UART_9600BPS,
//   UART_19200BPS,
//   UART_38400BPS,

// } UART_BPS;
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// ---------------------------------------------------------------------------
//
bool    uartInit(void);
bool    uartOpen(uint8_t ch, UART_BPS bps);
uint8_t uartRXAvailable(uint8_t ch) ;
uint8_t uartTXAvailable(uint8_t ch) ;
uint8_t uartRead(uint8_t ch);
uint8_t uartWrite(uint8_t ch, const uint8_t *p_data, uint8_t u8Len);
uint8_t uartMsgWrite(uint8_t ch,const uint8_t *pBuf);
uint8_t uartFlashWrite(uint8_t ch,flash uint8_t *pBuf);

void uartMsgByte2ASC(uint8_t ch,const uint8_t *pBuf,uint8_t u8Byte);
void uartByte2ASC(uint8_t ch, uint8_t u8Byte); 
void uartMsgByte3ASC(uint8_t ch,const uint8_t *pBuf,uint8_t u8Byte);
void uartByte3ASC(uint8_t ch,uint8_t u8Byte);
void uartMsgWord3DASC(uint8_t ch,const uint8_t *pBuf,uint16_t u16Data);
void uartWord3DASC(uint8_t ch, uint16_t u16Data);
void uartMsgWord4DASC(uint8_t ch,const uint8_t *pBuf,uint16_t u16Data);
void uartWord4DASC(uint8_t ch, uint16_t u16Data);
void uartMsgWord5DASC(uint8_t ch,const uint8_t *pBuf,uint16_t u16Data);
void uartWord5DASC(uint8_t ch, uint16_t u16Data);

void uartMsgByte2Hex(uint8_t ch,const uint8_t *pBuf,uint8_t u8Data);
void uartByte2Hex(uint8_t ch,uint8_t u8Data);
void uartMsgWord4Hex(uint8_t ch,const uint8_t *pBuf,uint16_t u16Data);
void uartWord4Hex(uint8_t ch,uint16_t u16Data);
 
void uartMsgByte7BASC(uint8_t ch,const uint8_t *pBuf,uint8_t u8Data);
void uartByte7BASC(uint8_t ch,uint8_t u8Data);


uint8_t uartPrintf(uint8_t ch,uint8_t *pBuf,uint8_t u8Len);
uint8_t uartflashPrintf(uint8_t ch,flash char *fmt, ...);

// -----------------------------------------------------------------------------
// CallBAck Function Prototypes Definitions
// -----------------------------------------------------------------------------
 

#endif
#endif /* src/common/hw/include/uart.h End Of File !! Well Done */

/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]  ATMEGA128A
 * [ Compller  ]
 * [ Filename  ]  AP.c
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
 * Hagseong Kang   2024-01-16   First release of this file 
 * --------------------------------------------------------------------------
 * Additional Notes:
 * **************************************************************************
 */
#include "ap.h"

/**
 * @brief 
 * 
 */
void apInit(void)
{
  uartOpen(_DEF_UART1,UART_38400BPS) ;
  //uartOpen(_DEF_UART2,UART_38400BPS) ;

  cliOpen(_DEF_UART1,UART_38400BPS) ;
  //cliOpenLog(_DEF_UART2,UART_38400BPS) ;
}
/*
 *
 */
void apMain(void)
{
  uint16_t preTime  = 0x00;
  uint8_t rxData = 0x00U ;
  // Global enable interrupts
  #asm("sei") 

  preTime = millis() ;
  cliShowMFG();

  while(1)
  {
    if((millis() - preTime) >= 250)
    {
      preTime = millis() ;

      //rxData = ReadPortBuffData(0);
      //uartMsgByte7BASC(_DEF_UART1,"\r\nRead Port Buff[0]",rxData);
    }

    if(cliMain() ==  false )
    {
        uartMsgWrite(_DEF_UART1,"CLI Error");
        delay_ms(500);
    }


  }
}

// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
 
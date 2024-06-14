/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ]  timer0_int.c
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
 * Hagseong Kang   2023-04-24   First release of this file
 * --------------------------------------------------------------------------
 * Additional Notes:
 * **************************************************************************
 */

#include "Timer0_int.h"

#ifdef _USE_HW_TIMER0
// ---------------------------------------------------------------------------
// Define Global define
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
// Define typedef struct
// ---------------------------------------------------------------------------
//
typedef struct
{
    void (*callBack)(void) ;

} Timer0_CB_tbl_t ;

typedef void (*cbTimer0_t)(void); 
// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
static  Timer0_CB_tbl_t timer0_CB_tbl[TIMER0_MAX_CB] ;
static volatile uint16_t sysTickCounter = 0 ;
// ---------------------------------------------------------------------------
//  Macro Define .
// ---------------------------------------------------------------------------
 
// ---------------------------------------------------------------------------
// Define private function prototypes.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
// Define private function definitions.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
// Define  Global Function definitions.
// ---------------------------------------------------------------------------
//
bool timer0Init(void)
{
  bool bRet = true ;
  uint8_t i = 0 ;
 
 
  // Timer/Counter 0 initialization
  // Clock source: System Clock
  // Clock value: 250.000 kHz
  // Mode: CTC top=OCR0
  // OC0 output: Disconnected
  // Timer Period: 1 ms
  ASSR=0<<AS0;
  TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (1<<WGM01) | (1<<CS02) | (0<<CS01) | (0<<CS00);
  TCNT0=0x00;
  OCR0=0xF9;

  // Timer(s)/Counter(s) Interrupt(s) initialization
  TIMSK |= (1<<OCIE0) ;
 

  for(i = 0 ; i < TIMER0_MAX_CB ; i++)
  {
  	timer0_CB_tbl[i].callBack = NULL ;
  }
  
  sysTickCounter = 0x00 ;
  return bRet ;
}
/**
 * @brief  Function Get 1mSec Harsware timer counter
 * 
 * @return uint16_t   1mSec Timer Counter value
 */
uint16_t  millis(void)  
{
  return sysTickCounter ;  
}
void timer0Enable(void)
{
  // Timer(s)/Counter(s) Interrupt(s) initialization
  TIMSK |= (1<<OCIE0) ;
}
void timer0Disable(void)
{
  // Timer(s)/Counter(s) Interrupt(s) initialization
  TIMSK &= ~(1<<OCIE0) ;
}
// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
void canSetTimer0Callback(uint8_t ch, void (*callBack)(void))
{
  if(ch < TIMER0_MAX_CB )
  {
    if(timer0_CB_tbl[ch].callBack == NULL )
    {
      timer0_CB_tbl[ch].callBack = callBack ;
    }
  }
}
// ------------------------------------------------------------------
// External Interrupt 0 service routine
// ------------------------------------------------------------------
//
/**
 * @brief Timer0 interrupt service routine  (1mSeC)
 * 
 * @return interrupt[TIM0_COMP] 
 */
 
interrupt [TIM0_COMP] void timer0CompIsr(void)
{
  uint8_t u8i = 0U ;
  // Place your code here
  sysTickCounter++ ;

  for(u8i=0U; u8i<TIMER0_MAX_CB; u8i++)
  {
    if(timer0_CB_tbl[u8i].callBack != NULL) 
    {
        (*timer0_CB_tbl[u8i].callBack)() ;
    }
  }

}
#endif
 /* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ]  portRead.h
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
 * Hagseong Kang   2024-02-26   First release of this file
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
#ifndef SRC_COMMON_HW_INCLUDE_PORT_READ_H_
#define SRC_COMMON_HW_INCLUDE_PORT_READ_H_
/* Includes */
#include "hw_def.h"

#ifdef _USE_HW_PORTREAD
// ---------------------------------------------------------------------------
// Define Global define
// ---------------------------------------------------------------------------
//
#define PORTREAD_MAX_CH     HW_PORTREAD_MAX_CH
 
// ---------------------------------------------------------------------------
// Define typedef
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// ---------------------------------------------------------------------------
//
#pragma used+
bool      PortReadInit(void);
uint8_t   ReadPortBuffData(uint8_t index);
uint8_t   ReadPortData(GPIO_Port selectPort);
bool      IsCheckPin(uint8_t index ,uint8_t selectBit) ;
GPIO_PinState IsCheckHWPin(GPIO_Port portCh ,uint8_t pin) ;
#pragma used-
// -----------------------------------------------------------------------------
// CallBAck Function Prototypes Definitions
// -----------------------------------------------------------------------------
 

#endif
#endif /* src/common/hw/include/portRead.h End Of File !! Well Done */
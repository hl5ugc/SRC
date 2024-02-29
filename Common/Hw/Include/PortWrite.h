 /* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ]  PortWrite.h
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
 * Hagseong Kang  2024-02-26   First release of this file
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
#ifndef SRC_COMMON_HW_INCLUDE_PORTWRITE_H_
#define SRC_COMMON_HW_INCLUDE_PORTWRITE_H_
/* Includes */
#include "hw_def.h"

#ifdef _USE_HW_PORTWRITE
// ---------------------------------------------------------------------------
// Define Global define
// ---------------------------------------------------------------------------
//
#define PORTWRITE_MAX_CH     HW_PORTWRITE_MAX_CH
 
// ---------------------------------------------------------------------------
// Define typedef
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// ---------------------------------------------------------------------------
//
bool  PortWriteInit(void);
void  WriteHWPortCBDisable(void);
void  WriteHWPortCBEnable(void);
bool  WritePortData(GPIO_Port writePort,uint8_t u8Data);
bool  WritePortBuffData(uint8_t u8index,uint8_t u8Bit,GPIO_PinState status);
uint8_t  GetwritePortBuffData(uint8_t u8Index);
// -----------------------------------------------------------------------------
// CallBAck Function Prototypes Definitions
// -----------------------------------------------------------------------------
 

#endif
#endif /* src/common/hw/include/portWrite.h End Of File !! Well Done */
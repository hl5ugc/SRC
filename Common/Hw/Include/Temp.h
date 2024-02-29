/* --------------------------------------------------------------------------
 * [ PROJECT   ]   
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  Temp.h
 * [ Version   ]  1.0
 * [ Created   ]  2024-02-27
 * --------------------------------------------------------------------------
 * Revision History :
 * ------------------------------------------------------------------
 *
 *
 *  *.The use of this source code shall be deemed to have been 
 *    tacitly agreed by the user.
 *  *.This source code is freely available for personal learning 
 *    and research and development.
 *  *.In the case of secondary authoring or redistribution using this source, 
 *    it is essential The company name of SAMJIN ELECTRONICS must be specified.
 *  *.Do not sell or for-profit this source code.
 *	*.This clause and the original author mark are prohibited from being 
 *	  modified or deleted. 
 *  
 *------------------------------------------------------------------
 * --------------------------------------------------------------------------
 * Author         Date       Comments on this revision
 * --------------------------------------------------------------------------
 * Hagseong Kang  2024-02-27   First release of this file
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
#ifndef COMMON_HW_INCLUDE_TEMP_H_
#define COMMON_HW_INCLUDE_TEMP_H_
/* Includes */
#include "hw_def.h"
#ifdef _USE_HW_TEMP
 
 
// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 
#define MAX_TEMP_CH     HW_TEMP_MAX_CH
#define DEF_TEMP_CB_CH  HW_TEMP_CONTROL_CB
// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
//
 
typedef enum
{
  ST_TEMP   = 0x01U,
  DT_TEMP   = 0x03U,
  ALL_TEMP  = 0x09U
} TEMP_CHANEL;

// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//
void TempInit(void);
void Is_TEMP_UpdateClear(TEMP_CHANEL tempCH);
bool Is_TEMP_Update(TEMP_CHANEL tempCH);
int16_t TempGet(TEMP_CHANEL tempCH);
#endif 
#endif 
/* TEMP.h End Of File !! Well Done */
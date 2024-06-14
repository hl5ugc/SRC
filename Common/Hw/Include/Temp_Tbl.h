/* --------------------------------------------------------------------------
 * [ PROJECT   ]   
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  Temp_Tbl.h
 * [ Version   ]  1.0
 * [ Created   ]  2024-06-10
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
 * Hagseong Kang  2024-06-10  First release of this file
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
#ifndef COMMON_HW_INCLUDE_TEMP_TBL_H_
#define COMMON_HW_INCLUDE_TEMP_TBL_H_
/* Includes */
#include "hw_def.h"
 
 
// Temp Sensor  DF-103FU-25S // 10K + SENSOR.... REF 4.096 
// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 
#define COOL_SEC_TIME_MAX   6000    // 2Min --> 12,000 X 10 = 120,000
#define DT_TEMP_MAX         310     // 30.0 C
#define DT_TEMP_MIN         170     // 10.0 C
// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
//
//
// extern volatile SYSTEM_FLAG temp_flag ;
// ---------------------------------------------------------------------------
//  Flag Macro Define .
// ---------------------------------------------------------------------------
/*
#define st_temp_update_flag_on                  temp_flag.bits.bit0 = 1
#define st_temp_update_flag_off                 temp_flag.bits.bit0 = 0
#define Is_st_temp_update_flag                  temp_flag.bits.bit0 == 1
#define Is_Not_st_temp_update_flag              temp_flag.bits.bit0 == 0
//
#define dt_temp_update_flag_on                  temp_flag.bits.bit1 = 1
#define dt_temp_update_flag_off                 temp_flag.bits.bit1 = 0
#define Is_dt_temp_update_flag                  temp_flag.bits.bit1 == 1
#define Is_Not_dt_temp_update_flag              temp_flag.bits.bit1 == 0
*/
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//
signed int temp_cal(uint16_t u16Data);


#endif /* TEMP_TBL.h End Of File !! Well Done */
 
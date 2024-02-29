/* --------------------------------------------------------------------------
 * [ PROJECT   ]   
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  MCP4822.h
 * [ Version   ]  1.0
 * [ Created   ]  2023[11:57:54 AM ]
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
 * Hagseong Kang  Jul 14, 2023    First release of this file
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
#ifndef COMMON_HW_INCLUDE_MCP4822_H_
#define COMMON_HW_INCLUDE_MCP4822_H_
/* Includes */
#include "hw_def.h"
#ifdef _USE_HW_MCP4822
 
// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 
#define MAX_DA_DATA       HW_MCP4822_MAX_DA_DATA
#define DA_DATA_MIN       HW_MCP4822_DA_DATA_MIN  
#define DA_DATA_MAX       HW_MCP4822_DA_DATA_MAX 
// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
// 
typedef enum
{
  MCP4822_CHA = 0x00U,
  MCP4822_CHB = 0x01U,

} MCP4822_CH;
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//
void MCP4822Init(void);
void MCP4822_Data_Out_Main(MCP4822_CH channel, uint16_t wDa_Data);
// 
void MCP4822_Level_Sv_data_Out(uint16_t da_data);
void MCP4822_Level_Sv_data_Clear_Out(void);
//
uint16_t Get_MCP4822_Data(void);
//
//void MCP4822_Sw_Transmit(MCP4822_CH channel, uint8_t bGain, uint16_t wDa_Data); 
//
#endif 
#endif 
/* default.h End Of File !! Well Done */
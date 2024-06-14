/* --------------------------------------------------------------------------
 * [ PROJECT   ]   
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  IPL_PULSE.h
 * [ Version   ]  1.0
 * [ Created   ]  2024-06-27
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
 * Hagseong Kang  2024-06-27   First release of this file
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
#ifndef COMMON_HW_INCLUDE_IPL_PULSE_H_
#define COMMON_HW_INCLUDE_IPL_PULSE_H_
/* Includes */
#include "hw_def.h"
 
 
 
// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 
#define Pulse_1_DUR_MAX     27U
#define Pulse_1_DUR_MIN     0U 
//
#define Pulse_3_DUR_MAX     11U
#define Pulse_3_DUR_MIN     0U 
//
#define Pulse_7_DUR_MAX     11U
#define Pulse_7_DUR_MIN     0U
//
#define Pulse_I_DUR_MAX     68U
#define Pulse_I_DUR_MIN     68U 
// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
//
extern SYSTEM_FLAG IPL_pulse_flag ;  
 
// --------------------------------------------------------------------------- 

#define IPL_pulse_flag_valus                IPL_pulse_flag.valus
//
#define IPL_pulse_run_flag_on               IPL_pulse_flag.bits.bit0 = 1
#define IPL_pulse_run_flag_off              IPL_pulse_flag.bits.bit0 = 0
#define Is_IPL_pulse_run_flag               IPL_pulse_flag.bits.bit0 == 1
#define Is_Not_IPL_pulse_run_flag           IPL_pulse_flag.bits.bit0 == 0
//
#define IPL_pulse_end_S_flag_on             IPL_pulse_flag.bits.bit4 = 1
#define IPL_pulse_end_S_flag_off            IPL_pulse_flag.bits.bit4 = 0
#define Is_IPL_pulse_end_S_flag             IPL_pulse_flag.bits.bit4 == 1
#define Is_Not_IPL_pulse_end_S_flag         IPL_pulse_flag.bits.bit4 == 0
//
#define IPL_pulse_end_E_flag_on             IPL_pulse_flag.bits.bit5 = 1
#define IPL_pulse_end_E_flag_off            IPL_pulse_flag.bits.bit5 = 0
#define Is_IPL_pulse_end_E_flag             IPL_pulse_flag.bits.bit5 == 1
#define Is_Not_IPL_pulse_end_E_flag         IPL_pulse_flag.bits.bit5 == 0
//
// ------------------------------------------------------------------------
//
extern uint16_t    Pulse_i_data[81] ;
extern uint8_t     Pulse_data_ptr  ;
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//
void IplPulseInit(void);
uint16_t Level_to_Flu_cal(uint16_t u16Ipulse_Type,uint16_t u16Dur,uint16_t u16Level);
uint16_t dur_data_load(uint16_t u16Ipulse_Type,uint8_t u16Dur);
void dur_ptr_limit_check(uint16_t u16Ipulse_Type,uint8_t u8Updown,uint8_t *pDurPtr);
 
#endif /* ADC.h End Of File !! Well Done */
/* --------------------------------------------------------------------------
 * [ PROJECT   ]   
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  IPL_SIO.h
 * [ Version   ]  1.0
 * [ Created   ]  2024-06-12
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
#ifndef COMMON_HW_INCLUDE_IPL_SIO_H_
#define COMMON_HW_INCLUDE_IPL_SIO_H_
/* Includes */
#include "hw_def.h"
 
// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 
#ifdef _USE_HW_TIMER0
#define USE_IPL_SIO_CB_CH     HW_IPL_SIO_TIMER0_CB   
#endif
// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
//
extern SYSTEM_FLAG IPL_cmd1_flag ;
extern SYSTEM_FLAG IPL_cmd2_flag ;
// --------------------------------------------------------------------------- 
#define Comm0_cmd1_valus                    IPL_cmd1_flag.valus
#define IPL_Power_on_rtn_flag_on            IPL_cmd1_flag.bits.bit0 = 1
#define IPL_Power_on_rtn_flag_off           IPL_cmd1_flag.bits.bit0 = 0
#define Is_IPL_Power_on_rtn                 IPL_cmd1_flag.bits.bit0 == 1
#define Is_Not_IPL_Power_on_rtn             IPL_cmd1_flag.bits.bit0 == 0
//
#define IPL_SIMMER_on_rtn_flag_on           IPL_cmd1_flag.bits.bit1 = 1
#define IPL_SIMMER_on_rtn_flag_off          IPL_cmd1_flag.bits.bit1 = 0
#define Is_IPL_SIMMER_on_rtn                IPL_cmd1_flag.bits.bit1 == 1
#define Is_Not_IPL_SIMMER_on_rtn            IPL_cmd1_flag.bits.bit1 == 0
// 
#define IPL_Shot_data_rtn_flag_on           IPL_cmd1_flag.bits.bit2 = 1
#define IPL_Shot_data_rtn_flag_off          IPL_cmd1_flag.bits.bit2 = 0
#define Is_IPL_Shot_data_rtn                IPL_cmd1_flag.bits.bit2 == 1
#define Is_Not_IPL_Shot_data_rtn            IPL_cmd1_flag.bits.bit2 == 0
//
// ------------------------------------------------------------------------
//
#define Power_error_valus                   IPL_cmd2_flag.valus
#define POWER_OVP_flag_on                   IPL_cmd2_flag.bits.bit0 = 1
#define POWER_OVP_flag_off                  IPL_cmd2_flag.bits.bit0 = 0
#define Is_POWER_OVP                        IPL_cmd2_flag.bits.bit0 == 1
#define Is_Not_POWER_OVP                    IPL_cmd2_flag.bits.bit0 == 0
//
#define POWER_OCP_flag_on                   IPL_cmd2_flag.bits.bit1 = 1
#define POWER_OCP_flag_off                  IPL_cmd2_flag.bits.bit1 = 0
#define Is_POWER_OCP                        IPL_cmd2_flag.bits.bit1 == 1
#define Is_Not_POWER_OCP                    IPL_cmd2_flag.bits.bit1 == 0
//
#define POWER_TH_flag_on                    IPL_cmd2_flag.bits.bit2 = 1
#define POWER_TH_flag_off                   IPL_cmd2_flag.bits.bit2 = 0
#define Is_POWER_TH                         IPL_cmd2_flag.bits.bit2 == 1
#define Is_Not_POWER_TH                     IPL_cmd2_flag.bits.bit2 == 0
//
#define POWER_SIM_flag_on                   IPL_cmd2_flag.bits.bit3 = 1
#define POWER_SIM_flag_off                  IPL_cmd2_flag.bits.bit3 = 0
#define Is_POWER_SIM                        IPL_cmd2_flag.bits.bit3 == 1
#define Is_Not_POWER_SIM                    IPL_cmd2_flag.bits.bit3 == 0
//
#define POWER_DISCH_flag_on                 IPL_cmd2_flag.bits.bit6 = 1
#define POWER_DISCH_flag_off                IPL_cmd2_flag.bits.bit6 = 0
#define Is_POWER_DISCH                      IPL_cmd2_flag.bits.bit6 == 1
#define Is_Not_POWER_DISCH                  IPL_cmd2_flag.bits.bit6 == 0
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//
void IplSioInit(void);
 
void Send_Simmer_on_cmd(void);
void Send_Simmer_off_cmd(void);
void Send_Power_on_cmd(void);
void Send_Power_off_cmd(void);
void Send_Discharge_on_cmd(void);
void Send_Discharge_off_cmd(void);
void Send_Status_req_cmd(void);
void Send_Shot_data_cmd(uint16_t u16Volt,uint16_t u16Pulse_W,uint8_t u16Hz_Data);
 
#endif /* IPL_SIO.h End Of File !! Well Done */
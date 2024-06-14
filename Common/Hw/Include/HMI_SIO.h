/* --------------------------------------------------------------------------
 * [ PROJECT   ]   
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  HMI_SIO.h
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
 * Hagseong Kang  2024-06-10   First release of this file
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
#ifndef COMMON_HW_INCLUDE_HMI_SIO_H_
#define COMMON_HW_INCLUDE_HMI_SIO_H_
/* Includes */
#include "hw_def.h"
 
 
 
// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 

#ifdef _USE_HW_TIMER0
#define USE_HMI_SIO_CB_CH     HW_HMI_SIO_TIMER0_CB   
#endif


#define HMI_STX_HI          0xF4U
#define HMI_STX_LO          0xF5U
#define HMI_WReg_CMD        0x80U
#define HMI_RReg_CMD        0x81U
#define HMI_WRam_CMD        0x82U
#define HMI_RRam_CMD        0x83U
// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
//
extern SYSTEM_FLAG hmi_comm_flag ;
// extern SYSTEM_FLAG key_in_flag ;
// // --------------------------------------------------------------------------- 
#define HMI_Comm_flag_valus                 hmi_comm_flag.valus
//
#define HMI_Comm_Freq_set_flag_on           hmi_comm_flag.bits.bit0 = 1
#define HMI_Comm_Freq_set_flag_off          hmi_comm_flag.bits.bit0 = 0
#define Is_HMI_Comm_Freq_set_flag           hmi_comm_flag.bits.bit0 == 1
#define Is_Not_HMI_Comm_Freq_set_flag       hmi_comm_flag.bits.bit0 == 0
//
#define FLU_updata_flag_on                  hmi_comm_flag.bits.bit1 = 1
#define FLU_updata_flag_off                 hmi_comm_flag.bits.bit1 = 0
#define Is_FLU_updata_flag                  hmi_comm_flag.bits.bit1 == 1
#define Is_Not_FLU_updata_flag              hmi_comm_flag.bits.bit1 == 0
//
#define DUR_updata_flag_on                  hmi_comm_flag.bits.bit2 = 1
#define DUR_updata_flag_off                 hmi_comm_flag.bits.bit2 = 0
#define Is_DUR_updata_flag                  hmi_comm_flag.bits.bit2 == 1
#define Is_Not_DUR_updata_flag              hmi_comm_flag.bits.bit2 == 0
//
#define FRE_updata_flag_on                  hmi_comm_flag.bits.bit3 = 1
#define FRE_updata_flag_off                 hmi_comm_flag.bits.bit3 = 0
#define Is_FRE_updata_flag                  hmi_comm_flag.bits.bit3 == 1
#define Is_Not_FRE_updata_flag              hmi_comm_flag.bits.bit3 == 0
//
#define Ready_btn_set_flag_on               hmi_comm_flag.bits.bit4 = 1
#define Ready_btn_set_flag_off              hmi_comm_flag.bits.bit4 = 0
#define Is_Ready_btn_set_flag               hmi_comm_flag.bits.bit4 == 1
#define Is_Not_Ready_btn_set_flag           hmi_comm_flag.bits.bit4 == 0
//
#define Cool_btn_set_flag_on                hmi_comm_flag.bits.bit5 = 1
#define Cool_btn_set_flag_off               hmi_comm_flag.bits.bit5 = 0
#define Is_Cool_btn_set_flag                hmi_comm_flag.bits.bit5 == 1
#define Is_Not_Cool_btn_set_flag            hmi_comm_flag.bits.bit5 == 0

#define Save_btn_set_flag_on                hmi_comm_flag.bits.bit6 = 1
#define Save_btn_set_flag_off               hmi_comm_flag.bits.bit6 = 0
#define Is_Save_btn_set_flag                hmi_comm_flag.bits.bit6 == 1
#define Is_Not_Save_btn_set_flag            hmi_comm_flag.bits.bit6 == 0
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//
void HMI_SioInit(void);
void HMI_SioMemInit(uint16_t *pBuff);  
//
void send_set_screen(uint8_t u8Screen_No);
void send_HMI_bytes(const uint8_t *pBuffs);
//

#endif /* HMI_SIO.h End Of File !! Well Done */
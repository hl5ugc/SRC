/* --------------------------------------------------------------------------
 * [ PROJECT   ]   
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  APR_EEPROM.h
 * [ Version   ]  1.0
 * [ Created   ]  2024.0
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
#ifndef COMMON_HW_INCLUDE_APR_EEPROM_H_
#define COMMON_HW_INCLUDE_APR_EEPROM_H_
/* Includes */
#include "hw_def.h"
#ifdef _USE_HW_MEMORY
 
// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 
#define BLOCK_SIZE          64U
#define PAGE_SIZE_MAX       512U
//
#define EP_HAED             (BLOCK_SIZE)
#define EP_BASE1            (BLOCK_SIZE * 2)  // 64 * 2 = 128

#define EP_PASSWORD         EP_BASE1 + 0U 
#define EP_ST_TEMP_SV_MIN   EP_BASE1 + 2U    
#define EP_ST_TEMP_SV_MAX   EP_BASE1 + 4U 
#define EP_ST_TEMP_OFFSET   EP_BASE1 + 6U  
#define EP_FILTER_SELECT    EP_BASE1 + 8U 
#define EP_F_PULSE_TYPE     EP_BASE1 + 9U
//
#define EP_TOTAL_COUNT      EP_BASE1 + 10U        
#define EP_TOTAL_COUNT_HI   EP_BASE1 + 10U        
#define EP_TOTAL_COUNT_LO   EP_BASE1 + 12U
//         
#define EP_LAMP_COUNT       EP_BASE1 + 14U         
#define EP_LAMP_COUNT_HI    EP_BASE1 + 14U        
#define EP_LAMP_COUNT_LO    EP_BASE1 + 16U 
//
#define EP_F510_COUNT       EP_BASE1 + 18U         
#define EP_F510_COUNT_HI    EP_BASE1 + 18U        
#define EP_F510_COUNT_LO    EP_BASE1 + 20U 
//
#define EP_F560_COUNT       EP_BASE1 + 22U         
#define EP_F560_COUNT_HI    EP_BASE1 + 22U        
#define EP_F560_COUNT_LO    EP_BASE1 + 24U 
//
#define EP_F585_COUNT       EP_BASE1 + 26U         
#define EP_F585_COUNT_HI    EP_BASE1 + 26U        
#define EP_F585_COUNT_LO    EP_BASE1 + 28U 
//
#define EP_F640_COUNT       EP_BASE1 + 30U         
#define EP_F640_COUNT_HI    EP_BASE1 + 30U        
#define EP_F640_COUNT_LO    EP_BASE1 + 32U 
//
#define EP_F700_COUNT       EP_BASE1 + 34U         
#define EP_F700_COUNT_HI    EP_BASE1 + 34U        
#define EP_F700_COUNT_LO    EP_BASE1 + 36U 
//
#define EP_F800_COUNT       EP_BASE1 + 38U         
#define EP_F800_COUNT_HI    EP_BASE1 + 38U        
#define EP_F800_COUNT_LO    EP_BASE1 + 40U 
//
#define EP_F900_COUNT       EP_BASE1 + 42U         
#define EP_F900_COUNT_HI    EP_BASE1 + 42U        
#define EP_F900_COUNT_LO    EP_BASE1 + 44U 

// -------------------------------------------
#define EP_SERIAL_YY        EP_BASE1 + 46U 
#define EP_SERIAL_MM        EP_BASE1 + 48U 
#define EP_SERIAL_DD        EP_BASE1 + 50U 
#define EP_SERIAL_NO        EP_BASE1 + 52U 
// ------------------------------------------
#define EP_APR_BACKUP       EP_BASE1 + 54U    // FILTER
#define EP_SYS_OPTION       EP_BASE1 + 56U 
// ----------------------------------------------
#define EP_F510_PULSE       (BLOCK_SIZE * 3U) + 0
#define EP_F560_PULSE       (BLOCK_SIZE * 3U) + 6
#define EP_F585_PULSE       (BLOCK_SIZE * 3U) + 12
#define EP_F640_PULSE       (BLOCK_SIZE * 3U) + 18
#define EP_F700_PULSE       (BLOCK_SIZE * 3U) + 24
#define EP_F800_PULSE       (BLOCK_SIZE * 3U) + 26
#define EP_F900_PULSE       (BLOCK_SIZE * 3U) + 28
//
// ------------------------------------------          
//
#define EP_F510_P_APR_BASE      (BLOCK_SIZE * 5U) 
#define EP_F510_S_D_PTR         EP_F520_APR_BASE + 0 
#define EP_F510_S_LEVEL         EP_F520_APR_BASE + 2 
#define EP_F510_T_D_PTR         EP_F520_APR_BASE + 4 
#define EP_F510_T_LEVEL         EP_F520_APR_BASE + 6 
#define EP_F510_V_D_PTR         EP_F520_APR_BASE + 8 
#define EP_F510_V_LEVEL         EP_F520_APR_BASE + 10 
#define EP_F510_I_D_PTR         EP_F520_APR_BASE + 12 
#define EP_F510_I_LEVEL         EP_F520_APR_BASE + 14  
// ------------------------------------------          
#define EP_F520_P_APR_BASE      (BLOCK_SIZE * 6U)  
#define EP_F520_S_D_PTR         EP_F520_APR_BASE +0 
#define EP_F520_S_LEVEL         EP_F520_APR_BASE +2 
#define EP_F520_T_D_PTR         EP_F520_APR_BASE +4 
#define EP_F520_T_LEVEL         EP_F520_APR_BASE +6 
#define EP_F520_V_D_PTR         EP_F520_APR_BASE +8 
#define EP_F520_V_LEVEL         EP_F520_APR_BASE +10 
#define EP_F520_I_D_PTR         EP_F520_APR_BASE +12 
#define EP_F520_I_LEVEL         EP_F520_APR_BASE +14 
// ------------------------------------------------
#define EP_F560_P_APR_BASE      (BLOCK_SIZE * 8U)  
#define EP_F560_S_D_PTR         EP_F560_APR_BASE +0 
#define EP_F560_S_LEVEL         EP_F560_APR_BASE +2 
#define EP_F560_T_D_PTR         EP_F560_APR_BASE +4 
#define EP_F560_T_LEVEL         EP_F560_APR_BASE +6 
#define EP_F560_V_D_PTR         EP_F560_APR_BASE +8 
#define EP_F560_V_LEVEL         EP_F560_APR_BASE +10 
#define EP_F560_I_D_PTR         EP_F560_APR_BASE +12 
#define EP_F560_I_LEVEL         EP_F560_APR_BASE +14 
// ------------------------------------------------ 
#define EP_F585_P_APR_BASE      (BLOCK_SIZE * 9U)      
#define EP_F585_S_D_PTR         EP_F585_APR_BASE +0 
#define EP_F585_S_LEVEL         EP_F585_APR_BASE +2 
#define EP_F585_T_D_PTR         EP_F585_APR_BASE +4 
#define EP_F585_T_LEVEL         EP_F585_APR_BASE +6 
#define EP_F585_V_D_PTR         EP_F585_APR_BASE +8 
#define EP_F585_V_LEVEL         EP_F585_APR_BASE +10 
#define EP_F585_I_D_PTR         EP_F585_APR_BASE +12 
#define EP_F585_I_LEVEL         EP_F585_APR_BASE +14 
// ------------------------------------------------ 
#define EP_F640_P_APR_BASE      (BLOCK_SIZE * 10U)     
#define EP_F640_S_D_PTR         EP_F640_APR_BASE +0 
#define EP_F640_S_LEVEL         EP_F640_APR_BASE +2 
#define EP_F640_T_D_PTR         EP_F640_APR_BASE +4 
#define EP_F640_T_LEVEL         EP_F640_APR_BASE +6 
#define EP_F640_V_D_PTR         EP_F640_APR_BASE +8 
#define EP_F640_V_LEVEL         EP_F640_APR_BASE +10 
#define EP_F640_I_D_PTR         EP_F640_APR_BASE +12 
#define EP_F640_I_LEVEL         EP_F640_APR_BASE +14 
// ------------------------------------------------ 
#define EP_F700_P_APR_BASE      (BLOCK_SIZE * 11U)     
#define EP_F700_S_D_PTR         EP_F700_APR_BASE +0 
#define EP_F700_S_LEVEL         EP_F700_APR_BASE +2 
#define EP_F700_T_D_PTR         EP_F700_APR_BASE +4 
#define EP_F700_T_LEVEL         EP_F700_APR_BASE +6 
#define EP_F700_V_D_PTR         EP_F700_APR_BASE +8 
#define EP_F700_V_LEVEL         EP_F700_APR_BASE +10 
#define EP_F700_I_D_PTR         EP_F700_APR_BASE +12 
#define EP_F700_I_LEVEL         EP_F700_APR_BASE +14 
// ------------------------------------------------  
#define EP_F800_P_APR_BASE      (BLOCK_SIZE * 12U)     
#define EP_F800_S_D_PTR         EP_F800_APR_BASE +0 
#define EP_F800_S_LEVEL         EP_F800_APR_BASE +2 
#define EP_F800_T_D_PTR         EP_F800_APR_BASE +4 
#define EP_F800_T_LEVEL         EP_F800_APR_BASE +6 
#define EP_F800_V_D_PTR         EP_F800_APR_BASE +8 
#define EP_F800_V_LEVEL         EP_F800_APR_BASE +10 
#define EP_F800_I_D_PTR         EP_F800_APR_BASE +12 
#define EP_F800_I_LEVEL         EP_F800_APR_BASE +14 
// ------------------------------------------------ 
#define EP_F900_P_APR_BASE      (BLOCK_SIZE * 13U)     
#define EP_F900_S_D_PTR         EP_F900_APR_BASE +0 
#define EP_F900_S_LEVEL         EP_F900_APR_BASE +2 
#define EP_F900_T_D_PTR         EP_F900_APR_BASE +4 
#define EP_F900_T_LEVEL         EP_F900_APR_BASE +6 
#define EP_F900_V_D_PTR         EP_F900_APR_BASE +8 
#define EP_F900_V_LEVEL         EP_F900_APR_BASE +10 
#define EP_F900_I_D_PTR         EP_F900_APR_BASE +12 
#define EP_F900_I_LEVEL         EP_F900_APR_BASE +14 
// ------------------------------------------------  
//                  
#define EP_F510_LEVEL_TBL       (BLOCK_SIZE * 20U)   
#define EP_F560_LEVEL_TBL       (BLOCK_SIZE * 22U)   
#define EP_F585_LEVEL_TBL       (BLOCK_SIZE * 24U)   
#define EP_F640_LEVEL_TBL       (BLOCK_SIZE * 26U)   
#define EP_F700_LEVEL_TBL       (BLOCK_SIZE * 28U)   
#define EP_F800_LEVEL_TBL       (BLOCK_SIZE * 30U)   
#define EP_F900_LEVEL_TBL       (BLOCK_SIZE * 32U)   
// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
// 
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//

uint8_t eeprom_data_load(void);
void eeprom_data_save(void);
void apr_data_load(uint8_t u8Filter, uint16_t u16Pulse_Type,uint8_t *pDurPtr,uint16_t *pLevel) ;
void apr_data_save(uint8_t u8Filter, uint16_t u16Pulse_Type,uint8_t *pDurPtr,uint16_t *pLevel)  ;
void temp_sv_eeprom_data_save(void);
void st_temp_mfr_save_eeprom(void);
void counter_eeprom_data_save(void);
void apr_flag_eeprom_save(FILTER_e Filter_Select);
void T_counter_eeprom_data_save(void);
void L_counter_eeprom_data_save(void);
void F_counter_eeprom_data_save(uint8_t u8Select);
void eeprom_serial_save(void);
void eeprom_serial_load(void);
void level_data_mfr_save_eeprom(void) ;
void level_data_save_eeprom(uint8_t u8Select,const uint16_t * pSrcBuff);
bool level_data_load_eeprom(uint8_t i_select,uint16_t * const pDesBuff);
void sys_option_eeprom_save(void);
void Filter_eeprom_data_save(FILTER_e Filter_Select,uint16_t u16Data);
uint16_t Filter_eeprom_data_load(FILTER_e Filter_Select);  

#endif 
#endif 
/* APR_EEPROM.h End Of File !! Well Done */
/* --------------------------------------------------------------------------
 * [ PROJECT   ]   
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  DWIN_LCD.h
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
#ifndef COMMON_HW_INCLUDE_DWIN_LCD_H_
#define COMMON_HW_INCLUDE_DWIN_LCD_H_
/* Includes */
#include "hw_def.h"
 
 
 
// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 
#define IPL_VER             100U
// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
//
typedef enum _Screen_No
{
  LOAD_SCREEN_NO          = 0U,
  SYSTEM_CHECK_SCREEN_NO  = 6U,
  SELECT_SCREEN_NO        = 8U,
  MAIN_SCREEN_NO          = 10U,
  KEYPAD_SCREEN_NO        = 30U,
  SETTING_SCREEN_NO       = 33U,
  CALI_SCREEN_NO          = 35U,
  INFORMATION_SCREEN_NO   = 40U
} SCR_NO_e ; 
// --------------------------------------------------------------------------- 
extern uint16_t PLC_DATA[100];

#define CURRENT_SCREEN          PLC_DATA[0U]
#define DURATION_VALUE          PLC_DATA[1U]
#define FLUENCE_VALUE           PLC_DATA[2U]
#define FILTER_VALUE            PLC_DATA[3U]
#define ST_TEMP_VALUE           PLC_DATA[4U]
#define DT_TEMP_VALUE           PLC_DATA[5U]
#define CURRENT_COUNT           PLC_DATA[6U] //  
#define CURRENT_COUNT_HI        PLC_DATA[6U] //   
#define CURRENT_COUNT_LO        PLC_DATA[7U] //
#define ST_TEMP_SV_MIN          PLC_DATA[8U]
#define ST_TEMP_SV_MAX          PLC_DATA[9U] 
#define ST_TEMP_OFFSET          PLC_DATA[10U] 
//
#define TOTAL_COUNT             PLC_DATA[11U]  
#define TOTAL_COUNT_HI          PLC_DATA[11U] 
#define TOTAL_COUNT_LO          PLC_DATA[12U] 
#define LAMP_COUNT              PLC_DATA[13U]
#define LAMP_COUNT_HI           PLC_DATA[13U]
#define LAMP_COUNT_LO           PLC_DATA[14U]
//
#define SERIAL_YY               PLC_DATA[0x15U]
#define SERIAL_MM               PLC_DATA[0x16U]
#define SERIAL_DD               PLC_DATA[0x17U]
#define SERIAL_NO               PLC_DATA[0x18U]
//
#define PASSWORD                PLC_DATA[30U] //
//
#define CAL_BASE_ADD            32U
#define CAL_DATA_1              PLC_DATA[CAL_BASE_ADD+0U] 
#define CAL_DATA_2              PLC_DATA[CAL_BASE_ADD+1U]
#define CAL_DATA_3              PLC_DATA[CAL_BASE_ADD+2U]
#define CAL_DATA_4              PLC_DATA[CAL_BASE_ADD+3U]
#define CAL_DATA_5              PLC_DATA[CAL_BASE_ADD+4U]
#define CAL_DATA_6              PLC_DATA[CAL_BASE_ADD+5U] 
#define CAL_DATA_7              PLC_DATA[CAL_BASE_ADD+6U] 
#define CAL_DATA_8              PLC_DATA[CAL_BASE_ADD+7U]
#define CAL_DATA_9              PLC_DATA[CAL_BASE_ADD+8U]
#define CAL_DATA_10             PLC_DATA[CAL_BASE_ADD+9U]
#define CAL_DATA_11             PLC_DATA[CAL_BASE_ADD+10U]
#define CAL_DATA_12             PLC_DATA[CAL_BASE_ADD+11U] 
#define CAL_DATA_13             PLC_DATA[CAL_BASE_ADD+12U] 
#define CAL_DATA_14             PLC_DATA[CAL_BASE_ADD+13U] 
#define CAL_DATA_15             PLC_DATA[CAL_BASE_ADD+14U] 
#define CAL_DATA_16             PLC_DATA[CAL_BASE_ADD+15U] 
#define CAL_DATA_17             PLC_DATA[CAL_BASE_ADD+16U] 
#define CAL_DATA_18             PLC_DATA[CAL_BASE_ADD+17U] 
#define CAL_DATA_19             PLC_DATA[CAL_BASE_ADD+18U] 
#define CAL_DATA_20             PLC_DATA[CAL_BASE_ADD+19U] 
#define CAL_DATA_21             PLC_DATA[CAL_BASE_ADD+20U]
#define CAL_DATA_22             PLC_DATA[CAL_BASE_ADD+21U]
#define CAL_DATA_23             PLC_DATA[CAL_BASE_ADD+22U]
#define CAL_DATA_24             PLC_DATA[CAL_BASE_ADD+23U]
#define CAL_DATA_25             PLC_DATA[CAL_BASE_ADD+24U]
#define CAL_DATA_26             PLC_DATA[CAL_BASE_ADD+25U]
#define CAL_DATA_27             PLC_DATA[CAL_BASE_ADD+26U]
#define CAL_DATA_28             PLC_DATA[CAL_BASE_ADD+27U]
#define CAL_DATA_29             PLC_DATA[CAL_BASE_ADD+28U]
#define CAL_DATA_30             PLC_DATA[CAL_BASE_ADD+29U]
#define CAL_DATA_31             PLC_DATA[CAL_BASE_ADD+30U]
#define CAL_DATA_32             PLC_DATA[CAL_BASE_ADD+31U]
#define CAL_END_ADD             CAL_BASE_ADD+31U
//
#define VER                     PLC_DATA[0x32] //
//
#define F510_COUNT_HI           PLC_DATA[0x40]
#define F510_COUNT_LO           PLC_DATA[0x41]
#define F560_COUNT_HI           PLC_DATA[0x42]
#define F560_COUNT_LO           PLC_DATA[0x43]
#define F585_COUNT_HI           PLC_DATA[0x44]
#define F585_COUNT_LO           PLC_DATA[0x45]
#define F640_COUNT_HI           PLC_DATA[0x46]
#define F640_COUNT_LO           PLC_DATA[0x47]
#define F700_COUNT_HI           PLC_DATA[0x48]
#define F700_COUNT_LO           PLC_DATA[0x49] // 73
#define F800_COUNT_HI           PLC_DATA[0x4A]
#define F800_COUNT_LO           PLC_DATA[0x4B] // 75
#define F900_COUNT_HI           PLC_DATA[0x4C]
#define F900_COUNT_LO           PLC_DATA[0x4D] // 77

#define KEY_BUFF1               PLC_DATA[90U]  // 100 -- 0x64
#define KEY_BUFF2               PLC_DATA[91U]  // 101 -- 0x65
#define KEY_BUFF3               PLC_DATA[92U]  // 102 -- 0x66
#define KEY_BUFF4               PLC_DATA[93U]  // 103 -- 0x67
#define KEY_BUFF5               PLC_DATA[94U]  // 104 -- 0x68 

#define CURRENT_SCREEN_ADD          0
#define DURATION_VALUE_ADD          1
#define FILTER_VALUE_ADD            2
#define FLUENCE_VALUE_ADD           3
#define ST_TEMP_VALUE_ADD           4
#define DT_TEMP_VALUE_ADD           5
#define CURRENT_COUNT_ADD           6  
#define CURRENT_COUNT_HI_ADD        6    
#define CURRENT_COUNT_LO_ADD        7  
#define ST_TEMP_SV_MIN_ADD          8
#define ST_TEMP_SV_MAX_ADD          9 
#define TOTAL_COUNT_ADD             11
#define LAMP_COUNT_ADD              13
#define F510_COUNT_ADD              0x40U   // 64
#define F560_COUNT_ADD              0x42U   // 66
#define F585_COUNT_ADD              0x44U   // 68
#define F640_COUNT_ADD              0x46U   // 70
#define F700_COUNT_ADD              0x48U   // 72
#define F800_COUNT_ADD              0x4AU   // 74
#define F900_COUNT_ADD              0x4CU   // 76
// ---------------------------------------------------------------------------
// 
// --------------------------------------------------------------------------- 
//
extern volatile uint8_t current_screen ;
//
extern SYSTEM_FLAG Display_flag ; 
#define Display_flag_valus                  Display_flag.valus
//
#define Laser_disp_flag_on                  Display_flag.bits.bit0 = 1
#define Laser_disp_flag_off                 Display_flag.bits.bit0 = 0
#define Is_Laser_disp_flag                  Display_flag.bits.bit0 == 1
#define Is_Not_Laser_disp_flag              Display_flag.bits.bit0 == 0
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//
void dwin_lcd_init(void);
 
void set_value(uint16_t u16Addr, uint16_t u16Value)  ;
void dwin_set_value(uint8_t u8Addr)  ;
void dwin_vp_value_read(uint16_t u16Addr,uint8_t u8Count);
//
void dwin_word2_write(uint8_t u8Addr) ;
void dwin_word3_write(uint8_t u8Addr) ;
void dwin_word4_write(uint8_t u8Addr) ;
//
void dwin_to_st_setting(void);
void dwin_cal_change_text_color(uint8_t u8Addr);
void dwin_information_display(void);
void dwin_key_pad(uint8_t *pCurrent_screen);
void dwin_change_text_color(uint8_t u8Add);
uint16_t dwin_pass_key_pad(uint8_t u8Select);
void Basic_Graphic(uint16_t g_vp,uint16_t X1,uint16_t Y1,uint16_t X2,uint16_t Y2,uint16_t screen_no);
void graphic_overwrite(uint16_t graphicID,uint16_t leftup_x,uint16_t leftup_y,uint16_t rightdown_x,uint16_t rightdown_y,uint16_t screen_no);
void control_data_display(void);
void head_msg_display(uint8_t u8Select);
//
void pulse_type_load(uint8_t i_new) ;
void select_filter_display(FILTER_e i_new);
void selected_filter_display(FILTER_e i_old ,FILTER_e i_new );

#endif /* DWIN_LCD.h End Of File !! Well Done */
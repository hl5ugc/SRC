/* --------------------------------------------------------------------------
 * [ PROJECT   ]   
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  AP_Flag.h
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
#ifndef SRC_AP_AP_Flag_H_
#define SRC_APAP_Flag_H_
/* Includes */
#include "def.h"
 
 
 
// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 

// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
//
//
extern SYSTEM_FLAG system_flag ;
//extern SYSTEM_FLAG delay_flag ;
extern SYSTEM_FLAG buzzer_flag ;
//extern SYSTEM_FLAG apr_in_flag ; 
//extern SYSTEM_FLAG Int6_flag ; 
extern SYSTEM_FLAG warning_flag ; 
extern SYSTEM_FLAG key_in_flag ;
extern SYSTEM_FLAG msg_flag ;
 
//
// ---------------------------------------------------------------------------
//  Flag Macro Define .
// ---------------------------------------------------------------------------
#define system_flag_valus                   system_flag.valus
//
#define system_interlock_flag_on            system_flag.bits.bit0 = 1
#define system_interlock_flag_off           system_flag.bits.bit0 = 0
#define Is_system_interlock_flag            system_flag.bits.bit0 == 1
#define Is_Not_system_interlock_flag        system_flag.bits.bit0 == 0
//
#define system_run_flag_on                  system_flag.bits.bit1 = 1
#define system_run_flag_off                 system_flag.bits.bit1 = 0
#define Is_system_run_flag                  system_flag.bits.bit1 == 1
#define Is_Not_system_run_flag              system_flag.bits.bit1 == 0
//
#define adc_end_flag_on                     system_flag.bits.bit2 = 1
#define adc_end_flag_off                    system_flag.bits.bit2 = 0
#define Is_adc_end_flag                     system_flag.bits.bit2 == 1
#define Is_Not_adc_end_flag                 system_flag.bits.bit2 == 0
//
#define water_flow_on_flag_on               system_flag.bits.bit3 = 1
#define water_flow_on_flag_off              system_flag.bits.bit3 = 0
#define Is_water_flow_on_flag               system_flag.bits.bit3 == 1
#define Is_Not_water_flow_on_flag           system_flag.bits.bit3 == 0
//
#define water_flow_check_flag_on            system_flag.bits.bit4 = 1
#define water_flow_check_flag_off           system_flag.bits.bit4 = 0
#define Is_water_flow_check_flag            system_flag.bits.bit4 == 1
#define Is_Not_water_flow_check_flag        system_flag.bits.bit4 == 0
//
#define running_flag_on                     system_flag.bits.bit5 = 1
#define running_flag_off                    system_flag.bits.bit5 = 0
#define Is_running_flag                     system_flag.bits.bit5 == 1
#define Is_Not_running_flag                 system_flag.bits.bit5 == 0
//
#define run_count_flag_on                   system_flag.bits.bit6 = 1
#define run_count_flag_off                  system_flag.bits.bit6 = 0
#define Is_run_count_flag                   system_flag.bits.bit6 == 1
#define Is_Not_run_count_flag               system_flag.bits.bit6 == 0
//
#define count_save_flag_on                  system_flag.bits.bit7 = 1
#define count_save_flag_off                 system_flag.bits.bit7 = 0
#define Is_count_save_flag                  system_flag.bits.bit7 == 1
#define Is_Not_count_save_flag              system_flag.bits.bit7 == 0
//
// --------------------------------------------------------------------
/*
#define Delay_10_flag_on                    delay_flag.bits.bit0 = 1
#define Delay_10_flag_off                   delay_flag.bits.bit0 = 0
#define Is_Delay_10_flag                    delay_flag.bits.bit0 == 1
#define Is_Not_Delay_10_flag                delay_flag.bits.bit0 == 0
//
#define Delay_30_flag_on                    delay_flag.bits.bit1 = 1
#define Delay_30_flag_off                   delay_flag.bits.bit1 = 0
#define Is_Delay_30_flag                    delay_flag.bits.bit1 == 1
#define Is_Not_Delay_30_flag                delay_flag.bits.bit1 == 0
//
#define Delay_50_flag_on                    delay_flag.bits.bit2 = 1
#define Delay_50_flag_off                   delay_flag.bits.bit2 = 0
#define Is_Delay_50_flag                    delay_flag.bits.bit2 == 1
#define Is_Not_Delay_50_flag                delay_flag.bits.bit2 == 0
//
#define Delay_100_flag_on                   delay_flag.bits.bit3 = 1
#define Delay_100_flag_off                  delay_flag.bits.bit3 = 0
#define Is_Delay_100_flag                   delay_flag.bits.bit3 == 1
#define Is_Not_Delay_100_flag               delay_flag.bits.bit3 == 0
//
#define Delay_200_flag_on                   delay_flag.bits.bit4 = 1
#define Delay_200_flag_off                  delay_flag.bits.bit4 = 0
#define Is_Delay_200_flag                   delay_flag.bits.bit4 == 1
#define Is_Not_Delay_200_flag               delay_flag.bits.bit4 == 0
//
#define Delay_250_flag_on                   delay_flag.bits.bit5 = 1
#define Delay_250_flag_off                  delay_flag.bits.bit5 = 0
#define Is_Delay_250_flag                   delay_flag.bits.bit5 == 1
#define Is_Not_Delay_250_flag               delay_flag.bits.bit5 == 0
//
#define Delay_300_flag_on                   delay_flag.bits.bit6 = 1
#define Delay_300_flag_off                  delay_flag.bits.bit6 = 0
#define Is_Delay_300_flag                   delay_flag.bits.bit6 == 1
#define Is_Not_Delay_300_flag               delay_flag.bits.bit6 == 0
//
#define Delay_500_flag_on                   delay_flag.bits.bit7 = 1
#define Delay_500_flag_off                  delay_flag.bits.bit7 = 0
#define Is_Delay_500_flag                   delay_flag.bits.bit7 == 1
#define Is_Not_Delay_500_flag               delay_flag.bits.bit7 == 0
*/
// --------------------------------------------------------------------
//
#define op_control_flag_on                  buzzer_flag.bits.bit0 = 1
#define op_control_flag_off                 buzzer_flag.bits.bit0 = 0
#define Is_op_control_flag                  buzzer_flag.bits.bit0 == 1
#define Is_Not_op_control_flag              buzzer_flag.bits.bit0 == 0
//
#define buzzer_mask_flag_on                 buzzer_flag.bits.bit1 = 1
#define buzzer_mask_flag_off                buzzer_flag.bits.bit1 = 0
#define Is_buzzer_mask_flag                 buzzer_flag.bits.bit1 == 1
#define Is_Not_buzzer_mask_flag             buzzer_flag.bits.bit1 == 0
//
#define buzzer_on_flag_on                   buzzer_flag.bits.bit2 = 1
#define buzzer_on_flag_off                  buzzer_flag.bits.bit2 = 0
#define Is_buzzer_on_flag                   buzzer_flag.bits.bit2 == 1
#define Is_Not_buzzer_on_flag               buzzer_flag.bits.bit2 == 0
//
#define Cool_off_flag_on                    buzzer_flag.bits.bit3 = 1
#define Cool_off_flag_off                   buzzer_flag.bits.bit3 = 0
#define Is_Cool_off_flag                    buzzer_flag.bits.bit3 == 1
#define Is_Not_Cool_off_flag                buzzer_flag.bits.bit3 == 0
//
// ---------------------------------------------------------------------------
//
#define key_in_flag_valus                       key_in_flag.valus
//
#define run_flag_on                             key_in_flag.bits.bit0 = 1
#define run_flag_off                            key_in_flag.bits.bit0 = 0
#define Is_run_flag                             key_in_flag.bits.bit0 == 1
#define Is_Not_run_flag                         key_in_flag.bits.bit0 == 0
//
// ---------------------------------------------------------------------------
#define warning_flag_valus                      warning_flag.valus
//
#define w_water_flow_flag_on                    warning_flag.bits.bit0 = 1
#define w_water_flow_flag_off                   warning_flag.bits.bit0 = 0
#define Is_w_water_flow_flag                    warning_flag.bits.bit0 == 1
#define Is_Not_w_water_flow_flag                warning_flag.bits.bit0 == 0
//
#define w_cool_temp_flag_on                     warning_flag.bits.bit1 = 1
#define w_cool_temp_flag_off                    warning_flag.bits.bit1 = 0
#define Is_w_cool_temp_flag                     warning_flag.bits.bit1 == 1
#define Is_Not_w_cool_temp_flag                 warning_flag.bits.bit1 == 0
//
#define w_w_flow_flag_on                        warning_flag.bits.bit2 = 1
#define w_w_flow_flag_off                       warning_flag.bits.bit2 = 0
#define Is_w_w_flow_flag                        warning_flag.bits.bit2 == 1
#define Is_Not_w_w_flow_flag                    warning_flag.bits.bit2 == 0
//
#define w_interlock_flag_on                     warning_flag.bits.bit3 = 1
#define w_interlock_flag_off                    warning_flag.bits.bit3 = 0
#define Is_w_interlock_flag                     warning_flag.bits.bit3 == 1
#define Is_Not_w_interlock_flag                 warning_flag.bits.bit3 == 0
//
#define w_st_temp_flag_on                       warning_flag.bits.bit4 = 1
#define w_st_temp_flag_off                      warning_flag.bits.bit4 = 0
#define Is_w_st_temp_flag                       warning_flag.bits.bit4 == 1
#define Is_Not_w_st_temp_flag                   warning_flag.bits.bit4 == 0 
//
#define w_IPL_power_flag_on                     warning_flag.bits.bit5 = 1
#define w_IPL_power_flag_off                    warning_flag.bits.bit5 = 0
#define Is_w_IPL_power_flag                     warning_flag.bits.bit5 == 1
#define Is_Not_w_IPL_power_flag                 warning_flag.bits.bit5 == 0
//
#define w_filter_flag_on                        warning_flag.bits.bit6 = 1  
#define w_filter_flag_off                       warning_flag.bits.bit6 = 0
#define Is_w_filter_flag                        warning_flag.bits.bit6 == 1
#define Is_Not_w_filter_flag                    warning_flag.bits.bit6 == 0
//
#define w_hd_ok_flag_on                         warning_flag.bits.bit7 = 1
#define w_hd_ok_flag_off                        warning_flag.bits.bit7 = 0
#define Is_w_hd_ok_flag                         warning_flag.bits.bit7 == 1
#define Is_Not_w_hd_ok_flag                     warning_flag.bits.bit7 == 0
//
// ----------------------------------------------------------------------------
/*
#define apr_flag_value                          apr_in_flag.valus
#define apr_flag_value_clear                    apr_in_flag.valus = 0x00 
#define apr_forehead_set_flag_on                apr_in_flag.bits.bit0 = 1
#define apr_forehead_set_flag_off               apr_in_flag.bits.bit0 = 0
#define Is_apr_forehead_set_flag                apr_in_flag.bits.bit0 == 1
#define Is_Not_apr_forehead_set_flag            apr_in_flag.bits.bit0 == 0

#define apr_arm_set_flag_on                     apr_in_flag.bits.bit1 = 1
#define apr_arm_set_flag_off                    apr_in_flag.bits.bit1 = 0
#define Is_apr_arm_set_flag                     apr_in_flag.bits.bit1 == 1
#define Is_Not_apr_arm_set_flag                 apr_in_flag.bits.bit1 == 0

#define apr_axilla_set_flag_on                  apr_in_flag.bits.bit2 = 1
#define apr_axilla_set_flag_off                 apr_in_flag.bits.bit2 = 0
#define Is_apr_axilla_set_flag                  apr_in_flag.bits.bit2 == 1
#define Is_Not_apr_axilla_set_flag              apr_in_flag.bits.bit2 == 0

#define apr_abdomen_set_flag_on                 apr_in_flag.bits.bit3 = 1
#define apr_abdomen_set_flag_off                apr_in_flag.bits.bit3 = 0
#define Is_apr_abdomen_set_flag                 apr_in_flag.bits.bit3 == 1
#define Is_Not_abdomen_arm_set_flag             apr_in_flag.bits.bit3 == 0

#define apr_vline_set_flag_on                   apr_in_flag.bits.bit4 = 1
#define apr_vline_set_flag_off                  apr_in_flag.bits.bit4 = 0
#define Is_apr_vline_set_flag                   apr_in_flag.bits.bit4 == 1
#define Is_Not_apr_vline_set_flag               apr_in_flag.bits.bit4 == 0

#define apr_leg_set_flag_on                     apr_in_flag.bits.bit5 = 1
#define apr_leg_set_flag_off                    apr_in_flag.bits.bit5 = 0
#define Is_apr_leg_set_flag                     apr_in_flag.bits.bit5 == 1
#define Is_Not_apr_leg_set_flag                 apr_in_flag.bits.bit5 == 0

#define apr_beard_set_flag_on                   apr_in_flag.bits.bit6 = 1
#define apr_beard_set_flag_off                  apr_in_flag.bits.bit6 = 0
#define Is_apr_beard_set_flag                   apr_in_flag.bits.bit6 == 1
#define Is_Not_apr_beard_set_flag               apr_in_flag.bits.bit6 == 0

#define apr_fhr_set_flag_on                     apr_in_flag.bits.bit7 = 1
#define apr_fhr_set_flag_off                    apr_in_flag.bits.bit7 = 0
#define Is_apr_fhr_set_flag                     apr_in_flag.bits.bit7 == 1
#define Is_Not_apr_fhr_set_flag                 apr_in_flag.bits.bit7 == 0
*/
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
//
#define msg_flag_valus                          msg_flag.valus
//
#define Temp_er_msg_on_flag_on                  msg_flag.bits.bit0 = 1
#define Temp_er_msg_on_flag_off                 msg_flag.bits.bit0 = 0
#define Is_Temp_er_msg_on_flag                  msg_flag.bits.bit0 == 1
#define Is_Not_Temp_er_msg_on_flag              msg_flag.bits.bit0 == 0
//
#define Temp_er_msg_off_flag_on                 msg_flag.bits.bit1 = 1
#define Temp_er_msg_off_flag_off                msg_flag.bits.bit1 = 0
#define Is_Temp_er_msg_off_flag                 msg_flag.bits.bit1 == 1
#define Is_Not_Temp_er_msg_off_flag             msg_flag.bits.bit1 == 0
//

//
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//
 
#endif 
/* ADC.h End Of File !! Well Done */
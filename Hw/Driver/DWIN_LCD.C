/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ] DWIN_LCD.c
 * [ Version   ]  1.0
 * [ Created   ]
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
 * Hagseong Kang  2024-06-12    First release of this file
 * --------------------------------------------------------------------------
 * Additional Notes:
 * **************************************************************************
 */
 /**
 * @brief
 * @param
 * @return
 */

#pragma used+
/* Define Includes */
#include "DWIN_LCD.h"
#include "HMI_SIO.h"
#include "DataConvert.H"
#include "Word.H"
// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
//  IPL Define Macros .
// ---------------------------------------------------------------------------
// 
 
// ---------------------------------------------------------------------------
//  Define Constants.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
// Define typedef.
// --------------------------------------------------------------------------- 
// 
 
// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
static uint8_t to_st_setting[6]        = {0XF5, 0x04, 0x80, 0x03, 0x00, 41U};
static uint8_t count_number_setting[6] = {0XF5, 0x04, 0x80, 0x03, 0x00, 42U};
static uint8_t write_serial[17]        = {0XF5, 0x0F, 0x82, 0x06, 0x20, 0x20, 0x4C, 0x4D, 0x30, 0x30, 
                                          0x30, 0x30, 0x30, 0x30, 0x2D, 0x30, 0x30};

static uint8_t send_num[9] = {0xF5, 0x07, 0x82, 0x07, 0x40, 0x20, 0x20, 0x20, 0x20};
static uint8_t new_password[18] = {0XF5, 0x0f, 0x82, 0x06, 0xA0,' ','N','E','W',' ','P','A','S','S','W','O','R','D'};
static uint8_t cv_password[18]  = {0XF5, 0x0f, 0x82, 0x06, 0xA0 ,' ',' ',' ','P','A','S','S','W','O','R','D',' ',' '};
static uint8_t en_password[18]  = {0XF5, 0x10, 0x82, 0x06, 0xA0 ,'E','n','g','i','n','e','e','r',' ','M','o','d','e'};
//
const uint16_t frq_dura_limit[20] = { 100,100,100,100,100, // 1 ~ 5Hz
                                       50, 50, 50, 50, 50, // 6 ~ 10Hz
                                       45, 41, 38, 35, 33, // 11 ~ 15Hz
                                       31, 29, 27, 26, 25 }; // 16 ~ 20Hz  

SYSTEM_FLAG Display_flag ;   

uint16_t PLC_DATA[100];

//static volatile uint8_t u8Selected_index = 0U;
static volatile uint8_t mask_number[4] = {0x00,};
static volatile uint8_t u8In_ptr = 0U ;
static uint8_t button = 0U ; 
static uint8_t u16Prev_selected = 0U ;
// ---------------------------------------------------------------------------
//  Define Varibales Macro.
// ---------------------------------------------------------------------------
 
// ---------------------------------------------------------------------------
// Define private function definitions.
// ---------------------------------------------------------------------------
//
static void key_pad_data_clear(void);
static void shift_num(uint8_t u8Value);
static void shift_num_mask(uint8_t u8Value);;
static void wait_key_off3(void); 
static void Flu_Duration_limit(void);
static void Dur_FREQUENCE_limit(void);
static void FRE_Duration_limit(void);
// ---------------------------------------------------------------------------
// Define Public function definitions.
// ---------------------------------------------------------------------------
//
void dwin_lcd_init(void)
{
  uint8_t u8i = 0U ;
  //
  for(u8i=0U; u8i<100U; u8i++)
  {
    PLC_DATA[u8i] = 0x00U ;
  }  
}
//
void dwin_to_st_setting(void)
{
  send_HMI_bytes((const uint8_t *)&to_st_setting[0]);  
}
//
void dwin_cal_change_text_color(uint8_t u8Addr)
{
  uint8_t to_orange[7] = {0xF5, 0x05, 0x82, 0x50, 0x03, 0xFC, 0x00};
  uint8_t to_blue[7]   = {0xF5, 0x05, 0x82, 0x50, 0x03, 0x00, 0x1F}; 
  
  const uint8_t select_level_SP_hi[32] = 
                { 0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60, // 8
                  0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60, // 16
                  0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61, // 24
                  0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61};// 32
   const uint8_t select_level_SP_lo[32] = 
                { 0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,
                  0x80,0x90,0xA0,0xB0,0xC0,0xD0,0xE0,0xF0, 
                  0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,
                  0x80,0x90,0xA0,0xB0,0xC0,0xD0,0xE0,0xF0,}; 
                                                              
  to_orange[3] = highByte(u16Prev_selected); 
  to_orange[4] =  lowByte(u16Prev_selected) | 0x03U;
  send_HMI_bytes((const uint8_t *)&to_orange[0]);  
  // 
  to_blue[3] = select_level_SP_hi[u8Addr-1U] ;
  to_blue[4] = select_level_SP_lo[u8Addr-1U] | 0x03U; 
  send_HMI_bytes((const uint8_t *)&to_blue[0]);   
  //               
  u16Prev_selected = cvtword(to_blue[3] ,to_blue[4]);
}
void dwin_information_display(void)
{
    write_serial[8] =  (uint8_t)(SERIAL_YY / 10) | 0x30U ;
    write_serial[9] =  (uint8_t)(SERIAL_YY % 10) | 0x30U ;
    write_serial[10] = (uint8_t)(SERIAL_MM / 10) | 0x30U ;
    write_serial[11] = (uint8_t)(SERIAL_MM % 10) | 0x30U ;
    write_serial[12] = (uint8_t)(SERIAL_DD / 10) | 0x30U ;
    write_serial[13] = (uint8_t)(SERIAL_DD % 10) | 0x30U ;
    write_serial[15] = (uint8_t)(SERIAL_NO / 10) | 0x30U ;
    write_serial[16] = (uint8_t)(SERIAL_NO % 10) | 0x30U ;
    send_HMI_bytes((const uint8_t *)&write_serial[0]);  

    dwin_word4_write(TOTAL_COUNT_ADD) ; //  
    dwin_word4_write(LAMP_COUNT_ADD) ;  //
    dwin_word4_write(TOTAL_COUNT_ADD) ; //  
    dwin_word4_write(LAMP_COUNT_ADD) ;  //      
    dwin_word4_write(F510_COUNT_ADD) ;  //   
    dwin_word4_write(F560_COUNT_ADD) ;  //  
    dwin_word4_write(F585_COUNT_ADD) ;  //  
    dwin_word4_write(F640_COUNT_ADD) ;  //  
    dwin_word4_write(F700_COUNT_ADD) ;  //  
    dwin_word4_write(F800_COUNT_ADD) ;  // 
    dwin_word4_write(F900_COUNT_ADD) ;  // 

    set_value(0x32,IPL_VER);   

    send_set_screen(SCR_INFO) ;  // 

}
void dwin_change_text_color(uint8_t u8Add)
{
    uint8_t to_black[7] = {0xF5, 0x05, 0x82, 0x07, 0x03, 0x00, 0x00};
    uint8_t to_red[7]   = {0xF5, 0x05, 0x82, 0x07, 0x03, 0xF8, 0x00};
    //
    if(u8Add < 0x19U) {
        to_black[4] = 0x53U;
        send_HMI_bytes((const uint8_t *)&to_black[0]); 
        to_black[4] = 0x63U;
        send_HMI_bytes((const uint8_t *)&to_black[0]); 
        to_black[4] = 0x73U;
        send_HMI_bytes((const uint8_t *)&to_black[0]); 
        to_black[4] = 0x83U;
        send_HMI_bytes((const uint8_t *)&to_black[0]); 
    }
    else {
        to_black[4] = 0x93U;
        send_HMI_bytes((const uint8_t *)&to_black[0]); 
        to_black[4] = 0xA3U;
        send_HMI_bytes((const uint8_t *)&to_black[0]);    
    }
    //
    switch(u8Add)
    {
        case 0x15U:
                to_red[4] = 0x53;
                send_HMI_bytes((const uint8_t *)&to_red[0]); 
                break ;
        case 0x16U:
                to_red[4] = 0x63U;
                send_HMI_bytes((const uint8_t *)&to_red[0]); 
                break ;
        case 0x17U:
                to_red[4] = 0x73U;
                send_HMI_bytes((const uint8_t *)&to_red[0]); 
                break ;
        case 0x18U:
                to_red[4] = 0x83U;
                send_HMI_bytes((const uint8_t *)&to_red[0]); 
                break ;  
        case 0x19U:
                to_red[4] = 0xA3U;
                send_HMI_bytes((const uint8_t *)&to_red[0]); 
                break ; 
        case 0x1AU:
                to_red[4] = 0x93U;
                send_HMI_bytes((const uint8_t *)&to_red[0]); 
                to_red[4] = 0xA3U;
                send_HMI_bytes((const uint8_t *)&to_red[0]); 
                break ; 
    }
}
void dwin_key_pad(uint8_t *pCurrent_screen)
{
  uint8_t back_to_main[6] = {0xF5, 0x04, 0x80, 0x03, 0x00, 0x02};

  while(pCurrent_screen[0] == SCR_KEYPAD)
  {
    switch(KEY_BUFF3) 
    {
      case _DEF_BIT0: //  
          bitClear(KEY_BUFF3,0U) ;
          pCurrent_screen[0] = SCR_MAIN ;
          send_HMI_bytes((const uint8_t *)&back_to_main[0]); 
          break;
      case _DEF_BIT1: //  
          bitClear(KEY_BUFF3,1U) ;
          shift_num(0x31U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;
      case _DEF_BIT2: //  
          bitClear(KEY_BUFF3,2U) ;
          shift_num(0x32U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;
      case _DEF_BIT3: //  
          bitClear(KEY_BUFF3,3U) ;
          shift_num(0x33U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;
      case _DEF_BIT4: //  
          bitClear(KEY_BUFF3,4U) ;
          shift_num(0x34U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;
      case _DEF_BIT5: //  
          bitClear(KEY_BUFF3,5U) ;
          shift_num(0x35U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;
      case _DEF_BIT6: //  
          bitClear(KEY_BUFF3,6U) ;
          shift_num(0x36U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;
      case _DEF_BIT7: //  
          bitClear(KEY_BUFF3,7U) ;
          shift_num(0x37U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;
      case _DEF_BIT8: //  
          bitClear(KEY_BUFF3,8U) ;
          shift_num(0x38U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          wait_key_off3();
          break;
      case _DEF_BIT9: //  
          bitClear(KEY_BUFF3,0U) ;
          shift_num(0x39U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;
      case _DEF_BIT10: //  
          bitClear(KEY_BUFF3,10U) ;
          shift_num(0x30U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          wait_key_off3();
          break;

      case _DEF_BIT11: //  
          bitClear(KEY_BUFF3,11U) ;
          break;
      case _DEF_BIT12: //  enter
          bitClear(KEY_BUFF3,12U) ;
          PASSWORD  = (uint16_t)(send_num[5] - '0') * 1000U ;
          PASSWORD += (uint16_t)(send_num[6] - '0') * 100U ;
          PASSWORD += (uint16_t)(send_num[7] - '0') * 10U ;
          PASSWORD += (uint16_t)(send_num[8] - '0')  ;

          if(PASSWORD == 9706U)
          {
            send_num[5] = 0x20U ;
            send_num[6] = 0x20U ;
            send_num[7] = 0x20U ;
            send_num[8] = 0x20U ;
            send_HMI_bytes((const uint8_t *)&send_num[0]); 

            if(button == 1U)
            {
              send_HMI_bytes((const uint8_t *)&to_st_setting[0]); 
              pCurrent_screen[0] = SCR_ST_SETTING;
            }
            if(button == 2U) 
            {
              send_HMI_bytes((const uint8_t *)&count_number_setting[0]); 
              pCurrent_screen[0] = SCR_COUNT_SERIAL; 
            }
          }
          //PLC_DATA[4]에 비밀번호 값 쓰고 비교 후 다음화면
          break;    
      case _DEF_BIT13: //  
          bitClear(KEY_BUFF3,13U) ;
          send_num[5] = 0x20U ;
          send_num[6] = 0x20U ;
          send_num[7] = 0x20U ;
          send_num[8] = 0x20U ;
          send_HMI_bytes((const uint8_t *)&send_num[0]);
          break ;
      case _DEF_BIT14: //  
          bitClear(KEY_BUFF3,14U) ;
          break; 
      case _DEF_BIT15: //  
          bitClear(KEY_BUFF3,15U) ;
          break;
    } 
  }
}

/**
 * @brief Get Password input data
 * 
 * @param u8Select    keypad password title
 * @return uint16_t   keypad input data
 */
uint16_t dwin_pass_key_pad(uint8_t u8Select)
{
  uint16_t u16Ret = 0x00U ;
  bool bStatus = true ;
  // Password Title Display
  if(u8Select == 1U)      { send_HMI_bytes((const uint8_t *)&cv_password[0]); }  
  else if(u8Select == 2U) { send_HMI_bytes((const uint8_t *)&new_password[0]);}  
  else if(u8Select == 3U) { send_HMI_bytes((const uint8_t *)&en_password[0]); } 
  else                    { send_HMI_bytes((const uint8_t *)&cv_password[0]); }  
  //
  mask_number[0] = '0' ;  
  mask_number[1] = '0' ;
  mask_number[2] = '0' ;
  mask_number[3] = '0' ;  
  u8In_ptr = 0U ; 
  while(bStatus == true)
  {
    switch(KEY_BUFF4) 
    {
      case _DEF_BIT0: //  
          bitClear(KEY_BUFF4,0U) ;
          key_pad_data_clear();
          u16Ret = 0x00U ;
          bStatus = false ;
          break;
      case _DEF_BIT1: //  
          bitClear(KEY_BUFF4,1U) ;
          shift_num(0x31U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;
      case _DEF_BIT2: //  
          bitClear(KEY_BUFF4,2U) ;
          shift_num(0x32U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;
      case _DEF_BIT3: //  
          bitClear(KEY_BUFF4,3U) ;
          shift_num(0x33U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;
      case _DEF_BIT4: //  
          bitClear(KEY_BUFF4,4U) ;
          shift_num(0x34U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;
      case _DEF_BIT5: //  
          bitClear(KEY_BUFF4,5U) ;
          shift_num(0x35U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;
      case _DEF_BIT6: //  
          bitClear(KEY_BUFF4,6U) ;
          shift_num(0x36U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;
      case _DEF_BIT7: //  
          bitClear(KEY_BUFF4,7U) ;
          shift_num(0x37U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;
      case _DEF_BIT8: //  
          bitClear(KEY_BUFF4,8U) ;
          shift_num(0x38U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;
      case _DEF_BIT9: //  
          bitClear(KEY_BUFF4,0U) ;
          shift_num(0x39U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;
      case _DEF_BIT10: //  
          bitClear(KEY_BUFF4,10U) ;
          shift_num(0x30U);
          send_HMI_bytes((const uint8_t *)&send_num[0]); 
          break;

      case _DEF_BIT11: //  
          bitClear(KEY_BUFF4,11U) ;
          break;
      case _DEF_BIT12: //  Enter
          bitClear(KEY_BUFF4,12U) ;
          u16Ret  = (uint16_t)(send_num[0] - '0') * 1000U ;
          u16Ret += (uint16_t)(send_num[1] - '0') * 100U ;
          u16Ret += (uint16_t)(send_num[2] - '0') * 10U ;
          u16Ret += (uint16_t)(send_num[3] - '0')  ;
          key_pad_data_clear();   
          bStatus = false ;  
          break;    
      case _DEF_BIT13: //  //clear
          bitClear(KEY_BUFF4,13U) ;
          key_pad_data_clear();  
          break ;
      case _DEF_BIT14: //  
          bitClear(KEY_BUFF4,14U) ;
          break; 
      case _DEF_BIT15: //  
          bitClear(KEY_BUFF4,15U) ;
          key_pad_data_clear(); 
          u16Ret = 0x00U ;
          bStatus = false ;
          break;
    } 
  }
  //
  return (u16Ret) ;
}
/**
 * @brief Set word data to dwin lcd 
 * 
 * @param u16Addr     VP Memory Address
 * @param u16Value   VP Memory Read Counter
 */
void set_value(uint16_t u16Addr, uint16_t u16Value) 
{
  uint8_t msg[7] = {HMI_STX_LO, 0x05U, HMI_WRam_CMD, 0xAAU, 0xAAU, 0xBBU, 0xBBU};

  msg[3] = highByte(u16Addr); 
  msg[4] =  lowByte(u16Addr); 
  msg[5] = highByte(u16Value); 
  msg[6] =  lowByte(u16Value); 

  send_HMI_bytes((const uint8_t *)&msg[0]); 
}
void dwin_set_value(uint8_t u8Addr) 
{
  uint8_t msg[7] = {HMI_STX_LO, 0x05, HMI_WRam_CMD, 0xAA, 0xAA, 0xBB, 0xBB};

  msg[3] = 0x00U ;
  msg[4] = u8Addr ;
  msg[5] = highByte(PLC_DATA[u8Addr]); 
  msg[6] =  lowByte(PLC_DATA[u8Addr]); 

  send_HMI_bytes((const uint8_t *)&msg[0]); 
}
/**
 * @brief   Get Dwin Vp Value Memory Data Read
 * 
 * @param u16Addr   VP Memory Address
 * @param u8Count   VP Memory Read Counter
 */
void dwin_vp_value_read(uint16_t u16Addr,uint8_t u8Count)
{
  uint8_t msg[6] = {HMI_STX_LO, 0x04U, HMI_RRam_CMD, 0x00U, 0x00U,0x01U };

  msg[3] = highByte(u16Addr); 
  msg[4] =  lowByte(u16Addr); 
  msg[5] =  u8Count ;
  //
  send_HMI_bytes((const uint8_t *)&msg[0]); 
}
//
void dwin_word2_write(uint8_t u8Addr) 
{
  uint8_t msg[9] = {0x00U,};
  //
  msg[0] = HMI_STX_LO ;
  msg[1] = 0x07U ;
  msg[2] = HMI_WRam_CMD ;  
  msg[3] = 0x00U ;
  msg[4] = u8Addr ;
  msg[5] = highByte(PLC_DATA[u8Addr + 0]); 
  msg[6] =  lowByte(PLC_DATA[u8Addr + 0]); 
  msg[7] = highByte(PLC_DATA[u8Addr + 1]); 
  msg[8] =  lowByte(PLC_DATA[u8Addr + 1]); 
  //
  send_HMI_bytes((const uint8_t *)&msg[0]); 
  //
}
void dwin_word3_write(uint8_t u8Addr)  
{
  uint8_t msg[11] = {0x00U,};
  //
  msg[0] = HMI_STX_LO ;
  msg[1] = 9U ;
  msg[2] = HMI_WRam_CMD ;  
  msg[3] = 0x00U ;
  msg[4] = u8Addr ;
  msg[5] = highByte(PLC_DATA[u8Addr + 0]); 
  msg[6] =  lowByte(PLC_DATA[u8Addr + 0]); 
  msg[7] = highByte(PLC_DATA[u8Addr + 1]); 
  msg[8] =  lowByte(PLC_DATA[u8Addr + 1]); 
  msg[9] = highByte(PLC_DATA[u8Addr + 2]); 
  msg[10] = lowByte(PLC_DATA[u8Addr + 2]); 
  //
  send_HMI_bytes((const uint8_t *)&msg[0]); 
}
void dwin_word4_write(uint8_t u8Addr) 
{
  uint8_t msg[13] = {0x00U,};
  //
  msg[0] = HMI_STX_LO ;
  msg[1] = 11U ;
  msg[2] = HMI_WRam_CMD ;  
  msg[3] = 0x00U ;
  msg[4] = u8Addr ;
  msg[5] = highByte(PLC_DATA[u8Addr + 0]); 
  msg[6] =  lowByte(PLC_DATA[u8Addr + 0]); 
  msg[7] = highByte(PLC_DATA[u8Addr + 1]); 
  msg[8] =  lowByte(PLC_DATA[u8Addr + 1]); 
  msg[9] = highByte(PLC_DATA[u8Addr + 2]); 
  msg[10]=  lowByte(PLC_DATA[u8Addr + 2]); 
  msg[11]= highByte(PLC_DATA[u8Addr + 3]); 
  msg[12]=  lowByte(PLC_DATA[u8Addr + 3]);
  //
  send_HMI_bytes((const uint8_t *)&msg[0]); 
}
static void key_pad_data_clear(void)
{
  send_num[5] = 0x20U ;
  send_num[6] = 0x20U ;
  send_num[7] = 0x20U ;
  send_num[8] = 0x20U ;  
  send_HMI_bytes((const uint8_t *)&send_num[0]); 

  mask_number[0] = '0' ;  
  mask_number[1] = '0' ;
  mask_number[2] = '0' ;
  mask_number[3] = '0' ;   
  // 
  u8In_ptr = 0 ;
}
static void shift_num(uint8_t u8Value)
{
    mask_number[0] = mask_number[1] ; 
    mask_number[1] = mask_number[2] ;
    mask_number[2] = mask_number[3] ;
    mask_number[3] = u8Value  ; 
    //
    if(u8In_ptr == 0x00U) {
        send_num[5] = send_num[6] ;
        send_num[6] = send_num[7] ;
        send_num[7] = send_num[8] ;
        send_num[8] = u8Value;  
        u8In_ptr++ ;
    }
    else {
        send_num[5] = send_num[6] ;
        send_num[6] = send_num[7] ;
        send_num[7] = '*' ;
        send_num[8] = u8Value;
    
    }
}
 
void Basic_Graphic(uint16_t g_vp,uint16_t X1,uint16_t Y1,uint16_t X2,uint16_t Y2,uint16_t screen_no)
{
  uint8_t wmsg[23] = {0xF5U,0x17U,0x82U,0xEEU,0xEEU,0x00U,0x06U,0x00U,0x01U,0xFFU,0xFFU,
                      0xAAU,0xAAU,0xBBU,0xBBU,0xCCU,0xCCU,0xDDU,0xDDU,0xAAU,0xAAU,0xBBU,0xBBU};
  //
  wmsg[3]  = highByte(g_vp); 
  wmsg[4]  =  lowByte(g_vp); 
  wmsg[9]  = highByte(screen_no); 
  wmsg[10] =  lowByte(screen_no); 
  wmsg[11] = highByte(X1); 
  wmsg[12] =  lowByte(X1); 
  wmsg[13] = highByte(Y1); 
  wmsg[14] =  lowByte(Y1); 
  wmsg[15] = highByte(X2); 
  wmsg[16] =  lowByte(X2); 
  wmsg[17] = highByte(Y2); 
  wmsg[18] =  lowByte(Y2);  
  //
  wmsg[19] = highByte(X1); 
  wmsg[20] =  lowByte(X1); 
  wmsg[21] = highByte(Y1); 
  wmsg[22] =  lowByte(Y1); 
  //
  send_HMI_bytes((const uint8_t *)&wmsg[0]); 
}
void graphic_overwrite(uint16_t graphicID, uint16_t leftup_x,uint16_t leftup_y,
                       uint16_t rightdown_x,uint16_t rightdown_y,uint16_t screen_no)
{
  uint8_t wmsg[23] = {0xF5U,0x17U,0x82U,0xEEU,0xEEU,0x00U,0x06U,0x00U,0x01U,0xFFU,0xFFU,
                      0xAAU,0xAAU,0xBBU,0xBBU,0xCCU,0xCCU,0xDDU,0xDDU,0xAAU,0xAAU,0xBBU,0xBBU};
  //
  wmsg[3]  = highByte(graphicID); 
  wmsg[4]  =  lowByte(graphicID); 
  wmsg[9]  = highByte(screen_no); 
  wmsg[10] =  lowByte(screen_no); 
  wmsg[11] = highByte(leftup_x); 
  wmsg[12] =  lowByte(leftup_x); 
  wmsg[13] = highByte(leftup_y); 
  wmsg[14] =  lowByte(leftup_y); 
  wmsg[15] = highByte(rightdown_x); 
  wmsg[16] =  lowByte(rightdown_x); 
  wmsg[17] = highByte(rightdown_y); 
  wmsg[18] =  lowByte(rightdown_y);  
  //
  wmsg[19] = highByte(leftup_x); 
  wmsg[20] =  lowByte(leftup_x); 
  wmsg[21] = highByte(leftup_y); 
  wmsg[22] =  lowByte(leftup_y); 
  //
  send_HMI_bytes((const uint8_t *)&wmsg[0]); 
}
//
void control_data_display(void)
{
  uint8_t msg[11] = {0x00,} ;
  //
  msg[0] = HMI_STX_LO ;
  msg[1] = 11U ;
  msg[2] = HMI_WRam_CMD ;  
  msg[3] = 0x00U ;
  msg[4] = 0x01U ;
  msg[5] = highByte(PLC_DATA[0]); 
  msg[6] =  lowByte(PLC_DATA[0]); 
  msg[7] = highByte(PLC_DATA[1]); 
  msg[8] =  lowByte(PLC_DATA[1]); 
  msg[9] = highByte(PLC_DATA[2]); 
  msg[10]=  lowByte(PLC_DATA[2]); 
  //
  send_HMI_bytes((const uint8_t *)&msg[0]); 
}
void head_msg_display(uint8_t u8Select)
{
  // VP 0x0610 
  // x:y = 200: 9 = 0x00C8,0x0009  , 620:99=0x02C6:0x0063
  //                     
  uint8_t w_msg[23] = {0xF5U,0x17U,0x82U,0x06U,0x10U,0x00U,0x06U,0x00U,0x01U,0x00U,
                       0xFFU,0x00U,0xC8U,0x00U,0x09U,0x02U,0x6CU,0x00U,0x63U,0x00U,
                       0xC8U,0x00U,0x09U};
  switch(u8Select)
  {
    case 0x00U :  // Laser Out Display off
                  if(Is_Laser_disp_flag) {
                    w_msg[10] = 2U ;   // Screen number 
                    send_HMI_bytes((const uint8_t *)&w_msg[0]);   
                    Laser_disp_flag_off ;
                  }
                  break ;
    case 0x01U :  // Laser Out Display on
                  if(Is_Not_Laser_disp_flag) {
                    w_msg[10] = 33U ;   // Screen number 
                    send_HMI_bytes((const uint8_t *)&w_msg[0]);   
                    Laser_disp_flag_on;
                  }
                  break ;
    case 0x02U:   //  Flow err Display on
                  w_msg[10] = 50U  ;               // Screen number 
                  send_HMI_bytes((const uint8_t *)&w_msg[0]);          
                  break ; 
    case 0x03U:   //  DT sensor err Display on
                  w_msg[10] = 51U  ;               
                  send_HMI_bytes((const uint8_t *)&w_msg[0]);          
                  break ;    
    case 0x04U:   //  ST sensor err Display on
                  w_msg[10] = 52U  ;              
                  send_HMI_bytes((const uint8_t *)&w_msg[0]);         
                  break ; 
    case 0x05U:   //  Hand sensor err Display on
                  w_msg[10] = 53U  ;              
                  send_HMI_bytes((const uint8_t *)&w_msg[0]);   
                  break ; 
    case 0x06U:   //  Interlock sensor err Display on
                  w_msg[10] = 54U  ;               
                  send_HMI_bytes((const uint8_t *)&w_msg[0]);   
                  break ;  
    case 0x07U:   //  LD power err Display on
                  w_msg[10] = 55U  ;              
                  send_HMI_bytes((const uint8_t *)&w_msg[0]); 
    case 99U:     // Head Msg Display off
                  w_msg[10] = 2  ;            
                  send_HMI_bytes((const uint8_t *)&w_msg[0]); 
                  Laser_disp_flag_off ;   
                  break ;   
    default:
                  break; 
  }
}
/**
 * @brief Filter Display Change ( Todo Change)
 * 
 * @param i_old 
 * @param i_new 
 */
/*
    FILTER_UNSELECT = 0U,
    FILTER_510      = 1U,
    FILTER_560      = 2U,
    FILTER_585      = 3U,
    FILTER_640      = 4U,
    FILTER_700      = 5U,
    FILTER_800      = 6U,
    FILTER_900      = 7U
    */
void selected_filter_display(FILTER_e i_old ,FILTER_e i_new )
{
  if(i_old != i_new) 
  {
    switch(i_old) 
    {
      case FILTER_510 :    
                  graphic_overwrite(0x0600U,15U,141U,15U+157U,141U+156U,8U);
                  break ;
      case FILTER_560 :    
                  graphic_overwrite(0x0610U,320U,141U,320U+157U,141U+156U,8U);
                  break ;
      case FILTER_585 :    
                  graphic_overwrite(0x0620U,618U,141U,618U+157U,141U+156U,8U);
                  break ;
      case FILTER_640 :    
                  graphic_overwrite(0x0630U,166U,333U,166U+157U,333U+156U,8U);
                  break ; 
      case FILTER_700 :    
                  graphic_overwrite(0x0640U,482U,334U,482U+157U,334U+156U,8U);
                  break ; 
      case FILTER_800 :   // Todo Change
                  graphic_overwrite(0x0640U,482U,334U,482U+157U,334U+156U,8U);
                  break ;  
      case FILTER_900 :    
                  graphic_overwrite(0x0640U,482U,334U,482U+157U,334U+156U,8U);
                  break ; 
    }
    //
    switch(i_new) 
    {
      case FILTER_510 :    
                  graphic_overwrite(0x0600U,15U,141U,15U+157U,141U+156U,9U);
                  break ;
      case FILTER_560 :    
                  graphic_overwrite(0x0610U,320U,141U,320U+157U,141U+156U,9U);
                  break ;
      case FILTER_585 :    
                  graphic_overwrite(0x0620U,618U,141U,618U+157U,141U+156U,9U);
                  break ;
      case FILTER_640 :    
                  graphic_overwrite(0x0630U,166U,333U,166U+157U,333U+156U,9U);
                  break ; 
      case FILTER_700 :    
                  graphic_overwrite(0x0640U,482U,334U,482U+157U,334U+156U,9U);
                  break ; 
      case FILTER_800 :   // Todo Change
                  graphic_overwrite(0x0640U,482U,334U,482U+157U,334U+156U,9U);
                  break ;  
      case FILTER_900 :    
                  graphic_overwrite(0x0640U,482U,334U,482U+157U,334U+156U,9U);
                  break ; 
    } 
  }
}
/** 
 *    Pulse Type display
 */
 

void pulse_type_load(uint8_t i_new) 
{
  switch(i_new) 
  {
    case 1 :    
                graphic_overwrite(0x0710U,31U,153U,31U+327U,153U+201U,10U);
                break ;
    case 2 :    
                graphic_overwrite(0x0710U,31U,153U,31U+327U,153U+201U,11U);
                break ;
    case 3 :    
                graphic_overwrite(0x0710U,31U,153U,31U+327U,153U+201U,12U);
                break ;
    case 4 :    
                graphic_overwrite(0x0710U,31U,153U,31U+327U,153U+201U,13U);
                break ;  
    default:
                break ;
  }
    //
}
/**
 * @brief     Selected Filter Data Display
 * 
 * @param i_neW   Selected Filer 
 */
void select_filter_display(FILTER_e i_new)
{
    switch(i_new) 
    {
        case FILTER_510 :    
                    FILTER_VALUE = 510 ;
                    break ;
        case FILTER_560 :    
                    FILTER_VALUE = 560 ;
                    break ;
        case FILTER_585 :    
                    FILTER_VALUE = 585 ;
                    break ;
        case FILTER_640 :    
                    FILTER_VALUE = 640 ;
                    break ;  
        case FILTER_700 :    
                    FILTER_VALUE = 700 ;
                    break ;
        case FILTER_800 :    
                    FILTER_VALUE = 800 ;
                    break ;  
        case FILTER_900 :    
                    FILTER_VALUE = 900 ;
                    break ;
    }
    //
    dwin_set_value(3U) ; 
}

// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
 
 
// ---------------------------------------------------------------------------
// Not used Function 
// ---------------------------------------------------------------------------
//
static void shift_num_mask(uint8_t u8Value)
{
    mask_number[0] = mask_number[1] ; 
    mask_number[1] = mask_number[2] ;
    mask_number[2] = mask_number[3] ;
    mask_number[3] = u8Value  ; 
    //
    send_num[5] = '*' ;
    send_num[6] = '*';
    send_num[7] = '*';
    send_num[8] = u8Value;
}
// FLU change limit check then duration data change.... 
// Not used
static void Flu_Duration_limit(void)
{ 
  if(DURATION_VALUE >= frq_dura_limit[FILTER_VALUE-1]) 
    { DURATION_VALUE = frq_dura_limit[FILTER_VALUE-1] ; }
}
// duration change limit check then duration data change.... 
// Not used
static void Dur_FREQUENCE_limit(void)
{
  bool     bLoop = true ;
  uint16_t u16cal_time  = 0U ; 
  //
  do
  {
    u16cal_time = 500U / FILTER_VALUE ; //
    if(DURATION_VALUE <= u16cal_time) 
    {
      bLoop = false ;
    }
    else { FILTER_VALUE-- ; }
    //
    if(FILTER_VALUE <= 1) 
    {
      FILTER_VALUE = 1 ;
      bLoop = false ;
    }
  }  
  while(bLoop) ;
}

//  FREQUENCE change limit check then DURATION data change.... 
// Not used
static void FRE_Duration_limit(void) 
{
  uint16_t u16cal_time  = 0U ; 
  //
  u16cal_time = 500U / FILTER_VALUE ; //
  if(DURATION_VALUE > u16cal_time)
  {
    DURATION_VALUE = u16cal_time ;
  }
} 
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//
static void wait_key_off3(void)
{
  bool bLoop = true ;
  uint8_t u8wait_counter  = 0U  ;
  uint8_t u8delay_counter = 0U ;
  //
  do
  {
    delay_ms(10U) ;
    //
    if(KEY_BUFF3 == 0x0000) { u8wait_counter++ ; }
    else 
    {
      u8wait_counter = 0U ;
      u8delay_counter = 1U ;
      KEY_BUFF3 &= 0x0000U ;
    }
    //
    if(u8delay_counter == 0) 
    {
      if(u8wait_counter > 60U ) { bLoop = false ; }
    }
    else 
    {
      if(u8wait_counter > 25U ) {  bLoop = false ; }
    }
  }
  while(bLoop) ;
}
#pragma used-  /* DWIN_LCD.c End Of File !! Well Done */
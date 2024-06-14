/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]  ATMEGA128A
 * [ Compller  ]
 * [ Filename  ]  AP.c
 * [ Version   ]  1.0
 * [ Created   ]
 * --------------------------------------------------------------------------
 * Revision History :
 * ------------------------------------------------------------------
 *
 *  *.본소스 코드를 이용하는 것은 본 조항을 사용자가 암묵적으로
 *    동의 한것으로 간주 합니다.
 *  *.본 소스코드는 개인학습 및 연구 개발용으로 자유롭게 사용가능
 *    합니다.
 *  *.본소스를 사용하여 2차 저작을 하거나 재배포 할 시에는 반드시
 *    SAMJIN ELECTRONICS의 회사명을 반드시 명시하여야 합니다.
 *  *.본 소스코드의 판매 및 영리 활동을 금지합니다 .
 *  *.본 조항 및 원저자 표시의 수정 및 삭제를 금지합니다.
 *
 *------------------------------------------------------------------
 * --------------------------------------------------------------------------
 * Author         Date       Comments on this revision
 * --------------------------------------------------------------------------
 * Hagseong Kang   2024-01-16   First release of this file 
 * --------------------------------------------------------------------------
 * Additional Notes:
 * **************************************************************************
 */
#pragma used+
#include "ap.h"
#include "word.h"
// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 
#define RUN_SW_DELAY_TIME   1000U

// ---------------------------------------------------------------------------
// Define typedef.
// --------------------------------------------------------------------------- 
// 
SYSTEM_FLAG system_flag ;
//SYSTEM_FLAG delay_flag ;
SYSTEM_FLAG buzzer_flag ;
//SYSTEM_FLAG apr_in_flag ; 
//SYSTEM_FLAG Int6_flag ; 
SYSTEM_FLAG warning_flag ; 
SYSTEM_FLAG key_in_flag ;
SYSTEM_FLAG msg_flag ;
 
// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
volatile uint8_t current_screen = 0U;
volatile uint8_t prev_screen    = 0U;
FILTER_e select_filter          = FILTER_UNSELECT;
FILTER_e selected_filter        = FILTER_UNSELECT; 
uint16_t select_pulse_type      = 0U; 
uint16_t selected_pulse_type    = 0U;  
uint16_t cool_sec_time          = 0U ; 
//
volatile uint8_t  bz_timer      = 0U;
volatile uint8_t  bz_counter    = 0U;
volatile uint8_t  error_code    = 0U;
//
uint16_t IPL_fre_set_para       = 0U;
uint16_t pulse_end_counter      = 0U;
//
uint8_t system_warning          = 0U;
uint16_t st_temp_data_old       = 0U;
uint16_t dt_temp_data_old       = 0U;
uint16_t water_flow_on_timer    = 0U;
volatile uint8_t key_in_counter = 0U;
uint16_t level_data_tbl[32]  = {0x00U,};  
volatile uint8_t   dur_ptr      = 0U;
uint16_t Dur_data               = 0U;
uint16_t level_data             = 0U;
uint16_t level_old_data         = 0U;
uint16_t IPL_volt_data          = 0U;
uint16_t IPL_interval_counter   = 0U;
 
// ---------------------------------------------------------------------------
//  Define Varibales Macro.
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// Define private function definitions.
// ---------------------------------------------------------------------------
//
static void system_interlock_check(void);
static void water_flow_on_main(void);
static void st_cool_control(void);        // Not used
//
static void INTRO_MENU(void) ;
static void SYS_CHECK_MENU(void);
static void SELECT_MENU(void);
static void MAIN_SCREEN(void);
static void st_set_menu(void);
static void COUNT_SERAIL_SET_MENU(void);
static void INFORMATION_MENU(void);
static void KEY_PAD(void);
static void Level_data_output(void);
//
static void main_menu_key_control(void);
static uint16_t pass_key_pad(uint8_t select);
static void Change_Password_Menu(void);
//
static void change_text_color(uint8_t addr);
//
static void IPL_on_run(void);
static void IPL_trg_funct_set(void);
static void selected_apr_load(uint8_t u8Select);
static void run_driver_off(void);
static void HW_system_error_check(void);  // Not used
//
static void CAL_SETTING_MENU(void) ;
static void cal_data_all_display(void);
static void cal_level_data_load_disp(void);
static void Cali_Data_offset(uint8_t u8Mode); // not used

static void cali_data_auto_cal(uint8_t cal_index_old,uint8_t cal_index) ;
//
static void Water_flow_Check(void) ;
static void InterLock_Check(void) ;
static void ST_Temp_Check(void) ;
static void DT_Temp_Check(void) ;
static void Head_error_msg_dis(uint8_t u8ErrorCode);
static void laser_hw_error_off(void);
static void temp_sensor_er_msg(void);   // not used
static void output_counter_main(void);
static void temp_display(void);
// ---------------------------------------------------------------------------
// Define Callback function definitions.
// ---------------------------------------------------------------------------
// 
static void cbAP_Timer0(void);
// ---------------------------------------------------------------------------
// Define Public function definitions.
// ---------------------------------------------------------------------------
// 
/**
 * @brief 
 * 
 */
void apInit(void)
{
 HMI_SioMemInit(&PLC_DATA[0]);
 canSetTimer0Callback(HW_AP_TIMER0_CB,cbAP_Timer0) ;
}
/*
 *
 */
void apMain(void)
{
  BUZZER_ON ;  
  delay_ms(30);  
  BUZZER_OFF ;  
  running_flag_off ; 
  pulse_end_counter =  RUN_SW_DELAY_TIME ;
  IPL_pulse_end_S_flag_on ; // start keyin
  // Global enable interrupts
  #asm("sei") ;
  
  delay_ms(300U) ;
  eeprom_data_save();  
  eeprom_data_load();  
  delay_ms(200U) ;
  water_flow_on_main(); 
  delay_ms(300U); 
  //
  current_screen = SCR_INTRO ;  
  //
  while (1)
  {
    switch(current_screen)
    {
        case SCR_INTRO:
                            INTRO_MENU(); 
                            break;
        case SCR_SYSCHECK:
                            SYS_CHECK_MENU();
                            //current_screen = SCR_INTRO ;
                            break;  
        case SCR_MODE_SELECT: 
                            SELECT_MENU();
                            //current_screen = SCR_INTRO ;
                            break ;
        case SCR_MAIN:
                            MAIN_SCREEN();
                            break;
        case SCR_KEYPAD:
                            KEY_PAD();
                            break;
        case SCR_INFO:
                            INFORMATION_MENU();
                            break;  
        /*                    
        case SCR_ST_SETTING:      
                            st_set_menu();
                            break;
        */
        case SCR_COUNT_SERIAL:
                            COUNT_SERAIL_SET_MENU();
                            break; 
        case SCR_CALI:
                            CAL_SETTING_MENU();
                            break;  
        case SCR_HW_TEST_MENU:
                            //HW_TEST_MENU();
                            break;
        default:
                            break;
    }
  } 
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
// 
/**
 * @brief System Intro Function
 * 
 */
void INTRO_MENU(void)
{
  send_set_screen(SCR_INTRO) ;
  delay_ms(500) ;
  if(bitRead(KEY_BUFF1,15U) == 0x01U)
  {
    current_screen = SCR_HW_TEST_MENU ;
  }
  delay_ms(500) ;
  if(bitRead(KEY_BUFF1,15U) == 0x01U)
  {
    current_screen = SCR_HW_TEST_MENU ;
  }
  if(current_screen == SCR_INTRO)
  {
    dwin_vp_value_read(0x0005U,0x05U) ;
    Basic_Graphic(0x0400U, 189U, 100U, 189U+424U, 100U+491U, 1U);
    delay_ms(500);
    if(bitRead(KEY_BUFF1,15U) == 0x01U)
    {
      current_screen = SCR_HW_TEST_MENU ;
    }
    else 
    {
      dwin_vp_value_read(0x0015,05) ;
      Basic_Graphic(0x0400, 189, 100, 189+424, 100+491, 2);
      delay_ms(500U); 
      if(bitRead(KEY_BUFF1,15U) == 0x01U)
      {
        current_screen = SCR_HW_TEST_MENU ;
      }
      else
      {
        dwin_vp_value_read(0x0025U,05U) ;
        Basic_Graphic(0x0400U, 189, 100, 189+424, 100+491, 3);
        delay_ms(500U); 
        dwin_vp_value_read(0x0035U,05U) ;
        Basic_Graphic(0x0400U, 189, 100, 189+424, 100+491, 4);
        delay_ms(500U);
        dwin_vp_value_read(0x0045U,05U) ;
        Basic_Graphic(0x0400, 189, 100, 189+424, 100+491, 5);
        delay_ms(500U);
        //
        current_screen = SCR_SYSCHECK ; 
      }
    }
  }
}
/**
 * @brief System H/W Check Function
 * 
 */
void SYS_CHECK_MENU(void)
{
  uint8_t  u8Status = 0U ;
  uint16_t u16Check = 0U ;

  send_set_screen(current_screen) ;
  delay_ms(300U) ;

  while(current_screen == SCR_SYSCHECK)
  {
    delay_ms(300U);
    switch(u8Status)
    {
      case 0x00U: // Power Check
          Send_Power_on_cmd();  // IPL Power On
          dwin_vp_value_read(0x0001U,0x05U);
          // Check Power Return
          Basic_Graphic(0x0500U,3U,136U,3U+210U,136U+184U,7U);
          delay_ms(300U);
          u8Status = 0x01U ;
          break;

      case 0x01U: // HP connector CHECK.. 
          if(Is_Not_w_hd_ok_flag) {
            dwin_vp_value_read(0x0010U,0x05U);
          }
          dwin_vp_value_read(0x0010U,0x05U);
          // Check Power Return
          Basic_Graphic(0x0510U,216U,136U,216U+210U,136U+184U,7U);
          delay_ms(300U);
          u8Status = 0x02U ;
          break;

      case 0x02U: //  water flow or RPM Meter Check!  
          if(Is_Not_w_w_flow_flag) {
              dwin_vp_value_read(0x0010U,5U) ;
          }
          dwin_vp_value_read(0x0020U,5U) ;
          Basic_Graphic(0x0520U,441U,137U,441U+210U,137U+184U,7U);
          delay_ms(300U);
          u8Status = 0x03U;
          break;

      case 0x03U: // ST,DT temp  sensor check ...  
          if(Is_Not_w_st_temp_flag) {
              dwin_vp_value_read(0x0010U,05U) ;
          }
          dwin_vp_value_read(0x0030U,05U) ;
          Basic_Graphic(0x0530U,128U,330U,128U+215U,330U+184U,7U);
          delay_ms(300U); 
          u8Status = 0x04U;
          break;

      case 0x04U: // DT temp Cooling check.... 
          if(Is_Not_w_cool_temp_flag) {
              dwin_vp_value_read(0x0010U,05U) ;
          } 
          dwin_vp_value_read(0x0040U,05U) ;    
          Basic_Graphic(0x0540,361,330,361+210,330+184,7);
          delay_ms(300U); 
          u8Status = 0x05U;
          break;
      case 0x05U: // interlock  check ....  
          while(Is_Not_w_interlock_flag) {
              dwin_vp_value_read(0x0010U,05U) ; 
              delay_ms(100U);
          } 
          dwin_vp_value_read(0x0050U,05U) ;
          Basic_Graphic(0x0550,580,330,580+210,330+184,7);
          delay_ms(300U);
          u8Status = 0x06U;
          break;
      case 0x06U:
          // LCD Testing... 
          // call memrory read ....
          delay_ms(500U) ;
          u16Check  = PLC_DATA[0x50U] ;
          u16Check += PLC_DATA[0x51U] ;
          u16Check += PLC_DATA[0x52U] ;
          u16Check += PLC_DATA[0x53U] ; 
          u16Check += PLC_DATA[0x54U] ; 
          //
          u8Status = 0x07U;
          current_screen = SCR_MODE_SELECT ; 
          break;
    }  
  }
}
/**
 * @brief   Select Filter 
 * 
 */
void SELECT_MENU(void)
{
  uint8_t u8Status = 0U ;   
  uint8_t u8Fliter_Status = 0U ;
  // 
  CURRENT_COUNT_HI = 0U ; 
  CURRENT_COUNT_LO = 0U ;
  
  dwin_word2_write(CURRENT_COUNT_HI_ADD) ;
  send_set_screen(SCR_MODE_SELECT) ;
  //
  selected_filter = select_filter ;
  selected_filter_display(select_filter,selected_filter);
  //
  while(current_screen == SCR_MODE_SELECT)
  {
    switch(KEY_BUFF1)
    {
      case _DEF_MBIT0:
          select_filter = FILTER_510 ;
          break ;
      case _DEF_MBIT1:
          select_filter = FILTER_560 ;
          break ;
      case _DEF_MBIT2:
          select_filter = FILTER_585 ;
          break ;
      case _DEF_MBIT3:
          select_filter = FILTER_640 ;
          break ;
      case _DEF_MBIT4:
          select_filter = FILTER_700 ;
          break ;
      case _DEF_MBIT5:
          select_filter = FILTER_800 ;
          break ;
      case _DEF_MBIT6:
          select_filter = FILTER_900 ;
          break ;
      default:
          break ;         
    } 
    //
    KEY_BUFF1 &= 0x0000U ; 
    if(selected_filter != select_filter)
    {
      selected_filter_display(selected_filter,select_filter);
      u8Status =  1U ;
    }
    // ----------------------------------------------------------
    if(Is_w_filter_flag) {
      if(u8Fliter_Status != 0x00U) {
        u8Fliter_Status = 0x00U ;
        Basic_Graphic(0x0690U,63U,518U,63U+632U,518U+134U,8U);
      }
    }
    else {
      if(u8Fliter_Status != 0x01U) {
        u8Fliter_Status = 0x01U ;
        Basic_Graphic(0x0690U,63U,518U,63U+632U,518U+134U,9U);
      }
    }
    // ----------------------------------------------------------
    if(u8Status == 1U) {
      Send_Simmer_on_cmd();
      delay_ms(100);
      selected_filter = select_filter ;
      // load filter Pulse type
      select_pulse_type = Filter_eeprom_data_load(select_filter); 
      // selected Filter Backup
      apr_flag_eeprom_save(select_filter);    
      //
      current_screen = SCR_MAIN ;  
      u8Status = 0U ;
    }
    else { delay_ms(10) ; }
  }
}
/**
 * @brief   IPL Main Treatment Function
 * 
 */
void MAIN_SCREEN(void)
{
  Dur_data = 0U ;
  level_old_data = 0U ; 
  selected_pulse_type = 0U ;
  // 
  send_set_screen(SCR_MAIN);
  // IPL Power level low data load ...
  level_data_load_eeprom(select_filter,(uint16_t * const)&level_data_tbl[0]);   
  // 
  // Load Druration time & Level ptr     
  apr_data_load(select_filter,select_pulse_type,&dur_ptr,&level_data) ;
  pulse_type_load(select_pulse_type) ;        // HMI Pulse type display ...   
  selected_pulse_type = select_pulse_type ; 
  // 
  // IPL Output Pulse Duration Data load        
  dur_data_load(select_pulse_type,dur_ptr) ;   
  dwin_set_value(1) ; // Duration Data Display ... 
  Dur_data = DURATION_VALUE ;
  // FLUENCE_VALUE = level_data   
  FLUENCE_VALUE = Level_to_Flu_cal(select_pulse_type,dur_ptr,level_data); 
  dwin_set_value(2U) ; // Flunece Data Display ... 
  level_old_data = level_data ; 
  // 
  Level_data_output();
  Send_Shot_data_cmd(IPL_volt_data,0,0); 
  //
  while(current_screen == SCR_MAIN)
  {
    main_menu_key_control();  // lcd key control routine ...
    // control data update  .....   
    if(Dur_data != DURATION_VALUE) {  // Check Duration Change
      dwin_set_value(1U);
      Dur_data = DURATION_VALUE ;
    }
    if(level_old_data != level_data) { // Check Level Change
      dwin_set_value(2U);
      level_old_data = level_data;
    }  
    //
    if(Is_run_count_flag) {
      run_count_flag_off ;
      count_save_flag_on ;
      dwin_word2_write(CURRENT_COUNT_HI_ADD);
    }  
    //
    if(Is_Ready_btn_set_flag) {
      if(Is_run_flag) {
        IPL_on_run();
      }
      else {
        running_flag_off ;
        IPL_TRIG_DIS ;
        if(Is_count_save_flag) {
          count_save_flag_off ;
          counter_eeprom_data_save();
        }
      }
      //
    }
    else {
      if(Is_running_flag) {
        running_flag_off ;
        IPL_TRIG_DIS ;
        if(Is_count_save_flag) {
          count_save_flag_off ;
          counter_eeprom_data_save();
        }
        head_msg_display(0); // // laser out display .. 
      }
      //  Not ready foot s/w on
      while(Is_run_flag) {
        bz_timer = 50U ;
        buzzer_on_flag_on ;
        delay_ms(200U);
      }
    }
    // 
    temp_display(); 
    delay_ms(1U);
  }
}
/**
 * @brief Calibration Setting Menu
 * 
 */
void CAL_SETTING_MENU(void) 
{
  uint16_t u16Pass = 0U ;
  //
  uint8_t  u8Cal_selected_index = 0U ;
  uint8_t  u8Cal_selected_index_old = 0U ;
  uint8_t  u8Plc_add = 0U ;
  uint8_t  u8Old_Plc_add = 0U ;
  uint16_t u8Old_IPL_volt_data = 0U ;

  while(1)
  {
    u16Pass = pass_key_pad(3); // engineer Mode
    
    if(u16Pass == 0x00U)
    {
        current_screen = prev_screen; 
        break ;
    }          
    if((u16Pass == PASSWORD) || (u16Pass == 8096)) break;
  }
  //
  if(current_screen == SCR_CALI)
  {
    u8Cal_selected_index = 15U ; 
    FILTER_VALUE = 1U ;
    DURATION_VALUE = 24U ;
    delay_ms(30); 
    level_data_load_eeprom(FILTER_VALUE,(uint16_t * const)&level_data_tbl[0]);
    cal_data_all_display(); // Init Cal data Display
    delay_ms(30);
    send_set_screen(SCR_CALI) ;  // 
    delay_ms(100);
    dwin_cal_change_text_color(u8Cal_selected_index) ;

    u8Plc_add = u8Cal_selected_index + (CAL_BASE_ADD-1U) ; // 15 + 31

    while(current_screen == SCR_CALI) 
    {
      if((KEY_BUFF2 > 0U) || (KEY_BUFF3 > 0U))
      {
        u8Cal_selected_index_old = u8Cal_selected_index ; 
        u8Old_Plc_add = u8Plc_add ;

        u8Cal_selected_index = location_set_dword(KEY_BUFF3,KEY_BUFF2);
        dwin_cal_change_text_color(u8Cal_selected_index) ;
        u8Plc_add = u8Cal_selected_index + (CAL_BASE_ADD-1U) ; // 15 + 31
        //
        KEY_BUFF2 = 0x00U ;
        KEY_BUFF3 = 0x00U ;
      }
      //
      switch(KEY_BUFF4)
      {
        case _DEF_BIT0 :  // F510 Select
            bitClear(KEY_BUFF4,0U) ;  
            FILTER_VALUE = 1U ;
            u8Old_IPL_volt_data = 0 ;
            cal_level_data_load_disp();
            break ;
        case _DEF_BIT1 :  // F560 Select
            bitClear(KEY_BUFF4,1U) ;  
            FILTER_VALUE = 2U ;
            u8Old_IPL_volt_data = 0 ;
            cal_level_data_load_disp();
            break ; 
        case _DEF_BIT2 :  // F585 Select
            bitClear(KEY_BUFF4,2U) ;  
            FILTER_VALUE = 3U ;
            u8Old_IPL_volt_data = 0 ;
            cal_level_data_load_disp();
            break ; 
        case _DEF_BIT3 :  // F640 Select
            bitClear(KEY_BUFF4,3U) ;  
            FILTER_VALUE = 4U ;
            u8Old_IPL_volt_data = 0 ;
            cal_level_data_load_disp();
            break ; 
        case _DEF_BIT4 :  // F700 Select
            bitClear(KEY_BUFF4,4U) ;  
            FILTER_VALUE = 5U ;
            u8Old_IPL_volt_data = 0 ;
            cal_level_data_load_disp();
            break ; 
        case _DEF_BIT5 :  // F800 Select modify Dwin Bit
            bitClear(KEY_BUFF4,5U) ;  
            FILTER_VALUE = 6U ;
            u8Old_IPL_volt_data = 0 ;
            cal_level_data_load_disp();
            break ; 
        case _DEF_BIT6 :  // F900 Select modify Dwin Bit
            bitClear(KEY_BUFF4,6U) ;  
            FILTER_VALUE = 7U ;
            u8Old_IPL_volt_data = 0 ;
            cal_level_data_load_disp();
            break ;
        case _DEF_BIT7 :  // Auto Select modify Dwin Bit
            bitClear(KEY_BUFF4,7U) ;  
            cali_data_auto_cal(u8Cal_selected_index_old,u8Cal_selected_index) ;
            u8Old_IPL_volt_data = 0 ;
            cal_data_all_display();
            break ;
        case _DEF_BIT8 :  // Save
            bitClear(KEY_BUFF4,8U) ;  
            BUZZER_ON ;
            level_data_save_eeprom(FILTER_VALUE,(const uint16_t *)&level_data_tbl[0]);
            BUZZER_OFF ;
            break ;
        case _DEF_BIT9 :  // Ready button
            bitClear(KEY_BUFF4,9U) ;  
            if(Is_Ready_btn_set_flag) {  // ready to standby  
              Basic_Graphic(0x0810,294,513,(294+220),(513+86),35U); 
              Ready_btn_set_flag_off ;
              u8Old_IPL_volt_data = 0U ; 
            }
            else {  // stand by to ready ..  
              if(Is_Not_run_flag) { 
                Basic_Graphic(0x0810,294,513,(294+220),(513+86),36U); 
                Ready_btn_set_flag_on ;   
              }
            }
            break ;  
        case _DEF_BIT10 :  // data up
            bitClear(KEY_BUFF4,10U) ;  
            if(++PLC_DATA[u8Plc_add] >= IPL_VOLT_MAX) 
               { PLC_DATA[u8Plc_add] =  IPL_VOLT_MAX ;}
            level_data_tbl[u8Cal_selected_index - 1U] = PLC_DATA[u8Plc_add];    
            set_value(u8Plc_add, PLC_DATA[u8Plc_add]);  
            u8Old_IPL_volt_data = 0 ;
            break ;
        case _DEF_BIT11 :  // data down
            bitClear(KEY_BUFF4,11U) ;  
            if(--PLC_DATA[u8Plc_add] <= IPL_VOLT_MIN) 
               { PLC_DATA[u8Plc_add] =  IPL_VOLT_MIN ; }
            level_data_tbl[u8Cal_selected_index - 1U] = PLC_DATA[u8Plc_add];    
            set_value(u8Plc_add, PLC_DATA[u8Plc_add]);  
            u8Old_IPL_volt_data = 0 ;
            break ;
        case _DEF_BIT15 :  // return
            bitClear(KEY_BUFF4,15U) ;  
            current_screen = SCR_MAIN ;
            select_filter  = (FILTER_e)FILTER_VALUE ;
            selected_filter  = select_filter ;  

            select_filter_display(  select_filter);
            Filter_eeprom_data_load(select_filter);
            break ;

        default:
            KEY_BUFF4 = 0x00U ;
            break;
      }
      if(Is_Ready_btn_set_flag) 
      {
        if(u8Old_IPL_volt_data != PLC_DATA[u8Plc_add])
        {
          IPL_volt_data = PLC_DATA[u8Plc_add] ;
          Send_Shot_data_cmd(IPL_volt_data,0,0); 
          u8Old_IPL_volt_data = IPL_volt_data ;
        }
        //
        if(Is_run_flag)
        {
          dur_data_load(2,6); // Pulse_3 , 24mSEC
          FILTER_VALUE = 1U ; // ??
          running_flag_on ;
          bz_counter = FILTER_VALUE ;
          //
          bitClear(TIMSK,1U);   // timer 0 disable 
          Pulse_data_ptr = 0U;
          IPL_trg_funct_set();
          IPL_pulse_run_flag_on ; 
          IPL_interval_counter = 0 ;
          // 
          delay_ms(100) ;
          running_flag_off ;   
          while(Is_run_flag) ; // waiting run off  
          //
          Basic_Graphic(0x0810,294,513,(294+220),(513+86),35U); 
          Ready_btn_set_flag_off ;
        }
      }
    } 
  }
}
/**
 * @brief   SCR_INFO
 * 
 */
void INFORMATION_MENU(void)
{
  dwin_information_display();

  while(current_screen == SCR_INFO)
  {
    if(bitRead(KEY_BUFF4,15U) == 0x01U)
    {
      bitClear(KEY_BUFF4,15U);
      current_screen = SCR_MAIN;
    }
  }
}
// --------------------------------------------------------------------
void st_set_menu(void)
{
  uint16_t u16PreTime = 0U ;
  dwin_word3_write(ST_TEMP_SV_MIN_ADD)  ;
  //    
  // send_hmi_bytes(to_st_setting);
  dwin_to_st_setting();
  delay_ms(100U);    
  // 
  u16PreTime = millis();
  while(current_screen == SCR_ST_SETTING)
  {
      if((KEY_BUFF2 & 0x00FFU) == 0x40)
      {
          KEY_BUFF2 &= ~(0x40);
          temp_sv_eeprom_data_save(); // DATA SAVE TO EEPROM          
          current_screen = SCR_MAIN; 
          break ;
      } 
      //
      if((millis() - u16PreTime) >= 300U )  // send st temp data every 300msec!!
      {
        u16PreTime = millis();
        dwin_set_value(4) ;
      }
  }
}
//
void COUNT_SERAIL_SET_MENU(void)
{
  uint8_t  u8i = 0U ;
  uint16_t u16Pass = 0U ;
  uint8_t  u8Selected_Index = 0U ;
  uint8_t  u8Reset_Mode = 0U ;

  while(1)
  {
      u16Pass = pass_key_pad(1);
      
      if(u16Pass == 0x00)
      {
          current_screen = prev_screen; 
          break;
      }          
      if((u16Pass == PASSWORD) || (u16Pass == 8096)) { break; }
  }
  if(current_screen == SCR_COUNT_SERIAL)
  {
    eeprom_data_load();    
    //
    dwin_word4_write(TOTAL_COUNT_ADD) ; //  
    dwin_word4_write(LAMP_COUNT_ADD) ;  // 
    delay_ms(50U); 
    //
    set_value(0x15U, SERIAL_YY);
    set_value(0x16U, SERIAL_MM);
    set_value(0x17U, SERIAL_DD);
    set_value(0x18U, SERIAL_NO);
    //
    delay_ms(20U);  
    send_set_screen(SCR_COUNT_SERIAL); 
    //
    u8Selected_Index = 0x15U ;
    dwin_change_text_color(0x15U);

    while(current_screen == SCR_COUNT_SERIAL)
    {
      switch(KEY_BUFF4) 
      {
        case _DEF_BIT0: //  
            bitClear(KEY_BUFF4,0U) ;
            eeprom_serial_save();
            current_screen = SCR_MAIN; 
            break;
        case _DEF_BIT1: //  
            bitClear(KEY_BUFF4,1U) ;
            if(u8Reset_Mode == 1U)
            {
              LAMP_COUNT_HI = 0U ;
              LAMP_COUNT_LO = 0U ;
              set_value(13U, LAMP_COUNT_HI);
              set_value(14U, LAMP_COUNT_LO); 
            }
            if(u8Reset_Mode == 2U)
            {
              TOTAL_COUNT_HI = 0U ;
              TOTAL_COUNT_LO = 0U ;
              set_value(11U, TOTAL_COUNT_HI);
              set_value(12U, TOTAL_COUNT_LO); 
              counter_eeprom_data_save();    
            }
            //  Counter Clear
            for(u8i=0x40U; u8i<0x4EU ; u8i++)
            {
              PLC_DATA[u8i] = 0x00U ;
            }
            counter_eeprom_data_save();

            for(u8i=0x40U; u8i<0x4EU ; u8i++)
            {
              set_value(u8i, PLC_DATA[u8i]);
            }
            break;
        case _DEF_BIT2: //  
            bitClear(KEY_BUFF4,2U) ;
            break;
        case _DEF_BIT3: // year  
            bitClear(KEY_BUFF4,3U) ;
            u8Selected_Index = 0x15U ;
            change_text_color(u8Selected_Index);
            break;
        case _DEF_BIT4: //  MM
            bitClear(KEY_BUFF4,4U) ;
            u8Selected_Index = 0x16U ;
            change_text_color(u8Selected_Index);
            break;
        case _DEF_BIT5: //  DD
            bitClear(KEY_BUFF4,5U) ;
            u8Selected_Index = 0x17U ;
            change_text_color(u8Selected_Index);
            break;
        case _DEF_BIT6: //  No
            bitClear(KEY_BUFF4,6U) ;
            u8Selected_Index = 0x18U ;
            change_text_color(u8Selected_Index);
            break;
        case _DEF_BIT7: //  Up
            bitClear(KEY_BUFF4,7U) ;
            //
            if(u8Selected_Index == 0x15U) {
              if(++PLC_DATA[u8Selected_Index] >= 99U) { PLC_DATA[u8Selected_Index] = 24U; }
            }
            if(u8Selected_Index == 0x16U) {
              if(++PLC_DATA[u8Selected_Index] >= 12U) { PLC_DATA[u8Selected_Index] = 1U; }
            }
            if(u8Selected_Index == 0x17U) {
              if(++PLC_DATA[u8Selected_Index] >= 31U) { PLC_DATA[u8Selected_Index] = 1U; }
            }
            if(u8Selected_Index == 0x18U) {
              if(++PLC_DATA[u8Selected_Index] >= 99U) { PLC_DATA[u8Selected_Index] = 1U; }
            }
            //
            set_value(u8Selected_Index, PLC_DATA[u8Selected_Index]);
            break;
        case _DEF_BIT8: //  Down
            bitClear(KEY_BUFF4,8U) ;
            if(u8Selected_Index == 0x15U) {
              if(--PLC_DATA[u8Selected_Index] <= 24U) { PLC_DATA[u8Selected_Index] = 99U; }
            }
            if(u8Selected_Index == 0x16U) {
              if(--PLC_DATA[u8Selected_Index] <=  1U) { PLC_DATA[u8Selected_Index] = 12U; }
            }
            if(u8Selected_Index == 0x17U) {
              if(--PLC_DATA[u8Selected_Index] <=  1U) { PLC_DATA[u8Selected_Index] = 31U; }
            }
            if(u8Selected_Index == 0x18U) {
              if(--PLC_DATA[u8Selected_Index] <=  1U) { PLC_DATA[u8Selected_Index] = 99U; }
            }
            //
            set_value(u8Selected_Index, PLC_DATA[u8Selected_Index]);
            break;
        case _DEF_BIT9: //  
            bitClear(KEY_BUFF4,0U) ;
            dwin_change_text_color(0U);
            current_screen = SCR_CHANGE_PASS; 
            Change_Password_Menu();
            current_screen = SCR_COUNT_SERIAL;
            send_set_screen(SCR_COUNT_SERIAL);
            break;
        case _DEF_BIT10: //  
            bitClear(KEY_BUFF4,10U) ;
            u8Reset_Mode = 1U ;
            dwin_change_text_color(0x19U);
            break;

        case _DEF_BIT11: //  
            bitClear(KEY_BUFF4,11U) ;
            u8Reset_Mode = 2U ;
            dwin_change_text_color(0x19U);
            break;
        case _DEF_BIT12: // 
            bitClear(KEY_BUFF4,12U) ; 
            break;    
        case _DEF_BIT13: // 
            bitClear(KEY_BUFF4,13U) ;
            break ;
        case _DEF_BIT14: //  
            bitClear(KEY_BUFF4,14U) ;
            break; 
        case _DEF_BIT15: //  
            bitClear(KEY_BUFF4,15U) ;
            break;
      } 
    }
  }
}
//
void Change_Password_Menu(void)
{
    uint16_t u16Pass      = 0U;
    uint16_t u16New_pass  = 0U;  
    //  
    while(1)
    {
      u16Pass = pass_key_pad(1);
      //
      if(u16Pass == 0x00U)
      {
          current_screen = prev_screen;
          return;
      }          
      if((u16Pass == PASSWORD) || (u16Pass == 8096U))
      { break; }
    } 
    //      
    while(current_screen == SCR_CHANGE_PASS)
    { 
       
        u16New_pass = pass_key_pad(2);
        PASSWORD = u16New_pass;  
        // save Password ...
        At24c_Write_2Bytes(EP_PASSWORD,PASSWORD) ;
        break;
    } 
}



// --------------------------------------------------- 
void KEY_PAD(void)
{
  dwin_key_pad(&current_screen);
}
uint16_t pass_key_pad(uint8_t select)
{
  return (dwin_pass_key_pad(select));
}
void change_text_color(uint8_t addr)
{
  dwin_change_text_color(addr);
}
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//
//
void cali_data_auto_cal(uint8_t cal_index_old,uint8_t cal_index) 
{
  uint8_t i ;
  uint8_t i_div ; 
  //
  uint16_t i_cal_data ; 
  uint16_t i_plc_data ; 
  uint16_t i_plc_data_old ;
  uint16_t i_step_data ; 
  //
  if(cal_index_old < cal_index)  
  {
    i_div  =  cal_index - cal_index_old ;
    //
    i_plc_data = level_data_tbl[cal_index-1] * 100 ;
    i_plc_data_old =  level_data_tbl[cal_index_old-1] * 100  ;
    //
    i_step_data = i_plc_data - i_plc_data_old ;
    i_step_data = i_step_data / i_div ;
    //
    i_cal_data = i_plc_data_old ;
    for(i=0; i<(i_div-1U); i++)  
    {
      i_cal_data =  i_cal_data + i_step_data ;
      level_data_tbl[cal_index_old + i] = i_cal_data / 100U ; 
    }
  }
} 
// ------------------------------------------------------------------------
// IPL
// ------------------------------------------------------------------------
//  
void selected_apr_load(uint8_t u8Select)
{
    // Old select data save
    apr_data_save(select_filter,selected_pulse_type,&dur_ptr,&level_data); 
    //  
    select_pulse_type = u8Select ; 
    // New Data Load
    apr_data_load(select_filter,select_pulse_type,&dur_ptr,&level_data); 
    pulse_type_load(select_pulse_type) ;    // HMI Pulse type display ...  
    //
    // IPL Output Pulse Duration Data load        
    dur_data_load(select_pulse_type,dur_ptr) ;   
    dwin_set_value(1) ; // Duration Data Display ... 
    Dur_data = DURATION_VALUE ;
    //   
    Level_to_Flu_cal(select_pulse_type,dur_ptr,level_data); 
    dwin_set_value(2) ; // Flunece Data Display ... 
    level_old_data = level_data ;
    
    selected_pulse_type = select_pulse_type ; 
    Filter_eeprom_data_save(select_filter,selected_pulse_type) ;
    //
}
void Level_data_output(void)
{
    IPL_volt_data = level_data_tbl[level_data-1] ;
    
    /*
    if(level_old_data != level_data) {
        IPL_volt_data = level_data_tbl[level_data-1] ;
        if(IPL_volt_data > 0xfff) IPL_volt_data = 0 ;
        Send_Shot_data_cmd(IPL_volt_data,0,0); 
        level_old_data = level_data ;
    } 
    */
}
void IPL_on_run(void)
{
  if(Is_Not_running_flag) {
    running_flag_on ;
    Pulse_data_ptr = 0 ;
    bitClear(TIMSK,1U) ;      // timer 0 enable   
    IPL_trg_funct_set() ; 
    IPL_pulse_run_flag_on ; 
    IPL_interval_counter = 0 ;
  }  
}
//
void IPL_trg_funct_set(void)
{
  bitClear(TIMSK,4U);         // timer 1a disable ..
  TIFR &= 0x3CU ; 
  IPL_TRIG_DIS ; 
  // 
  if((Is_Not_system_interlock_flag) || (Is_w_st_temp_flag))
  {
      run_driver_off(); 
      KEY_BUFF2 = _DEF_BIT2 ; // ready touch on   
      bitSet(TIMSK,1U) ;      // timer 0 enable  
  } 
  else if((Is_Not_Ready_btn_set_flag) || (Is_Not_RUN_SW_ON)){
      run_driver_off();   
      bitSet(TIMSK,1U) ;      // timer 0 enable   
  } 
  else if(Pulse_i_data[Pulse_data_ptr] == 0x00U) {

      IPL_pulse_run_flag_off ;
      bitSet(TIMSK,1U) ;      // timer 0 enable 
  } 
  else 
  {
    // 100uSec is 25 , 1mSec is 250 ...
    // TRIG off 150uf Delay off   37 is 150uF ... more check and modify
    // 
    IPL_fre_set_para = Pulse_i_data[Pulse_data_ptr] ;
    IPL_fre_set_para = (uint16_t)(IPL_fre_set_para * 25U) ; 
    //
    Pulse_data_ptr++ ;
    //   
    if(bitRead(Pulse_data_ptr,0U) == 0x01U) {
        IPL_fre_set_para = IPL_fre_set_para - 37U ;  
    }
    else {
        IPL_fre_set_para = IPL_fre_set_para + 37U ; 
    }
    // --------------------------------------------------------------  
    // Timer base counter Reset  
    //
    TCCR1A = 0x00U;
    TCCR1B = 0x0BU;
    TCNT1H = 0x00U;
    TCNT1L = 0x00U; 
    //
    // --------------------------------------------------------------  
    // Frequeny Timer Setting
    OCR1AH = highByte(IPL_fre_set_para) ;   // frequency data ...
    OCR1AL =  lowByte(IPL_fre_set_para) ;                  
    //
    // --------------------------------------------------------------- 
    bitSet(TIMSK,4U) ;   // start... 
    TIFR &= ~(0x3CU) ; 
    // --------------------------------------------------------------    
    if(bitRead(Pulse_data_ptr,0U) == 0x01U)  { IPL_TRIG_EN ; }
    else  { IPL_TRIG_DIS ; }
    // --------------------------------------------------------------    
    // buzeer start .....  
    if(Pulse_data_ptr == 0x01) 
    {
        if(Is_Not_buzzer_mask_flag)  
        { 
            bz_timer = 20 ;   
            buzzer_on_flag_on ; 
        } 
        output_counter_main();
    }
  }
}
void run_driver_off(void)
{  
  // w_hw_stop_flag_on ; 
  bitClear(ETIMSK,4U) ; // TIMER 3 INT  disable ...
  IPL_TRIG_DIS ;  
}
// --------------------------------------------------
// DWIN WORK
// --------------------------------------------------
//
 
void cal_data_all_display(void)
{
  uint8_t u8i ;
  //           
  for(u8i=0; u8i<31U; u8i++)
  {
    PLC_DATA[u8i+CAL_BASE_ADD] = level_data_tbl[u8i] ;
    set_value(u8i+CAL_BASE_ADD, PLC_DATA[u8i+CAL_BASE_ADD]);
    delay_ms(10) ;  
  }
}
void cal_level_data_load_disp(void)
{
  Basic_Graphic(0x0800,120,108,120+496,108+68,FILTER_VALUE + 34U);

  if(Is_Ready_btn_set_flag)  // ready to standb 
  {
    Basic_Graphic(0x0810,294,513,(294+220),(513+86),35); 
    Ready_btn_set_flag_off ;
  }
  level_data_load_eeprom(FILTER_VALUE,(uint16_t * const)&level_data_tbl[0]); 
   
  cal_data_all_display();  
}
void output_counter_main(void)
{
  CURRENT_COUNT_LO++ ;
  if(CURRENT_COUNT_LO == 0x0U)  { CURRENT_COUNT_HI++ ; }

  LAMP_COUNT_LO++ ;   
  if(LAMP_COUNT_LO == 0x00U)    { LAMP_COUNT_HI++ ; }

  TOTAL_COUNT_LO++ ; 
  if(TOTAL_COUNT_LO == 0x00U)   { TOTAL_COUNT_HI++ ; }
  // ------------------------------------------------------------
  switch(select_filter)
  {
    case FILTER_510 :
                F510_COUNT_LO++ ;
                if(F510_COUNT_LO == 0x00) F510_COUNT_HI++ ; 
                break ;
    case FILTER_560:
                F560_COUNT_LO++ ;
                if(F560_COUNT_LO == 0x00) F560_COUNT_HI++ ; 
                break ;    
    case FILTER_585 :
                F585_COUNT_LO++ ;
                if(F585_COUNT_LO == 0x00) F585_COUNT_HI++ ; 
                break ;     
    case FILTER_640 :
                F640_COUNT_LO++ ;
                if(F640_COUNT_LO == 0x00) F640_COUNT_HI++ ; 
                break ;
    case FILTER_700 :
                F700_COUNT_LO++ ;
                if(F700_COUNT_LO == 0x00) F700_COUNT_HI++ ; 
                break ;   
    case FILTER_800 :
                F800_COUNT_LO++ ;
                if(F800_COUNT_LO == 0x00) F800_COUNT_HI++ ; 
                break ; 
    case FILTER_900 :
                F900_COUNT_LO++ ;
                if(F900_COUNT_LO == 0x00) F900_COUNT_HI++ ; 
                break ;                      
  }
  //
  run_count_flag_on ; // Dwin Counter UpDate Exe Flag On
}
/**
 *
 * 
 */
void temp_display(void)
{
  if(st_temp_data_old != ST_TEMP_VALUE) 
  {
    st_temp_data_old = ST_TEMP_VALUE ;
    set_value(ST_TEMP_VALUE_ADD,(signed int)PLC_DATA[ST_TEMP_VALUE_ADD]/10);  
  } 

  if(dt_temp_data_old != DT_TEMP_VALUE) 
  {
    dt_temp_data_old = DT_TEMP_VALUE ;
    set_value(DT_TEMP_VALUE_ADD,PLC_DATA[DT_TEMP_VALUE_ADD]); 
  }
}
//
// ------------------------------------------------------------------------
// MENU
// ------------------------------------------------------------------------
//  
void main_menu_key_control(void)
{
  uint8_t  u8i ; 
  uint16_t u16Key_buff1 ; 
  uint16_t u16Key_buff2 ;
  //  
  u16Key_buff1 = KEY_BUFF1 ; 
  u16Key_buff2 = KEY_BUFF2 ; 

  switch(u16Key_buff1)
  {
    case _DEF_BIT0 :  //  Single Pulse Select
        KEY_BUFF1 &= ~(_DEF_BIT0) ; 
        selected_apr_load(1U) ;  
        Level_data_output();
        Send_Shot_data_cmd(IPL_volt_data,0U,0U); 
        break ;
    case _DEF_BIT1 :
        KEY_BUFF1 &= ~(_DEF_BIT1) ; 
        selected_apr_load(2U) ;  
        Level_data_output();
        Send_Shot_data_cmd(IPL_volt_data,0U,0U); 
        break ;
    case _DEF_BIT2 :
        KEY_BUFF1 &= ~(_DEF_BIT2) ; 
        selected_apr_load(3U) ;  
        Level_data_output();
        Send_Shot_data_cmd(IPL_volt_data,0U,0U); 
        break ;
    case _DEF_BIT3 :
        KEY_BUFF1 &= ~(_DEF_BIT3) ; 
        selected_apr_load(4U) ;  
        Level_data_output();
        Send_Shot_data_cmd(IPL_volt_data,0U,0U); 
        break ;

    case _DEF_BIT4 :  // Counter Clear
        KEY_BUFF1 &= ~(_DEF_BIT4) ; 
        if(Is_Not_running_flag)  
        {
          CURRENT_COUNT_HI = 0U ; 
          CURRENT_COUNT_LO = 0U ;
          dwin_word2_write(CURRENT_COUNT_HI_ADD) ; 
        }
        break ;

    case _DEF_BIT5 :  //  
        KEY_BUFF1 &= ~(_DEF_BIT5) ; 
        if(Is_Cool_btn_set_flag) {
          Basic_Graphic(0x0720,344,525,344+116,525+67,10);
          COOL_DRIVER_DIS ;
          Cool_btn_set_flag_off ;
        }
        else {
          Basic_Graphic(0x0720,344,525,344+116,525+67,14);
          COOL_DRIVER_EN ;
          Cool_btn_set_flag_on ;   
        }
        break ;

    case _DEF_BIT6 :  //  Ready
        KEY_BUFF1 &= ~(_DEF_BIT6) ; 
        if(Is_Ready_btn_set_flag) {  // ready to standby  
          Basic_Graphic(0x0730,544,510,544+234,510+89,10);
          Ready_btn_set_flag_off ; 
        }
        else {  // stand by to ready ..  
          if(Is_Not_running_flag) { 
            //
            Basic_Graphic(0x0730,544,510,544+234,510+89,14);
            Ready_btn_set_flag_on ; 
            //
            Level_data_output();
            Send_Shot_data_cmd(IPL_volt_data,0,0); 
            delay_ms(10);  
          }
        }
        break ;

    case _DEF_BIT7 :  //  Information Screen
        KEY_BUFF1 &= ~(_DEF_BIT7) ; // key flag clear  
        if(Is_Not_Ready_btn_set_flag) 
        {
          if(Is_Not_running_flag)  
          {
            prev_screen = current_screen;
            current_screen = SCR_INFO; 
          }
        }
        break;
    case _DEF_BIT8 :   // setup Screen
        bitClear(KEY_BUFF1,8U); // key flag clear  
        if(Is_Not_running_flag)  
        {
          for(u8i=0U; u8i<5U; u8i++) 
          {
              delay_ms(300) ;
              if(bitRead(KEY_BUFF1,8U) == 0x00U) { break ; }
              bitClear(KEY_BUFF1,8U); // key flag clear  
          }
          //
          if(u8i == 5U)
          {
            prev_screen = current_screen;
            current_screen = SCR_COUNT_SERIAL;
          }
          else { bitClear(KEY_BUFF1,8U); }
        }
        break;

    case _DEF_BIT9 :   //  select screen
        bitClear(KEY_BUFF1,9U);  
        if(Is_Not_Ready_btn_set_flag)
        {
          if(Is_Not_running_flag) 
          {
              prev_screen = current_screen;
              current_screen = SCR_MODE_SELECT;
              Send_Simmer_off_cmd() ;
          }
        }
        break;
    case _DEF_BIT10 :   //  select screen  
        bitClear(KEY_BUFF1,10U); 
        if(Is_Not_Ready_btn_set_flag)
        {
          if(Is_Not_running_flag) 
          {
            prev_screen = current_screen;
            current_screen = SCR_MODE_SELECT;  
            Send_Simmer_off_cmd() ;
          }
        }
        break; 

    case _DEF_BIT11 :   // Cali .
        bitClear(KEY_BUFF1,11U); 
        if(Is_Not_Ready_btn_set_flag)
        {
          if(Is_Not_running_flag) 
          {
            for(u8i=0U; u8i<5U; u8i++) 
            {
                delay_ms(300) ;
                if(bitRead(KEY_BUFF1,11U) == 0x00U) { break ; }
                bitClear(KEY_BUFF1,11U); // key flag clear  
            }
            //
            if(u8i == 5U)
            {
              prev_screen = current_screen;
              current_screen = SCR_CALI;
            }
            else { bitClear(KEY_BUFF1,11U); } 
            }
        }
        break; 
  }
  //
  if(Is_Not_Ready_btn_set_flag)
  {
    if(u16Key_buff2 > 0U)
    {
      switch(u16Key_buff2)
      {
        case _DEF_BIT0 :  // level down
            bitClear(KEY_BUFF2,0U);
            if(level_data <= LEVEL_DAT_MIN) { level_data = LEVEL_DAT_MIN  ; }
            else { level_data-- ;  }
            apr_data_save(select_filter,select_pulse_type,&dur_ptr,&level_data); 
            FLUENCE_VALUE = Level_to_Flu_cal(select_pulse_type,dur_ptr,level_data) ;
            Level_data_output();
            Send_Shot_data_cmd(IPL_volt_data,0,0); 
            break ;

        case _DEF_BIT1 :  // level Up
            bitClear(KEY_BUFF2,1U);
            if(level_data >= LEVEL_DAT_MAX) { level_data = LEVEL_DAT_MAX  ; }
            else { level_data++ ;  }
            apr_data_save(select_filter,select_pulse_type,&dur_ptr,&level_data); 
            FLUENCE_VALUE = Level_to_Flu_cal(select_pulse_type,dur_ptr,level_data) ;
            Level_data_output();
            Send_Shot_data_cmd(IPL_volt_data,0,0); 
            break;

        case _DEF_BIT2 :  //  
            bitClear(KEY_BUFF2,2U);
            dur_ptr_limit_check(select_pulse_type,'d',&dur_ptr);
            DURATION_VALUE = dur_data_load(select_pulse_type,dur_ptr);
            apr_data_save(select_filter,select_pulse_type,&dur_ptr,&level_data); 
            //if(DURATION_VALUE <= DURATION_MIN) DURATION_VALUE = DURATION_MIN ;
            //else DURATION_VALUE-- ; 
            break;
        case _DEF_BIT3 :  //  
            bitClear(KEY_BUFF2,CAL_DATA_32);
            dur_ptr_limit_check(select_pulse_type,'u',&dur_ptr);
            DURATION_VALUE = dur_data_load(select_pulse_type,dur_ptr);
            apr_data_save(select_filter,select_pulse_type,&dur_ptr,&level_data); 
            //if(DURATION_VALUE >=  DURATION_MAX ) DURATION_VALUE = DURATION_MAX ;
            //else DURATION_VALUE++ ; 
            break;
      }
    }
  }
}

// ---------------------------------------------------------------------------
// System 
// ---------------------------------------------------------------------------
//
void system_interlock_check(void)
{
  if(Is_INTERLOCK_ON) { 
    system_interlock_flag_on ;
    w_interlock_flag_on ;
  }
  else  {
    system_interlock_flag_off ; 
    w_interlock_flag_off ; 
    system_warning = 1U ;
  } 
}
void water_flow_on_main(void)
{
  water_flow_on_timer = 0U ;
  water_flow_on_flag_on ;
}
void Water_flow_Check(void) 
{
  if(Is_RPM_SW_ON) 
  {
      w_water_flow_flag_off ;   // Water Flow Sensor OK
  }
  else
  {
    w_water_flow_flag_on ;      // Water Flow Sensor Error
    laser_hw_error_off();  
    //
    while(1)
    { 
        Head_error_msg_dis(2);
        //
        if(Is_RPM_SW_ON)  { break ; }
    }
    w_water_flow_flag_off ;
  } 
}
void InterLock_Check(void) 
{
  if(Is_INTERLOCK_ON) 
  {
      w_interlock_flag_off ; 
  }
  else 
  {
    w_interlock_flag_on ;   
    laser_hw_error_off();            
    //
    while(1){ 
        
        Head_error_msg_dis(6);
        //
        if(Is_INTERLOCK_ON) {  break ; }
    }
    w_interlock_flag_off ;  
  }
}
void DT_Temp_Check(void) 
{
    /*
    if((DT_TEMP_VALUE >= DT_TEMP_MIN ) && 
        (DT_TEMP_VALUE <= DT_TEMP_MAX )) {
        w_temp_sensor_flag_off ; 
        return ;   
    }
    //
    w_temp_sensor_flag_on ;   
    laser_hw_error_off();            
    //
    while(1){ 
        
        Head_error_msg_dis(3);
        //
        if((DT_TEMP_VALUE >= DT_TEMP_MIN ) && 
        (DT_TEMP_VALUE <= DT_TEMP_MAX ))   break ;
    }
    w_temp_sensor_flag_off ; 
    */ 

}
void ST_Temp_Check(void) 
{
    /*
    if(ST_TEMP_VALUE <=(ST_TEMP_SV_MAX * 10)) {
        w_cool_temp_flag_off ; 
        return ;   
    }
    //
    w_cool_temp_flag_on ;   
    laser_hw_error_off();            
    //
    while(1){ 
        
        Head_error_msg_dis(4);
        //
        if(ST_TEMP_VALUE <=(ST_TEMP_SV_MAX * 10))  break ;
    }
    w_cool_temp_flag_off ; 
    */
    if(ST_TEMP_VALUE <= (ST_TEMP_SV_MAX * 10U)) { w_cool_temp_flag_off ; }
    else  { w_cool_temp_flag_on ; }
  
}
//  Buzzer on & Temp Error Msg blinking... 
void temp_sensor_er_msg(void)
{ 
  // 
  if(Is_w_st_temp_flag) 
  {
    if(Is_Not_Temp_er_msg_on_flag) 
    {         
      head_msg_display(4U); 
      bz_timer = 50U ;   
      buzzer_on_flag_on ; 
      Temp_er_msg_on_flag_on ; 
    }
  }
  else
  {
    if(Is_Temp_er_msg_on_flag) 
    { 
      head_msg_display(99U); 
      Temp_er_msg_on_flag_off ; 
    }
  } 
}
//  Buzzer on & Head Error Msg blinking... 
void Head_error_msg_dis(uint8_t u8ErrorCode)
{
  head_msg_display(u8ErrorCode); 
  bz_timer = 50U ;   
  buzzer_on_flag_on ;
  delay_ms(300U) ;
  head_msg_display(99U); 
  delay_ms(200U) ;
}
// Laser HW Error Off
void laser_hw_error_off(void)
{
  // laser off
  if(Is_running_flag) 
  {
    running_flag_off ; 
    if(Is_count_save_flag) 
    {
      count_save_flag_off ; 
      counter_eeprom_data_save();
    }
    head_msg_display(0) ;   // laser out display .. 
  } 
  // ready off
  Basic_Graphic(0x0590U, 0x25BU, 0x0203U, 0x0320U, 0x0249U, 0x0002U);
  Ready_btn_set_flag_off ; 
  level_old_data = 0U ;  // da restarting...
}

// st is hand temp sensor
void st_cool_control(void) 
{
  // auto cooling.... but manual cooling....so not Used  
  // St temp check routine .....
  if(ST_TEMP_VALUE > (ST_TEMP_SV_MAX * 10U)) { w_st_temp_flag_on ; }
  else if(ST_TEMP_VALUE < (ST_TEMP_SV_MIN * 10U)) { w_st_temp_flag_on ; }
  else { w_st_temp_flag_off ; }

  /*
    if(ST_TEMP_VALUE > (ST_TEMP_SV_MAX*10)) { 
        if(Is_Cool_btn_set_flag) return ;
        COOL_DRIVER_EN ;
        Basic_Graphic(0x0580,0x012d,0x0207,0x01f2,0x024d,0x0002);
        Cool_btn_set_flag_on ; 
    }   
    else if(ST_TEMP_VALUE < (ST_TEMP_SV_MIN*10) ) { 
        if(Is_Not_Cool_btn_set_flag) return ;
        COOL_DRIVER_DIS ; 
        Basic_Graphic(0x0580,0x012d,0x0207,0x01f2,0x024d, 0x0021) ;
        Cool_btn_set_flag_off ;  
    }
  */
}
static void HW_system_error_check(void)
{
    if(Is_w_cool_temp_flag)          error_code = 1U;  // DT_SENSOR
    else if(Is_w_water_flow_flag)    error_code = 2U;  // water flow
    else if(Is_w_interlock_flag)     error_code = 3U;  // interlock
    //
    while(error_code > 0U) 
    {
        send_set_screen(error_code + 33U) ;
        while(1) ;
    }

}
// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
void cbAP_Timer0(void)
{
  static uint8_t time_counter = 0U ; 
  //
  system_interlock_check();

  time_counter = (time_counter + 1U) % 10U ;

  if(time_counter == 0U)
  {
    read_adc(1);
  }
  else if(time_counter == 1U)
  {
    ST_TEMP_VALUE = temp_cal(ADCGetData(1))  ;
  }
  else if(time_counter == 3) 
  { 
    read_adc(3) ; 
  }
  else if(time_counter == 4) 
  {
    DT_TEMP_VALUE = temp_cal(ADCGetData(3)) / 10U;  
  }
  else if(time_counter == 5) 
  {
    if(Is_HP_FILTER_OK) { w_filter_flag_on ; }
    else                { w_filter_flag_off ; }
  }
  else if(time_counter == 6) 
  {
    if(Is_HP_CONNECT_SW_ON) { w_hd_ok_flag_on ; }
    else                    { w_hd_ok_flag_off ; }
  }
  else if(time_counter == 7)  // RUN / FOOT s/w check...
  {  
    if(Is_RUN_SW_ON)
    {
      if(Is_Not_IPL_pulse_end_S_flag)
      {
        key_in_counter++ ;
        if(key_in_counter > 5U)
        {
          key_in_counter = 0U;
          bitSet(key_in_flag_valus,0U) ;  // flag set ..
          IPL_pulse_end_S_flag_off ;
          IPL_pulse_end_E_flag_off ;
          pulse_end_counter = RUN_SW_DELAY_TIME ;
        }
      }
      else { pulse_end_counter = RUN_SW_DELAY_TIME ; }
    }
    else
    {
      key_in_counter = 0U;
      bitClear(key_in_flag_valus,0U) ;  // flag clear ..
      if(Is_Not_IPL_pulse_end_E_flag)
      {
        if(Is_Not_IPL_pulse_end_S_flag)
        {
           IPL_pulse_end_S_flag_on ;
        }
      }
    }
  }
  else if(time_counter == 9)  // RUN / FOOT s/w check...
  {
    if(Is_running_flag) { cool_sec_time = 0U; }
    if(Is_Cool_btn_set_flag)
    {
      if(++cool_sec_time >= COOL_SEC_TIME_MAX )
      {
        COOL_DRIVER_DIS ;
        cool_sec_time = 0U ; 
        Cool_off_flag_on ;
      }
      else { COOL_DRIVER_EN ; }
    }
  }
  // -------------------------------------------------------------------------------
  if(Is_Not_IPL_pulse_end_E_flag) 
  { 
    if(Is_IPL_pulse_end_S_flag)
    {
        if(--pulse_end_counter == 0x00U) 
        {
            IPL_pulse_end_S_flag_off ;
            IPL_pulse_end_E_flag_on ;
        }
    }
  }
  // ST temp < -3'C off  
  if(Is_Cool_btn_set_flag) 
  {
    if((signed int)ST_TEMP_VALUE <  -50)  { COOL_DRIVER_DIS ; }
    if((signed int)ST_TEMP_VALUE >=   0)  { COOL_DRIVER_EN ; }
  }
  // Water flow check ...
  if(Is_water_flow_on_flag) {   // waitting for water_flow start time end! 
    water_flow_on_timer++ ;
    if(water_flow_on_timer > 3000U) 
    {
        water_flow_on_timer = 0 ; 
        water_flow_check_flag_on ;
    }
  }
  if(Is_water_flow_check_flag) // check water_flow 
  {
    if(Is_RPM_SW_ON) w_water_flow_flag_off ;
    else w_water_flow_flag_on ;
  }
  // Buzzer Control ....
  if(Is_Not_buzzer_mask_flag) 
  {   
    if(Is_buzzer_on_flag) {
      BUZZER_ON ;   
      //
      if(--bz_timer == 0x00U) 
      {
          BUZZER_OFF ;
          buzzer_on_flag_off ;
      }
    }
    else  BUZZER_OFF ;    
  }
  else BUZZER_OFF ;
}
// ---------------------------------------------------------------------------
//  Define Interrup Callbacks definitions.
// ---------------------------------------------------------------------------
//
// --------------------------------------------------
// Timer1 output compare A interrupt service routine
//  
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
    // Place your code here
    IPL_trg_funct_set() ;
}
// --------------------------------------------------
// Timer2 output compare interrupt service routine
// --------------------------------------------------

interrupt [TIM2_COMP] void timer2_comp_isr(void)
{
    // Place your code here 
    //
    if(Is_running_flag) 
    {
        if(++IPL_interval_counter >= 3000U)  // IPL OUTPUT INTERVAL 
        {  
          bitClear(TIMSK,1U) ;      // timer 0 disable     
          Pulse_data_ptr = 0U ;   
          IPL_trg_funct_set() ; 
          IPL_interval_counter = 0U ;
        }
    }
    else IPL_interval_counter = 0U ; 
    //
}
//
// ---------------------------------------------------------------------------
// Not used Function 
// ---------------------------------------------------------------------------
//
static void Cali_Data_offset(uint8_t u8Mode)
{
  uint8_t u8i = 0U ;

  if(u8Mode == 1U) // up
  {                     
    for(u8i=CAL_BASE_ADD; u8i<(31U+CAL_BASE_ADD); u8i++)
    {
      PLC_DATA[u8i]++;  
      if(PLC_DATA[u8i] > IPL_VOLT_MAX) PLC_DATA[u8i] = IPL_VOLT_MAX ; 
      set_value(u8i, PLC_DATA[u8i]);
    }
  }
  else // down
  {
    for(u8i=CAL_BASE_ADD ; u8i<(31U+CAL_BASE_ADD); u8i++)
    {
      PLC_DATA[u8i]--;
      if(PLC_DATA[u8i] < IPL_VOLT_MIN) PLC_DATA[u8i] = IPL_VOLT_MIN ; 
      set_value(u8i, PLC_DATA[u8i]);
    }
  }
}
#pragma used-

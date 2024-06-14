/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ]  MEMORY.c
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


/* Define Includes */
#include "APR_EEPROM.h"
#include "At24c256.h"
 
// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
//  Define Constants.
// ---------------------------------------------------------------------------
//
//   EP_HEAD_DUR , Level 
const uint16_t F510_D_PTR[]  =  { 5, 5, 5, 5} ; 
const uint16_t F510_level[]  =  { 5, 5, 5, 5} ;  
//
const uint16_t F560_D_PTR[]  =  { 5, 5, 5, 5} ; 
const uint16_t F560_level[]  =  { 5, 5, 5, 5} ;  
//
const uint16_t F585_D_PTR[]  =  { 5, 5, 5, 5} ; 
const uint16_t F585_level[]  =  { 5, 5, 5, 5} ; 
//
const uint16_t F640_D_PTR[]  =  { 5, 5, 5, 5} ; 
const uint16_t F640_level[]  =  { 5, 5, 5, 5} ; 
//
const uint16_t F700_D_PTR[]  =  { 5, 5, 5, 5} ; 
const uint16_t F700_level[]  =  { 5, 5, 5, 5} ;  

const uint16_t F800_D_PTR[]  =  { 5, 5, 5, 5} ; 
const uint16_t F800_level[]  =  { 5, 5, 5, 5} ; 

const uint16_t F900_D_PTR[]  =  { 5, 5, 5, 5} ; 
const uint16_t F900_level[]  =  { 5, 5, 5, 5} ;  
// 510mm 
flash const uint16_t level_mfr_data_tbl1[32]  = {150,154,158,162,167,171,175,180,
                                            185,190,196,202,207,213,219,225,
                                            230,235,240,245,250,255,260,265,
                                            270,271,273,274,276,278,280,280} ; 
// 560mm
flash const uint16_t level_mfr_data_tbl2[32] = {150,154,158,162,167,171,175,180,
                                            185,190,196,202,207,213,219,225,
                                            230,235,240,245,250,255,260,265,
                                            270,271,273,274,276,278,280,280} ;
// 585mm
flash const uint16_t level_mfr_data_tbl3[32] = {150,154,158,162,167,171,175,180,
                                            185,190,196,202,207,213,219,225,
                                            230,235,240,245,250,255,260,265,
                                            270,271,273,274,276,278,280,280} ; 
// 640mm                                            
flash const uint16_t level_mfr_data_tbl4[32] = {150,154,159,164,170,178,185,192,
                                            196,203,210,217,224,231,238,245,
                                            248,254,261,268,274,281,288,295,
                                            300,303,306,309,313,316,320,320} ;
// 700mm
flash const uint16_t level_mfr_data_tbl5[32] ={ 150,156,162,168,175,181,187,194,
                                            200,206,213,219,225,232,238,245,
                                            251,257,263,269,276,281,287,293,
                                            299,305,311,317,323,329,336,336 } ;   
// 800mm
flash const uint16_t level_mfr_data_tbl6[32] ={ 150,156,162,168,175,181,187,194,
                                            200,206,213,219,225,232,238,245,
                                            251,257,263,269,276,281,287,293,
                                            299,305,311,317,323,329,336,336 } ; 
// 900mm
flash const uint16_t level_mfr_data_tbl7[32] ={ 150,156,162,168,175,181,187,194,
                                            200,206,213,219,225,232,238,245,
                                            251,257,263,269,276,281,287,293,
                                            299,305,311,317,323,329,336,336 } ; 
const uint16_t co_st_tbl[]={0, 30, 0 } ; 
// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
extern uint16_t PLC_DATA[100] ;

#define E_CURRENT_SCREEN          PLC_DATA[0]
#define E_DURATION_VALUE          PLC_DATA[1]
#define E_FLUENCE_VALUE           PLC_DATA[2]
#define E_FILTER_VALUE            PLC_DATA[3]
#define E_ST_TEMP_VALUE           PLC_DATA[4]
#define E_DT_TEMP_VALUE           PLC_DATA[5]
#define E_CURRENT_COUNT           PLC_DATA[6] //  
#define E_CURRENT_COUNT_HI        PLC_DATA[6] //   
#define E_CURRENT_COUNT_LO        PLC_DATA[7] //
#define E_ST_TEMP_SV_MIN          PLC_DATA[8]
#define E_ST_TEMP_SV_MAX          PLC_DATA[9]
#define E_ST_TEMP_OFFSET          PLC_DATA[10]  
//

#define E_TOTAL_COUNT             PLC_DATA[11]  
#define E_TOTAL_COUNT_HI          PLC_DATA[11] 
#define E_TOTAL_COUNT_LO          PLC_DATA[12] 
#define E_LAMP_COUNT              PLC_DATA[13]
#define E_LAMP_COUNT_HI           PLC_DATA[13]
#define E_LAMP_COUNT_LO           PLC_DATA[14]
//
#define E_SERIAL_YY               PLC_DATA[0x15]
#define E_SERIAL_MM               PLC_DATA[0x16]
#define E_SERIAL_DD               PLC_DATA[0x17]
#define E_SERIAL_NO               PLC_DATA[0x18]
//
#define E_PASSWORD                PLC_DATA[30] // check address
#define E_VER                     PLC_DATA[0x32] //
//
#define E_F510_COUNT_HI           PLC_DATA[0x40]
#define E_F510_COUNT_LO           PLC_DATA[0x41]
#define E_F560_COUNT_HI           PLC_DATA[0x42]
#define E_F560_COUNT_LO           PLC_DATA[0x43]
#define E_F585_COUNT_HI           PLC_DATA[0x44]
#define E_F585_COUNT_LO           PLC_DATA[0x45]
#define E_F640_COUNT_HI           PLC_DATA[0x46]
#define E_F640_COUNT_LO           PLC_DATA[0x47]
#define E_F700_COUNT_HI           PLC_DATA[0x48]
#define E_F700_COUNT_LO           PLC_DATA[0x49] // 73
#define E_F800_COUNT_HI           PLC_DATA[0x4A]
#define E_F800_COUNT_LO           PLC_DATA[0x4B] // 75
#define E_F900_COUNT_HI           PLC_DATA[0x4C]
#define E_F900_COUNT_LO           PLC_DATA[0x4D] // 77

uint16_t FILTER_Backup_data ;
uint16_t OPTION_Backup_data ;  // Bit 0  is Buzzer Mask
// ---------------------------------------------------------------------------
// Define private function definitions.
// ---------------------------------------------------------------------------
//
static uint16_t get_APR_Address(uint8_t u8Filter, uint16_t u16PulseType) ;
static void save_Duty_Level(uint16_t u16Add,flash uint16_t *pSrcBuff1,flash uint16_t *pSrcBuff2); 
// ---------------------------------------------------------------------------
// Define Public function definitions.
// ---------------------------------------------------------------------------
//
uint8_t eeprom_data_load(void)
{
    E_PASSWORD = At24c_Read_2Bytes(EP_PASSWORD) ; 
    // 
    E_ST_TEMP_SV_MIN = At24c_Read_2Bytes(EP_ST_TEMP_SV_MIN) ;
    E_ST_TEMP_SV_MAX = At24c_Read_2Bytes(EP_ST_TEMP_SV_MAX) ; 

    E_ST_TEMP_OFFSET = At24c_Read_2Bytes(EP_ST_TEMP_OFFSET) ;
    //
    E_TOTAL_COUNT_HI = At24c_Read_2Bytes(EP_TOTAL_COUNT_HI) ;  
    E_TOTAL_COUNT_LO = At24c_Read_2Bytes(EP_TOTAL_COUNT_LO) ;
    E_LAMP_COUNT_HI = At24c_Read_2Bytes(EP_LAMP_COUNT_HI) ; 
    E_LAMP_COUNT_LO = At24c_Read_2Bytes(EP_LAMP_COUNT_LO) ;
    //
    E_F510_COUNT_HI = At24c_Read_2Bytes(EP_F510_COUNT_HI) ;           
    E_F510_COUNT_LO = At24c_Read_2Bytes(EP_F510_COUNT_LO) ;          
    E_F560_COUNT_HI = At24c_Read_2Bytes(EP_F560_COUNT_HI) ;        
    E_F560_COUNT_LO = At24c_Read_2Bytes(EP_F560_COUNT_LO) ;          
    E_F585_COUNT_HI = At24c_Read_2Bytes(EP_F585_COUNT_HI) ;        
    E_F585_COUNT_LO = At24c_Read_2Bytes(EP_F585_COUNT_LO) ;           
    E_F640_COUNT_HI = At24c_Read_2Bytes(EP_F640_COUNT_HI) ;            
    E_F640_COUNT_LO = At24c_Read_2Bytes(EP_F640_COUNT_LO) ;          
    E_F700_COUNT_HI = At24c_Read_2Bytes(EP_F700_COUNT_HI) ;           
    E_F700_COUNT_LO = At24c_Read_2Bytes(EP_F700_COUNT_LO) ;   
    E_F800_COUNT_HI = At24c_Read_2Bytes(EP_F800_COUNT_HI) ;           
    E_F800_COUNT_LO = At24c_Read_2Bytes(EP_F800_COUNT_LO) ;  
    E_F900_COUNT_HI = At24c_Read_2Bytes(EP_F900_COUNT_HI) ;           
    E_F900_COUNT_LO = At24c_Read_2Bytes(EP_F900_COUNT_LO) ;     
    // 
    E_SERIAL_YY = At24c_Read_2Bytes(EP_SERIAL_YY) ;
    E_SERIAL_MM = At24c_Read_2Bytes(EP_SERIAL_MM) ;       
    E_SERIAL_DD = At24c_Read_2Bytes(EP_SERIAL_DD) ;
    E_SERIAL_NO = At24c_Read_2Bytes(EP_SERIAL_NO) ;
    //
    FILTER_Backup_data = At24c_Read_2Bytes(EP_APR_BACKUP) ; 
    OPTION_Backup_data = At24c_Read_2Bytes(EP_SYS_OPTION) ;
    //
    return ((uint8_t)FILTER_Backup_data) ;
}
// ---------------------------------------------------------------------------
//   
// --------------------------------------------------------------------------- 
//
// Eeprom data init ....
//
void eeprom_data_save(void)
{
  if(At24c_Read_2Bytes(EP_HAED) != 0xf4f6) 
  {
    save_Duty_Level(EP_F510_P_APR_BASE,F510_D_PTR,F510_level) ;
    save_Duty_Level(EP_F560_P_APR_BASE,F560_D_PTR,F560_level) ;
    save_Duty_Level(EP_F585_P_APR_BASE,F585_D_PTR,F585_level) ;
    save_Duty_Level(EP_F640_P_APR_BASE,F640_D_PTR,F640_level) ;
    save_Duty_Level(EP_F700_P_APR_BASE,F700_D_PTR,F700_level) ;
    save_Duty_Level(EP_F800_P_APR_BASE,F800_D_PTR,F800_level) ;
    save_Duty_Level(EP_F900_P_APR_BASE,F900_D_PTR,F900_level) ;
    //
    At24c_Write_2Bytes( EP_F510_PULSE,0x01U);
    At24c_Write_2Bytes( EP_F560_PULSE,0x02U);
    At24c_Write_2Bytes( EP_F585_PULSE,0x03U);
    At24c_Write_2Bytes( EP_F640_PULSE,0x04U);
    At24c_Write_2Bytes( EP_F700_PULSE,0x01U);
    At24c_Write_2Bytes( EP_F800_PULSE,0x02U);
    At24c_Write_2Bytes( EP_F900_PULSE,0x03U);
    //
    At24c_Write_2Bytes(EP_PASSWORD,2820U) ;
    At24c_Write_2Bytes(EP_HAED,0xF4F6U) ; 
    // 
    E_TOTAL_COUNT_HI  =  0x00U ;
    E_TOTAL_COUNT_LO  =  0x00U ;
    E_LAMP_COUNT_HI   =  0x00U ;
    E_LAMP_COUNT_LO   =  0x0U ;
    //
    E_F510_COUNT_HI   = 0x00U ;           
    E_F510_COUNT_LO   = 0x00U ;          
    E_F560_COUNT_HI   = 0x00U ;        
    E_F560_COUNT_LO   = 0x00U ;          
    E_F585_COUNT_HI   = 0x00U ;        
    E_F585_COUNT_LO   = 0x00U ;           
    E_F640_COUNT_HI   = 0x00U ;            
    E_F640_COUNT_LO   = 0x00U ;          
    E_F700_COUNT_HI   = 0x00U ;           
    E_F700_COUNT_LO   = 0x00U ;  
    E_F800_COUNT_HI   = 0x00U ;           
    E_F800_COUNT_LO   = 0x00U ; 
    E_F900_COUNT_HI   = 0x00U ;           
    E_F900_COUNT_LO   = 0x00U ; 
    //
    counter_eeprom_data_save();
    E_SERIAL_YY = 24U ;  
    E_SERIAL_MM = 6U ;
    E_SERIAL_DD = 25U ;
    E_SERIAL_NO = 1U ;
    eeprom_serial_save(); 
    //
    st_temp_mfr_save_eeprom();  
    level_data_mfr_save_eeprom(); 
    apr_flag_eeprom_save(1);  
  }
}
//
void apr_data_load(uint8_t u8Filter, uint16_t u16Pulse_Type,uint8_t *pDurPtr,uint16_t *pLevel) 
{
    uint16_t u16Add ;
    // ---------------------------------------------------------
    u16Add = get_APR_Address(u8Filter,u16Pulse_Type);
    
    pDurPtr[0] = (uint8_t)At24c_Read_2Bytes(u16Add) ;
    pLevel[0]  = At24c_Read_2Bytes(u16Add+2) ;  
}
/**
 * @brief Duty ptr & level save in Filter & Pulse Type eeprom address
 * 
 * @param u8Filter 
 * @param u16Pulse_Type 
 * @param pDurPtr 
 * @param pLevel 
 */
void apr_data_save(uint8_t u8Filter, uint16_t u16Pulse_Type,uint8_t *pDurPtr,uint16_t *pLevel) 
{
    uint16_t u16Add ;
    //
    u16Add = get_APR_Address(u8Filter,u16Pulse_Type);
    //
    At24c_Write_2Bytes(u16Add + 0,pDurPtr[0]) ;
    At24c_Write_2Bytes(u16Add + 2,pLevel[0]) ;
}
// ---------------------------------------------------------------------------
//   
// --------------------------------------------------------------------------- 
//
void temp_sv_eeprom_data_save(void)
{
    At24c_Write_2Bytes(EP_ST_TEMP_SV_MIN,E_ST_TEMP_SV_MIN) ;  
    At24c_Write_2Bytes(EP_ST_TEMP_SV_MAX,E_ST_TEMP_SV_MAX) ; 
    At24c_Write_2Bytes(EP_ST_TEMP_OFFSET,E_ST_TEMP_OFFSET) ;
}
void st_temp_mfr_save_eeprom(void)
{
    E_ST_TEMP_SV_MIN = co_st_tbl[0] ;
    E_ST_TEMP_SV_MAX = co_st_tbl[1] ;
    E_ST_TEMP_OFFSET = co_st_tbl[2] ;
    // 
    At24c_Write_2Bytes(EP_ST_TEMP_SV_MIN,E_ST_TEMP_SV_MIN) ;  
    At24c_Write_2Bytes(EP_ST_TEMP_SV_MAX,E_ST_TEMP_SV_MAX) ; 
    At24c_Write_2Bytes(EP_ST_TEMP_OFFSET,E_ST_TEMP_OFFSET) ;
}
void counter_eeprom_data_save(void)
{
    At24c_Write_2Bytes(EP_TOTAL_COUNT_HI,E_TOTAL_COUNT_HI) ;  
    At24c_Write_2Bytes(EP_TOTAL_COUNT_LO,E_TOTAL_COUNT_LO) ; 
    At24c_Write_2Bytes(EP_LAMP_COUNT_HI,E_LAMP_COUNT_HI) ;  
    At24c_Write_2Bytes(EP_LAMP_COUNT_LO,E_LAMP_COUNT_LO) ;  
    //
    At24c_Write_2Bytes(EP_F510_COUNT_HI,E_F510_COUNT_HI) ;           
    At24c_Write_2Bytes(EP_F510_COUNT_LO,E_F510_COUNT_LO) ;          
    At24c_Write_2Bytes(EP_F560_COUNT_HI,E_F560_COUNT_HI) ;        
    At24c_Write_2Bytes(EP_F560_COUNT_LO,E_F560_COUNT_LO) ;          
    At24c_Write_2Bytes(EP_F585_COUNT_HI,E_F585_COUNT_HI) ;        
    At24c_Write_2Bytes(EP_F585_COUNT_LO,E_F585_COUNT_LO) ;           
    At24c_Write_2Bytes(EP_F640_COUNT_HI,E_F640_COUNT_HI) ;            
    At24c_Write_2Bytes(EP_F640_COUNT_LO,E_F640_COUNT_LO) ;          
    At24c_Write_2Bytes(EP_F700_COUNT_HI,E_F700_COUNT_HI) ;           
    At24c_Write_2Bytes(EP_F700_COUNT_LO,E_F700_COUNT_LO) ; 
    At24c_Write_2Bytes(EP_F800_COUNT_HI,E_F800_COUNT_HI) ;           
    At24c_Write_2Bytes(EP_F800_COUNT_LO,E_F800_COUNT_LO) ; 
    At24c_Write_2Bytes(EP_F900_COUNT_HI,E_F900_COUNT_HI) ;           
    At24c_Write_2Bytes(EP_F900_COUNT_LO,E_F900_COUNT_LO) ; 
}
void apr_flag_eeprom_save(FILTER_e Filter_Select)
{
    FILTER_Backup_data  = (uint16_t)Filter_Select ; 
 
    At24c_Write_2Bytes(EP_APR_BACKUP,FILTER_Backup_data) ;  
}
void T_counter_eeprom_data_save(void)
{
    At24c_Write_2Bytes(EP_TOTAL_COUNT_HI,E_TOTAL_COUNT_HI) ;  
    At24c_Write_2Bytes(EP_TOTAL_COUNT_LO,E_TOTAL_COUNT_LO) ; 
}
void L_counter_eeprom_data_save(void)
{
    At24c_Write_2Bytes(EP_LAMP_COUNT_HI,E_LAMP_COUNT_HI) ;  
    At24c_Write_2Bytes(EP_LAMP_COUNT_LO,E_LAMP_COUNT_LO) ; 
}
void F_counter_eeprom_data_save(uint8_t u8Select)
{
    //
    switch(u8Select) {
        case 1 :
                    At24c_Write_2Bytes(EP_F510_COUNT_HI,E_F510_COUNT_HI) ;           
                    At24c_Write_2Bytes(EP_F510_COUNT_LO,E_F510_COUNT_LO) ; 
                    break ;         
        case 2 :
                    At24c_Write_2Bytes(EP_F560_COUNT_HI,E_F560_COUNT_HI) ;        
                    At24c_Write_2Bytes(EP_F560_COUNT_LO,E_F560_COUNT_LO) ;
                    break ;          
        case 3 :
                    At24c_Write_2Bytes(EP_F585_COUNT_HI,E_F585_COUNT_HI) ;        
                    At24c_Write_2Bytes(EP_F585_COUNT_LO,E_F585_COUNT_LO) ; 
                    break ;          
        case 4 :
                    At24c_Write_2Bytes(EP_F640_COUNT_HI,E_F640_COUNT_HI) ;            
                    At24c_Write_2Bytes(EP_F640_COUNT_LO,E_F640_COUNT_LO) ; 
                    break ;         
        case 5 :
                    At24c_Write_2Bytes(EP_F700_COUNT_HI,E_F700_COUNT_HI) ;           
                    At24c_Write_2Bytes(EP_F700_COUNT_LO,E_F700_COUNT_LO) ; 
                    break ;
        case 6 :
                    At24c_Write_2Bytes(EP_F800_COUNT_HI,E_F800_COUNT_HI) ;           
                    At24c_Write_2Bytes(EP_F800_COUNT_LO,E_F800_COUNT_LO) ; 
                    break ; 
        case 7 :
                    At24c_Write_2Bytes(EP_F900_COUNT_HI,E_F900_COUNT_HI) ;           
                    At24c_Write_2Bytes(EP_F900_COUNT_LO,E_F900_COUNT_LO) ; 
                    break ;        
    } 
}
// ---------------------------------------------------------------------------
//   
// --------------------------------------------------------------------------- 
//
void eeprom_serial_save(void)
{
    At24c_Write_2Bytes(EP_SERIAL_YY,E_SERIAL_YY) ; 
    At24c_Write_2Bytes(EP_SERIAL_MM,E_SERIAL_MM) ;
    At24c_Write_2Bytes(EP_SERIAL_DD,E_SERIAL_DD) ;
    At24c_Write_2Bytes(EP_SERIAL_NO,E_SERIAL_NO) ;   
}
void eeprom_serial_load(void)
{
    E_SERIAL_YY = At24c_Read_2Bytes(EP_SERIAL_YY) ;
    E_SERIAL_MM = At24c_Read_2Bytes(EP_SERIAL_MM) ;       
    E_SERIAL_DD = At24c_Read_2Bytes(EP_SERIAL_DD) ;
    E_SERIAL_NO = At24c_Read_2Bytes(EP_SERIAL_NO) ; 

}
void level_data_mfr_save_eeprom(void) 
{
  At24c_FWrite_block(level_mfr_data_tbl1,EP_F510_LEVEL_TBL,32U);
  At24c_FWrite_block(level_mfr_data_tbl2,EP_F560_LEVEL_TBL,32U);
  At24c_FWrite_block(level_mfr_data_tbl3,EP_F585_LEVEL_TBL,32U);
  At24c_FWrite_block(level_mfr_data_tbl4,EP_F640_LEVEL_TBL,32U);
  At24c_FWrite_block(level_mfr_data_tbl5,EP_F700_LEVEL_TBL,32U);
  At24c_FWrite_block(level_mfr_data_tbl6,EP_F800_LEVEL_TBL,32U);
  At24c_FWrite_block(level_mfr_data_tbl7,EP_F900_LEVEL_TBL,32U);
}
void level_data_save_eeprom(uint8_t u8Select,const uint16_t * pSrcBuff)
{
    uint16_t u16Add = 0U;   
    // 
    switch(u8Select) 
    {
        case 1 :    //    
                    u16Add = EP_F510_LEVEL_TBL ; 
                    break ;  
        case 2 :    //    
                    u16Add = EP_F560_LEVEL_TBL ; 
                    break ; 
        case 3 :    //    
                    u16Add = EP_F585_LEVEL_TBL ; 
                    break ; 
        case 4 :    //    
                    u16Add = EP_F640_LEVEL_TBL ; 
                    break ; 
        case 5 :    //    
                    u16Add = EP_F700_LEVEL_TBL ; 
                    break ; 
        case 6 :    //    
                    u16Add = EP_F800_LEVEL_TBL ; 
                    break ;
        case 7 :    //    
                    u16Add = EP_F900_LEVEL_TBL ; 
                    break ;    
    } 
    //
    At24c_Write_block((const uint16_t *)pSrcBuff , u16Add, 32U) ; 
}
//
bool level_data_load_eeprom(uint8_t i_select,uint16_t * const pDesBuff)
{
  bool bRet = true ;
  uint8_t   u8i   = 0U;
  uint16_t u16Add = 0U;   
  // 
  switch(i_select) 
  {
      case 1 :    //    
                  u16Add = EP_F510_LEVEL_TBL ; 
                  break ;  
      case 2 :    //    
                  u16Add = EP_F560_LEVEL_TBL ; 
                  break ; 
      case 3 :    //    
                  u16Add = EP_F585_LEVEL_TBL ; 
                  break ; 
      case 4 :    //    
                  u16Add = EP_F640_LEVEL_TBL ; 
                  break ; 
      case 5 :    //    
                  u16Add = EP_F700_LEVEL_TBL ; 
                  break ; 
      case 6 :    //    
                  u16Add = EP_F800_LEVEL_TBL ; 
                  break ;
      case 7 :    //    
                  u16Add = EP_F900_LEVEL_TBL ; 
                  break ;    
  } 
  //
  At24c256Init(); 
  delay_ms(20);

  At24c_Read_16Bit_block(pDesBuff,u16Add,32U); 
  //
  for(u8i=0;u8i<31;u8i++) // check read Data Error !!
  {   
      if(pDesBuff[u8i] < IPL_VOLT_MIN)       pDesBuff[u8i] = IPL_VOLT_MIN ;
      else if( pDesBuff[u8i] > IPL_VOLT_MAX) pDesBuff[u8i] = IPL_VOLT_MAX ;
      //
      // Error
      bRet = false ;
  }
  return (bRet);
}
//
void sys_option_eeprom_save(void)
{
  
}
uint16_t Filter_eeprom_data_load(FILTER_e Filter_Select)
{
  uint16_t u16Add ;
  //
  if(Filter_Select == FILTER_510)        u16Add = EP_F510_PULSE  ;
  else if(Filter_Select == FILTER_560)   u16Add = EP_F560_PULSE  ; 
  else if(Filter_Select == FILTER_585)   u16Add = EP_F585_PULSE  ;  
  else if(Filter_Select == FILTER_640)   u16Add = EP_F640_PULSE  ; 
  else if(Filter_Select == FILTER_700)   u16Add = EP_F700_PULSE  ;
  else if(Filter_Select == FILTER_800)   u16Add = EP_F800_PULSE  ;
  else if(Filter_Select == FILTER_900)   u16Add = EP_F900_PULSE  ;
  else return (0x00) ;   
  //
  //select_pulse_type = At24c_Read_2Bytes(u16Add) ;
  return (At24c_Read_2Bytes(u16Add));
}
void Filter_eeprom_data_save(FILTER_e Filter_Select,uint16_t u16Data)
{
  uint16_t u16Add ;

  if(Filter_Select == FILTER_510)        u16Add = EP_F510_PULSE  ;
  else if(Filter_Select == FILTER_560)   u16Add = EP_F560_PULSE  ; 
  else if(Filter_Select == FILTER_585)   u16Add = EP_F585_PULSE  ;  
  else if(Filter_Select == FILTER_640)   u16Add = EP_F640_PULSE  ; 
  else if(Filter_Select == FILTER_700)   u16Add = EP_F700_PULSE  ;
  else if(Filter_Select == FILTER_800)   u16Add = EP_F800_PULSE  ;
  else if(Filter_Select == FILTER_900)   u16Add = EP_F900_PULSE  ;
  else return ;  
  At24c_Write_2Bytes(u16Add,u16Data) ;     
}
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//
/**
 * @brief 
 * 
 */

void save_Duty_Level(uint16_t u16Add,flash uint16_t *pSrcBuff1,flash uint16_t *pSrcBuff2)
{
  At24c_Write_2Bytes(u16Add + 0 ,pSrcBuff1[0]) ; 
  At24c_Write_2Bytes(u16Add + 2 ,pSrcBuff2[0]) ; 
  At24c_Write_2Bytes(u16Add + 4 ,pSrcBuff1[1]) ; 
  At24c_Write_2Bytes(u16Add + 6 ,pSrcBuff2[1]) ; 
  At24c_Write_2Bytes(u16Add + 8 ,pSrcBuff1[2]) ; 
  At24c_Write_2Bytes(u16Add + 10,pSrcBuff2[2]) ; 
  At24c_Write_2Bytes(u16Add + 12,pSrcBuff1[3]) ; 
  At24c_Write_2Bytes(u16Add + 14,pSrcBuff2[3]) ; 
}

uint16_t get_APR_Address(uint8_t u8Filter, uint16_t u16PulseType) 
{
  uint16_t u16Ret = 0x00U ; 
  //
  switch(u8Filter)
  {
      case 0x01U:  
                      u16Ret = EP_F510_P_APR_BASE  ;                 
                      break ;
      case 0x02U:  
                      u16Ret = EP_F560_P_APR_BASE  ;                 
                      break ;
      case 0x03U:  
                      u16Ret = EP_F585_P_APR_BASE  ;                  
                      break ; 
      case 0x04U:  
                      u16Ret = EP_F640_P_APR_BASE  ;                 
                      break ;
      case 0x05U:  
                      u16Ret = EP_F700_P_APR_BASE  ;                   
                      break ;   
      case 0x06U:  
                      u16Ret = EP_F800_P_APR_BASE  ;                   
                      break ; 
      case 0x07U:  
                      u16Ret = EP_F900_P_APR_BASE  ;                   
                      break ; 
  }  
  //
  switch(u16PulseType)
  {
      case 0x01:      // BASE Pointer
                      //                 
                      break ;
      case 0x02:  
                      u16Ret += 4;                  
                      break ;
      case 0x03:  
                      u16Ret += 8;                 
                      break ; 
      case 0x04:  
                      u16Ret += 12; ;                 
                      break ;     
  }

  return (u16Ret);
}
// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
 
/* MEMORY.c End Of File !! Well Done */

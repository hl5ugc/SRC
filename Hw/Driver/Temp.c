/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ]  Temp.c
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

#pragma used-
/* Define Includes */
#include "Temp.h"
#include "timer0_int.h"
#include "Adc.h"
 
//
#include "cli.h"
#include "uart.h"
#include "PortWrite.h"
// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//
#define TEMP_CONTROL_INTREVAL   10U // 10msec
#define TEMP_CONTROL_LOOP       5U  // 50msec
#define MAX_TEMP_DATA_TABLE     14U
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
const float TEMP_0_50_TBL[MAX_TEMP_DATA_TABLE] =
                                  { -10.0,-5.0, 0.0, 5.0,10.0,15.0,20.0,25.0, 
                                     30.0,35.0,40.0,45.0,50.0,55.0} ;
const uint16_t TEMP_0_50_LoDATA_TBL[MAX_TEMP_DATA_TABLE] =
                                  { 829,791,740,704,657,609,560,512,
                                    464,419,376,337,300,267 }; 

static signed int Temp_Data_New[MAX_TEMP_CH]    = {0,};
static signed int Temp_Data_backup[MAX_TEMP_CH] = {0,};
static signed int Temp_Data_Offset[MAX_TEMP_CH] = {0,};
 
static volatile SYSTEM_FLAG  Temp_Flag ;

static volatile uint8_t timerCbTemp = 0x00U ;
// ---------------------------------------------------------------------------
//  Define Varibales Macro.
// ---------------------------------------------------------------------------
#define Temp_Flag_Value                 Temp_Flag.valus 
//
#define Temp1_Flag_On                   Temp_Flag.bits.bit0 = 1 
#define Temp1_Flag_Off                  Temp_Flag.bits.bit0 = 0 
#define Is_Temp1_Flag                   (Temp_Flag.bits.bit0 == 1) 
#define Is_Not_Temp1_Flag               (Temp_Flag.bits.bit0 == 0)
//
#define Temp2_Flag_On                   Temp_Flag.bits.bit1 = 1 
#define Temp2_Flag_Off                  Temp_Flag.bits.bit1 = 0 
#define Is_Temp2_Flag                   (Temp_Flag.bits.bit1 == 1) 
#define Is_Not_Temp2_Flag               (Temp_Flag.bits.bit1 == 0)
// ---------------------------------------------------------------------------
// Define private function definitions.
// ---------------------------------------------------------------------------
//
static void cbTempControl(void) ; 

static void cliTemp(cli_args_t *args);
static signed int temp_cal(uint16_t temp_Data) ;
static void temp_ADC_Conversion(TEMP_CHANEL tempCH);
static void temp_Data_Update(void);
// ---------------------------------------------------------------------------
// Define Public function definitions.
// ---------------------------------------------------------------------------
//
void TempInit(void)
{
  uint8_t u8I = 0U;

  for(u8I=0; u8I<MAX_TEMP_CH; u8I++)
  {
    Temp_Data_New[u8I] = 0 ;
    Temp_Data_backup[u8I] = 0 ;
    Temp_Data_Offset[u8I] = 0 ;
  }

  #ifdef _USE_HW_TIMER0
  canSetTimer0Callback(DEF_TEMP_CB_CH,cbTempControl) ;
  #endif

  cliAdd("Temp","[1/2]",cliTemp); 
}

int16_t TempGet(TEMP_CHANEL tempCH)
{
  int16_t i16Ret = 0;

  switch(tempCH)
  {
    case ST_TEMP:
      i16Ret = Temp_Data_New[0U] ;
      break;
    case DT_TEMP:
      i16Ret = Temp_Data_New[1U] ;
      break;
    case ALL_TEMP:
      break;
  }

  return (i16Ret);
}
bool Is_TEMP_Update(TEMP_CHANEL tempCH)
{
  bool bRet = false ;

  switch(tempCH)
  {
    case ST_TEMP:
      if(Is_Temp1_Flag) bRet = true ;
      break;
    case DT_TEMP:
      if(Is_Temp2_Flag) bRet = true ;
      break;
    case ALL_TEMP:
       bRet = false ;
      break;
  }
  //
  return (bRet);
}
void Is_TEMP_UpdateClear(TEMP_CHANEL tempCH)
{
  switch(tempCH)
  {
    case ST_TEMP:
      Temp1_Flag_Off ;
      break;
    case DT_TEMP:
      Temp2_Flag_Off ;
      break;
    case ALL_TEMP:
      Temp1_Flag_Off ;
      Temp2_Flag_Off ;
      break;
  }
}

// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//
void temp_Data_Update(void)
{
  if(Temp_Data_backup[0U] != Temp_Data_New[0U])
  {
    Temp_Data_New[0U] = Temp_Data_backup[0U] ;
    Temp1_Flag_On ;
  } 

  if(Temp_Data_backup[1U] != Temp_Data_New[1U])
  {
    Temp_Data_New[1U] = Temp_Data_backup[1U] ;
    Temp2_Flag_On ;
  } 
}
/**
 * @brief Temp Chanel ADC lo Data to Temp Data Conversion
 * 
 * @param tempCH 
 */
void temp_ADC_Conversion(TEMP_CHANEL tempCH)
{
  uint16_t u16Adc_Data = 0x00U ;
  switch(tempCH)
  {
    case ST_TEMP:
      u16Adc_Data = ADCGetData((uint8_t)ST_TEMP);
      Temp_Data_backup[0U] = temp_cal(u16Adc_Data) + Temp_Data_Offset[0U];
      break;
    case DT_TEMP:
      u16Adc_Data = ADCGetData((uint8_t)DT_TEMP);
      Temp_Data_backup[1U] = temp_cal(u16Adc_Data) + Temp_Data_Offset[1U];
      break;
    case ALL_TEMP:
      u16Adc_Data = ADCGetData((uint8_t)ST_TEMP);
      Temp_Data_backup[0U] = temp_cal(u16Adc_Data) + Temp_Data_Offset[0U];
      u16Adc_Data = ADCGetData((uint8_t)DT_TEMP);
      Temp_Data_backup[1U] = temp_cal(u16Adc_Data) + Temp_Data_Offset[1U];
      break;
  }
}
/**
 * @brief ADC LoData to Temp Data Conversion Average Routine
 * 
 * @param temp_Data : ADC Lo Data
 * @return signed int : Temp data
 */
signed int temp_cal(uint16_t temp_Data) 
{
    uint8_t u8i = 0 ;
    //
    signed int i_Temp = 0 ;
    float a_Data  = 0.0 ;
    float b_Data  = 0.0 ;

    if(temp_Data >= TEMP_0_50_LoDATA_TBL[0])
    {
      i_Temp = TEMP_0_50_TBL[0] * 10 ; // under -10.0
    }
    else if(temp_Data <= TEMP_0_50_LoDATA_TBL[MAX_TEMP_DATA_TABLE-1U])
    {
      i_Temp = TEMP_0_50_TBL[MAX_TEMP_DATA_TABLE-1U] * 10 ; // under -10.0
    }
    else
    {
      for(u8i=1; u8i<MAX_TEMP_DATA_TABLE; u8i++)
      {
        if(temp_Data == TEMP_0_50_LoDATA_TBL[u8i]) 
        {
          i_Temp = TEMP_0_50_TBL[u8i] * 10 ;
        }
        else if(temp_Data > TEMP_0_50_LoDATA_TBL[u8i]) 
        {
          a_Data = 5.0/((float)TEMP_0_50_LoDATA_TBL[u8i] - (float)TEMP_0_50_LoDATA_TBL[u8i-1U]) ;
          b_Data = TEMP_0_50_TBL[u8i] - (a_Data * (float)TEMP_0_50_LoDATA_TBL[u8i]);
          i_Temp = (a_Data * (float)temp_Data + b_Data) * 10 ;
          break ;
        }
        else ;
      }
    }
  return (i_Temp);
}
// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
#ifdef _USE_HW_TIMER0  
#ifdef     DEF_TEMP_CB_CH
void cbTempControl(void) 
{
  static uint8_t Temp_Conversion_loop = 0x00U;
  static uint8_t Temp_Time_internal  = 0x00U;
  // Check Port read Interval xxmSec
  Temp_Time_internal = (Temp_Time_internal + 1U) % TEMP_CONTROL_INTREVAL ;
  if(timerCbTemp == 0x00U)
  {
    if(Temp_Time_internal == 0x00U)
    {
      //PORTC.1 ^= 1 ;
      Temp_Conversion_loop = (Temp_Conversion_loop + 1U) % TEMP_CONTROL_LOOP ; //
      switch(Temp_Conversion_loop)
      {
        case 0x01U : 
          temp_ADC_Conversion(ST_TEMP); 
          //PORTC.2 ^= 1 ;
          break;
        case 0x02U : 
          temp_ADC_Conversion(DT_TEMP); 
          //PORTC.3 ^= 1 ;
          break;   
        case 0x04U : 
          temp_Data_Update(); 
          //PORTC.4 ^= 1 ;
          break; 
      }
    }
  }
}
#endif
#endif
//
// uartflashPrintf(_DEF_UART1,"Temp Ch 0x%04X",TempGet(ST_TEMP));
// uartflashPrintf(_DEF_UART1,"\r\nTemp Ch%d = %04d",u8SelectCh,TempGet(ST_TEMP));
//
void cliTemp(cli_args_t *args)
{
  uint8_t u8Ret = 0x01U;
  uint8_t u8SelectCh = 0x00U ;
 
  if(args->argc == 1)
  {
    u8SelectCh = (uint8_t)args->getData(0) ; // ASCII DECMAL & HEX Convert to binary
    if((u8SelectCh > 0x00U) && (u8SelectCh <= MAX_TEMP_CH))
    {
      u8Ret = 0x00U ;
      if(u8SelectCh == 0x01U)
      {
        while(cliKeepLoop())
        {
          uartflashPrintf(_DEF_UART1,"\r\nTemp Ch%d = %04d",u8SelectCh,TempGet(ST_TEMP));  
          delay_ms(200);
        }
      }
      else if(u8SelectCh == 0x02U)
      {
        while(cliKeepLoop())
        {
          uartflashPrintf(_DEF_UART1,"\r\nTemp Ch%d = %04d",u8SelectCh,TempGet(DT_TEMP));  
          delay_ms(200);
        }
      }
      else
      {
        u8Ret = 0x01U ;
      }
    }
  }
  //
  if(u8Ret != 0x00)
  {
    uartMsgWrite(_DEF_UART1,"hl5ugc>> Temp [1,2] \r\n");  delay_ms(50);
  }
}

#pragma used-  /* TEMP.c End Of File !! Well Done */
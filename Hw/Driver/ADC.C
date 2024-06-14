/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ]  ADC.c
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
 * Hagseong Kang  2024-06-10    First release of this file
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
#include "ADC.h"
 
// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//
#define FIRST_ADC_INPUT     0
#define LAST_ADC_INPUT      (MAX_ADC_CH -1U) 
#define ADC_VREF_TYPE       0x40U
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
static volatile uint16_t adc_Data[MAX_ADC_CH];
static volatile uint16_t adc_All_Data[MAX_ADC_CH][9];
static volatile SYSTEM_FLAG  Adc_Flag ;
// ---------------------------------------------------------------------------
//  Define Varibales Macro.
// ---------------------------------------------------------------------------
#define adc_End_Flag_On                 Adc_Flag.bits.bit0 = 1 
#define adc_End_Flag_Off                Adc_Flag.bits.bit0 = 0 
#define Is_Adc_End_Flag                 (Adc_Flag.bits.bit0 == 1) 
#define Is_Not_Adc_End_Flag             (Adc_Flag.bits.bit0 == 0)
// ---------------------------------------------------------------------------
// Define private function definitions.
// ---------------------------------------------------------------------------
//

static void ad_data_avg(uint8_t u8AD_Index);
// ---------------------------------------------------------------------------
// Define Public function definitions.
// ---------------------------------------------------------------------------
//
void ADCInit(void)
{
  // ADC initialization
  // ADC Clock frequency: 250.000 kHz
  // ADC Voltage Reference: AREF pin
  ADMUX  = FIRST_ADC_INPUT | (ADC_VREF_TYPE & 0xFFU);
  #if (ADC_INT_ENABLE == 1)
  ADCSRA = 0xCE; 
  #else
  ADCSRA = 0x85;  // ADC Clock frequency: 500.000 kHz
  #endif
} 
/**
 * @brief Get ADC Lo data(12bits) from AVG LoData Buffer
 * 
 * @param index     : ADC Chanel
 * @return uint16_t : ADC Lo data
 */
uint16_t ADCGetData(uint8_t u8index)
{
    uint16_t u16Result = 0x00U;
    //
    if(u8index < MAX_ADC_CH)
    {
        u16Result = adc_All_Data[u8index][8] & 0x03FFU;
    }
    //
    return (u16Result);
}
/**
 * @brief   ADC Convert with index Channel and save buff & return
 * 
 * @param u8ad_index  ADC Channel
 * @return uint16_t   ADC Result Data
 */
uint16_t read_adc(uint8_t u8ad_index)
{
  uint16_t u16Ret = 0U ;
  
  if(u8ad_index < MAX_ADC_CH)
  {
    ADMUX = u8ad_index | (ADC_VREF_TYPE & 0xFFU);
    // Delay needed for the stabilization of the ADC input voltage
    delay_us(10);
    // Start the AD conversion
    ADCSRA|=0x40;
    // Wait for the AD conversion to complete
    while ((ADCSRA & 0x10)==0);
    ADCSRA|=0x10;

    u16Ret = ADCW & 0x03FFU ;
  }
  //
  adc_All_Data[u8ad_index][8] = u16Ret ;
  return (u16Ret) ;
}
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
/**
 * @brief  ADC interrupt service routine  with auto input scanning
 * @param  void
 * @return adc_data[4]
 */

interrupt [ADC_INT] void cbAdc_Isr(void)
{
    static uint8_t input_Index = 0; 
    static uint8_t u8Ptr = 0U ;
    // of the AD conversion result
    adc_Data[input_Index] = ADCW;  
    u8Ptr = input_Index ;
    // Select next ADC input
    if (++input_Index > (LAST_ADC_INPUT-FIRST_ADC_INPUT)) 
    {
        input_Index = 0;   
        adc_End_Flag_On ;   
    }
    //
    ADMUX=(FIRST_ADC_INPUT | ADC_VREF_TYPE) + input_Index;
    // Delay needed for the stabilization of the ADC input voltage
    adc_All_Data[u8Ptr][0] = adc_All_Data[u8Ptr][1] ;
    adc_All_Data[u8Ptr][1] = adc_All_Data[u8Ptr][2] ;
    adc_All_Data[u8Ptr][2] = adc_All_Data[u8Ptr][3] ;
    adc_All_Data[u8Ptr][3] = adc_All_Data[u8Ptr][4] ;
    adc_All_Data[u8Ptr][4] = adc_All_Data[u8Ptr][5] ;
    adc_All_Data[u8Ptr][5] = adc_All_Data[u8Ptr][6] ;
    adc_All_Data[u8Ptr][6] = adc_All_Data[u8Ptr][7] ;
    adc_All_Data[u8Ptr][7] = adc_Data[u8Ptr] ; 

    ad_data_avg(u8Ptr);

    //delay_us(2);
    // Start the AD conversion
    ADCSRA |= 0x40 ;
    //
}
/**
 * @brief   ADC Data Average
 * 
 * @param u8AD_Index ADC Channel
 */
static void ad_data_avg(uint8_t u8AD_Index)
{
    uint16_t u16Cal = 0U ;

    u16Cal  = adc_All_Data[u8AD_Index][0] ;
    u16Cal += adc_All_Data[u8AD_Index][1] ;
    u16Cal += adc_All_Data[u8AD_Index][2] ;
    u16Cal += adc_All_Data[u8AD_Index][3] ;
    u16Cal += adc_All_Data[u8AD_Index][4] ;
    u16Cal += adc_All_Data[u8AD_Index][5] ;
    u16Cal += adc_All_Data[u8AD_Index][6] ;
    u16Cal += adc_All_Data[u8AD_Index][8] ;
    //
    adc_All_Data[u8AD_Index][8]  = (u16Cal >> 3U) & 0x03FF ;
}
 
#pragma used-  /* ADC.c End Of File !! Well Done */
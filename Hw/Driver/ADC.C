/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ]  ADC.c
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
#include "ADC.h"
 
#include "cli.h"
#include "uart.h"
// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//
#define FIRST_ADC_INPUT     0
#define LAST_ADC_INPUT      (MAX_ADC_CH -1U) 
#define ADC_VREF_TYPE       0x00 
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
static volatile uint16_t adc_Data[LAST_ADC_INPUT - FIRST_ADC_INPUT + 1U];
static volatile uint16_t adc_All_Data[LAST_ADC_INPUT - FIRST_ADC_INPUT + 1U][9];
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
static void cliADC(cli_args_t *args);
static void adc_data_push(uint16_t * const pBuffer, uint16_t u16data);
// ---------------------------------------------------------------------------
// Define Public function definitions.
// ---------------------------------------------------------------------------
//
void ADCInit(void)
{
  // ADC initialization
  // ADC Clock frequency: 250.000 kHz
  // ADC Voltage Reference: AREF pin
  ADMUX=FIRST_ADC_INPUT | (ADC_VREF_TYPE & 0xff);
  ADCSRA=0xCE; 

  cliAdd("ADC","Select ?",cliADC);        // EEPROM MFR DATA READF
}
/**
 * @brief Get ADC Lo data(12bits) from AVG LoData Buffer
 * 
 * @param index     : ADC Chanel
 * @return uint16_t : ADC Lo data
 */
uint16_t ADCGetData(uint8_t index)
{
    uint16_t u16Result = 0x00U;

    if(index < MAX_ADC_CH)
    {
        u16Result = adc_All_Data[index][8] & 0x0FFFU;
    }

    return (u16Result);
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
    uint16_t i_Ad_Data = 0 ;

    // of the AD conversion result
    adc_Data[input_Index] = ADCW;  
    i_Ad_Data = adc_Data[input_Index] ; //
     
    adc_data_push(&adc_All_Data[input_Index][0],i_Ad_Data);
    //
    // Select next ADC input
    if (++input_Index > (LAST_ADC_INPUT-FIRST_ADC_INPUT)) 
    {
        input_Index = 0;   
        adc_End_Flag_On ;   
    }
    //
    ADMUX=(FIRST_ADC_INPUT | ADC_VREF_TYPE) + input_Index;
    // Delay needed for the stabilization of the ADC input voltage
    delay_us(10);
    // Start the AD conversion
    ADCSRA |= 0x40 ;
    //
}
//
void adc_data_push(uint16_t * const pBuffer, uint16_t u16data)
{
    pBuffer[0] = pBuffer[1];
    pBuffer[1] = pBuffer[2];
    pBuffer[2] = pBuffer[3];
    pBuffer[3] = pBuffer[4];
    pBuffer[4] = pBuffer[5];
    pBuffer[5] = pBuffer[6];
    pBuffer[6] = pBuffer[7];
    pBuffer[7] = u16data;
    //
    pBuffer[8]  = pBuffer[0] ;
    pBuffer[8] += pBuffer[1] ;
    pBuffer[8] += pBuffer[2] ;
    pBuffer[8] += pBuffer[3] ;
    pBuffer[8] += pBuffer[4] ;
    pBuffer[8] += pBuffer[5] ;
    pBuffer[8] += pBuffer[6] ;
    pBuffer[8] += pBuffer[7] ;
    //
    pBuffer[8] = pBuffer[8] >> 3U ;
}
void cliADC(cli_args_t *args)
{
    uint8_t  *u8Command  = NULL ;
    uint8_t selectNo = 0x00U;
    uint16_t *selectData = 0 ;

    //ADCSRA &= ~(1<<ADIE) ;

    if(args->argc == 1)
    {
        selectNo = (uint8_t)args->getData(0) ; // ASCII DECMAL & HEX Convert to binary

        if(selectNo < MAX_ADC_CH)
        {
            selectData = &adc_All_Data[selectNo][0];
            uartMsgByte2ASC(_DEF_UART1,"\r\nADC[",selectNo);delay_ms(10);
            uartMsgWord5DASC(_DEF_UART1,"] = ",selectData[8]); delay_ms(30);
        }
    }
    else if(args->argc == 2)
    {
        u8Command = args->getStr(0);
        if((u8Command[0U] == 'T') || (u8Command[0U] == 't'))
        {
            selectNo = (uint8_t)args->getData(1) ; // ASCII DECMAL & HEX Convert to binary
            if(selectNo < MAX_ADC_CH)
            {
                while(cliKeepLoop())
                {
                    //ADCSRA &= ~(1<<ADIE) ; // ADC Int. Disbale
                    selectData = &adc_All_Data[selectNo][0];
                    //ADCSRA |= (1<<ADIE) ;   // ADC Int. Enable
                    uartMsgByte2ASC(_DEF_UART1,"\r\nADC[",selectNo);delay_ms(10);
                    uartMsgWord5DASC(_DEF_UART1,"] = ",selectData[8]); delay_ms(150);
                }
            }
            else
            {
            uartMsgWrite(_DEF_UART1,"hl5ugc>> ADC T [1~6] \r\n");  delay_ms(50);
            }
        }
        else
        {
            uartMsgWrite(_DEF_UART1,"hl5ugc>> ADC T [1~6] \r\n");  delay_ms(50);
        }
    }
    else
    {
      uartMsgWrite(_DEF_UART1,"hl5ugc>> ADC [1~6/T]  [1~6] \r\n");  delay_ms(50);
      uartMsgWrite(_DEF_UART1,"Select Range Over!! \r\n");  delay_ms(50);
    }
    //ADCSRA |= (1<<ADIE) ;
}

#pragma used-  /* ADC.c End Of File !! Well Done */
/* --------------------------------------------------------------------------
 * [ PROJECT   ]   
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  ADC.h
 * [ Version   ]  1.0
 * [ Created   ]  2024-02-27
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
#ifndef COMMON_HW_INCLUDE_ADC_H_
#define COMMON_HW_INCLUDE_ADC_H_
/* Includes */
#include "hw_def.h"
#ifdef _USE_HW_ADC
 

// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 

// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
//
#define ADC_INT_ENABLE  HW_INTERRUPT_ENABALE
#define MAX_ADC_CH      HW_ADC_MAX_CH
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//
void ADCInit(void);

uint16_t ADCGetData(uint8_t u8index); 
uint16_t read_adc(uint8_t u8ad_index);
 
#endif 
#endif 
/* ADC.h End Of File !! Well Done */
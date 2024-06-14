/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ]  TEMP_TBL.c
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

#pragma used+
/* Define Includes */
#include "Temp_Tbl.h"
 
// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
//  Define Constants.
// ---------------------------------------------------------------------------
//
const float TEMP_0_50_TBL[14] = {   
                -10.0,-5.0,0.0, 5.0,10.0,15.0,20.0,
                 25.0,30.0,35.0,40.0, 45.0,50.0,55.0} ;
const uint16_t TEMP_0_50_DATA_TBL[14] = {
                829U,791U,740U,704U,657U,609U,560U, //  7
                512U,464U,419U,376U,337U,300U,267U };  
// ---------------------------------------------------------------------------
// Define typedef.
// --------------------------------------------------------------------------- 
// 
 
// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
// SYSTEM_FLAG  temp_flag ;
// ---------------------------------------------------------------------------
//  Define Varibales Macro.
// ---------------------------------------------------------------------------
 
// ---------------------------------------------------------------------------
// Define private function definitions.
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
// Define Public function definitions.
// ---------------------------------------------------------------------------
//
signed int temp_cal(uint16_t u16Data)
{
    signed int sRet = 0 ;
    uint8_t u8i  = 0;
    float fA_Data = 0.0f ;
    float fB_Data = 0.0f ;
    //  
    if(u16Data >= TEMP_0_50_DATA_TBL[0]) 
    {
        sRet  = TEMP_0_50_TBL[0] * 10 ;  // over
    }
    else if(u16Data <= TEMP_0_50_DATA_TBL[13]) 
    {
        sRet  = TEMP_0_50_TBL[11] * 10 ;  // over
    } 
    else
    {
        for(u8i=1; u8i<14; u8i++)
        {
            if(u16Data == TEMP_0_50_DATA_TBL[u8i]) 
            {
                sRet = TEMP_0_50_TBL[u8i] * 10 ;
                break ;
            }
            else  
            {
                if(u16Data > TEMP_0_50_DATA_TBL[u8i]) 
                {
                    fA_Data = 5.0f /((float)TEMP_0_50_DATA_TBL[u8i] -  (float)TEMP_0_50_DATA_TBL[u8i-1]) ;
                    fB_Data = TEMP_0_50_TBL[u8i] - (fA_Data * (float)TEMP_0_50_DATA_TBL[u8i]) ; 
                    sRet   = (fA_Data * (float)u16Data + fB_Data) * 10  ;
                    break ;
                }
            }
        } 
    }  
    // 
    return (sRet);
}
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
 
#pragma used-  /* YEMP_TBL.c End Of File !! Well Done */
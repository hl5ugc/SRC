// =======================================================================
// [ PROJECT   ]
// -----------------------------------------------------------------------
// [ License   ] SAMJIN ELECTRONICS
// [ Author    ] Copyright 2021-08 By HAG-SEONG KANG
// [ E-MAIL    ] hl5ugc@nate.com (82)10- 3841-9706
// [ C  P  U   ]
// [ Compller  ] CodeWizardAVR V3.12 Professional
// [ Filename  ] DataConvert.H
// [ Version   ] 1.0
// [ Created   ] 2024-01-17
// ----------------------------------------------------------------------------
// [Updata  List] :
//
//
//
//
//
// =============================================================================
//
//
//
#ifndef SRC_COMMON_HW_INCLUDE_DataConvert_H_
#define SRC_COMMON_HW_INCLUDE_DataConvert_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "def.h"

// -----------------------------------------------------------------------------
// Globals Defines
// -----------------------------------------------------------------------------
//

//
// -----------------------------------------------------------------------------
// Type Definitions
// -----------------------------------------------------------------------------
 
// -----------------------------------------------------------------------------
// Constant Definitions
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Global Structures Define
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Global Variables Define
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Flag Macro Definitions
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Variable Definitions
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Function Prototypes Definitions
// -----------------------------------------------------------------------------

void cvtByte2DASC(uint8_t u8Data,uint8_t * const pBuff) ;
void cvtByte3DASC(uint8_t u8Data,uint8_t * const pBuff) ;
void cvtWord3DASC(uint16_t u16Data,uint8_t * const pBuff) ;
void cvtWord4DASC(uint16_t u16Data,uint8_t * const pBuff) ;
void cvtWord5DASC(uint16_t u16Data,uint8_t * const pBuff) ;
void cvtByte2HEX(uint8_t u8Data,uint8_t * const pBuff) ;
void cvtWord4HEX(uint16_t u16Data,uint8_t * const pBuff) ;
void cvtByte7BASC(uint8_t u8Data,uint8_t * const pBuff) ;
//
void cvt2HEXBin(const uint8_t *pSBuff , uint8_t  * const pData);
void cvt4HEXBin(const uint8_t *pSBuff , uint16_t * const pData);
void cvt6HEXBin(const uint8_t *pSBuff , uint32_t * const pData);
//
void cvt6ASCBin(const uint8_t *pBuff , uint16_t * const pData);
// -----------------------------------------------------------------------------
// Function Definition
// -----------------------------------------------------------------------------



#ifdef __cplusplus
}
#endif

#endif   /* DataConvert End Of file !! Well Done !! */
// ----------------------------------------------------------------------------

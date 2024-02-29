/*
 * [ PROJECT   ]   
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  At24c256.h
 * [ Version   ]  1.0
 * [ Created   ]  2023[11:57:54 AM ]
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

 
/* Mutiple includes protection */
#ifndef COMMON_HW_INCLUDE_At24c256_H_
#define COMMON_HW_INCLUDE_At24c256_H_
/* Includes */
#include "hw_def.h"
#ifdef _USE_HW_AT24C256

 
// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 
#ifndef uint8_t
#define uint8_t unsigned char
#define uint16_t unsigned int
#endif

#define EEPROM_DEVICE     256        

#define AT24C_DEVICE      0xA0U
#define AT24CXX_BLOCK     32
#define AT24CXX_PAGE      512
#define AT24C64_A_MASK    0x1FU
#define AT24C128_A_MASK   0x3FU
#define AT24C256_A_MASK   0x7FU
 
#if (EEPROM_DEVICE == 256)
#define AT24CXX_ADD_MASK  AT24C256_A_MASK
#elif (EEPROM_DEVICE == 128)
#define AT24CXX_ADD_MASK  AT24C128_A_MASK
#else
#define AT24CXX_ADD_MASK  AT24C64_A_MASK
#endif
// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
// 
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//
void At24c256Init(void);
//
void At24c_Read_Byte_block(uint8_t * const pu8Buff , uint16_t u16Address, uint8_t u8Cunter);
void At24c_Read_16Bit_block(uint16_t * const pu16Buff , uint16_t u16Address, uint8_t u8Cunter);
void At24c_Write_Byte(uint16_t u16Address, uint8_t u8Data); 
void At24c_Write_2Bytes(uint16_t u16Address, uint16_t u16Data)  ;
void At24c_Write_block(const uint16_t *pu16Buff , uint16_t u16Address, uint8_t u8Cunter) ;
void At24c_Write_Byte_block(const uint8_t *pu8Buff , uint16_t u16Address, uint8_t u8Cunter); 
void At24c_Write_16Bit_block(const uint16_t *pu16Buff , uint16_t u16Address, uint8_t u8Cunter);

uint8_t  At24c_Read_Byte(uint16_t u16Address) ;
uint16_t At24c_Read_2Bytes(uint16_t u16Address) ;
#endif 
#endif 
/* default.h End Of File !! Well Done */

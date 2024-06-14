/*
 * [ PROJECT   ]  5_stm32g431_UART
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  word.h
 * [ Version   ]  1.0
 * [ Created   ]  2024[12:53:33 PM ]
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
 *  *.This clause and the original author mark are prohibited from being
 *    modified or deleted.
 *  
 *------------------------------------------------------------------
 * --------------------------------------------------------------------------
 * Author         Date       Comments on this revision
 * --------------------------------------------------------------------------
 * Hagseong Kang  May 30, 2024    First release of this file
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
#ifndef COMMON_CORE_WORD_H_
#define COMMON_CORE_WORD_H_

#ifdef __cplusplus
extern "C" {
#endif
/* Includes */
#include "def.h"


 
// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 

// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
// 
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//
/** @ingroup util_word
    Return low word of a 32-bit integer.

    @param uint32_t ww (0x00000000..0xFFFFFFFF)
    @return low word of input (0x0000..0xFFFF)
*/
static inline uint16_t lowWord(uint32_t ww)
{
  return (uint16_t) ((ww) & 0xFFFFU);
}


/** @ingroup util_word
    Return high word of a 32-bit integer.

    @param uint32_t ww (0x00000000..0xFFFFFFFF)
    @return high word of input (0x0000..0xFFFF)
*/
static inline uint16_t highWord(uint32_t ww)
{
  return (uint16_t) ((ww) >> 16U);
}


/* *************************************************/
static inline uint8_t lowByte(uint16_t ww)
{
  return (uint8_t) ((ww) & 0x00FFU);
}


static inline uint8_t highByte(uint16_t ww)
{
  return (uint8_t) ((ww) >> 8U);
}

static inline uint16_t cvtword(uint8_t u8H_Byte,uint8_t u8L_Byte)
{
  uint16_t u16Data = 0U;
  u16Data = (uint16_t)(u8H_Byte<<8U);
  u16Data = u16Data + u8L_Byte;
  return (u16Data);
}
static inline uint8_t location_set_dword(uint16_t data_h,uint16_t data_l)
{
    uint8_t u8Ret = 0U ;
    uint32_t u32Data = 0UL ;

    u32Data  = ((uint32_t)data_h << 16U) ;
    u32Data += data_l ;

    if(u32Data != 0x00) 
    {
      for(u8Ret=0; u8Ret<32U; u8Ret++) 
      {
        if((u32Data & 0x01) == 0x01) 
        {
          u8Ret = u8Ret + 1U ;
          break ;
        }
        u32Data = u32Data >> 1U ;
      }
    }
    return (u8Ret);
}
static inline uint8_t location_set_word(uint16_t data)
{
    uint8_t u8Ret = 0U ;

    if(data != 0x00) 
    {
      for(u8Ret=0; u8Ret<16U; u8Ret++) 
      {
        if((data & 0x01) == 0x01) 
        {
          u8Ret = u8Ret + 1U ;
          break ;
        }
        data = data >> 1U ;
      }
    }
    return (u8Ret);
}
static inline uint8_t location_set_byte(uint8_t data)
{
    uint8_t u8Ret = 0U ;

    if(data != 0x00) 
    {
      for(u8Ret=0; u8Ret<8; u8Ret++) 
      {
        if((data & 0x01) == 0x01) 
        {
          u8Ret = u8Ret + 1U ;
          break ;
        }
        data = data >> 1U ;
      }
    }
    return (u8Ret);
}

#define bitSet(value, bit)  ((value) |= (1UL << (bit)))
#define bitClear(value, bit)  ((value) &= ~(1UL << (bit)))

#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define bitRead(value, bit)  (((value) >> (bit)) & 0x01U)

#ifdef __cplusplus
}
#endif
#endif /* word.h End Of File !! Well Done */
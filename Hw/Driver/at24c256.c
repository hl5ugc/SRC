/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ]  At24c256.c
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
 * Hagseong Kang  Apr 20, 2023    First release of this file
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
 
#include "At24c256.h"
 
// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
//  Define Constants.
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
// Define private function definitions.  
// ---------------------------------------------------------------------------
//
static void twi_init(void);
static void twi_Start(void);
static void twi_Stop(void) ;
static uint8_t twi_Ack_Read(void);
static uint8_t twi_Read(void);
 
static void twi_Write(uint8_t twi_data);
static void twi_Ack_Write(uint8_t twi_data);
static void twi_Write_Address(uint16_t address);
// ---------------------------------------------------------------------------
// Define Public function definitions. 
// ---------------------------------------------------------------------------
//
void At24c256Init(void)
{
  twi_init();
}
/**
 * @brief Multi Read 2bytes Block from AT24Cxx EEPROM
 * 
 * @param pu8Buff     Reades byte buffer pointer
 * @param u16Address  Start Read Address
 * @param u8Cunter    The quantity to be read
 */
void At24c_Read_16Bit_block(uint16_t * const pu16Buff , uint16_t u16Address, uint8_t u8Cunter) 
{     
  uint16_t u16Temp = 0x00U;
  uint8_t index = 0x00U;
  twi_Write_Address(u16Address);  // write low address
  //
  twi_Start();
  twi_Write(AT24C_DEVICE | 0x01); // twi device read command
  //
  do
  {
      u16Temp = twi_Ack_Read() ; 
      u16Temp = ((u16Temp << 8U) & 0xFF00U) ;
      u16Temp = u16Temp | twi_Ack_Read()  ;
      pu16Buff[index] = u16Temp ; 
      index++ ;
      u8Cunter-- ;
  }
  while(u8Cunter > 1) ; 
  // 
  u16Temp = twi_Ack_Read() ; 
  u16Temp = ((u16Temp << 8U) & 0xFF00U) ;
  u16Temp = u16Temp | twi_Read()  ;
  pu16Buff[index] = u16Temp ;
  //
  twi_Stop();  
}
/**
 * @brief Multi Read byte Block from AT24Cxx EEPROM
 * 
 * @param pu8Buff     Reades byte buffer pointer
 * @param u16Address  Start Read Address
 * @param u8Cunter    The quantity to be read
 */
void At24c_Read_Byte_block(uint8_t * const pu8Buff, uint16_t u16Address, uint8_t u8Cunter) 
{     
  uint8_t index = 0x00U;

  twi_Write_Address(u16Address);  // write low address
  //
  twi_Start();
  twi_Write(AT24C_DEVICE | 0x01); // twi device read command
  //
  do
  {
    pu8Buff[index] = twi_Ack_Read();
    index++;
    u8Cunter--;

  } while (u8Cunter > 1);
  pu8Buff[index] = twi_Read();
  twi_Stop(); 
}
/**
 * @brief AT24Cxx Read 2 bytes
 * 
 * @param u16Address Read EEPROM Address
 * @return uint8_t   Readed 2 bytes Data
 */
// working
uint16_t At24c_Read_2Bytes(uint16_t u16Address) 
{     
  uint16_t bRet = 0x00U;
  uint8_t   bData = 0x00U;
  twi_Write_Address(u16Address);
  //
  twi_Start();
  twi_Write(AT24C_DEVICE | 0x01U);    // twi device read command
  // bRet = twi_Ack_Read();
  // bRet =(bRet << 8U) & 0xFF00U ;
  // bRet = bRet | twi_Read();
  bData = twi_Ack_Read();
  bRet =((uint16_t)bData << 8U) & 0xFF00U ;
  bData = twi_Read();
  bRet = bRet + bData;
  twi_Stop();
  //
  return (bRet) ;  
}
/**
 * @brief AT24Cxx Read 1 byte
 * 
 * @param u16Address Read EEPROM Address
 * @return uint8_t   Readed byte Data
 */
uint8_t At24c_Read_Byte(uint16_t u16Address) 
{     
  uint8_t bRet = 0x00U;
  twi_Write_Address(u16Address);
  //
  twi_Start();
  twi_Write(AT24C_DEVICE | 0x01U);    // twi device read command
  bRet = twi_Read();
  twi_Stop();
  //
  return (bRet) ;   
}
 
/**
 * @brief 1 Byte Data write in u16Address
 * 
 * @param u16Address Write address
 * @param u8Data     Data to be Writed 
 */
void At24c_Write_Byte(uint16_t u16Address, uint8_t u8Data) 
{     
  twi_Write_Address(u16Address);       // write low address
  twi_Write(u8Data);
  twi_Stop();
  delay_ms(15) ;    // DELAY 11mSEC 
  // 
}
/**
 * @brief 2 Bytes Data write in u16Address
 * 
 * @param u16Address Write address
 * @param u16Data    Data to be Writed 
 */
void At24c_Write_2Bytes(uint16_t u16Address, uint16_t u16Data) 
{     
  twi_Write_Address(u16Address);       // write low address
  //
  twi_Write(u16Data >> 8U);
  twi_Write(u16Data);
  twi_Stop();
  delay_ms(15) ;    // DELAY 11mSEC 
}
/**
 * @brief Multi Write 1byte  Block  in u16Address 
 * 
 * @param pu8Buff     Multi Write 1byte
 * @param u16Address  Write address
 * @param u8Cunter    The quantity to be write
 */
void At24c_Write_Byte_block(const uint8_t *pu8Buff , uint16_t u16Address, uint8_t u8Cunter) 
{     
  uint8_t index = 0x00U;
  twi_Write_Address(u16Address);       // write low address
  //
  do
  {
      twi_Write(pu8Buff[index]); 
      index++ ;
      u8Cunter-- ;
  }
  while(u8Cunter > 0) ; 
  //
  twi_Stop();  
  delay_ms(15) ;    // DELAY 11mSEC 
}
/**
 * @brief Multi Write 2bytes  Block  in u16Address 
 * 
 * @param pu16Buff   Flash  Multi Write 2bytes
 * @param u16Address  Write address
 * @param u8Cunter    The quantity to be write
 */
void At24c_FWrite_block(flash uint16_t *pu16Buff , uint16_t u16Address, uint8_t u8Counter) 
{
  uint8_t index = 0x00U;
  twi_Write_Address(u16Address);       // write low address 
  //
  do
  {
      twi_Write((pu16Buff[index])>>8U);  
      twi_Write(pu16Buff[index])  ; 
      index++ ;
      u8Counter-- ;
  }
  while(u8Counter > 0) ; 
  //
  twi_Stop();  
  delay_ms(15) ;    // DELAY 11mSEC 
}
/**
 * @brief Multi Write 2bytes  Block  in u16Address 
 * 
 * @param pu16Buff    Multi Write 2bytes
 * @param u16Address  Write address
 * @param u8Cunter    The quantity to be write
 */
void At24c_Write_16Bit_block(const uint16_t *pu16Buff , uint16_t u16Address, uint8_t u8Cunter) 
{     
  uint8_t index = 0x00U;
  twi_Write_Address(u16Address);       // write low address 
  //
  do
  {
      twi_Write((pu16Buff[index])>>8);  
      twi_Write(pu16Buff[index])  ; 
      index++ ;
      u8Cunter-- ;
  }
  while(u8Cunter > 0) ; 
  //
  twi_Stop();  
  delay_ms(15) ;    // DELAY 11mSEC 
}
/**
 * @brief Multi Write 2bytes  Block  in u16Address 
 * 
 * @param pu16Buff    Multi Write 2bytes
 * @param u16Address  Write address
 * @param u8Cunter    The quantity to be write
 */
void At24c_Write_block(const uint16_t *pu16Buff , uint16_t u16Address, uint8_t u8Cunter) 
{     
  uint8_t index = 0x00U;
  twi_Write_Address(u16Address);       // write low address 
  //
  do
  {
      twi_Write((pu16Buff[index])>>8);  
      twi_Write(pu16Buff[index])  ; 
      index++ ;
      u8Cunter-- ;
  }
  while(u8Cunter > 0) ; 
  //
  twi_Stop();  
  delay_ms(15) ;    // DELAY 11mSEC 
}
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//
void twi_init(void)
{
  TWBR = 13U; // TWPS = 0 , 16/(16+2 * TWBR) = 16 /(16+24) = 400KHz
  TWSR = 0x00U;
}
void twi_Start(void)
{
  TWCR = 0xA4U;
  while ((TWCR & 0x80U) == 0x00U);
}
void twi_Stop(void)
{
  TWCR = 0x94U;
}
uint8_t twi_Read(void)
{
  TWCR = 0x84U;
  while ((TWCR & 0x80U) == 0x00U);
  return TWDR;
}

uint8_t twi_Ack_Read(void)
{
  TWCR = 0xC4U;
  while ((TWCR & 0x80U) == 0x00U);
  return TWDR;
}
void twi_Write(uint8_t twi_data)
{
  TWDR = twi_data;
  TWCR = 0x84U;
  while ((TWCR & 0x80U) == 0x00U);
}
void twi_Ack_Write(uint8_t twi_data)
{
  TWDR = twi_data;
  TWCR = 0xC4U;
  while ((TWCR & 0x80U) == 0x00U) ;
}
void twi_Write_Address(uint16_t address)
{
  twi_Start();
  twi_Write(AT24C_DEVICE);                      // write device address
  twi_Write((address >> 8U) & AT24CXX_ADD_MASK); // write high address
  twi_Write(address);
}
// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
 
 

#pragma used- /* At24c256.c End Of File !! Well Done */

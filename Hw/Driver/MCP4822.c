/* --------------------------------------------------------------------------
 * [ PROJECT   ]   
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  MCP4822.c
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
 * Hagseong Kang  2024-06-12    First release of this file
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
#include "MCP4822.h"    
// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//
#define MCP482x_CS1_LO       PORTB.0 = 0
#define MCP482x_CS1_HI       PORTB.0 = 1 
#define MCP482x_CS2_LO       PORTB.0 = 0
#define MCP482x_CS2_HI       PORTB.0 = 1
// 
#define MCP482x_CLK_LO       PORTB.1 = 0
#define MCP482x_CLK_HI       PORTB.1 = 1
//
#define MCP482x_DATA_LO      PORTB.2 = 0
#define MCP482x_DATA_HI      PORTB.2 = 1
//
#define MCP482x_LDAC_LO      PORTB.4 = 0
#define MCP482x_LDAC_HI      PORTB.4 = 1 

#define MCP482x_GAIN           0x30    // Gain X1 
// 
// ---------------------------------------------------------------------------
//  Define Constants.
// ---------------------------------------------------------------------------
//
typedef struct
{
  uint8_t   Lo_Data ; // 리틀 엔디안 Little-Endian
  uint8_t   Hi_Data ;
} cvt_u16_u8_t;
typedef union
{
    uint16_t        u16Val ;
    cvt_u16_u8_t    u8Val ;
} cvt_u16_t ;


// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
//static uint16_t New_CHA_Data = 0x00U ;
static uint16_t Old_CHA_Data = 0x00U ; 
static uint16_t MCP4822_Sv_Data = 0x00U;
// ---------------------------------------------------------------------------
// Define private function definitions.  
// ---------------------------------------------------------------------------
//
static void MCP4822_Transmit(MCP4822_CH channel, uint8_t bGain, uint16_t wDa_Data);
static void MCP482x_init(void);
// ---------------------------------------------------------------------------
// Define Public function definitions. 
// ---------------------------------------------------------------------------
//
void MCP4822Init(void)
{
  MCP482x_init();
}

uint16_t Get_MCP4822_Data(void)
{
  return (MCP4822_Sv_Data);  
}
/**
 * @brief  MCP4822 D/A SV Data Outout Routine 
 * @param   
 * @return void 
 * 110A ->  4095 ,  90A -> 3350        
 */ 
void MCP4822_Sv_data_Out(uint16_t u16da_data)
{
  //  5000 -> 4095  , 5.00V Output 
  MCP4822_Sv_Data = u16da_data ;

  if(MCP4822_Sv_Data < MAX_DA_DATA)
  {   
      MCP4822_Transmit(MCP4822_CHA,2U,MCP4822_Sv_Data); 
      Old_CHA_Data = MCP4822_Sv_Data ; 
      // 
  }    
}
/**
 * @brief 
 * 
 */
void MCP4822_Sv_Data_Clear_Out(void)
{
    MCP4822_Data_Out_Main(MCP4822_CHA,0x000U);
    //
    Old_CHA_Data = 0x0000U ;
}
/**
 * @brief  MCP4822 D/A Outout Routine 
 * @param  byte bChannel, word wDa_Data 
 * @return void              
 */ 
void MCP4822_Data_Out_Main(MCP4822_CH channel, uint16_t wDa_Data)
{
    MCP482x_LDAC_LO ;
    //
    switch(channel) 
    {
      case MCP4822_CHA :  //
        //MCP482x_CS1_LO ;
        MCP4822_Transmit('A',2U,wDa_Data);
        //MCP482x_CS1_HI ;
        break ;
      case MCP4822_CHB :  //
        //MCP482x_CS1_LO ;
        MCP4822_Transmit('B',2U,wDa_Data);
        //MCP482x_CS1_HI ;
        break ;
    }
    //
} 
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
 
//
// D/A 12Bit
/*
void Da_data_out_main(uint8_t u8Ch , uint16_t u16daData)
{
    MCP482x_LDAC_LO ;
    //    
    switch(u8Ch)
    {
        case 'A' :
                    MCP482x_CS1_LO ;
                    MCP4822_Transmit('A',2,u16daData);
                    MCP482x_CS1_HI ;
                    break ;
        case 'B' :
                    MCP482x_CS1_LO ;
                    MCP4822_Transmit('B',2,u16daData);
                    MCP482x_CS1_HI ;
                    break ;                    
        case 'C' :
                    MCP482x_CS2_LO ;
                    MCP4822_Transmit('A',2,u16daData);
                    MCP482x_CS2_HI ;
                    break ;
        case 'D' :
                    MCP482x_CS2_LO ;
                    MCP4822_Transmit('B',2,u16daData);
                    MCP482x_CS2_HI ;
                    break ;    
    }
}
*/

/**
 * @brief   SPI Control MCP4822 D/A Convert Routine 
 * 
 * @param channel   DAC Output Port (A,B)
 * @param bGain     Output Gain x1,x2
 * @param wDa_Data  Output 12Bits Data 
 */
void MCP4822_Transmit(MCP4822_CH channel, uint8_t bGain, uint16_t wDa_Data)
{
    // uint8_t bTemp   = 0x00U ;
    uint8_t u8HiData = 0x00U ;
    uint8_t u8LoData = 0x00U ;
    //  
    if(wDa_Data <=  MAX_DA_DATA) 
    {
      MCP482x_CS1_LO ;
      //
      u8HiData  = (wDa_Data >> 8U) & 0x000FU ;  
      if(channel == MCP4822_CHB ) 
      {
        u8HiData = u8HiData |  0x80U ;    // Select Channel B   
      }  
      else 
      {
        u8HiData = u8HiData & 0x7FU ;     // Select Channel A 
      }
      //
      if(bGain == 2U) u8HiData |= 0x10 ; // Gain 2
      else u8HiData |= 0x30 ;            // Gain 1
      //
      u8LoData  = (wDa_Data)  & 0x00FFU ;
      //
      SPDR = u8HiData ;   
      while((SPSR & 0x80U)==0x00) ; 
      SPDR = u8LoData ;   
      while((SPSR & 0x80U)==0x00) ; 
      //
      MCP482x_CS1_HI ;
      MCP482x_LDAC_HI ;
      MCP482x_LDAC_LO ;
      MCP482x_LDAC_LO ;
      MCP482x_LDAC_HI ;
    } 
}
/**
 * @brief MCP4822 Control Port init & MCP4822 Output Clear
 * 
 */
static void MCP482x_init(void)
{
    // SPI initialization
    // SPI Type: Master
    // SPI Clock Rate: 250.000 kHz
    // SPI Clock Phase: Cycle Half
    // SPI Clock Polarity: Low
    // SPI Data Order: MSB First
    SPCR=0x52U;
    SPSR=0x00U;
    // 
    delay_ms(1);
    MCP482x_LDAC_LO;
    MCP482x_CS1_LO ;
    MCP4822_Transmit(MCP4822_CHA,1U,0x0000U) ;
    MCP4822_Transmit(MCP4822_CHB,1U,0x0000U) ;
    MCP482x_CS1_LO ;
    //
    MCP482x_LDAC_HI ;
    MCP482x_LDAC_LO ;
    MCP482x_LDAC_HI ; 

}
// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
 
 
 
#pragma used-  /* MCP4822.c End Of File !! Well Done */
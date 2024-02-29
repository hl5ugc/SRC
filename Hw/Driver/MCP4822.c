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


 
/* Define Includes */
#include "MCP4822.h"
#include "cli.h" 
#include "uart.h"      
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
static uint16_t New_CHA_Data = 0x00U ;
static uint16_t Old_CHA_Data = 0x00U ; 
static uint16_t MCP4822_Sv_Data = 0x00U;
// ---------------------------------------------------------------------------
// Define private function definitions.  
// ---------------------------------------------------------------------------
//
static void MCP4822_Transmit(MCP4822_CH channel, uint8_t bGain, uint16_t wDa_Data);
static void MCP482x_init(void);
static void cliMCP4822_Check(cli_args_t *args);
// ---------------------------------------------------------------------------
// Define Public function definitions. 
// ---------------------------------------------------------------------------
//
void MCP4822Init(void)
{
  MCP482x_init();

  cliAdd("MCP4822","Ch[A/B/T] Data", cliMCP4822_Check); //  
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
void MCP4822_Level_Sv_data_Out(uint16_t da_data)
{
    //  5000 -> 4095  , 5.00V Output 
    //
    MCP4822_Sv_Data = da_data ;

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
void MCP4822_Level_Sv_data_Clear_Out(void)
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
/**
 * @brief  SPI Control MCP4822 D/A Convert Routine 
 * @param  word wDa_Data
 * @return void              
 */ 
//
void MCP4822_Transmit(MCP4822_CH channel, uint8_t bGain, uint16_t wDa_Data)
{
    uint8_t bTemp   = 0x00U ;
    uint8_t bHiData = 0x00U ;
    uint8_t bLoData = 0x00U ;
    //  
    MCP482x_CS1_LO ;
    if(wDa_Data > MAX_DA_DATA) wDa_Data = 0x0000U ;
    //
    bHiData  = (wDa_Data >> 8U) & 0x000FU ;  
    if(channel == MCP4822_CHB ) 
    {
      bHiData = bHiData |  0x80U ;    // Select Channel B   
    }  
    else 
    {
      bHiData = bHiData & 0x7FU ;     // Select Channel A 
    }
    //
    if(bGain == 2U) bHiData |= 0x10 ; // Gain 2
    else bHiData |= 0x30 ;            // Gain 1
    //
    bLoData  = (wDa_Data)  & 0x00FFU ;
    //
    SPDR = bHiData ;   
    while((SPSR & 0x80U)==0x00) ; 
    SPDR = bLoData ;   
    while((SPSR & 0x80U)==0x00) ; 
    //
    MCP482x_CS1_HI ;
    MCP482x_LDAC_HI ;
    MCP482x_LDAC_LO ;
    MCP482x_LDAC_LO ;
    MCP482x_LDAC_HI ; 
}
/**
 * @brief 
 * 
 */
void MCP482x_init(void)
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
void cliMCP4822_Check(cli_args_t *args)
{
  uint8_t u8Result = 0x00U ;
  uint16_t u16Data = 0x00U ;
  cvt_u16_t daData ;  

  if(args->argc == 0)
  {
    u8Result = 0x01U ;
  }
  else if(args->argc == 1)
  {
      if(args->isStr(0,"T") || args->isStr(0,"t"))
      {
        uartMsgWrite(_DEF_UART1,"Chanel A  Data 0x0000 - 0x0FFF\r\n"); delay_ms(50);
        u16Data = 0x0000U;
        while(cliKeepLoop())
        {
          MCP4822_Transmit(MCP4822_CHA,2U,u16Data) ; 
          delay_ms(1);
          u16Data = (u16Data + 0x000FU) % 0x1000 ;
        } 
      } 
      else 
      {
        u8Result = 0x01U ;
      }
  }
  else if(args->argc >= 2)
  {
    u16Data = args->getData(1);
    daData.u16Val = u16Data;
    if(u16Data <= 0x0FFFU)
    {
      if(args->isStr(0,"A") || args->isStr(0,"a"))
      {
        uartMsgWord4Hex(_DEF_UART1,"\r\nA = 0x",u16Data);  
        while(cliKeepLoop())
        {
          MCP4822_Transmit(MCP4822_CHA,2U,u16Data) ; 
          delay_ms(100); 
          uartMsgWrite(_DEF_UART1,".");
        }
      }
      else if(args->isStr(0,"B") || args->isStr(0,"b"))
      {
        while(cliKeepLoop())
        {
          MCP4822_Transmit(MCP4822_CHB,2U,u16Data) ; 
          delay_ms(100); 
          uartMsgWrite(_DEF_UART1,".");
        } 
      } 
      else  {  u8Result = 0x02U ;}
    }
    else    {  u8Result = 0x03U ;}
  }
  //
  if(u8Result != 0x00U)
  {
    uartMsgWrite(_DEF_UART1,"MCP4822 Ch[A/B/T] Data\r\n"); delay_ms(50);
    uartMsgWrite(_DEF_UART1,"hl5ugc >> MCP4822 T(Test) \r\n"); delay_ms(50);
    uartMsgWrite(_DEF_UART1,"hl5ugc >> MCP4822 [A/B] Data(0x0F00)\r\n"); delay_ms(50);
    uartMsgWrite(_DEF_UART1,"Data Range Data(0x0000 - 0x0FFF)\r\n"); delay_ms(50);
  }

}
 
 
/* MCP4822.c End Of File !! Well Done */
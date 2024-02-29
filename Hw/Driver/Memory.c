/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ]  MEMORY.c
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
#include "MEMORY.h"
#include "At24c256.h"

#include "cli.h"
#include "uart.h"
// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//
#define AT24C256_BLOCK      512U
#define AT24C256_PAGE       64U
#define AT24C128_BLOCK      256U
#define AT24C128_PAGE       64U
#define AT24C64_BLOCK       256U
#define AT24C64_PAGE        32U
#define AT24C32_BLOCK       128U
#define AT24C32_PAGE        32U
//
#define APR_PTR_MAX                 7
#define APR_SUB_PTR_MAX             1 
//
#define EP_HEAD                     (AT24CXX_BLOCK * 1)   // 32 Start Address Bytes
#define EP_BASE                     (AT24CXX_BLOCK * 2)   // 64
// -----------------------------------------------------------
#define APR_BASE_PTR                (AT24CXX_BLOCK * 13)   // 416
#define APR_BASE_PTR1               (AT24CXX_BLOCK * 13)   // 416   
#define APR_BASE_PTR2               (AT24CXX_BLOCK * 14)   //   
#define APR_BASE_PTR3               (AT24CXX_BLOCK * 15)   //    
#define APR_BASE_PTR4               (AT24CXX_BLOCK * 16)   //    
#define APR_BASE_PTR5               (AT24CXX_BLOCK * 17)   //   
#define APR_BASE_PTR6               (AT24CXX_BLOCK * 18)   //    
#define APR_BASE_PTR7               (AT24CXX_BLOCK * 19)   // 608 
//
#define EP_LEVEL_TBL_PTR            (AT24CXX_BLOCK * 20)  // 320 ~ 320 + 96  
#define EP_LEVEL_TBL_END_PTR        (AT24CXX_BLOCK * 23) // 320 ~ 320 + 96   = 416  
//
#define EP_PASSWORD                 (EP_BASE + 0)
#define EP_ST_TEMP_SV_MIN           (EP_BASE + 2)    
#define EP_ST_TEMP_SV_MAX           (EP_BASE + 4) 
#define EP_ST_TEMP_OFFSET           (EP_BASE + 6)   
//
#define EP_TOTAL_COUNT              (EP_BASE + 10)        
#define EP_TOTAL_COUNT_HI           (EP_BASE + 10)        
#define EP_TOTAL_COUNT_LO           (EP_BASE + 12)         
#define EP_DIODE_COUNT              (EP_BASE + 14)         
#define EP_DIODE_COUNT_HI           (EP_BASE + 14)        
#define EP_DIODE_COUNT_LO           (EP_BASE + 16) 
// -------------------------------------------
#define EP_SERIAL_YY                (EP_BASE + 20) 
#define EP_SERIAL_MM                (EP_BASE + 22) 
#define EP_SERIAL_DD                (EP_BASE + 24) 
#define EP_SERIAL_NO                (EP_BASE + 28) 
// ------------------------------------------
#define EP_APR_BACKUP               (EP_BASE + 30) 
#define EP_SYS_OPTION               (EP_BASE + 32) 
// -----------------------------------------------------------
#define EP_APR1_FLU                 (APR_BASE_PTR1 + 0) 
#define EP_APR1_DUR                 (APR_BASE_PTR1 + 2)
#define EP_APR1_FRQ                 (APR_BASE_PTR1 + 4) 
#define EP_APR1_LEV                 (APR_BASE_PTR1 + 6) 
//
#define EP_APR2_FLU                 (APR_BASE_PTR2 + 0) 
#define EP_APR2_DUR                 (APR_BASE_PTR2 + 2)
#define EP_APR2_FRQ                 (APR_BASE_PTR2 + 4) 
#define EP_APR2_LEV                 (APR_BASE_PTR2 + 6) 
//                                              
#define EP_APR3_FLU                 (APR_BASE_PTR3 + 0) 
#define EP_APR3_DUR                 (APR_BASE_PTR3 + 2)
#define EP_APR3_FRQ                 (APR_BASE_PTR3 + 4) 
#define EP_APR3_LEV                 (APR_BASE_PTR3 + 6) 
//
#define EP_APR4_FLU                 (APR_BASE_PTR4 + 0) 
#define EP_APR4_DUR                 (APR_BASE_PTR4 + 2)
#define EP_APR4_FRQ                 (APR_BASE_PTR4 + 4) 
#define EP_APR4_LEV                 (APR_BASE_PTR4 + 6) 
//
#define EP_APR5_FLU                 (APR_BASE_PTR5 + 0) 
#define EP_APR5_DUR                 (APR_BASE_PTR5 + 2)
#define EP_APR5_FRQ                 (APR_BASE_PTR5 + 4) 
#define EP_APR5_LEV                 (APR_BASE_PTR5 + 6) 
//
#define EP_APR6_FLU                 (APR_BASE_PTR6 + 0) 
#define EP_APR6_DUR                 (APR_BASE_PTR6 + 2)
#define EP_APR6_FRQ                 (APR_BASE_PTR6 + 4) 
#define EP_APR6_LEV                 (APR_BASE_PTR6 + 6) 
//
#define EP_APR7_FLU                 (APR_BASE_PTR7 + 0) 
#define EP_APR7_DUR                 (APR_BASE_PTR7 + 2)
#define EP_APR7_FRQ                 (APR_BASE_PTR7 + 4) 
#define EP_APR7_LEV                 (APR_BASE_PTR7 + 6) 
// ---------------------------------------------------------------
#define EP_LEVEL_TBL                EP_LEVEL_TBL_PTR  
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
static void cliEEPROM_Check(cli_args_t *args);
static void cliEEPROM_Dump(cli_args_t *args);
static void cliEEPROM_MFR(cli_args_t *args);

static void Word_Data_Write(uint16_t address,uint16_t data);
static void ReadHeadData(void);
static void ReadPasswordData(void);
static void ReadDiodeCountData(void); 
static void ReadSerialData(void); 
static void ReadLevelData(void); 
static void AllDataDelete(uint16_t option);
static void Data_Dump(uint16_t address);
// ---------------------------------------------------------------------------
// Define Public function definitions.
// ---------------------------------------------------------------------------
//
void MemoryInit(void)
{
  // cliAdd("EEprom", "R/W Add Data", cliEEPROM_Check);  // EEPROM READ/WRITE Test
  // cliAdd("EEDump","Add Count",cliEEPROM_Dump);        // EEPROM DUMP
  cliAdd("EEMFR","Select ?",cliEEPROM_MFR);        // EEPROM MFR DATA READF
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
 * @brief
 *
 * @param args hl5ugc>> EEprom R/W Address Data
 */
void cliEEPROM_Check(cli_args_t *args)
{
  uint8_t  *u8Command  = NULL ;
  uint16_t u16Address = 0x00U ;
  uint16_t u16data    = 0x00U ;

  if(args->argc >= 1)
  {
    u8Command = args->getStr(0);
    
    if(args->argc >= 2)
    {
      u16Address = args->getData(1) ; // ASCII DECMAL & HEX Convert to binary
    }
    if(args->argc >= 3)
    {
      u16data = args->getData(2) ; // ASCII DECMAL & HEX Convert to binary
    }
    if(u16Address >= 64U)
    {
    //
      if((u8Command[0] == 'r') || (u8Command[0] == 'R'))
      {
        u16data = At24c_Read_2Bytes(u16Address);
        uartMsgWord5DASC(_DEF_UART1,"\n\r",u16Address);
        uartMsgWord5DASC(_DEF_UART1," => ",u16data);
      }
      if((u8Command[0] == 'w') || (u8Command[0] == 'W'))
      {
        At24c_Write_2Bytes(u16Address,u16data);
        u16data = At24c_Read_2Bytes(u16Address);
        uartMsgWord5DASC(_DEF_UART1,"\n\r",u16Address);
        uartMsgWord5DASC(_DEF_UART1," => ",u16data);
      }
    }
    else
    {
      uartMsgWrite(_DEF_UART1,"Address Err! Addrees < 64");
    }
  }
  else
  {
    uartMsgWrite(_DEF_UART1,"hl5ugc>> EEprom R/W Address Data");
  }
}
/**
 * @brief 
 * 
 * @param args 
 */
void cliEEPROM_Dump(cli_args_t *args)
{
  uint16_t u16i = 0x00U ;
  uint16_t u16Address = 0x00U ;
  uint16_t u16Count   = 0x00U ;
  uint16_t u16Data    = 0x00U ;

  if(args->argc >= 2)
  {
    u16Address = args->getData(0) ; // ASCII DECMAL & HEX Convert to binary
    u16Count   = args->getData(1) ;
    uartMsgWrite(_DEF_UART1,"\r\n"); delay_ms(10); 
    //
    if(u16Count > 0)
    {
      for(u16i=0x00U; u16i<u16Count ; u16i++)
      {
        u16Data = At24c_Read_2Bytes(u16Address);
        if((u16i % 8) == 0x00U)
        {
          uartMsgWord5DASC(_DEF_UART1,"\r\n",(u16Address)); delay_ms(10); 
          uartMsgWord5DASC(_DEF_UART1,":",u16Data); delay_ms(10); 
        }
        else
        {
          uartMsgWord5DASC(_DEF_UART1,",",u16Data); delay_ms(10); 
        }
        u16Address = u16Address + 2U ;
      }
      uartMsgWrite(_DEF_UART1,"\r\n\r\n"); delay_ms(10); 
    }
    else 
    {
      uartMsgWrite(_DEF_UART1,"Count Error!! \r\n");
      delay_ms(50);
    }
  }
  else 
  {
    uartMsgWrite(_DEF_UART1,"hl5ugc>> eedump Address Count");
    delay_ms(50);
  }
}

/**
 * @brief 
 * 
 * @param args 
 * @return * void 
 */
void cliEEPROM_MFR(cli_args_t *args)
{
  uint8_t u8Select = 0x00U ;
  uint16_t u16Option = 0x00U ;
  uint16_t u16Option2 = 0x00U ;

  // uartMsgWord5DASC(_DEF_UART1,"args->argc = ",args->argc); delay_ms(10); 

  if(args->argc >= 1)
  {
    u8Select = args->getData(0);

    if(args->argc == 2)
    {
      u16Option =  args->getData(1);
    }
    if(args->argc == 3)
    {
      u16Option  =  args->getData(1);
      u16Option2 =  args->getData(2);
    }
    if((u8Select > 0U) && (u8Select < 10U) || (u8Select == 99U))
    {
      switch(u8Select)
      {
        case 0x01U :
          ReadHeadData();
          break;
        case 0x02U :
          ReadPasswordData();
          break;  
        case 0x03U :
          ReadDiodeCountData();
          break; 
        case 0x04U :  
          ReadSerialData();
          break; 
        case 0x05U :  
          ReadLevelData();
          break; 
        case 0x06U :  
          Data_Dump(u16Option);   
          break; 
        case 0x07U :  
          AllDataDelete(u16Option);   
          break; 
        case 0x08U :  
          Word_Data_Write(u16Option,u16Option2);   
          break; 
        case 0x09U :  
          //AllDataDelete(u16Option);   
          break; 
        case 99U:
          ReadHeadData();
          ReadPasswordData();
          ReadDiodeCountData();
          ReadSerialData();
          ReadLevelData();
          break; 
      }
    }
    else
    {
      uartMsgWrite(_DEF_UART1,"Select Error!! (Select [0 ~ 9] \n\r");
    }
  }
  else
  {
    uartMsgWrite(_DEF_UART1,"hl5ugc>> eemfr Select ?");       delay_ms(50);
    uartMsgWrite(_DEF_UART1,"  (Select [0 ~ 9]\n\r");         delay_ms(50);
    uartMsgWrite(_DEF_UART1,"1.Haed Data Read\n\r");          delay_ms(50);
    uartMsgWrite(_DEF_UART1,"2.Password Data Read\n\r");      delay_ms(50);
    uartMsgWrite(_DEF_UART1,"3.Count Data Read\n\r");         delay_ms(50);
    uartMsgWrite(_DEF_UART1,"4.Serial Data Read\n\r");        delay_ms(50);
    uartMsgWrite(_DEF_UART1,"5.Level Data Read\n\r");         delay_ms(50);
    uartMsgWrite(_DEF_UART1,"6.Memory Dump => ");             delay_ms(50);
    uartMsgWrite(_DEF_UART1," EEMFR 6 Address \n\r");         delay_ms(50);
    uartMsgWrite(_DEF_UART1,"7.All Data Delete");             delay_ms(50);
    uartMsgWrite(_DEF_UART1," => EEMFR 7 [128/256]\n\r");     delay_ms(50);
    uartMsgWrite(_DEF_UART1,"8.EEprom Data Write");           delay_ms(50);
    uartMsgWrite(_DEF_UART1," => EEMFR 8 Address WordData\n\r");  delay_ms(50);
    uartMsgWrite(_DEF_UART1,"99.All Data Read\n\r");          delay_ms(50);
  }
}

void Word_Data_Write(uint16_t address,uint16_t data)
{
  uint16_t u16data = 0x00U;

  At24c_Write_2Bytes(address,data);
  u16data = At24c_Read_2Bytes(address);

  uartMsgWord4Hex(_DEF_UART1,"\n\r Address 0x",address);  delay_ms(10);
  uartMsgWord4Hex(_DEF_UART1," => 0x",u16data);           delay_ms(10);
  uartMsgWrite(_DEF_UART1," Data Write OK!!\n\r");        delay_ms(50);
}  
/**
 * @brief Read EEprom Haed
 * 
 */
void ReadHeadData(void)
{
  uint16_t u16Data = 0x00U ;

  u16Data = At24c_Read_2Bytes(EP_HEAD);
  uartMsgWord4Hex(_DEF_UART1,"Head = 0x",u16Data);
  delay_ms(10); 
  uartMsgWrite(_DEF_UART1,"\n\r");
}
void ReadPasswordData(void)
{
  uint16_t u16Data = 0x00U ;

  u16Data = At24c_Read_2Bytes(EP_PASSWORD);
  uartMsgWord5DASC(_DEF_UART1,"Password = ",u16Data);
  delay_ms(10); 
  uartMsgWrite(_DEF_UART1,"\n\r");
}
/**
 * @brief 
 * 
 * @return * void 
 */
void ReadDiodeCountData(void)
{
  uint16_t u16Data = 0x00U ;

  u16Data = At24c_Read_2Bytes(EP_TOTAL_COUNT_HI);
  uartMsgWord5DASC(_DEF_UART1,"Total Count Hi,Lo = ",u16Data); delay_ms(10); 
  //
  u16Data = At24c_Read_2Bytes(EP_TOTAL_COUNT_LO);
  uartMsgWord5DASC(_DEF_UART1," , ",u16Data);  delay_ms(10); 
  uartMsgWrite(_DEF_UART1,"\n\r"); delay_ms(10);   

  u16Data = At24c_Read_2Bytes(EP_DIODE_COUNT_HI);
  uartMsgWord5DASC(_DEF_UART1,"Diode Count Hi,Lo = ",u16Data); delay_ms(10); 
  //
  u16Data = At24c_Read_2Bytes(EP_DIODE_COUNT_LO);
  uartMsgWord5DASC(_DEF_UART1," , ",u16Data);  delay_ms(10); 
  uartMsgWrite(_DEF_UART1,"\n\r"); delay_ms(10);  
}
/**
 * @brief 
 * 
 */
void ReadSerialData(void)
{
  uint16_t u16Data = 0x00U ;
  //
  u16Data = At24c_Read_2Bytes(EP_SERIAL_YY);
  uartMsgByte2ASC(_DEF_UART1,"YY/MM/DD-No = ",(uint8_t)u16Data); delay_ms(10); 
  u16Data = At24c_Read_2Bytes(EP_SERIAL_MM);
  uartMsgByte2ASC(_DEF_UART1," / ",(uint8_t)u16Data); delay_ms(10); 
  u16Data = At24c_Read_2Bytes(EP_SERIAL_DD);
  uartMsgByte2ASC(_DEF_UART1," / ",(uint8_t)u16Data); delay_ms(10); 
  u16Data = At24c_Read_2Bytes(EP_SERIAL_NO);
  uartMsgByte3ASC(_DEF_UART1," - ",(uint8_t)u16Data); delay_ms(10); 
  uartMsgWrite(_DEF_UART1,"\n\r"); delay_ms(10);  
}

void ReadLevelData(void)
{
  uint8_t u8Loop = 0x00U ;
  uint16_t u16Add = 0x00U ;
  uint16_t u16Data = 0x00U ;
  //
  uartMsgWrite(_DEF_UART1,"===================================\n\r"); delay_ms(50);  
  //
  u16Add = EP_LEVEL_TBL;
  uartMsgWord5DASC(_DEF_UART1,"Base Address = ",(u16Add)); delay_ms(10); 
  //
  for(u8Loop=0U; u8Loop < 32; u8Loop++)
  {
    u16Data = At24c_Read_2Bytes(u16Add);
    if((u8Loop % 4) == 0x00U)
    {
      uartMsgByte2ASC(_DEF_UART1,"\r\n",(u8Loop)); delay_ms(10); 
      uartMsgWord5DASC(_DEF_UART1," : ",u16Data); delay_ms(10); 
    }
    else
    {
      uartMsgWord5DASC(_DEF_UART1," , ",u16Data); delay_ms(10); 
    }
    //
    u16Add = u16Add + 2 ;
  }
  uartMsgWrite(_DEF_UART1,"\n\r===================================\n\r"); delay_ms(50);  
}
/**
 * @brief 
 * 
 */


void AllDataDelete(uint16_t option)
{
  uint8_t u8Result = 0x00U ;
  uint8_t u8Page = 0x00U ;
  uint8_t u8Msg[64] = {0x00,};
  uint16_t u16Loop = 0x00U ;
  uint16_t u16Add = 0x00U ;
  uint16_t u16Count = 0x00U ;
  //
  uartMsgWord3DASC(_DEF_UART1," At24c",option); delay_ms(50);  
  uartMsgWrite(_DEF_UART1," => Memory Data All Delete\n\r"); delay_ms(50);  
  //
  switch(option)
  {
    case 32:
          u8Page = AT24C32_PAGE ;
          u16Count = AT24C32_BLOCK ;
          break ;
    case 64:
          u8Page = AT24C64_PAGE ;
          u16Count = AT24C64_BLOCK ;
          break ;
    case 128:
          u8Page = AT24C128_PAGE ;
          u16Count = AT24C128_BLOCK ;
          break ;
    case 256:
          u8Page = AT24C256_PAGE ;
          u16Count = AT24C256_BLOCK ;
          break ; 
    default:
          u8Result = 0x01U ;
          break;
  }
  //
  if(u8Result == 0x00U)
  {
    for(u16Loop=0x00U; u16Loop<u16Count;u16Loop++)
    {
      uartMsgWord4Hex(_DEF_UART1,"Address 0x",u16Add); delay_ms(10); 
      At24c_Write_Byte_block((const uint8_t *)&u8Msg[0],u16Add,u8Page);
      u16Add = u16Add + u8Page ;
      uartMsgWrite(_DEF_UART1," : Ok! \r\n"); delay_ms(5);  
    }
  }
  //
  if(u8Result != 0x00U)
  {
    uartMsgWrite(_DEF_UART1," Option Error :[32/64/128/256] \n\r"); delay_ms(50);  
  }
}
void Data_Dump(uint16_t address)
{
  uint8_t u8I = 0x00U ;
  uint8_t u8Count   = 64U ;
  uint8_t u8Data[64]  = {0x55U,} ;

  uint16_t u16Address =  0x00U ;
  u16Address = address / 32 ; 
  u16Address = u16Address * 32 ; 
  //
  uartMsgWrite(_DEF_UART1,"Memory Data Dump\n\r"); delay_ms(50);  
  uartMsgWord4Hex(_DEF_UART1,"Start Address 0x",u16Address); delay_ms(10); 
  //
  At24c_Read_Byte_block((uint8_t * const)&u8Data[0],u16Address,32U);
  At24c_Read_Byte_block((uint8_t * const)&u8Data[32U],u16Address+32U,32U);
  //
  for(u8I=0x00U; u8I<u8Count ; u8I++)
  {
 
    if((u8I % 16) == 0x00U)
    {
      uartMsgWord4Hex(_DEF_UART1,"\r\n",(u16Address)); delay_ms(10); 
      uartMsgByte2Hex(_DEF_UART1,":",u8Data[u8I]); delay_ms(10); 
    }
    else
    {
      uartMsgByte2Hex(_DEF_UART1,",",u8Data[u8I]); delay_ms(10); 
    }
    //
    u16Address =(u16Address + 1U) ;
  }
}
/* MEMORY.c End Of File !! Well Done */

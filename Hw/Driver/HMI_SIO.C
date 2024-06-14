/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ] HMI_SIO.c
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

#pragma used+
/* Define Includes */
#include "HMI_SIO.h"
#include "Timer0_int.H"
#include "DataConvert.H"
#include "Word.H"
// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
//  IPL Define Macros .
// ---------------------------------------------------------------------------
// 

#define SEND_HMI_PORT   0
#define HMI_USART_BPS    19200 
#if (SEND_HMI_PORT == 0) 
//
#define HMI_UDR         UDR0  
#define HMI_UCSRA       UCSR0A 
#define HMI_UCSRB       UCSR0B 
#define HMI_UCSRC       UCSR0C 
#define HMI_UBRRH       UBRR0H 
#define HMI_UBRRL       UBRR0L 
#define HMI_USART_RXC   USART0_RXC
#define HMI_USART_TXC   USART0_TXC  
#else 
//
#define HMI_UDR         UDR1  
#define HMI_UCSRA       UCSR1A 
#define HMI_UCSRB       UCSR1B 
#define HMI_UCSRC       UCSR1C 
#define HMI_UBRRH       UBRR1H 
#define HMI_UBRRL       UBRR1L 
#define HMI_USART_RXC   USART1_RXC
#define HMI_USART_TXC   USART1_TXC  

#endif 

#ifndef RXB8

#define RXB8 1
#define TXB8 0
#define UPE 2
#define OVR 3
#define FE 4
#define UDRE 5
#define RXC 7

#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<OVR)
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)

#endif
// ---------------------------------------------------------------------------
//  Define Constants.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
// Define typedef.
// --------------------------------------------------------------------------- 
// 
typedef struct _Uart_Buff
{
  uint8_t Wr_ptr ;
  uint8_t Rd_ptr ;
  uint8_t Status ;
  uint8_t Wait_Time ;
  uint8_t Count ;
  uint8_t Len ;
  uint8_t *pBuff ;
} Uart_Buff_t ;
// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
uint16_t  * pPLC_DATA ; 
// ---------------------------------------------------------------------------
// RS232 Receiver buffer
// ---------------------------------------------------------------------------
// 
#define HMI_RX_BUFF_SIZE  64
static uint8_t  HMI_rx232_buffer[HMI_RX_BUFF_SIZE] ;

static bool isOpen ;
Uart_Buff_t HMI_TxBuff ;
Uart_Buff_t HMI_RxBuff ;
// ---------------------------------------------------------------------------
// RS232 Transmitter buffer
// ---------------------------------------------------------------------------
//
#define HMI_TX_BUFF_SIZE  64
static uint8_t  HMI_tx232_buffer[HMI_TX_BUFF_SIZE];

//
static uint8_t HMI_Rx_Q_Buffer[HMI_RX_BUFF_SIZE];
static uint8_t HMI_Rx_Q_Counter = 0U ;
// ---------------------------------------------------------------------------
//  Define Varibales Macro.
// ---------------------------------------------------------------------------
SYSTEM_FLAG hmi_comm_flag ;
//SYSTEM_FLAG key_in_flag ;
#define Current_Screen      pPLC_DATA[0]
#define key_buff1           pPLC_DATA[90]  // 100 -- 0x64
#define key_buff2           pPLC_DATA[91]  // 101 -- 0x65
#define key_buff3           pPLC_DATA[92]  // 102 -- 0x66
#define key_buff4           pPLC_DATA[93]  // 103 -- 0x67
#define key_buff5           pPLC_DATA[94]  // 104 -- 0x68 
// ---------------------------------------------------------------------------
// Define private function definitions.
// ---------------------------------------------------------------------------
//
//void send_samjin_head(void); 
 
static void HMI_comm_init(void);
static void send_to_HMI_1byte(uint8_t u8data) ;
static void send_HMI_Msg(const uint8_t *pBuffs, uint8_t u8Len);

static void cbHMI_SIO_Check(void);
// ---------------------------------------------------------------------------
// Define Public function definitions.
// ---------------------------------------------------------------------------
//
void HMI_SioInit(void)
{
  HMI_comm_init();

  HMI_RxBuff.Wr_ptr     = 0U ;
  HMI_RxBuff.Rd_ptr     = 0U ;
  HMI_RxBuff.Count      = 0U ;
  HMI_RxBuff.Wait_Time  = 0U;
  HMI_RxBuff.Status     = false ;
  HMI_RxBuff.Len        = HMI_RX_BUFF_SIZE ;
  HMI_RxBuff.pBuff      = &HMI_rx232_buffer[0];

  HMI_TxBuff.Wr_ptr     = 0U ;
  HMI_TxBuff.Rd_ptr     = 0U ;
  HMI_TxBuff.Count      = 0U ;
  HMI_TxBuff.Wait_Time  = 0U;
  HMI_TxBuff.Status     = false ;
  HMI_TxBuff.Len        = HMI_TX_BUFF_SIZE ;
  HMI_TxBuff.pBuff      = &HMI_tx232_buffer[0];

 
  canSetTimer0Callback(USE_HMI_SIO_CB_CH,cbHMI_SIO_Check) ;
 
  isOpen = true ;
}
void HMI_SioMemInit(uint16_t *pBuff)
{
  if(isOpen == true) {
    pPLC_DATA = pBuff ;
  }
}

//
void send_set_screen(uint8_t u8Screen_No)
{    
    uint8_t u8Msg[6] = {0x00,};

    u8Msg[0] = (HMI_STX_LO);
    u8Msg[1] = (0x04U);
    u8Msg[2] = (HMI_WReg_CMD);
    u8Msg[3] = (0x03U);
    u8Msg[4] = (0x00U); 
    u8Msg[5] = (u8Screen_No);

    send_HMI_bytes((const uint8_t *)&u8Msg[0]);
}
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//
 
/// 
void send_HMI_bytes(const uint8_t *pBuffs)
{             
    uint8_t u8i;
    uint8_t u8BufSize = pBuffs[1]; 
    //
    while(HMI_TxBuff.Wr_ptr != HMI_TxBuff.Rd_ptr );
    //
    HMI_TxBuff.Wr_ptr = 0U ;
    HMI_TxBuff.Rd_ptr = 0U ;
    //
    for(u8i=0; u8i<u8BufSize + 2U ; u8i++)
    {
        send_to_HMI_1byte(pBuffs[u8i]);
    }
    //
    HMI_UDR = HMI_STX_HI ;
    //  
    delay_ms(u8i*2);    
}
//  
void send_to_HMI_1byte(uint8_t u8data)
{   
    HMI_TxBuff.pBuff[HMI_TxBuff.Wr_ptr]=  u8data ;
    HMI_TxBuff.Wr_ptr = (HMI_TxBuff.Wr_ptr + 1U) % HMI_TxBuff.Len ;
}  
void send_HMI_Msg(const uint8_t *pBuffs, uint8_t u8Len)
{             
    uint8_t u8i;
    //
    while(HMI_TxBuff.Wr_ptr != HMI_TxBuff.Rd_ptr );
    //
    HMI_TxBuff.Wr_ptr = 0U ;
    HMI_TxBuff.Rd_ptr = 0U ;
    //
    for(u8i=0; u8i<u8Len ;u8i++)
    {
        send_to_HMI_1byte(pBuffs[u8i]);
    }
    //   
}
// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
void cbHMI_SIO_Check(void)
{
    uint8_t  u8i = 0U;  
    uint8_t  u8Counter = 0U;  
    uint16_t u16Add  = 0U;  
 
    if(HMI_RxBuff.Wait_Time == 0x00U)
    {
      if(HMI_RxBuff.Count >= 4U)
      {
        for(HMI_Rx_Q_Counter=0U; HMI_Rx_Q_Counter<HMI_RxBuff.Count; HMI_Rx_Q_Counter++)
        {
            HMI_Rx_Q_Buffer[HMI_Rx_Q_Counter] = HMI_RxBuff.pBuff[HMI_RxBuff.Rd_ptr] ;
            HMI_RxBuff.Rd_ptr = (HMI_RxBuff.Rd_ptr + 1U) % HMI_RX_BUFF_SIZE ;
        }
        //
        HMI_RxBuff.Count  = 0U ;
        // Check Start of Text
        if((HMI_Rx_Q_Buffer[0] == HMI_STX_HI) && (HMI_Rx_Q_Buffer[1] == HMI_STX_LO))
        {
          switch(HMI_Rx_Q_Buffer[3])
          {
            case HMI_RReg_CMD :
                u8Counter = HMI_Rx_Q_Buffer[5];
                if(HMI_Rx_Q_Buffer[4] == 0x03U)
                {
                  Current_Screen =  cvtword(HMI_Rx_Q_Buffer[6],HMI_Rx_Q_Buffer[7]);       
                }
                if(HMI_Rx_Q_Buffer[4] == 0x20U)
                {
                  for(u8i=0; u8i<u8Counter; u8i++)
                  {
                    pPLC_DATA[u8i+11U]  = (uint8_t)(HMI_Rx_Q_Buffer[6+u8i] & 0x0FU) * 10U ;
                    pPLC_DATA[u8i+11U] += (uint8_t)(HMI_Rx_Q_Buffer[6+u8i] & 0x0FU) ;
                  }
                }
                break ;
            case HMI_RRam_CMD :
                u16Add    = cvtword(HMI_Rx_Q_Buffer[4],HMI_Rx_Q_Buffer[5]);
                u8Counter = HMI_Rx_Q_Buffer[6];
                //
                if(u16Add > 99U)
                {
                  pPLC_DATA[u16Add-10U] = cvtword(HMI_Rx_Q_Buffer[7],HMI_Rx_Q_Buffer[8]);
                }
                else
                {
                  for(u8i=0; u8i<u8Counter; u8i++)
                  {
                    pPLC_DATA[u16Add + u8i] = cvtword(HMI_Rx_Q_Buffer[(u8i*2)+7],HMI_Rx_Q_Buffer[(u8i*2)+8]);
                  }
                }
                break;
            case HMI_WRam_CMD :
                break;     
          } 
        }
      }
    }
    else 
    {
       HMI_RxBuff.Wait_Time = HMI_RxBuff.Wait_Time - 1U ;
    }
}

// ---------------------------------------------------------------------------
//  Define Interrut CallBack  definitions.
// ---------------------------------------------------------------------------
//
interrupt [HMI_USART_RXC] void HMI_usart_rx_isr(void)
{
    uint8_t u8Status = 0U;
    uint8_t u8Data = 0U;
    
    u8Status = HMI_UCSRA;;
    u8Data   = HMI_UDR;  
    //
    //-------------------------------------------------------------
    if ((u8Status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN)) == 0)
    {
        HMI_RxBuff.pBuff[HMI_RxBuff.Wr_ptr] = u8Data ;
        HMI_RxBuff.Wr_ptr = (HMI_RxBuff.Wr_ptr + 1U) % HMI_RxBuff.Len ;
        HMI_RxBuff.Wait_Time = 4U ;
        HMI_RxBuff.Count++ ;
    } 
    else {
        HMI_UCSRA = 0x00 ;
    }
} 
// ---------------------------------------------------------------------------
// USART0 Transmitter interrupt service routine
// ---------------------------------------------------------------------------
interrupt [HMI_USART_TXC] void HMI_usart_tx_isr(void)
{
    if (HMI_TxBuff.Wr_ptr != HMI_TxBuff.Rd_ptr )
    {
        HMI_UDR = HMI_TxBuff.pBuff[HMI_TxBuff.Rd_ptr ]; 

        HMI_TxBuff.Rd_ptr = (HMI_TxBuff.Rd_ptr + 1U) % HMI_TxBuff.Len ;       
    }
}

void HMI_comm_init(void)
{ 
#if (HMI_USART_BPS == 9600)
    // HMI USART  initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // HMI USART  Receiver: On
    // HMI USART Transmitter: On
    // HMI USART Mode: Asynchronous
    // HMI USART Baud Rate: 9600
    HMI_UCSRA=0x00;
    HMI_UCSRB=0xD8;
    HMI_UCSRC=0x06;
    HMI_UBRRH=0x00;
    HMI_UBRRL=0x67;  
    //
#elif (HMI_USART_BPS == 19200)
    // HMI USART  initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // HMI USART  Receiver: On
    // HMI USART Transmitter: On
    // HMI USART Mode: Asynchronous
    // HMI USART Baud Rate: 19200
    HMI_UCSRA=0x00;
    HMI_UCSRB=0xD8;
    HMI_UCSRC=0x06;
    HMI_UBRRH=0x00;
    HMI_UBRRL=0x33; 
#elif (HMI_USART_BPS == 38400)
    // HMI USART  initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // HMI USART  Receiver: On
    // HMI USART Transmitter: On
    // HMI USART Mode: Asynchronous
    // HMI USART Baud Rate: 38400
    HMI_UCSRA=0x00;
    HMI_UCSRB=0xD8;
    HMI_UCSRC=0x06;
    HMI_UBRRH=0x00;
    HMI_UBRRL=0x19; 
#endif 
//
}

#pragma used-  /* HMI_SIO.c End Of File !! Well Done */
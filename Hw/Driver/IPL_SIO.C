/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ]  IPL_SIO.c
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
#include "IPL_SIO.h"
#include "Timer0_int.h"
#include "DataConvert.H"
// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//
#define STX         0x02
#define ETX         0x03 
 
#define IPL_STX     0x02        // '@' 
#define IPL_ETX     0x03        // '$' 
#define IPL_ACK     '#'
#define ALL_ADD '?' 
// ---------------------------------------------------------------------------
//  IPL Define Macros .
// ---------------------------------------------------------------------------
// 
#define IPL_COMMAND  1      // IPL_COMMAND  IS EL
#if (IPL_COMMAND == 1)
#define CMD_SIMMER_ON           0x41U
#define CMD_SIMMER_OFF          0x42U
#define CMD_POWER_ON            0x43U
#define CMD_POWER_OFF           0x44U
#define CMD_DISCHARGE_ON        0x45U
#define CMD_DISCHARGE_OFF       0x46U
#define CMD_SHOT_DATA           0x47U
#define CMD_SHOT_DATA_RTN       0x48U
#define CMD_STATUS_REQ          0x4AU
#define CMD_FAIL_CODE           0x4AU
#else 
//
#define CMD_POWER_ON            0x41U
#define CMD_POWER_OFF           0x42U
#define CMD_SHOT_DATA           0x43U
#define CMD_SHOT_DATA_RTN       0x43U
#define CMD_HAND_TEMP           0x44U
#define CMD_STATUS_REQ          0x45U
#define CMD_FAIL_CODE           0x45U
#endif

#define SEND_IPL_PORT    1 
#define IPL_USART_BPS    9600 
//#define IPL_USART_BPS   19200 // imsi
#if (SEND_IPL_PORT == 0) 
//
#define UDR             UDR0
#define IPL_UDR         UDR0 
#define IPL_UCSRA       UCSR0A 
#define IPL_UCSRB       UCSR0B 
#define IPL_UCSRC       UCSR0C 
#define IPL_UBRRH       UBRR0H 
#define IPL_UBRRL       UBRR0L 
#define IPL_USART_RXC   USART0_RXC
#define IPL_USART_TXC   USART0_TXC  
#else 
//
#define UDR             UDR1
#define IPL_UDR         UDR1 
#define IPL_UCSRA       UCSR1A 
#define IPL_UCSRB       UCSR1B 
#define IPL_UCSRC       UCSR1C 
#define IPL_UBRRH       UBRR1H 
#define IPL_UBRRL       UBRR1L 
#define IPL_USART_RXC   USART1_RXC
#define IPL_USART_TXC   USART1_TXC  

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
 
// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
#define IPL232_BUFFER_SIZE  64
uint8_t IPL_rx232_buffer[IPL232_BUFFER_SIZE] ;
volatile uint8_t IPL_rx232_wr_index,IPL_rx232_rd_index ;
// 

// This flag is set on USART0 Receiver buffer overflow
bit IPL_rx232_buffer_overflow; 
// ---------------------------------------------------------------------------
// RS232 Transmitter buffer
// ---------------------------------------------------------------------------
//#define IPL232_BUFFER_SIZE  64
uint8_t IPL_tx232_buffer[IPL232_BUFFER_SIZE];
volatile uint8_t IPL_tx232_wr_index,IPL_tx232_rd_index,IPL_tx232_counter;
// 
// Check
//extern volatile uint8_t IPL_fre_set_data ;
//extern volatile uint8_t on_time_set_data ;
//
// uint8_t *pIPL_SEND_MSG ;
// ---------------------------------------------------------------------------
//  Define Varibales Macro.
// ---------------------------------------------------------------------------
SYSTEM_FLAG IPL_cmd1_flag ;
SYSTEM_FLAG IPL_cmd2_flag ;

#define start_text               IPL_rx232_buffer[0] 
#define IPL_command              IPL_rx232_buffer[1]
#define IPL_data1                IPL_rx232_buffer[2]
#define IPL_data2                IPL_rx232_buffer[3]
#define IPL_data3                IPL_rx232_buffer[4]
#define IPL_data4                IPL_rx232_buffer[5]
#define IPL_chksum               IPL_rx232_buffer[6] 
#define end_text                 IPL_rx232_buffer[7] 

// ---------------------------------------------------------------------------
// Define private function definitions.
// ---------------------------------------------------------------------------
//
//void send_samjin_head(void); 
static void IPL_comm_init(void);
static void send_to_IPL_1byte(uint8_t u8data);
static void send_IPL_bytes(const uint8_t * pBuff);

//static void send_4digit_data(uint16_t u16Data) ;
//static void send_fbyte(flash uint8_t *pBuff) ;
//static void send_2d(uint8_t u8Data);
//static void send_3d(uint8_t u8Data) ;
//static void send_3d_word(uint16_t u16Data) ;
//static void send_4d(uint16_t u16Data) ;
//static void send_5d(uint16_t u16Data) ;
//static void send_2h(uint8_t u8Data);
//static void send_1b(uint8_t u8Data);
//static void send_STX(void) ;
//static void send_ETX(void) ;         

 
//static void send_IPL_bytes_len(const uint8_t * pBuff,uint8_t u8len);
//static void send_4h(uint16_t u16Data);
//static uint8_t IPL_data_ascii_bin(void);
//static void send_IPL_cmd_data(uint8_t u8Cmd , uint8_t u8Data );
//static void send_msg(void);
//static void send_IPL_msg(void) ;
 
static void cbIPL_SIO_Check(void);
// ---------------------------------------------------------------------------
// Define Public function definitions.
// ---------------------------------------------------------------------------
//
/**
 * @brief  IPL UART PORT Init & Callback Set for IPL RxData Parsing
 * 
 */
void IplSioInit(void)
{
    IPL_comm_init();

    canSetTimer0Callback(USE_IPL_SIO_CB_CH,cbIPL_SIO_Check) ;
}

/**
 * @brief   Discharge ON / OFF COMMAND 
 * 
 */
void Send_Discharge_on_cmd(void)
{
    uint8_t msg[8] = {STX,0x08,0x31,0x45,0x30,0x34,0x46,ETX};
    send_IPL_bytes((const uint8_t *)&msg[0]); 
}
void Send_Discharge_off_cmd(void)
{
    uint8_t msg[8] = {STX,0x08,0x31,0x46,0x30,0x34,0x44,ETX};
    send_IPL_bytes((const uint8_t *)&msg[0]); 
}
void Send_Status_req_cmd(void)
{
    uint8_t msg[8] = {STX,0x08,0x31,0x4A,0x30,0x34,0x31,ETX};
    send_IPL_bytes((const uint8_t *)&msg[0]);   
}
/**
 * @brief Setting IPL Voltage , Pulse Width , Hz
 * 
 * @param u16Volt 
 * @param u16Pulse_W 
 * @param u16Hz_Data 
 */
void Send_Shot_data_cmd(uint16_t u16Volt,uint16_t u16Pulse_W,uint8_t u16Hz_Data)
{
    bool bStatus = true ;
    uint8_t u8i ; 
    uint8_t u8j ; 
    uint8_t msg[15] = {STX,0x0F,0x31,0x47,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,ETX} ;   

    if((u16Volt <= IPL_VOLT_MAX) && (u16Volt >= IPL_VOLT_MIN))
    {
        cvtWord3DASC(u16Volt,(uint8_t * const)&msg[4]);
        // u16Pulse_W = 120 , hZ 5
        cvtWord3DASC(u16Pulse_W,(uint8_t * const)&msg[7]);
        cvtByte2DASC((uint8_t)u16Hz_Data,(uint8_t * const)&msg[10]);
        //
        u8j = msg[0];
        for(u8i=1U; u8i<12U; u8i++) 
        {
            u8j = u8j ^ msg[u8i] ; 
        }
        cvtByte2HEX(u8j,(uint8_t * const)&msg[12]);
        //
        if( bStatus == true)
        {
            send_IPL_bytes((const uint8_t *)&msg[0]);  
        }
    }
}
/**
 * @brief   SIMMER ON / OFF COMMAND
 * 
 */
void Send_Simmer_on_cmd(void)
{
    uint8_t msg[8] = {STX,0x08,0x31,0x41,0x30,0x34,0x41,ETX};
    send_IPL_bytes((const uint8_t *)&msg[0]);
}
void Send_Simmer_off_cmd(void)
{
    uint8_t msg[8] = {STX,0x08,0x31,0x41,0x30,0x34,0x39,ETX};
    send_IPL_bytes((const uint8_t *)&msg[0]);  
}
/**
 * @brief   POWER ON / OFF COMMAND 
 * 
 */
void Send_Power_on_cmd(void)
{
    uint8_t msg[8] = {STX,0x08,0x31,0x43,0x30,0x34,0x38,ETX};
    send_IPL_bytes((const uint8_t *)&msg[0]);  
}
void Send_Power_off_cmd(void)
{
    uint8_t msg[8] = {STX,0x08,0x31,0x44,0x30,0x34,0x46,ETX};
    send_IPL_bytes((const uint8_t *)&msg[0]); 
}
/*
void send_IPL_cmd_data(uint8_t u8Cmd , uint8_t u8Data )
{
    send_to_IPL_1byte(STX) ;
    send_to_IPL_1byte(u8Cmd) ; 
    //
    send_to_IPL_1byte('0') ;
    send_3d(u8Data);
    send_to_IPL_1byte('0') ;    
    send_to_IPL_1byte(ETX) ;

}
*/
uint8_t IPL_data_ascii_bin(void)
{
    uint8_t u8Cal_Data ;
    //
    u8Cal_Data  = (IPL_data2 & 0x0F) * 100U ; 
    u8Cal_Data += (IPL_data3 & 0x0F) * 10U ;
    u8Cal_Data += (IPL_data4 & 0x0F)   ;
  
    return  u8Cal_Data ; 
} 
 
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//
/*
void send_4digit_data(uint16_t u16Data) 
{
    uint8_t u8CvtData[4] = {0x00,};
    
    while(IPL_tx232_wr_index != IPL_tx232_rd_index );    
 
    send_to_IPL_1byte('D');
  
    cvtWord4DASC(u16Data,(uint8_t * const)&u8CvtData[0]);
    send_IPL_bytes_len((const uint8_t *)&u8CvtData[0],4U);
    //
    send_to_IPL_1byte(ETX);
    send_STX();
    
}
void send_4digit_data_IPL(uint16_t u16Data) 
{
    uint8_t u8CvtData[4] = {0x00,};
    
    while(IPL_tx232_wr_index != IPL_tx232_rd_index);    

    send_to_IPL_1byte('D');
  
    cvtWord4DASC(u16Data,(uint8_t * const)&u8CvtData[0]);
    send_IPL_bytes_len((const uint8_t *)&u8CvtData[0],4U);
    send_to_IPL_1byte(ETX);

    IPL_UDR = STX ;
    
}
*/
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//
/*
void send_2d(uint8_t u8Data)
{
    uint8_t u8i;
    
    u8i = u8Data / 10U ;
    if( u8i == 0x00 ) send_to_IPL_1byte('0');
    else              send_to_IPL_1byte(u8i+'0');
    
    u8i = u8Data % 10U ;
    send_to_IPL_1byte(u8i+'0');
}  
void send_3d(uint8_t u8Data) 
{
    uint8_t u8i = 0U;
    uint8_t u8j = 0U ; 
  
    u8i =  u8Data / 100 ;
    send_to_IPL_1byte(u8i | 0x30 );
    
    u8j = u8Data % 100 ;
    u8i =  u8j / 10 ;
    send_to_IPL_1byte(u8i | 0x30 );
    
    u8i = u8j % 10 ;     
    send_to_IPL_1byte(u8i | 0x30 );
}
void send_3d_word(uint16_t u16Data) 
{
    uint8_t u8Msg[3] = {0x00U,};

    cvtWord3DASC(u16Data,(uint8_t * const)&u8Msg[0]);
    send_IPL_bytes_len((const uint8_t *)&u8Msg[0],3U);
}
void send_4d(uint16_t u16Data) 
{
    uint8_t u8Msg[4] = {0x00U,};

    cvtWord4DASC(u16Data,(uint8_t * const)&u8Msg[0]);
    send_IPL_bytes_len((const uint8_t *)&u8Msg[0],4U);
}
void send_5d(uint16_t u16Data) 
{
    uint8_t u8Msg[5] = {0x00U,};

    cvtWord5DASC(u16Data,(uint8_t * const)&u8Msg[0]);
    send_IPL_bytes_len((const uint8_t *)&u8Msg[0],5U);
}

void send_2h(uint8_t u8Data)
{
    uint8_t u8i;
    
    u8i = (u8Data >> 4) & 0x0FU ;
    if(u8i <= 9U ) send_to_IPL_1byte(u8i+'0');
    else           send_to_IPL_1byte(u8i - 10U + 'A');
    
    u8i = u8Data & 0x0FU ;
    if(u8i <= 9U ) send_to_IPL_1byte(u8i+'0');
    else           send_to_IPL_1byte(u8i - 10U + 'A');
} 
void send_4h(uint16_t u16Data)
{
    uint8_t u8i;
    
    u8i = (uint8_t)((u16Data >> 12) & 0x0FU) ;
    if(u8i <= 9 )   send_to_IPL_1byte(u8i+'0');
    else            send_to_IPL_1byte(u8i - 10 + 'A');
     
    u8i = (uint8_t)((u16Data >> 8) & 0x0FU) ;
    if(u8i <= 9 )   send_to_IPL_1byte(u8i+'0');
    else            send_to_IPL_1byte(u8i - 10 + 'A');
          
    u8i = (uint8_t)((u16Data >> 4) & 0x0FU) ;
    if(u8i <= 9 )   send_to_IPL_1byte(u8i+'0');
    else            send_to_IPL_1byte(u8i - 10 + 'A');
    
    u8i =(uint8_t)(u16Data & 0x0FU) ;
    if(u8i <= 9 )   send_to_IPL_1byte(u8i+'0');
    else            send_to_IPL_1byte(u8i - 10 + 'A');
} 
void send_1b(uint8_t u8Data)
{
    send_to_IPL_1byte(((u8Data >> 7) & 0x01U ) + '0') ;  // bit 7
    send_to_IPL_1byte(((u8Data >> 6) & 0x01U ) + '0') ;  // bit 6
    send_to_IPL_1byte(((u8Data >> 5) & 0x01U ) + '0') ;  // bit 5
    send_to_IPL_1byte(((u8Data >> 4) & 0x01U ) + '0') ;  // bit 4
    send_to_IPL_1byte(((u8Data >> 3) & 0x01U ) + '0') ;  // bit 3
    send_to_IPL_1byte(((u8Data >> 2) & 0x01U ) + '0') ;  // bit 2
    send_to_IPL_1byte(((u8Data >> 1) & 0x01U ) + '0') ;  // bit 1
    send_to_IPL_1byte((u8Data & 0x01U) + '0') ; // bit 0
} 
//
void send_fbyte(flash uint8_t *pBuff) 
{
     uint8_t u8i = 0U;

    while(IPL_tx232_wr_index != IPL_tx232_rd_index); 
    //
    IPL_tx232_wr_index = 0 ;
    IPL_tx232_rd_index = 0 ;
    //
    while(pBuff[u8i] != 0x00 )
    {
        send_to_IPL_1byte(pBuff[u8i]);
        u8i++ ;   
    }          
}
*/
/**
 * @brief  bufs[0] = stx,Len,data ....
 * 
 * @param pBuff 
 */
void send_IPL_bytes(const uint8_t * pBuff)
{             
    uint8_t u8i = 0U;
    uint8_t u8Bufsize = pBuff[1]; 
    //
    while(IPL_tx232_wr_index != IPL_tx232_rd_index); 
    //
    IPL_tx232_wr_index = 0 ;
    IPL_tx232_rd_index = 0 ;
    //
    for(u8i=1; u8i<u8Bufsize; u8i++)
    {
        send_to_IPL_1byte(pBuff[u8i]) ;
    }
    IPL_UDR = pBuff[0];
    //  
}
/*
static void send_IPL_bytes_len(const uint8_t * pBuff,uint8_t u8len)
{             
    uint8_t u8i = 0U;
    //
    for(u8i=1; u8i<u8len; u8i++)
    {
        send_to_IPL_1byte(pBuff[u8i]) ;
    }
}
 
void send_IPL_Buff(const uint8_t * pBuff) 
{
    uint8_t u8i = 0U ;
    while(IPL_tx232_wr_index != IPL_tx232_rd_index); 
    //
    IPL_tx232_wr_index = 0 ;
    IPL_tx232_rd_index = 0 ;
    //
    while(pBuff[u8i] != 0x00 )
    {
        send_to_IPL_1byte(pBuff[u8i]);
        u8i++ ;   
    } 
    send_msg();              
}

void send_STX(void)
{                   

    IPL_UDR = STX ;
} 
void send_ETX(void)
{   
           
    IPL_UDR = ETX ;
}
//
void send_msg(void)
{
    send_to_IPL_1byte(0x0AU);  
    send_to_IPL_1byte(0x0DU); 
    IPL_UDR = '@' ; 
}
void send_IPL_msg(void) 
{
    uint8_t u8i = 0;
    while(IPL_tx232_wr_index != IPL_tx232_rd_index); 
    //
    IPL_tx232_wr_index = 0 ;
    IPL_tx232_rd_index = 0 ;

    //
    while( pIPL_SEND_MSG[u8i] != 0x00 )
    {
        send_to_IPL_1byte(pIPL_SEND_MSG[u8i]);
        u8i++ ;   
    } 
    send_msg();  
}
*/
/// 
// ****************************************************************************
static void send_to_IPL_1byte(uint8_t u8data)
{   
    IPL_tx232_buffer[IPL_tx232_wr_index] =  u8data ;
    IPL_tx232_wr_index = (IPL_tx232_wr_index + 1U) % IPL232_BUFFER_SIZE ;
}  
// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
/**
 * @brief IPL UART Parsing Function
 * 
 */
static void cbIPL_SIO_Check(void)
{
    uint8_t u8Cal_Data = 0U ;

    if(IPL_rx232_buffer_overflow)
    {
        IPL_rx232_buffer_overflow = 0 ;
        if(IPL_rx232_buffer[0] == IPL_STX)
        {
            switch (IPL_rx232_buffer[3])
            {
                case CMD_SIMMER_ON :    //  
                                        IPL_SIMMER_on_rtn_flag_on ;
                                        break ;
                case CMD_SIMMER_OFF :   //  .
                                        IPL_SIMMER_on_rtn_flag_off ;
                                        break ; 
                case CMD_POWER_ON :     //  
                                        IPL_Power_on_rtn_flag_on ;
                                        break ;  
                case CMD_POWER_OFF :    //  
                                        IPL_Power_on_rtn_flag_off ;
                                        break ;  
                case CMD_FAIL_CODE :    //  
                                        u8Cal_Data = (IPL_rx232_buffer[4] & 0x0FU << 4) ;  
                                        u8Cal_Data = (IPL_rx232_buffer[5] & 0x0FU ) ;  
                                        Power_error_valus = u8Cal_Data ;
                                        break ;   
                case CMD_SHOT_DATA_RTN :    //  
                                        IPL_Shot_data_rtn_flag_on ;
                                        break ;
            }
        }
    }
}

interrupt [IPL_USART_RXC] void IPL_usart_rx_isr(void)
{

    uint8_t u8Status = 0U;
    uint8_t u8Data = 0U;
    
    u8Status = IPL_UCSRA;;
    u8Data   = IPL_UDR;  
    // -----------------------------------------------------------
    if(u8Data == IPL_STX) 
    {
        IPL_rx232_wr_index = 0x00 ;
        IPL_rx232_buffer_overflow = 0 ; 
    }
    else if(u8Data == IPL_ETX)
    {
        IPL_rx232_buffer_overflow = 1 ; 
    }    
    //-------------------------------------------------------------
    if ((u8Status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN)) == 0)
    {
        IPL_rx232_buffer[IPL_rx232_wr_index] = u8Data ;
        IPL_rx232_wr_index = (IPL_rx232_wr_index + 1U) & IPL232_BUFFER_SIZE ;
    } 
    else {
        IPL_UCSRA = 0x00 ;
    }
} 
// ---------------------------------------------------------------------------
// USART0 Transmitter interrupt service routine
// ---------------------------------------------------------------------------
interrupt [IPL_USART_TXC] void IPL_usart_tx_isr(void)
{
    if (IPL_tx232_rd_index != IPL_tx232_wr_index)
    {             
        IPL_UDR = IPL_tx232_buffer[IPL_tx232_rd_index]; 
        IPL_tx232_rd_index = (IPL_tx232_rd_index + 1U) % IPL232_BUFFER_SIZE ;
    }
}

static void IPL_comm_init(void)
{ 

#if (IPL_USART_BPS == 9600)
    // USART0 initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART0 Receiver: On
    // USART0 Transmitter int : On
    // USART0 Mode: Asynchronous
    // USART0 Baud Rate: 9600
    IPL_UCSRA=0x00;
    IPL_UCSRB=0xD8;
    IPL_UCSRC=0x06;
    IPL_UBRRH=0x00;
    IPL_UBRRL=0x67;  
    //
#elif (IPL_USART_BPS == 19200)
    // USART0 initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART0 Receiver: On
    // USART0 Transmitter: On
    // USART0 Mode: Asynchronous
    // USART0 Baud Rate: 19200
    IPL_UCSRA=0x00;
    IPL_UCSRB=0xD8;
    IPL_UCSRC=0x06;
    IPL_UBRRH=0x00;
    IPL_UBRRL=0x33; 
#elif (IPL_USART_BPS == 38400)
    // USART0 initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART0 Receiver: On
    // USART0 Transmitter: On
    // USART0 Mode: Asynchronous
    // USART0 Baud Rate: 38400
    IPL_UCSRA=0x00;
    IPL_UCSRB=0xD8; 
    //IPL_UCSRB=0x98;     // tx int disable
    IPL_UCSRC=0x06;
    IPL_UBRRH=0x00;
    IPL_UBRRL=0x19; 
#endif 
  IPL_rx232_wr_index = 0 ;
  IPL_rx232_rd_index = 0;
  IPL_rx232_buffer_overflow = 0;
  IPL_tx232_wr_index = 0 ;
  IPL_tx232_rd_index = 0 ;
  IPL_tx232_counter = 0 ;
}

#pragma used-  /* IPL_SIO.c End Of File !! Well Done */
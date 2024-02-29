

#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_


#include "def.h"
#include "bsp.h"

#define _USE_HW_TIMER0
#define      HW_TIMER0_MAX_CB         5
#define      HW_TIMER0_CB1            0
#define      HW_PORT_WRITE_CB1        1
#define      HW_PORT_READ_CB1         2 
#define      HW_TEMP_CONTROL_CB       3

#define _USE_HW_PORTREAD
#define      HW_P_READ_BUFF_MAX       2U
#define      HW_PORTREAD_CH0          (0x00U)      
#define      HW_PORTREAD_MAX_CH       9U

#define _USE_HW_PORTWRITE
#define      HW_P_WRITE_BUFF_MAX      2U
#define      HW_PORTWRITE_CH0         (0x00U)  
#define      HW_PORTWRITE_MAX_CH      10U

#define _USE_HW_UART
#define      HW_UART_MAX_CH           1 
#define      HW_COM_OUT_DELAY         3 // 38400

#define _USE_HW_CLI
#define _CLI_UART     _DEF_UART1

#define      HW_CLI_LINE_HIS_MAX      4
#define      HW_CLI_LINE_BUF_MAX      32
#define      HW_CLI_CMD_LIST_MAX      16
#define      HW_CLI_CMD_NAME_MAX      16
#define      HW_CLI_HLP_NAME_MAX      16

#define _USE_HW_ADC
#define      HW_ADC_MAX_CH            6  

#define _USE_HW_TEMP                  1
#define      HW_TEMP_MAX_CH           2

#define _USE_HW_AT24C256              1
#define _USE_HW_MEMORY                1
#define _USE_HW_MCP4822               1
#define      HW_MCP4822_MAX_DA_DATA   0x0FFFU
#define      HW_MCP4822_DA_DATA_MIN   400U
#define      HW_MCP4822_DA_DATA_MAX   4000U // D/A DATA MAX LIMIT 4096 if over 4v then 5v -> 4v -> Amp Gain

typedef enum 
{
  GPIO_A = 0 ,
  GPIO_B ,
  GPIO_C ,
  GPIO_D ,
  GPIO_E ,
  GPIO_F ,
  GPIO_G ,
  GPIO_H ,  
  GPIO_J , 
  GPIO_K , 
  GPIO_L , 
  GPIO_GG = 0xFFU
} GPIO_Port ;

typedef enum 
{
  GPIO_PIN_RESET = 0,
  GPIO_PIN_SET
} GPIO_PinState ; 

typedef struct _data_bits
{
  uint8_t bit0  		: 1 ;
  uint8_t bit1  		: 1 ;
  uint8_t bit2  		: 1 ;
  uint8_t bit3  		: 1 ;
  uint8_t bit4  		: 1 ;
  uint8_t bit5  		: 1 ;
  uint8_t bit6  		: 1 ;
  uint8_t bit7  		: 1 ;
}	DATA_BITS ;

typedef union _System_Flag
{
    DATA_BITS bits ;
    uint8_t valus   ;
}  SYSTEM_FLAG  ;

typedef union _IO_FLAG
{
  DATA_BITS bits ;
  uint8_t   valus ;  
} IO_FLAG_t ;
#endif /* SRC_HW_HW_DEF_H_ */

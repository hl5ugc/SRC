

#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_


#include "def.h"
#include "bsp.h"

#define _USE_HW_TIMER0
#define      HW_TIMER0_MAX_CB         5
#define      HW_AP_TIMER0_CB          0
//#define      HW_UART_TX_TIMER0_CB     1
//#define      HW_UART_RX_TIMER0_CB     2
#define      HW_HMI_SIO_TIMER0_CB     1
#define      HW_IPL_SIO_TIMER0_CB     2 
 

// #define _USE_HW_PORTREAD
// #define      HW_P_READ_BUFF_MAX       2U
// #define      HW_PORTREAD_CH0          (0x00U)      
// #define      HW_PORTREAD_MAX_CH       9U

// #define _USE_HW_PORTWRITE
// #define      HW_P_WRITE_BUFF_MAX      2U
// #define      HW_PORTWRITE_CH0         (0x00U)  
// #define      HW_PORTWRITE_MAX_CH      10U

#define _USE_HW_UART
#define      HW_UART_MAX_CH           1 
#define      HW_COM_OUT_DELAY         3 // 38400

/* 
#define _USE_HW_CLI
#define _CLI_UART     _DEF_UART1

#define      HW_CLI_LINE_HIS_MAX      4
#define      HW_CLI_LINE_BUF_MAX      32
#define      HW_CLI_CMD_LIST_MAX      16
#define      HW_CLI_CMD_NAME_MAX      16
#define      HW_CLI_HLP_NAME_MAX      16
*/
#define _USE_HW_ADC
#define      HW_INTERRUPT_ENABALE     0
#define      HW_ADC_MAX_CH            4

// #define _USE_HW_TEMP                  1
// #define      HW_TEMP_MAX_CH           2

#define _USE_HW_AT24C256              1
#define        _AT24C256 
#define _USE_HW_MEMORY                1
#define _USE_HW_MCP4822               1
#define      HW_MCP4822_MAX_DA_DATA   0x0FFFU
#define      HW_MCP4822_DA_DATA_MIN   000U
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
// 
// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
//
#define SCR_INTRO           0U
#define SCR_SYSCHECK        6U
#define SCR_MODE_SELECT     8U
#define SCR_MAIN            10U
#define SCR_CHANGE_PASS     30U
#define SCR_PASSWORD        30U
#define SCR_COUNT_SERIAL    33U
#define SCR_ST_SETTING      33U
#define SCR_CALI            35U
#define SCR_INFO            40U
#define SCR_KEYPAD          30U
#define SCR_HW_TEST_MENU    90U 

#define DURATION_MAX        20U
#define DURATION_MIN        1U
#define FREQUENCE_MAX       10U
#define FREQUENCE_MIN       1U
#define FLUENCE_MAX         40U  // DURATION_MAX * 40
#define FLUENCE_MIN         1U

#define IPL_VOLT_MAX        350U
#define IPL_VOLT_MIN        150U 
#define LEVEL_DAT_MAX       31U
#define LEVEL_DAT_MIN       1U

#define MAX_FRQ_DATA        10U
#define MIN_FRQ_DATA        1U
//
#define MAX_ON_TIME_DATA    100U
#define MIN_ON_TIME_DATA    20U
// ---------------------------------------------------------------------------
// Bit control PortA - PortG
// --------------------------------------------------------------------------- 
//
//
#define IPL_TRIG_EN             PORTB.6 = 0
#define IPL_TRIG_DIS            PORTB.6 = 1
#define SSR2_DRIVER_EN          PORTC.4 = 1
#define SSR2_DRIVER_DIS         PORTC.4 = 0
#define SSR1_DRIVER_EN          PORTC.5 = 1
#define SSR1_DRIVER_DIS         PORTC.5 = 0
//
#define COOL_DRIVER_EN          PORTC.5 = 1
#define COOL_DRIVER_DIS         PORTC.5 = 0
//
#define BLUE_LED_ON             PORTE.3 = 1
#define BLUE_LED_OFF            PORTE.3 = 0
#define BUZZER_ON               PORTE.4 = 1
#define BUZZER_OFF              PORTE.4 = 0
#define RED_LED_ON              PORTE.5 = 1
#define RED_LED_OFF             PORTE.5 = 0
#define OUTPUT_LED_ON           PORTE |= 0b00101000 
#define OUTPUT_LED_OFF          PORTE &= 0b11010111
//
#define DRIVER1_OUT_ON          PORTC.2 = 0 
#define DRIVER2_OUT_ON          PORTC.3 = 0 
#define DRIVER3_OUT_ON          PORTC.6 = 0 
#define DRIVER4_OUT_ON          PORTC.7 = 0 
#define DRIVER1_OUT_OFF         PORTC.2 = 1
#define DRIVER2_OUT_OFF         PORTC.3 = 1 
#define DRIVER3_OUT_OFF         PORTC.6 = 1 
#define DRIVER4_OUT_OFF         PORTC.7 = 1 
//
#define Is_INTERLOCK_ON         ((PINA & 0x01) == 0x00)
#define Is_Not_INTERLOCK_ON     ((PINA & 0x01) != 0x00)
#define Is_RUN_SW_ON            ((PINA & 0x02) == 0x00)
#define Is_Not_RUN_SW_ON        ((PINA & 0x02) != 0x00)
#define Is_FOOT_SW_ON           ((PINA & 0x02) == 0x00)
#define Is_Not_FOOT_SW_ON       ((PINA & 0x02) != 0x00)
#define Is_HP_CONNECT_SW_ON     ((PINA & 0x04) == 0x00)  
#define Is_Not_HP_CONNECT_SW_ON ((PINA & 0x04) != 0x00)  
#define Is_HP_FILTER_OK         ((PINA & 0x08) == 0x00)
#define Is_Not_HP_FILTER_OK     ((PINA & 0x08) != 0x00)
#define Is_SP1_SW_OK            ((PINA & 0x10) == 0x00)
#define Is_Not_SP1_SW_OK        ((PINA & 0x10) != 0x00)
#define Is_SP2_SW_OK            ((PINA & 0x20) == 0x00)
#define Is_Not_SP2_SW_OK        ((PINA & 0x20) != 0x00)
#define Is_RPM_SW_ON            ((PINA & 0x40) == 0x00)
#define Is_Not_RPM_SW_ON        ((PINA & 0x40) != 0x00)
//
#define Is_LD_CNT_ON            ((PINC & 0x01) == 0x00)
#define Is_Not_LD_CNT_ON        ((PINC & 0x01) != 0x00)
#define Is_LD_ALRAM_ON          ((PINC & 0x02) == 0x00)
#define Is_Not_LD_ALRAM_ON      ((PINC & 0x02) != 0x00)
#endif /* SRC_HW_HW_DEF_H_ */

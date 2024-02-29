

#ifndef SRC_COMMON_DEF_H_
#define SRC_COMMON_DEF_H_


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define _USE_ATMEGA128

#ifdef  _USE_ATMEGA8
#include <mega8.h>
#endif

#ifdef  _USE_ATMEGA128
#include <mega128a.h>
#endif

#include <delay.h>

/* 
#define _DEF_BIT0         ((uint8_t)0x01)
#define _DEF_BIT1         ((uint8_t)0x02)
#define _DEF_BIT2         ((uint8_t)0x04)
#define _DEF_BIT3         ((uint8_t)0x08)
#define _DEF_BIT4         ((uint8_t)0x10)
#define _DEF_BIT5         ((uint8_t)0x20)
#define _DEF_BIT6         ((uint8_t)0x40)
#define _DEF_BIT7         ((uint8_t)0x80)

#define _DEF_PIN0         (0x00U)
#define _DEF_PIN1         (0x01U)
#define _DEF_PIN2         (0x02U)
#define _DEF_PIN3         (0x03U)
#define _DEF_PIN4         (0x04U)
#define _DEF_PIN5         (0x05U)
#define _DEF_PIN6         (0x06U)
#define _DEF_PIN7         (0x07U) 
*/
#define _DEF_BIT0         (0x00U)
#define _DEF_BIT1         (0x01U)
#define _DEF_BIT2         (0x02U)
#define _DEF_BIT3         (0x03U)
#define _DEF_BIT4         (0x04U)
#define _DEF_BIT5         (0x05U)
#define _DEF_BIT6         (0x06U)
#define _DEF_BIT7         (0x07U)

#define _DEF_MBIT0        ((uint8_t)0x01)
#define _DEF_MBIT1        ((uint8_t)0x02)
#define _DEF_MBIT2        ((uint8_t)0x04)
#define _DEF_MBIT3        ((uint8_t)0x08)
#define _DEF_MBIT4        ((uint8_t)0x10)
#define _DEF_MBIT5        ((uint8_t)0x20)
#define _DEF_MBIT6        ((uint8_t)0x40)
#define _DEF_MBIT7        ((uint8_t)0x80)

#define _DEF_PIN0         (0x00U)
#define _DEF_PIN1         (0x01U)
#define _DEF_PIN2         (0x02U)
#define _DEF_PIN3         (0x03U)
#define _DEF_PIN4         (0x04U)
#define _DEF_PIN5         (0x05U)
#define _DEF_PIN6         (0x06U)
#define _DEF_PIN7         (0x07U) 

#define _DEF_UART1        0
#define _DEF_UART2        1

typedef enum
{
  UART_9600BPS,
  UART_19200BPS,
  UART_38400BPS,

} UART_BPS;

#define DEF_DRV_READY         (0x00)
#define DEF_DRV_RUN           (0x01)
#define DEF_DRV_POWER         (0x02)

#endif /* SRC_COMMON_DEF_H_ */

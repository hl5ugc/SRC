

#ifndef SRC_COMMON_DEF_H_
#define SRC_COMMON_DEF_H_


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define _USE_ATMEGA128

#ifdef  _USE_ATMEGA128
#include <mega128a.h>
#endif

#include <delay.h>

#define PARAM_UNUSED(x)   ((void)x)

#define _DEF_BIT0         (0x0001U)
#define _DEF_BIT1         (0x0002U)
#define _DEF_BIT2         (0x0004U)
#define _DEF_BIT3         (0x0008U)
#define _DEF_BIT4         (0x0010U)
#define _DEF_BIT5         (0x0020U)
#define _DEF_BIT6         (0x0040U)
#define _DEF_BIT7         (0x0080U)
#define _DEF_BIT8         (0x0100U)
#define _DEF_BIT9         (0x0200U)
#define _DEF_BIT10        (0x0400U)
#define _DEF_BIT11        (0x0800U)
#define _DEF_BIT12        (0x1000U)
#define _DEF_BIT13        (0x2000U)
#define _DEF_BIT14        (0x4000U)
#define _DEF_BIT15        (0x8000U)

#define _DEF_PIN0         (0x00U)
#define _DEF_PIN1         (0x01U)
#define _DEF_PIN2         (0x02U)
#define _DEF_PIN3         (0x03U)
#define _DEF_PIN4         (0x04U)
#define _DEF_PIN5         (0x05U)
#define _DEF_PIN6         (0x06U)
#define _DEF_PIN7         (0x07U) 

#define _DEF_MBIT0        ((uint8_t)0x01U)
#define _DEF_MBIT1        ((uint8_t)0x02U)
#define _DEF_MBIT2        ((uint8_t)0x04U)
#define _DEF_MBIT3        ((uint8_t)0x08U)
#define _DEF_MBIT4        ((uint8_t)0x10U)
#define _DEF_MBIT5        ((uint8_t)0x20U)
#define _DEF_MBIT6        ((uint8_t)0x40U)
#define _DEF_MBIT7        ((uint8_t)0x80U)
#define _DEF_MBIT8        ((uint16_t)0x0100U)
#define _DEF_MBIT9        ((uint16_t)0x0200U)
#define _DEF_MBIT10       ((uint16_t)0x0400U)
#define _DEF_MBIT11       ((uint16_t)0x0800U)
#define _DEF_MBIT12       ((uint16_t)0x1000U)
#define _DEF_MBIT13       ((uint16_t)0x2000U)
#define _DEF_MBIT14       ((uint16_t)0x4000U)
#define _DEF_MBIT15       ((uint16_t)0x8000U)


#define _DEF_UART1        0
#define _DEF_UART2        1

typedef enum
{
  UART_9600BPS,
  UART_19200BPS,
  UART_38400BPS,

} UART_BPS;
typedef enum 
{
    FILTER_UNSELECT = 0U,
    FILTER_510      = 1U,
    FILTER_560      = 2U,
    FILTER_585      = 3U,
    FILTER_640      = 4U,
    FILTER_700      = 5U,
    FILTER_800      = 6U,
    FILTER_900      = 7U

} FILTER_e ;

#endif /* SRC_COMMON_DEF_H_ */

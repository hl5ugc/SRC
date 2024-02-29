/* --------------------------------------------------------------------------
 * [ PROJECT   ]
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2023 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]
 * [ Filename  ]  uart.c
 * [ Version   ]  1.0
 * [ Created   ]
 * --------------------------------------------------------------------------
 * Revision History :
 * ------------------------------------------------------------------
 *
 *  *.본소스 코드를 이용하는 것은 본 조항을 사용자가 암묵적으로
 *    동의 한것으로 간주 합니다.
 *  *.본 소스코드는 개인학습 및 연구 개발용으로 자유롭게 사용가능
 *    합니다.
 *  *.본소스를 사용하여 2차 저작을 하거나 재배포 할 시에는 반드시
 *    SAMJIN ELECTRONICS의 회사명을 반드시 명시하여야 합니다.
 *  *.본 소스코드의 판매 및 영리 활동을 금지합니다 .
 *  *.본 조항 및 원저자 표시의 수정 및 삭제를 금지합니다.
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

/* Includes */
#include "qbuffer.h"

// ---------------------------------------------------------------------------
// Define Global define
// ---------------------------------------------------------------------------
//

//
// ---------------------------------------------------------------------------
// Define typedef
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
//  Macro Define .
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// ---------------------------------------------------------------------------
//
void qbufferInit(void)
{

}

bool qbufferCreate(qUartBuff_t *p_node, uint8_t *p_buf, uint8_t length)
{
  bool result = true;

  p_node->in    = 0;
  p_node->out   = 0;
  p_node->len   = length;
  p_node->p_buf = p_buf;

  return result;
}

bool qbufferWrite(qUartBuff_t *p_node, const uint8_t *p_data, uint8_t length)
{
  bool bRet = true;
  uint8_t u8i = 0x00U ;
  uint8_t u8NextWr = 0x00U ;

  for (u8i=0; u8i<length; u8i++)
  {
    u8NextWr = (p_node->in + 1) % p_node->len;

    if(u8NextWr != p_node->out)
    {
      if(p_node->p_buf != NULL)
      {
         p_node->p_buf[p_node->in] = p_data[u8i]; 
      }
      p_node->in = u8NextWr ;
    }
    else
    {
      bRet = false ;
    }
  }

  return bRet;
}

bool qbufferRead(qUartBuff_t *p_node, uint8_t *p_data, uint8_t length)
{
  bool bRet = false;
  uint8_t i ;
  for (i=0; i<length; i++)
  {
    if (p_node->out != p_node->in)
    {
      p_data[i] = p_node->p_buf[p_node->out];
      if(++p_node->out >= p_node->len )
      {
        p_node->out = 0 ; 
      }
      bRet = true;
    }
  }
/*   if (p_node->p_buf != NULL)
  {
    for (i=0; i<length; i++)
    {
      p_data[i] = p_node->p_buf[p_node->out];
      if (p_node->out != p_node->in)
      {
        p_node->out = (p_node->out + 1) % p_node->len;
        result = true ;
      }
      else
      {
        bRet = false;
        break;
      }
    }
  } */

  return bRet;
}

bool qbufferReadByte(qUartBuff_t *p_node, uint8_t *p_data)
{
  bool bRet = false ;

  if (p_node->out != p_node->in)
  {
    *p_data = p_node->p_buf[p_node->out];
    if(++p_node->out >= p_node->len )
    {
      p_node->out = 0 ; 
    }
    bRet = true;
  }
/*   if (p_node->p_buf != NULL)    // Check Created Buff
  {
     *p_data = p_node->p_buf[p_node->out];

      if(p_node->out != p_node->in)
      {
        p_node->out = (p_node->out + 1) % p_node->len;
         bRet = true ;
      }
  } */

  return bRet;
}
/**
 * @brief Function How many bytes in Buffer
 * 
 * @param p_node    buffer struct
 * @return uint8_t  Read Available bytes in buffer
 */
uint8_t qbufferRxAvailable(qUartBuff_t *p_node)
{
  uint8_t u8Ret = 0;

  if(p_node->out == p_node->in ) {
    u8Ret = 0 ;  
  }
  else if(p_node->out > p_node->in )
  {
    u8Ret = (uint8_t)(p_node->len - p_node->out );
    u8Ret = (uint8_t)(u8Ret + p_node->in) ;
  }
  else {
    u8Ret = (uint8_t)(p_node->in - p_node->out) ;
  }

  return u8Ret;
}
/*
*/
uint8_t qbufferTxAvailable(qUartBuff_t *p_node)
{
  uint8_t u8Ret  = 0 ;

  if(p_node->in == p_node->out ) {
    u8Ret = p_node->len ;  
  }
  else if(p_node->in > p_node->out )
  {
    u8Ret = (uint8_t)(p_node->len - p_node->in );
    u8Ret = (uint8_t)(u8Ret + p_node->out) ;
  }
  else 
  {
    u8Ret = (uint8_t)(p_node->out - p_node->in) ;
  }

  return u8Ret;
}

bool qbufferEmpty(qUartBuff_t *p_node)
{
  bool bResult = false ;

  if(p_node->in ==   p_node->out)
  {
    bResult = true ;
  }
  //
  return bResult ;
}
void qbufferFlush(qUartBuff_t *p_node)
{
  p_node->in  = 0;
  p_node->out = 0;
}
// ---------------------------------------------------------------------------
// Define private function definitions.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//

 /* src/common/hw/include/uart.h End Of File !! Well Done */
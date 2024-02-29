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
 *  *.���ҽ� �ڵ带 �̿��ϴ� ���� �� ������ ����ڰ� �Ϲ�������
 *    ���� �Ѱ����� ���� �մϴ�.
 *  *.�� �ҽ��ڵ�� �����н� �� ���� ���߿����� �����Ӱ� ��밡��
 *    �մϴ�.
 *  *.���ҽ��� ����Ͽ� 2�� ������ �ϰų� ����� �� �ÿ��� �ݵ��
 *    SAMJIN ELECTRONICS�� ȸ����� �ݵ�� ����Ͽ��� �մϴ�.
 *  *.�� �ҽ��ڵ��� �Ǹ� �� ���� Ȱ���� �����մϴ� .
 *  *.�� ���� �� ������ ǥ���� ���� �� ������ �����մϴ�.
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
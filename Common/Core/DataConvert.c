//
// =======================================================================
// [ PROJECT   ]
// -----------------------------------------------------------------------
// [ License   ] SAMJIN ELECTRONICS
// [ Author    ] Copyright 2021-08 By HAG-SEONG KANG
// [ E-MAIL    ] hl5ugc@nate.com (82)10- 3841-9706
// [ C  P  U   ]
// [ Compller  ] CodeWizardAVR V3.12 Professional
// [ Filename  ] DataConvert.C
// [ Version   ] 1.0
// [ Created   ] 2024-01-17
// ----------------------------------------------------------------------------
// Revision History :
// ----------------------------------------------------------------------------
// Author         Date          Comments on this revision
// ----------------------------------------------------------------------------
// HAG-SEONG KANG 2021-12-09    First release of header file
//
//
// ============================================================================
//
//
//
//

#include "DataConvert.H"


// ---------------------------------------------------------------------------
// Define basic
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
//  Define typedef
// ---------------------------------------------------------------------------
//
typedef struct
{
  uint8_t   u8Data1 ;
  uint8_t   u8Data2 ;
} cvt_u16_u8_t;
typedef struct
{
  uint8_t   u8Data1 ;
  uint8_t   u8Data2 ;
  uint8_t   u8Data3 ;
  uint8_t   u8Data4 ;
} cvt_u32_u8_t;
//
typedef union
{
    uint16_t        u16Val ;
    cvt_u16_u8_t    u8Val ;
} cvt_u16_t ;
//
typedef union
{
    uint32_t        u32Val ;
    cvt_u32_u8_t    u8Val ;
} cvt_u32_t ;
// ---------------------------------------------------------------------------
//  Define Constants.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
// Bit control PortA - PortG
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
//  Define Varibales.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
//  Define Private function protoypye.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
//  Define private function definitions.
// ---------------------------------------------------------------------------
//
static uint8_t hex2bin(const uint8_t  * pSBuff);
static uint8_t asc2bin(const uint8_t  * pBuff);
static uint8_t HexLowToUpper(const uint8_t LowerAlpabet);
// ---------------------------------------------------------------------------
// Declare your private variables here
// ---------------------------------------------------------------------------
//


// ---------------------------------------------------------------------------
//  Define Public function definitions.
// ---------------------------------------------------------------------------
//
/*
 * @brief Byte data convert to 2digit ASCII Decimal
 *
 */
void cvtByte2DASC(uint8_t u8Data,uint8_t * const pBuff)
{
    uint8_t u8Cal = 0x00U ;
    //
    if(u8Data > 99U) { u8Data =  u8Data % 100U ; }
    //
    u8Cal =  u8Data / 10U ;
    pBuff[0x00U] = u8Cal + 0x30U ;
    //
    u8Cal =  u8Data % 10U ;
    pBuff[0x01U] = u8Cal + 0x30U ;
}
/*
 * @brief
 *
 */
void cvtByte3DASC(uint8_t u8Data,uint8_t * const pBuff)
{
    uint8_t u8Cal = 0x00U ;
    uint8_t u8Cal2 = 0x00U ;
    //
    u8Cal =  u8Data / 100 ;
    pBuff[0x00U] = u8Cal + 0x30U ;
    //
    u8Cal =  u8Data % 100 ;
    u8Cal2 = u8Cal / 10 ;
    pBuff[0x01U] = u8Cal2 + 0x30U ;
    //
    u8Cal2 =  u8Cal % 10 ;
    pBuff[0x02U] = u8Cal2 + 0x30U ;
}
/*
 * @brief
 *
 */
void cvtWord3DASC(uint16_t u16Data,uint8_t * const pBuff)
{
    uint8_t u8Cal = 0x00U ;
    uint8_t u8Cal2 = 0x00U ;
    //
    if(u16Data > 999) { u16Data =  u16Data % 1000 ;  }
    //
    u8Cal =  u16Data / 100 ;
    pBuff[0x00U]  = u8Cal + 0x30U ;
    //
    u8Cal =  u16Data % 100 ;
    u8Cal2 = u8Cal / 10 ;
    pBuff[0x01U]  = u8Cal2 + 0x30U ;
    //
    u8Cal2 =  u8Cal % 10 ;
    pBuff[0x02U]  = u8Cal2 + 0x30U ;
}
/*
 * @brief
 *
 */
void cvtWord4DASC(uint16_t u16Data,uint8_t * const pBuff)
{
    uint8_t  u8Cal = 0x00U ;
    uint16_t u16Cal = 0x00U ;
    //
    if(u16Data > 9999U) { u16Data =  u16Data % 10000U ;  }
    //
    u8Cal =  u16Data / 1000U ;
    pBuff[0x00U] = u8Cal + 0x30U ;
    //
    u16Cal =  u16Data % 1000U ;
    u8Cal = u16Cal / 100U ;
    pBuff[0x01U]  = u8Cal + 0x30U ;
    //
    u16Cal =  u16Cal % 100U  ;
    u8Cal =  u16Cal / 10U ;
    pBuff[0x02U]  = u8Cal + 0x30U ;
    //
    u8Cal =  u16Cal % 10U ;
    pBuff[0x03U]  = u8Cal + 0x30U ;
}
/*
 * @brief
 *
 */
void cvtWord5DASC(uint16_t u16Data,uint8_t * const pBuff)
{
    uint8_t  u8Cal = 0x00U ;
    uint16_t u16Cal = 0x00U ;
    //
    u8Cal  =  u16Data / 10000U ;
    pBuff[0x00U] = u8Cal + 0x30U ;
    //
    u16Cal =  u16Data % 10000U ;
    u8Cal  = u16Cal / 1000U ;
    pBuff[0x01U] = u8Cal + 0x30U ;
    //
    u16Cal =  u16Cal % 1000U ;
    u8Cal  =  u16Cal / 100U ;
    pBuff[0x02U] = u8Cal + 0x30U ;
    //
    u16Cal =  u16Cal % 100U ;
    u8Cal  = u16Cal / 10U ;
    pBuff[0x03U] = u8Cal + 0x30U ;
    //
    u8Cal =  u16Cal % 10U ;
    pBuff[0x04U] = u8Cal + 0x30U ;
}
/*
 * @brief
 *
 */
void cvtByte2HEX(uint8_t u8Data,uint8_t * const pBuff)
{
    uint8_t u8Cal = 0x00U ;
    //
    u8Cal =  (u8Data >> 4) & 0x0FU ;
    if(u8Cal <= 9U)  { pBuff[0x00U] = u8Cal + 0x30U ; }
    else             { pBuff[0x00U] = u8Cal + 0x37U ; }
    //
    u8Cal =  (u8Data  & 0x0FU);
    if(u8Cal <= 9U)  { pBuff[0x01U] = u8Cal + 0x30U ; }
    else             { pBuff[0x01U] = u8Cal + 0x37U ; }
}
/*
 * @brief
 *
 */
void cvtWord4HEX(uint16_t u16Data,uint8_t * const pBuff)
{
    uint8_t u8Cal = 0x00U ;
    //
    u8Cal =  (u16Data >> 12U) & 0x0FU ;
    if(u8Cal <= 9U)  { pBuff[0x00U] = u8Cal + 0x30U ; }
    else             { pBuff[0x00U] = u8Cal + 0x37U ; }
    //
    u8Cal =  (u16Data >> 8U) & 0x0FU ;
    if(u8Cal <= 9U)  { pBuff[0x01U] = u8Cal + 0x30U ; }
    else             { pBuff[0x01U] = u8Cal + 0x37U ; }
    //
    u8Cal =  (u16Data >> 4U) & 0x0FU ;
    if(u8Cal <= 9U)  { pBuff[0x02U] = u8Cal + 0x30U ; }
    else             { pBuff[0x02U] = u8Cal + 0x37U ; }
    //
    u8Cal =  (u16Data  & 0x0FU);
    if(u8Cal <= 9U)  { pBuff[0x03U] = u8Cal + 0x30U ; }
    else             { pBuff[0x03U] = u8Cal + 0x37U ; }
}
/*
 * @brief
 *
 */
void  cvtByte7BASC(uint8_t u8Data,uint8_t * const pBuff)
{
    pBuff[0x00U] = (((u8Data >> 7U) & 0x01U) + '0') ;   
    pBuff[0x01U] = (((u8Data >> 6U) & 0x01U) + '0') ;  
    pBuff[0x02U] = (((u8Data >> 5U) & 0x01U) + '0') ; 
    pBuff[0x03U] = (((u8Data >> 4U) & 0x01U) + '0') ;  
    pBuff[0x04U] = (((u8Data >> 3U) & 0x01U) + '0') ; 
    pBuff[0x05U] = (((u8Data >> 2U) & 0x01U) + '0') ;  
    pBuff[0x06U] = (((u8Data >> 1U) & 0x01U) + '0') ;  
    pBuff[0x07U] = ((u8Data         & 0x01U) + '0') ;
}

/**
 * @brief
 *
 * @param pBuff
 * @return uint8_t
 */
uint8_t hex2bin(const uint8_t * pSBuff)
{
    uint8_t u8Cal = 0x00U ;
    uint8_t u8Caltemp = 0x00U ;
    uint8_t pBuff[2] = {0x00U,0x00U} ;
    //
    pBuff[0x00U]  = HexLowToUpper(pSBuff[0x00U]);
    pBuff[0x01U]  = HexLowToUpper(pSBuff[0x01U]);
    //
    u8Cal = pBuff[0x00U] ;
    if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
    else              { u8Cal = u8Cal - 0x37U; }
    u8Caltemp = ((u8Cal << 4 )  & 0xF0U ) ;
    //
    u8Cal = pBuff[0x01U] ;
    if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
    else              { u8Cal = u8Cal - 0x37U; }
    u8Caltemp = u8Caltemp +  u8Cal   ;
    //
    return u8Caltemp ;
}
/**
 * @brief LowerAlpabet To UpperAlpabet
 * 
 * @param LowerApabet 
 * @return uint8_t : UpperAlpabet
 */
uint8_t HexLowToUpper(const uint8_t LowerAlpabet)
{
    uint8_t u8Result = 0x00U;

    if((LowerAlpabet >= 'a') && (LowerAlpabet <= 'z'))
    {
        if(LowerAlpabet <= 'f')
        {
            u8Result  = LowerAlpabet - 32U ;
        }
        else {
             u8Result  = 0x30U ;
        }
    }
    else { u8Result = LowerAlpabet ; }

    return (u8Result);
}
/**
 * @brief   ASCII Decimal Data Convert To uint8_t Data
 * 
 * @param   pBuff   ASCII Decimal
 * @return  uint8_t Converted uint8_t Data
 */
uint8_t asc2bin(const uint8_t * pBuff) 
{
    uint8_t u8Ret = 0x00U ;
    uint8_t u8Cal = 0x00U ;

    u8Cal = pBuff[0x00U] ;
    if((u8Cal >= '0') && (u8Cal <= '9'))
    {
        u8Ret = (u8Cal - 0x30U) ;
    }

    return (u8Ret);
}
/*
 * @brief
 *
 */
//
void cvt2HEXBin(const uint8_t * pSBuff , uint8_t * const pData)
{
    uint8_t u8Cal = 0x00U ;
    uint8_t u8Len = 0x00U ;
    uint8_t u8Caltemp = 0x00U ;
    uint8_t pBuff[4] = {0x00,};
    //
    u8Len = strlen(pSBuff) ;

    for(u8Cal = 0; u8Cal<u8Len; u8Cal++)
    {
        pBuff[u8Cal]  = HexLowToUpper(pSBuff[u8Cal]);
    }
    //
    if(u8Len == 2) 
    {
        u8Cal = pBuff[0x00U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u8Caltemp = ((u8Cal << 4 )  & 0xF0U ) ;
        //
        u8Cal = pBuff[0x01U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u8Caltemp = u8Caltemp +  u8Cal   ;
    //
    }
    else if(u8Len == 1)
    {
        u8Cal = pBuff[0x00U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        //
        u8Caltemp =  u8Cal  & 0x0FU;
    }
    else { u8Caltemp = 0 ; }
    //
    pData[0x00U] =  u8Caltemp ;
}
/*
 * @brief 4Byte Ascii Hex Convert to uint16_t data
 *
 */
void  cvt4HEXBin(const uint8_t * pSBuff , uint16_t * const pData)
{
    uint8_t  u8Cal = 0x00U ;
    uint8_t  u8Len = 0x00U ;
    uint16_t u16Caltemp = 0x00U;
    uint8_t  pBuff[4] = {0x00,};
    //
    u8Len = strlen(pSBuff) ;
    for(u8Cal = 0;u8Cal<u8Len; u8Cal++)
    {
        pBuff[u8Cal]  = HexLowToUpper(pSBuff[u8Cal]);
    }
    //
    if(u8Len == 4)
    {
        u8Cal = pBuff[0x00U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = (((uint16_t)u8Cal << 12U)  & 0xF000U ) ;
        //
        u8Cal = pBuff[0x01U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp + (((uint16_t)u8Cal << 8U)  & 0x0F00U ) ;
        //
        u8Cal = pBuff[0x02U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp + (((uint16_t)u8Cal << 4U)  & 0x00F0U ) ;
        //
        u8Cal = pBuff[0x03U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp +  (uint16_t)u8Cal   ;
        //
    }
    else if(u8Len == 3)
    {
        //
        u8Cal = pBuff[0x00U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = (((uint16_t)u8Cal << 8U)  & 0x0F00U ) ;
        //
        u8Cal = pBuff[0x01U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp + (((uint16_t)u8Cal << 4U)  & 0x00F0U ) ;
        //
        u8Cal = pBuff[0x02U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp +  (uint16_t)u8Cal   ;
        //
    }
    else if(u8Len == 2)
    {
        u8Cal = pBuff[0x00U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = (((uint16_t)u8Cal << 4U)  & 0x00F0U ) ;
        //
        u8Cal = pBuff[0x01U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp +  (uint16_t)u8Cal   ;
        //
    }
    else if(u8Len == 1)
    {
        u8Cal = pBuff[0x00U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = (uint16_t)u8Cal   ;
        //
    }
    else { u16Caltemp = 0 ; }
    
    pData[0x00U] =  u16Caltemp ;
  
}
/*
 * @brief
 *
 */
void  cvt6HEXBin(const uint8_t * pSBuff , uint32_t * const pData)
{

    uint8_t  u8Len = 0x00U ;
    cvt_u32_t u32Caltemp  ;
    //
    u32Caltemp.u32Val =  0x00U ;
    //
    u8Len = strlen(pSBuff) ;
    //
    if(u8Len == 8)
    {
        u32Caltemp.u8Val.u8Data4 = hex2bin(&pSBuff[0x00U]);
        u32Caltemp.u8Val.u8Data3 = hex2bin(&pSBuff[0x02U]);
        u32Caltemp.u8Val.u8Data2 = hex2bin(&pSBuff[0x04U]);
        u32Caltemp.u8Val.u8Data1 = hex2bin(&pSBuff[0x06U]);
    }
    else if(u8Len == 6)
    {
        u32Caltemp.u8Val.u8Data4 = 0 ;
        u32Caltemp.u8Val.u8Data3 = hex2bin(&pSBuff[0x00U]);
        u32Caltemp.u8Val.u8Data2 = hex2bin(&pSBuff[0x02U]);
        u32Caltemp.u8Val.u8Data1 = hex2bin(&pSBuff[0x04U]);
    }
    else if(u8Len == 4)
    {
        u32Caltemp.u8Val.u8Data4 = 0 ;
        u32Caltemp.u8Val.u8Data3 = 0 ;
        u32Caltemp.u8Val.u8Data2 = hex2bin(&pSBuff[0x00U]);
        u32Caltemp.u8Val.u8Data1 = hex2bin(&pSBuff[0x02U]);
    }
    else if(u8Len == 2)
    {
        u32Caltemp.u8Val.u8Data4 = 0 ;
        u32Caltemp.u8Val.u8Data3 = 0 ;
        u32Caltemp.u8Val.u8Data2 = 0 ;
        u32Caltemp.u8Val.u8Data1 = hex2bin(&pSBuff[0x00U]);
    }
    else { u32Caltemp.u32Val = 0 ; }
    //
    pData[0x00U] =  u32Caltemp.u32Val ;
} 
/**
 * @brief ASCII Decimal Data Convert TO uint16_t Data
 * 
 * @param pBuff ASCII Decimal Data String
 * @param pData Return uint16_t Data
 */
void cvt6ASCBin(const uint8_t *pBuff , uint16_t * const pData)
{
    uint16_t u16Cal = 0x00U ;
    uint8_t  u8Len  = 0x00U ;
    pData[0x00U]    = 0x00U ;
    //
    u8Len = strlen(pBuff) ;
    if((u8Len > 0U) && (u8Len <= 5U))
    {
        switch(u8Len)
        {
            case 5U: // 65535
                u16Cal  = (uint16_t)asc2bin(&pBuff[0x00U]) * 10000U ;
                u16Cal += (uint16_t)asc2bin(&pBuff[0x01U]) * 1000U ;
                u16Cal += (uint16_t)asc2bin(&pBuff[0x02U]) * 100U ;
                u16Cal += (uint16_t)asc2bin(&pBuff[0x03U]) * 10U ;
                u16Cal += (uint16_t)asc2bin(&pBuff[0x04U])  ;
                break ;
            case 4U: // 9999
                u16Cal  = (uint16_t)asc2bin(&pBuff[0x00U]) * 1000U ;
                u16Cal += (uint16_t)asc2bin(&pBuff[0x01U]) * 100U ;
                u16Cal += (uint16_t)asc2bin(&pBuff[0x02U]) * 10U ;
                u16Cal += (uint16_t)asc2bin(&pBuff[0x03U])  ;
                break ;  
            case 3U: // 999
                u16Cal  = (uint16_t)asc2bin(&pBuff[0x00U]) * 100U ;
                u16Cal += (uint16_t)asc2bin(&pBuff[0x01U]) * 10U ;
                u16Cal += (uint16_t)asc2bin(&pBuff[0x02U])  ;
                break ;
            case 2U: // 99
                u16Cal  = (uint16_t)asc2bin(&pBuff[0x00U]) * 10U ;
                u16Cal += (uint16_t)asc2bin(&pBuff[0x01U])  ;
                break ; 
            default:
                u16Cal  = (uint16_t)asc2bin(&pBuff[0x00U])  ;
                break ;   
        }

        pData[0x00U] = u16Cal ;
    }
}

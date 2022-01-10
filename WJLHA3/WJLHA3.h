/**************************************************************************
 * Based on Weighted Probability Model Code(Jielin Code) And <Hash Algorithm with Adaptive Hash Value Length Based on Weighted Probability Model>
 * @author JieLin Wang(China)
 * @copyright JieLin Wang 2022-01-10
 * @Version 3.0.1
 * @email 254908447@qq.com
 */
#ifndef _WJLHA3_h
#define _WJLHA3_h
#include "math.h"
#include "memory.h"
#include "stdlib.h"
#include <stdio.h>
/*************************************************************************************
the main Wang Jie lin hash function
InBytesBuFF: the first address of bytes cache waiting to be encoding.
InBytesBuFF_Length: the bytes cache length.
HashValueBuFF:the hash value Byte Buff.
HashValueBuFF_Length: the hash value's byte length, by user-defined or system-defined.
*************************************************************************************/
void WJLHA3(unsigned char *InBytesBuFF,unsigned int InBytesBuFF_Length, unsigned char *HashValueBuFF,unsigned int HashValueBuFF_Length);

#endif

/**************************************************************************
 * Based on Weighted Probability Model Code(Jielin Code) And <Hash Algorithm with Adaptive Hash Value Length Based on Weighted Probability Model>
 * @author JieLin Wang(China)
 * @copyright JieLin Wang 2021-05-26
 * @Version 3.0.0
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
keytBuFF: the keyt bytes for encoding.
keytBuFF_Length:the keytBuFF's byte length.
HashValueBuFF:the hash value Byte Buff.
HashValueBuFF_Length: the hash value's byte length, by user-defined or system-defined.
*************************************************************************************/
void WJLHA3(unsigned char *InBytesBuFF, int InBytesBuFF_Length, unsigned char *keytBuFF, int keytBuFF_Length, unsigned char *HashValueBuFF, int HashValueBuFF_Length);

#endif
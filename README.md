# WjlHashAlgorithm

The common one-way hash functions (Hash functions) currently include MD5, SHA, MAC, CRC, etc.

 MD5 Message-Digest Algorithm, a widely used cryptographic hash function, can generate a 128-bit (16-byte) hash value to ensure that information transmission is complete and consistent. After 1996, this algorithm was proved to have weakness and could be cracked. In the field of data transmission, higher security is needed. So other algorithms are generally used, such as SHA-2 and SM3. In 2004, experts confirmed that the MD5 algorithm cannot prevent collisions, so it is not suitable for security authentication, such as SSL public key certification or digital signature.
 
Wang Jielin Hash algorithm(WJLHA) is a brand-new Hash algorithm created by utilizing the weighted probability model function. This function can encode an input message string of any length into an output string of any(in a proper range) length.

The algorithm has not found the same hash value in the experiment. It can be used iteratively and the length of the output can be customized. The algorithm can be applied flexibly and suit for digital signatures, file verification, collision technology, etc.

However, this version (WjlHashAlgorithm 1.0.1) is the first version of this algorithm, and it has many limitations and sometimes occurs some bugs. Errors may appear especially when extreme demands are entered. For example, the input is too long and the setted output is too short and vice-verse. We are trying to fix them and still coding to improve it. 

If you have any problem or suggestion to this program, feel free to contract me as:

My CSDN:  https://blog.csdn.net/wjlxueshu
My E-mail: wangjielin@rilled.cn

## Usage of the Jielin-HashAlgorithm in Java and for C ([Click-here](https://github.com/Jielin-Code/WjlHashAlgorithm/blob/master/README%20for%20C.md))
### [WJLHA3](https://github.com/Jielin-Code/WjlHashAlgorithm/tree/master/WJLHA3)
- 1. Sequence segmentation and XOR operation are added.
- 2. Nonlinear wheel functions with weighted coefficients are utilized.
- 3. More powerful ans safer Hash algorithm.
- 4. Completely open source.
- 

	#include "WJLHA3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#ifdef WIN32
#define  inline __inline
#endif // WIN32

// test
int main(){
	long t1,t2;
	int i = 0, tmp = 0;
	int InBUFF_Length = 1024;// The byte length entered
	int HashValueBuFF_Length = 32; // Customize the byte length of the output hash
	unsigned char *In_BUFF;
	unsigned char *HashValue_BUFF;
	// test
	unsigned char In_BUFFs[35]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9'};

	In_BUFF = (unsigned char *)malloc(InBUFF_Length);
	HashValue_BUFF = (unsigned char *)malloc(HashValueBuFF_Length);
	// Data of the InBUFF_Length length were randomly generated
	srand((unsigned)time(NULL));
	printf("\n");
	for(i = 0; i < InBUFF_Length; ++i){
		In_BUFF[i] = rand() % 256;//(unsigned char)(i % 256);
		printf("%02X ", In_BUFF[i]);
	}
	
	// WJLHA3
	printf("\n");
	t1 = GetTickCount();
	WJLHA3(In_BUFF, InBUFF_Length, HashValue_BUFF, HashValueBuFF_Length);
	t2 = GetTickCount();
	printf("Encoding takes time:%d ms\n", t2 - t1);
	printf("\nWJLHA String：");
	for(i = 0; i < HashValueBuFF_Length; ++i){
		printf("%02X ",HashValue_BUFF[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}


All professionals are welcome to test our algorithm and your coments will be appreciable.  

Copyright (c) 2020 Wang Jielin.  All rights reserved. 

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
	int i = 0, tmp = 0;
	int InBUFF_Length = 100;// Length of the input  unit: byte
	int HashValueBuFF_Length = 33; //Length of output  unit: byte
	int keyt_Length = 257;// Length of private key
	unsigned char *In_BUFF;
	unsigned char *HashValue_BUFF;
	unsigned char *keyt_BUFF;

	In_BUFF = (unsigned char *)malloc(InBUFF_Length);
	HashValue_BUFF = (unsigned char *)malloc(HashValueBuFF_Length);
	keyt_BUFF  = (unsigned char *)malloc(keyt_Length);
	// andomly generate In_BUFF, length = InBUFF_Length
	for(i = 0; i < InBUFF_Length; ++i){
		In_BUFF[i] = (unsigned char)(i % 256);
	}
	for(i = 0; i < keyt_Length; ++i){
		keyt_BUFF[i] = (unsigned char)(i % 255);
	}
	// Call WJLHA3 algorithm
	printf("\n");

	WJLHA3(In_BUFF, InBUFF_Length, keyt_BUFF, keyt_Length, HashValue_BUFF, HashValueBuFF_Length);
	printf("\n Signed WJLHA£º");
	for(i = 0; i < HashValueBuFF_Length; ++i){
		printf("%d,",(char)HashValue_BUFF[i]);
	}
	printf("\n");
	printf("\nWJLHA string£º");
	for(i = 0; i < HashValueBuFF_Length; ++i){
		printf("%02X",HashValue_BUFF[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}

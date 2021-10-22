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

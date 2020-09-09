# Usage of the Jielin-HashAlgorithm in C

Download the latest version of WjlHashAlgorithm C library [WjlHashAlgorithm2.1.0.zip](https://github.com/Jielin-Code/WjlHashAlgorithm/blob/master/WJLHashAlgorithm2.1.0(lib%20for%20C).zip), Which have two folders (include and lib). Copy these folders in your project directory. Use it in the following way.

### Step1. 
Put the following lines in the C file and edit the directory path as per your project directory. 

```
#include "..\\Project name\\include\WJLHashAlgorithm.h"
#pragma comment(lib,"..\\Project name\\lib\\WJLHashAlgorithm2.0.1.lib")
```
### Step2. 
Include the following code for testing in the main method  
```
int main() {
	int i = 0, tmp = 0;
	//byteLength is the output length in byte of the desired Hash
	//32 byte refers to 256 bits. This value can be defined according to the number of bytes. 
	//It can be 16 * 8 = 128 bits or 37 * 8 = 296 bits, which means that it can be set as per desired.
	int byteLength = 16;
	//A Secret key, which can be any value from 0 to 999999.
	int secretKey = 0;//Different secret key will have different Hash value
	unsigned char *outputByteString;
	char *inputString;

	outputByteString = (unsigned char *)malloc(byteLength);

	inputString = "Input String";

	// Calling of the function "encryption" which returns Hash value in bytes 
	outputByteString = encrypt(inputString, secretKey, byteLength);

	printf("\nWJLHA in Bytes :");
	for (i = 0; i < byteLength; ++i) {
		printf("%d,", (char)outputByteString[i]);
	}
	printf("\n");
	printf("\nWJLHA in Hexa :");
	for (i = 0; i < byteLength; ++i) {
		printf("%02x", outputByteString[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}

```

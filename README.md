# WjlHashAlgorithm

The common one-way hash functions (Hash functions) currently include MD5, SHA, MAC, CRC, etc.

 MD5 Message-Digest Algorithm, a widely used cryptographic hash function, can generate a 128-bit (16-byte) hash value to ensure that information transmission is complete and consistent. After 1996, this algorithm was proved to have weakness and could be cracked. In the field of data transmission, higher security is needed. So other algorithms are generally used, such as SHA-2 and SM3. In 2004, experts confirmed that the MD5 algorithm cannot prevent collisions, so it is not suitable for security authentication, such as SSL public key certification or digital signature.
 
Wang Jielin Hash algorithm(WJLHA) is a brand-new Hash algorithm created by utilizing the weighted probability model function. This function can encode an input message string of any length into an output string of any(in a proper range) length.

The algorithm has not found the same hash value in the experiment. It can be used iteratively and the length of the output can be customized. The algorithm can be applied flexibly and suit for digital signatures, file verification, collision technology, etc.

However, this version (WjlHashAlgorithm 1.0.1) is the first version of this algorithm, and it has many limitations and sometimes occurs some bugs. Errors may appear especially when extreme demands are entered. For example, the input is too long and the setted output is too short and vice-verse. We are trying to fix them and still coding to improve it. 

If you have any problem or suggestion to this program, feel free to contract me as:

My CSDN:  https://blog.csdn.net/wjlxueshu
My E-mail: 254908447@qq.com

# Usage of the Jielin-HashAlgorithm

### [WjlHashAlgorithm1.0.1.Jar](https://github.com/Jielin-Wang/WjlHashAlgorithm/raw/master/WJLHashAlgorithm%201.0.1.jar)
Download the WjlHashAlgorithm.Jar and import as a external JAR in the project directory and test with the following code.
```
public static void main(String[] args) {
		//Input parameter is the output length of the Hash which is changeable 
		WJLHashAlgorithm hashAlgorithm=new WJLHashAlgorithm(16);
		String string= hashAlgorithm.encrypt("abc");
		System.out.print(string);
	}

```
### [WjlHashAlgorithm2.0.0.Jar](https://github.com/Jielin-Code/WjlHashAlgorithm/blob/master/WJLHashAlgorithm%202.0.0.jar)

- 1. Customize the bit length (or bytes) of the output hash value, there is no limit for the time being.
- 2. Support the user to input the digital password and encode the own hash value.
- 3. Added a Method "setSecretKey". Different secret key have different Hash for the same input.

```
public static void main(String[] args) {
		//Input parameter is the output length of the Hash which is changeable
		//32 byte refers to 256 bits. This value can be defined according to the number of bytes. 
		//It can be 16 * 8 = 128 bits or 37 * 8 = 296 bits, which means that it can be set as per desired.
		WJLHashAlgorithm hashAlgorithm=new WJLHashAlgorithm(32);
		//Add Secret key
		hashAlgorithm.setSecretKey(1); //A Secret key, which can be any value from 0 to 999999.
		String string= hashAlgorithm.encrypt("abc"); //"ABC" is a  input string to be encoded
		System.out.print(string);
	}

```

Lenght of the Hash value is changable and can be generated with a desired Hash length(Hash value as input parameter to the constructor).

All professionals are welcome to test our algorithm and your coments will be appreciable.  

Copyright (c) 2020 Wang Jielin.  All rights reserved. 

#include "WJLHA3.h"
// Jielincode Encoding Struct
typedef struct
{
	unsigned int RC_CODE_BITS;
	unsigned int RC_SHIFT_BITS;
	unsigned int RC_MAX_RANGE;
	unsigned int RC_MIN_RANGE;
	double JIELINCOE;
	unsigned int EFLow;
	unsigned int EFRange;
	unsigned int EFDigits;
	unsigned int EFFollow;
	unsigned int EOut_buff_loop;
	unsigned char *HashValueBuFF;
	unsigned int HashValueBuFF_Length;
	unsigned int InBytesBuFF_Length;
}WJLCoder;
// Obtain a sequence X and obtain a weighted coefficient---JIELINCODE Coefficient
void TheCOE(WJLCoder *coder){
	// get the Jielin code coefficient
	coder->JIELINCOE = pow(   2.0, 1.0 - ( ((double)coder->HashValueBuFF_Length) / (double)coder->InBytesBuFF_Length )   );
}
// Output bytes to cache and weighted encoding
void OutPutByte(WJLCoder *coder, unsigned char ucByte)
{
	coder->HashValueBuFF[ coder->EOut_buff_loop % coder->HashValueBuFF_Length ] = coder->HashValueBuFF[ (coder->EOut_buff_loop + ucByte) % coder->HashValueBuFF_Length ] ^ ucByte;
	coder->EOut_buff_loop ++;
}
// Encode by JielinCeo
void Encode(WJLCoder *coder, unsigned char symbol)
{	
	unsigned int High = 0,i = 0;
	if (1 == symbol){// the Symbol 1
		coder->EFLow = coder->EFLow +  (unsigned int)((double)coder->EFRange * 0.5 * coder->JIELINCOE);
	}
	coder->EFRange = (unsigned int)((double)coder->EFRange * 0.5 * coder->JIELINCOE);
	while(coder->EFRange <= coder->RC_MIN_RANGE){
		High = coder->EFLow + coder->EFRange - 1;
		if(coder->EFFollow != 0) {
			if (High <= coder->RC_MAX_RANGE) {
				OutPutByte(coder, coder->EFDigits);
				for (i = 1; i <= coder->EFFollow - 1; ++i){
					OutPutByte(coder, 0xFF);
				}
				coder->EFFollow = 0;
				coder->EFLow = coder->EFLow + coder->RC_MAX_RANGE;
			} else if (coder->EFLow >= coder->RC_MAX_RANGE) {
				OutPutByte(coder, coder->EFDigits + 1);
				for (i = 1; i <= coder->EFFollow - 1; ++i){
					OutPutByte(coder, 0x00);
				}									
				coder->EFFollow = 0;
			} else {
				coder->EFFollow += 1;
				coder->EFLow = (coder->EFLow << 8) & (coder->RC_MAX_RANGE - 1);
				coder->EFRange = coder->EFRange << 8;
				continue;
			}
		}
		if  (((coder->EFLow ^ High) & (0xFF << coder->RC_SHIFT_BITS)) == 0) {
			OutPutByte(coder, (unsigned char)(coder->EFLow >> coder->RC_SHIFT_BITS));
		}else{
			coder->EFLow = coder->EFLow - coder->RC_MAX_RANGE;
			coder->EFDigits = coder->EFLow >> coder->RC_SHIFT_BITS;
			coder->EFFollow = 1;
		}
		coder->EFLow = ( ( (coder->EFLow << 8) & (coder->RC_MAX_RANGE - 1) ) | (coder->EFLow & coder->RC_MAX_RANGE) );
		coder->EFRange = coder->EFRange << 8;
	}
}
// Finish Encode by JielinCeo
void FinishEncode(WJLCoder *coder)
{
	unsigned int n = 0;
	if (coder->EFFollow != 0) {
		if (coder->EFLow < coder->RC_MAX_RANGE) {
			OutPutByte(coder, coder->EFDigits);
			for (n = 1; n <= coder->EFFollow - 1; n++) {
				OutPutByte(coder, 0xFF);
			}
		} else {
			OutPutByte(coder, coder->EFDigits + 1);
			for (n = 1; n <= coder->EFFollow - 1; n++) {
				OutPutByte(coder, 0x00);
			}
		}
	}
	coder->EFLow = coder->EFLow << 1;
	n = coder->RC_CODE_BITS + 1;
	do {
		n -= 8;
		OutPutByte(coder, (unsigned char)(coder->EFLow >> n));
	} while (!(n <= 0));
}
// Initialization WJLCoder
void InitializationWJLCoder(WJLCoder *coder)
{
	coder->RC_CODE_BITS = 31;
	coder->RC_SHIFT_BITS = coder->RC_CODE_BITS - 8;
	coder->RC_MAX_RANGE = 1 << coder->RC_CODE_BITS;
	coder->RC_MIN_RANGE = 1 << coder->RC_SHIFT_BITS;
	coder->JIELINCOE = 0.0;
	coder->EFLow = coder->RC_MAX_RANGE;
	coder->EFRange = coder->RC_MAX_RANGE;
	coder->EFDigits = 0;
	coder->EFFollow = 0;
	coder->EOut_buff_loop = 0;
	coder->HashValueBuFF_Length = 0;
}
// the main function
void WJLHA3(unsigned char *InBytesBuFF,unsigned int InBytesBuFF_Length, unsigned char *HashValueBuFF,unsigned int HashValueBuFF_Length)
{
	int i = 0, j = 0;
	WJLCoder *coder;
	// Less than 4 bytes are easily collided
	if(InBytesBuFF_Length < 4){
		return;
	}
	coder = (WJLCoder *)malloc(sizeof(WJLCoder));
	if(coder == NULL){
		return;
	}
	// Initialization WJLCoder Object
	InitializationWJLCoder(coder);
	coder->HashValueBuFF_Length = HashValueBuFF_Length;
	coder->HashValueBuFF  = (unsigned char *)malloc(HashValueBuFF_Length);
	memset(coder->HashValueBuFF, 0x00, HashValueBuFF_Length);
	coder->InBytesBuFF_Length = InBytesBuFF_Length;
	TheCOE(coder);
	// Up to 64 bits
	if(HashValueBuFF_Length >= 8){
		if(HashValueBuFF == NULL){
			HashValueBuFF = (unsigned char *)malloc(HashValueBuFF_Length);
		}
	}else{
		if(coder->HashValueBuFF) free(coder->HashValueBuFF);
		if(coder) free(coder);
		return;
	}
        // Encode each bits
	for(i = 0; i < InBytesBuFF_Length; ++i){
		for(j = 7; j >= 0; --j){
			Encode(coder, ((InBytesBuFF[i] >> j) & 0x01));
		}
	}
	if(InBytesBuFF_Length <= HashValueBuFF_Length){
		// Encode another 8L + 8 symbols 1
		for(i = 0; i < InBytesBuFF_Length + 1; ++i){
			for(j = 0; j < 8; ++j){
				Encode(coder, 0x01);
			}
		}
	}
	FinishEncode(coder);
	memcpy(HashValueBuFF, coder->HashValueBuFF, HashValueBuFF_Length);
	// Free memory
	if(coder->HashValueBuFF) free(coder->HashValueBuFF);
	if(coder) free(coder);
}

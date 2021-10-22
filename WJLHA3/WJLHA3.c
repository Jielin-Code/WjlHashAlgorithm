#include "WJLHA3.h"
// Jielincode Encoding Struct
typedef struct
{
	unsigned int RC_CODE_BITS;
	unsigned int RC_SHIFT_BITS;
	unsigned int RC_MAX_RANGE;
	unsigned int RC_MIN_RANGE;
	double p0;
	double p1;
	double H;
	double COE;
	double JIELINCOE;
	unsigned int EFLow;
	unsigned int EFRange;
	unsigned int EFDigits;
	unsigned int EFFollow;
	unsigned int EOut_buff_loop;
	unsigned char *HashValueBuFF;
	int HashValueBuFF_Length;
}WJLCoder;
// Obtain a sequence X and obtain a weighted coefficient---JIELINCODE Coefficient
void TheCOEofY(WJLCoder *coder, unsigned char *X, int X_len){
	int i, j, Count0 = 0;
	// Number of statistical symbols 0
	for(i = 0; i < X_len; ++i){
		for(j = 7; j >= 0; -- j) {
			if( ((X[i] >> j) & 0x01) == 0 ){
				Count0 ++;
			}
		}
	}
	// Get the probability p0 of symbol 0 and the probability p1 of symbol 1
	coder->p0 = (double)Count0 / (double)(X_len * 8.0);
	coder->p1 = 1.0 - coder->p0;
	// Binary sequences of all 0 or all 1 need to be preprocessed
	if(coder->p0 == 0.0){
		coder->p0 = 0.0000000001;
		coder->p1 = 1.0 - coder->p0;
	}else if(coder->p1 == 0.0){
		coder->p1 = 0.0000000001;
		coder->p0 = 1.0 - coder->p1;
	}
	// get the standard information entropy
	coder->H = -coder->p0 * (log(coder->p0)/log(2.0))- coder->p1 * (log(coder->p1)/log(2.0));
	// get the Jielin code coefficient
	coder->COE = pow(   2.0, coder->H - ( ((double)coder->HashValueBuFF_Length) / (double)X_len )   );
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
		if(coder->p0 <= coder->p1){
			coder->EFLow = coder->EFLow +  (unsigned int)((double)coder->EFRange * coder->p0 * coder->JIELINCOE);
			coder->EFRange = (unsigned int)((double)coder->EFRange * coder->p1 * coder->JIELINCOE);
		}else{
			coder->EFRange = (unsigned int)((double)coder->EFRange * coder->p0 * coder->JIELINCOE);
		}
	}else{
		if(coder->p0 <= coder->p1){
			coder->EFRange = (unsigned int)((double)coder->EFRange * coder->p0 * coder->JIELINCOE);
		}else{
			coder->EFLow = coder->EFLow +  (unsigned int)((double)coder->EFRange * coder->p0 * coder->JIELINCOE);
			coder->EFRange = (unsigned int)((double)coder->EFRange * coder->p1 * coder->JIELINCOE);
		}
	}
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
	coder->p0 = 0.0;
	coder->p1 = 0.0;
	coder->H = 0.0;
	coder->COE = 0.0;
	coder->JIELINCOE = 0.0;
	coder->EFLow = coder->RC_MAX_RANGE;
	coder->EFRange = coder->RC_MAX_RANGE;
	coder->EFDigits = 0;
	coder->EFFollow = 0;
	coder->EOut_buff_loop = 0;
	coder->HashValueBuFF_Length = 0;
}
// the main function
void WJLHA3(unsigned char *InBytesBuFF, int InBytesBuFF_Length, unsigned char *HashValueBuFF, int HashValueBuFF_Length)
{
	unsigned char *Y;
	int Y_len = 0, i = 0, j = 0, k = 0;
	WJLCoder *coder;
	double tmpY_len = 0.0;
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
	TheCOEofY(coder, InBytesBuFF, InBytesBuFF_Length);
	// Up to 128 bits
	if(HashValueBuFF_Length >= 16){
		if(HashValueBuFF == NULL){
			HashValueBuFF = (unsigned char *)malloc(HashValueBuFF_Length);
		}
	}else{
		if(coder->HashValueBuFF) free(coder->HashValueBuFF);
		if(coder) free(coder);
		return;
	}
	
	// Fill the message, 512L(bit)=64LByte
	tmpY_len = ceil(coder->H * (InBytesBuFF_Length + 8));
	if(tmpY_len < 64.0 * HashValueBuFF_Length){
		k = (int)(64.0 * HashValueBuFF_Length - tmpY_len);
	}
	if(k >= 0){
		Y_len = (int)(tmpY_len + k);
	}
	Y = (unsigned char *)malloc(Y_len * sizeof(unsigned char));
	// Copy X
	memcpy(Y, InBytesBuFF, InBytesBuFF_Length);
	// Fill 0xFF
	for(i = InBytesBuFF_Length; i < InBytesBuFF_Length + k; ++i){
		Y[i] = 0xFF;
	}
	// Fill coder->p0
	memcpy(Y + InBytesBuFF_Length + k, &coder->p0, sizeof(double));
    // Encode each bits
	for(i = 0; i < InBytesBuFF_Length; ++i){
		for(j = 7; j >= 0; --j){
			coder->JIELINCOE = coder->COE - (double)InBytesBuFF[i]/100000.0;
			Encode(coder, ((InBytesBuFF[i] >> j) & 0x01));
		}
	}
	FinishEncode(coder);
	memcpy(HashValueBuFF, coder->HashValueBuFF, HashValueBuFF_Length);
	// Free memory
	if(coder->HashValueBuFF) free(coder->HashValueBuFF);
	if(coder) free(coder);
}

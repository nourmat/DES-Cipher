#include <iostream>
#include <stdio.h>
#include <bitset>
#include <vector>
#include <stdio.h>

#define ull unsigned long long
#define ll long long
#define ul unsigned long
#define ui unsigned int

using namespace std;

ui perm_array_64To64[64] = { 
	58, 50, 42, 34, 26, 18, 10,  2,
    60, 52, 44, 36, 28, 20, 12,  4,
    62, 54, 46, 38, 30, 22, 14,  6,
    64, 56, 48, 40, 32, 24, 16,  8,
    57, 49, 41, 33, 25, 17,  9,  1,
    59, 51, 43, 35, 27, 19, 11,  3,
    61, 53, 45, 37, 29, 21, 13,  5,
    63, 55, 47, 39, 31, 23, 15,  7
};

ui FinalPermutation[64] = {
    40,  8, 48, 16, 56, 24, 64, 32,
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25
};

ui perm_array_64To56[56] = {
	57, 49, 41, 33, 25, 17,  9,
    1, 58, 50, 42, 34, 26, 18,
   10,  2, 59, 51, 43, 35, 27,
   19, 11,  3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
   14,  6, 61, 53, 45, 37, 29,
   21, 13,  5, 28, 20, 12,  4
};

ui perm_array_56To48[48] = {
	14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
   23, 19, 12,  4, 26,  8,
   16,  7, 27, 20, 13,  2,
   41, 52, 31, 37, 47, 55,
   30, 40, 51, 45, 33, 48,
   44, 49, 39, 56, 34, 53,
   46, 42, 50, 36, 29, 32
};

ui perm_array_32To48[48] = {
	 32,  1,  2,  3,  4,  5,  4,  5,
     6,  7,  8,  9,  8,  9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27,
    28, 29, 28, 29, 30, 31, 32,  1
}; 
ui perm_array_32To32[32] = {
     16,  7, 20, 21,
    29, 12, 28, 17,
     1, 15, 23, 26,
     5, 18, 31, 10,
     2,  8, 24, 14,
    32, 27,  3,  9,
    19, 13, 30,  6,
    22, 11,  4, 25
};

ui circular_shift_schedular [16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

ui sbox[8][4][16] = {
   {
   {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
   { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
   { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
   {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
   },

   {
   {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
   { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
   { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
   {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
   },

   {
   {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
   {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
   {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
   { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
   },

   {
   { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
   {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
   {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
   { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},
   },

   {
   { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
   {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
   { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
   {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},
   },

   {
   {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
   {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
   { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
   { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
   },

   {
   { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
   {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
   { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
   { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
   },

   {
   {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
   { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
   { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
   { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11},
   },
};

//void per (ull word){
//	ull temp = 0;
//	for (int i = 31 ; i >= 0;i++){
//		ull mask = (wor);
//		temp |= ( & (1U << i));
//	}
//}

bitset<64> initialPermutation(bitset<64> &word){
	string words = word.to_string();
	char output[64];
	for (int i = 0 ; i < 64 ; i++)
		output[i] = words[perm_array_64To64[i]-1];
	return bitset<64> (output);
}

bitset<64> inverseInitialPermutation(bitset<64> &word){
	string words = word.to_string();
	char output[64];
	for (int i = 0 ; i < 64; i++)
		output[i] = words[FinalPermutation[i]-1];
	return bitset<64> (output);
}

bitset<56> permutedChoice1(bitset<64> &word){
	string words = word.to_string();
	char output[56];
	for (int i = 0 ; i < 56 ; i++)
		output[i] = words[perm_array_64To56[i]-1];
	return bitset<56> (output);
}

bitset<48> permutedChoice2(bitset<56> &word)
{
	string words = word.to_string();
	char output[48];
	for (int i = 0 ; i < 48; i++)
		output[i] = words[perm_array_56To48[i]-1];
	return bitset<48> (output);
}

bitset<48> expansionPermutation(bitset<32> &word){
	string words = word.to_string();
	char output[48];
	for (int i = 0 ; i < 48; i++)
		output[i] = words[perm_array_32To48[i]-1];
	return bitset<48> (output);
}

bitset<32> pBox(bitset<32> &word){
	string words = word.to_string();
	char output[32];
	for (int i = 0 ; i < 32; i++)
		output[i] = words[perm_array_32To32[i]-1];
	return bitset<32> (output);
}

void smallDboxComp (ull &full6bits, int sboxType){
	ull input = (full6bits>>1) & (0xf);
	ull key = full6bits & (0x1); //left bit
	key |= ((full6bits>>4) & (0x2)); //right bit

	full6bits = sbox[sboxType][key][input];
}

bitset<32> keyedSubstitutionSBox (bitset<48> &word){
	
	ull s[8];
	ull wordlong = word.to_ullong();

	//prepare each sbox element sepratly in an unsigned long long
	int count = 48-6;
	for (int i = 0; i < 8; i++){
		s[i] = (wordlong>>count) & (0x3f); //binaray 11 1111  save output in s[i]
		smallDboxComp(s[i],i);
		count -=6;
	}

	ull output = 0;
	count = 32-4;
	for (int i = 0; i < 8; i++){
		output |= (s[i]<<count);
		count-=4;
	}

	return bitset<32> (output);
}

void leftCirculate(bitset<56> &key,ull shift_amount){
	ull key56 = key.to_ullong();

	//separate
	ull key28D = key56 & ~(0xfffffff<<28);
	ull key28C = (key56>>28) & ~(0xfffffff<<28);

	//circulate
	key28D = ((key28D<<shift_amount) | (key28D>>(28-shift_amount)))  & ~(0xf<<28);
	key28C = ((key28C<<shift_amount) | (key28C>>(28-shift_amount))) & ~(0xf<<28);
	//return to 56
	key56 = 0;
	key56 |= (key28C<<28) | (key28D<<0);	

	key = (bitset<56>) key56;
}

vector<bitset<48>> genkeys(ull key){
	bitset<64> key64 (key);
	bitset<56> key56 = permutedChoice1(key64);
	vector<bitset<48>> generatedkeys48;
	
	for (int i = 0; i < 16; i++){
		leftCirculate(key56,circular_shift_schedular[i]);
		bitset <48> key48 = permutedChoice2(key56);
		generatedkeys48.push_back(key48);
	}
	return generatedkeys48;
}

//it is the functon xored with the left(i-1)
ull fun(ull lastright, bitset<48> genkey){
	bitset<32> rightbits (lastright);
	//expand the rightbits to 48 bits
	bitset<48> rightexpanded = expansionPermutation(rightbits);

	ull rightexpandedlong = rightexpanded.to_ullong() ^ genkey.to_ullong();
	//passes to sboxs
	rightbits = keyedSubstitutionSBox(bitset <48> (rightexpandedlong));
	rightbits = pBox(rightbits);
	return rightbits.to_ullong();
}

ull desEncryption(vector<bitset<48>> generatedkeys, ull plaintext){
	//intilal permutation
	plaintext = initialPermutation(bitset<64> (plaintext)).to_ullong();
	
	//begin the rounds
	ull lastright = plaintext & ~(0xffffffff << 32);
	ull lastleft = (plaintext >> 32) & ~(0xffffffff << 32);

	for (int i = 0; i < 16; i++){
		ull left = lastright;
		ull right = lastleft ^ fun(lastright,generatedkeys[i]);
		lastright = right;
		lastleft = left;
	}

	ull ciphertext = (lastright << 32);
	ciphertext |= lastleft;

	return inverseInitialPermutation(bitset<64> (ciphertext)).to_ullong();;
}

ull desDecryption (vector<bitset<48>> generatedkeys, ull plaintext){
	vector<bitset<48>> ungen;
	for (int i =  generatedkeys.size()-1 ; i >= 0 ;i--)
		ungen.push_back(generatedkeys[i]); 
	return desEncryption(ungen,plaintext);
}

int main(){

	ull plain_text,key;
	int times;
	scanf("%llx",&key);
	scanf("%llx",&plain_text);
	cin>>times;

	//generate keys for the 16 rounds
	vector<bitset<48>> generatedkeys = genkeys(key);
	ull cipher = plain_text;
	for (int i = 0; i < times; i++)
		cipher = desEncryption(generatedkeys,cipher);
	
	printf("\n%llx ",cipher);
	system("pause");
}
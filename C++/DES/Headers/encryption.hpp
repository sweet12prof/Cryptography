#include <bit>
#include <bitset>  
#include <array> 
#include <cstdint>
#include <string>

const std::size_t pSize = 64;            //PlainTextSize
const std::size_t kSize = 56;            //KeySizeAFterParityDrop
const std::size_t pSplitSize = 32;       //PlaintextsizeafterSplit
const std::size_t kSplitSize = 28;       //KeysizeafterSplit
const std::size_t ksize_o = 48;          //RoundKey
const std::size_t karray = 16;           //Array holding KeySchedule

//Struct Holds the Left and Right Half Of Plaintext
struct P_LR_BLOCK
{
    std::bitset <pSplitSize> Lside, 
                             Rside;
};

//Struct Holds the Left and Right Half Of Keys
struct K_LR_BLOCK{
   std::bitset <kSplitSize> Lside, 
                             Rside;
};

//Table to Drop Parity bits and permute Key
std::array <unsigned int, kSize> ParityDropIndexTable{
    57, 49, 41, 33, 25, 17, 9, 1, 
    58, 50, 42, 34, 26, 18, 10, 2, 
    59, 51, 43, 35, 27, 19, 11, 3, 
    60, 52, 44, 36, 63, 55, 47, 39, 
    31, 23, 15, 7,  62, 54, 46, 38, 
    30, 22, 14, 6,  61, 53, 45, 37, 
    29, 21, 13, 5,  28, 20, 12, 4
};

//Table for Key Compression 56to48bits
std::array <unsigned int, ksize_o> CompressionD_Box{
    14, 17, 11, 24, 1,   5,  3, 28,
    15, 6, 21,  10, 23, 19, 12,  4, 
    26, 8, 16,  7,  27, 20, 13,  2, 
    41, 52, 31, 37, 47, 55, 30, 40, 
    51, 45, 33, 48, 44, 49, 39, 56, 
    34, 53, 46, 42, 50, 36, 29, 32 
};



std::bitset<pSize>   Cipher(std::bitset<pSize>, const std::bitset<48> &, const size_t &);
std::bitset<pSize>   Permute(const std::bitset<pSize> &, std::array<int, pSize>);
std::bitset<ksize_o> kPermute(const std::bitset<kSize> &, std::array<int, kSize>);

void pSplit(const std::bitset<pSize> &);
void ksplit(const std::bitset<kSize> &, K_LR_BLOCK & );

void Swapper (P_LR_BLOCK &);
std::bitset <pSize> Combine(P_LR_BLOCK);

//KeyFunctions
void Keygen (const std::bitset<pSize> &, K_LR_BLOCK & , std::array <std::bitset<ksize_o>, karray> & ); ///ParentFunction
std::bitset<kSize> KeyReduce (const std::bitset <pSize> &);  //RemovesParitiesandPermuteKey
void circularShift(std::bitset<kSplitSize>  &);              //CircularshiftSub Routine
std::bitset <ksize_o> CompComb (const K_LR_BLOCK &);         //Compress and Combine - Final key subroutine

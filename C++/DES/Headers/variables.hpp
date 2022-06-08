#include <bitset>  
#include <array> 
#include <cstdint>
#include <string>


//----------------------------------------------------------------------//
//                    Key schd Variables             -------------------//
//----------------------------------------------------------------------//
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



// ------------------------------------------------------------------- //
//                           DES Function Variables
// ------------------------------------------------------------------- //

std::array <unsigned int, ksize_o> ExpansionD {
     32,   1,  2,  3,  4,  5, 
      4,   5,  6,  7,  8,  9,
      8,   9, 10, 11, 12, 13, 
      12, 13, 14, 15, 16, 17, 
      16, 17, 18, 19, 20, 21, 
      20, 21, 22, 23, 24, 25,
      24, 25, 26, 27, 28, 29, 
      28, 29, 31, 31, 32,  1
};

std::array <unsigned int, pSize> F_Sbox_1{
   14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
    0, 15,  7,  4, 14,  2, 13, 10,  3,  6, 12, 11,  9,  5,  3,  8,
    4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
   15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13

};

std::array <unsigned int, pSize> F_Sbox_2{
    15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
     3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
     0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
    13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9

};

std::array <unsigned int, pSize> F_Sbox_3{
    10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
    13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
    13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
    1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
};

std::array <unsigned int, pSize> F_Sbox_4{
    7, 13, 14, 3 ,0, 6 ,9 ,10 ,1, 2, 8, 5, 11, 12, 4 ,15,
    13, 8, 11, 5 ,6 ,15 ,0 ,3 ,4 ,7, 2, 12, 1, 10, 14, 9,
    10, 6, 9 ,0 ,12 ,11 ,7 ,13 ,15, 1, 3, 14, 5, 2, 8, 4,
    3, 15, 0 ,6, 10 ,1 ,13 ,8 ,9 ,4 ,5, 11, 12, 7, 2, 14
};

std::array <unsigned int, pSize> F_Sbox_5{
    2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
    14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
    4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
    11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
};

std::array <unsigned int, pSize> F_Sbox_6{
    12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
    10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
    9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
    4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 10, 0, 8, 13
};

std::array <unsigned int, pSize> F_Sbox_7{
    4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
    13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
    1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
    6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
};

std::array <unsigned int, pSize> F_Sbox_8{
    13, 2, 8,  4,  6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
    1, 15, 13, 8, 10, 3,  7,  4, 12, 5, 6, 11, 10, 14, 9, 2,
    7, 11, 4,  1, 9, 12, 14,  2, 0,  6, 10, 10, 15, 3, 5, 8,
    2,  1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 9, 3, 5, 6, 11

};

std::array <unsigned int, pSplitSize> F_StraightBox{
    16, 7 ,20 ,21 ,29 ,12 ,28 ,17,
    1 ,15 ,23 ,26 ,5 ,18 ,31 ,10,
    2 ,8 ,24 ,14 ,32 ,27 ,3 ,9,
    19 ,13 ,30 ,6 ,22 ,11, 4, 25
} ;
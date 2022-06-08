#include "./variables.hpp"
//#include <bit>
//KeyFunctions
void Keygen (const std::bitset<pSize> &, K_LR_BLOCK & , std::array <std::bitset<ksize_o>, karray> & ); ///ParentFunction
std::bitset<kSize> KeyReduce (const std::bitset <pSize> &);  //RemovesParitiesandPermuteKey
void circularShift(std::bitset<kSplitSize>  &);              //CircularshiftSub Routine
std::bitset <ksize_o> CompComb (const K_LR_BLOCK &);         //Compress and Combine - Final key subroutine
void ksplit(const std::bitset<kSize> &, K_LR_BLOCK & );

//DESFunction
std::bitset<ksize_o> F_ExpansionD(const std::bitset<pSplitSize> &);
inline std::bitset <ksize_o> Func_xor (const std::bitset<ksize_o> & , const std::bitset <ksize_o> &  );
std::bitset <pSplitSize> F_Sub_boxes (const std::bitset<ksize_o> &); 
std::bitset <pSplitSize> F_Straight_D_box (const std::bitset<pSplitSize> &); 
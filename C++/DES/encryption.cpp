#include "../Headers/encryption.hpp"
#include <iostream>
int main(){
    K_LR_BLOCK k_lr;
    std::bitset<pSize> key64 = 0xAABB09182736CCDD;
    std::array <std::bitset<ksize_o>, karray>  keyArray;
    Keygen(key64, k_lr, keyArray);
     for( const auto & item : keyArray)
            std::cout << std::hex << item.to_ulong() << std::endl;
}


void Keygen (const std::bitset<pSize> & key, K_LR_BLOCK & k_lr,  std::array <std::bitset<ksize_o>, karray> & keyArr){

    std::bitset<kSize> key56 = KeyReduce(key);
    ksplit(key56, k_lr);
    for (size_t i{1}; i<17; i++ ){
        if( i == 1 || i == 2 || i == 9 || i == 16 )
            {
                circularShift(k_lr.Lside);
                circularShift(k_lr.Rside);
                keyArr[i - 1] = CompComb(k_lr);
            }
        else 
        {
            circularShift(k_lr.Lside); circularShift(k_lr.Lside);
            circularShift(k_lr.Rside); circularShift(k_lr.Rside);
            keyArr[i - 1] = CompComb(k_lr);
        }
    }
}

std::bitset<kSize>  KeyReduce(const std::bitset <pSize> & key){
    std::bitset <kSize> out;
   int j =0;
     for (size_t i{kSize}; i > 0; i-- ){
         out[i-1] = key[-1 * (ParityDropIndexTable[j] - 64)];
         j++;
     }
     return out;
}

void ksplit(const std::bitset<kSize> & key56, K_LR_BLOCK & k_lr){
    for (size_t i{0}; i<kSize; i++)
         if( i < 28 )
            k_lr.Rside[i] = key56[i];
        else 
            k_lr.Lside[i-28] = key56[i];   
}

void circularShift(std::bitset<kSplitSize>  & side  ){
   std::bitset<kSplitSize> ini;
   size_t j = kSplitSize;
   for (size_t i {1}; i < kSplitSize; i++ )
       ini[i] = side[i - 1];
       ini[0] = side[kSplitSize - 1];
    side = ini;
} 

std::bitset <ksize_o> CompComb (const K_LR_BLOCK & k_lr){
std::bitset<kSize> merge (k_lr.Lside.to_string() + k_lr.Rside.to_string() );
std::bitset<ksize_o> out;
    int j=0;

     for (size_t i{ksize_o}; i > 0; i-- ){
         out[i-1] = merge[-1 * (CompressionD_Box[j] - 56) ];
         j++;
     }
     return out;
}
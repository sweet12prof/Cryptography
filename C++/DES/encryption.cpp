#include "./Headers/Headers.hpp"
#include <iostream>
std::array <size_t, 8> getNextIndexBits (const std::bitset <ksize_o>  );
int main(){
    K_LR_BLOCK k_lr;
    // std::bitset<pSize> key64 = 0xAABB09182736CCDD;
    // std::array <std::bitset<ksize_o>, karray>  keyArray;
    // Keygen(key64, k_lr, keyArray);
    //  for( const auto & item : keyArray)
    //         std::cout << std::hex << item.to_ulong() << std::endl;
    std::bitset <ksize_o> a = 0xFCFCFCFCFCFC;
    std::bitset <pSplitSize> b = 0xFCFCFCFC;
   std::cout << F_Straight_D_box(F_Sub_boxes(Func_xor(F_ExpansionD(b), a)));
}




//----------------------------------------------------------------------//
//                    Key schd Variables             -------------------//
//----------------------------------------------------------------------//
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



//----------------------------------------------------------------------//
//                    DES Function SubRoutines       -------------------//
//----------------------------------------------------------------------//

std::bitset<ksize_o> F_ExpansionD(const std::bitset<pSplitSize> & p_Rside){
    size_t j{0};
    std::bitset<ksize_o> out;

    for (int i{ksize_o}; i > 0; i-- ){
        out[i - 1] = p_Rside[-1 * (ExpansionD[j] - 32)];
        j++;
    }
    return out;
}

inline std::bitset <ksize_o> Func_xor (const std::bitset<ksize_o> & key, const std::bitset <ksize_o> & p_postExp ){
    return key ^ p_postExp;
}

std::bitset <pSplitSize> F_Sub_boxes (const std::bitset<ksize_o> & postXor){
     std::array <size_t, 8> someArr = getNextIndexBits(postXor);
     std::bitset<pSplitSize> out(0);
     std::bitset<32> SboxOut (0);
     std::bitset<32> pout = 0xFFFFFFFF;
     
    

    SboxOut = F_Sbox_1[someArr[0]];
    out = out ^ SboxOut;
    out <<= 4;

        SboxOut = F_Sbox_2[someArr[1]];
    out = out ^ SboxOut;
    out <<= 4;

        SboxOut = F_Sbox_3[someArr[2]];
    out = out ^ SboxOut;
    out <<= 4;


        SboxOut = F_Sbox_4[someArr[3]];
    out = out ^ SboxOut;
    out <<= 4;

        SboxOut = F_Sbox_5[someArr[4]];
    out = out ^ SboxOut;
    out <<= 4;

        SboxOut = F_Sbox_6[someArr[5]];
    out = out ^ SboxOut;
    out <<= 4;

        SboxOut = F_Sbox_7[someArr[6]];
    out = out ^ SboxOut;
    out <<= 4;

        SboxOut = F_Sbox_8[someArr[7]];
    out = out ^ SboxOut;

   return out ;
}

  std::array <size_t, 8> getNextIndexBits (const std::bitset <ksize_o>  postXor){
    std::bitset<48> mask = 0xFC0000000000;
    std::bitset<48> temp;
    std::bitset<6> index;
    std::bitset<6> indexImm;
    std::size_t indexRes;
    std::array <size_t, 8> indexArr;

    std::size_t k{42};
    for(size_t i{0}; i<8; i++){
        //temp = temp & std::bitset<48>(0);
        temp = mask & postXor;
        mask = mask >> 6;
        temp = temp >> k; 
        index = std::bitset<6>(temp.to_ulong());
        {
            indexImm[5] = index[5];
            indexImm[4] = index[0];
            indexImm[3] = index[4];
            indexImm[2] = index[3];
            indexImm[1] = index[2]; 
            indexImm[0] = index[1];
        }
        k-=6;
        indexArr[i] = indexImm.to_ulong();
      //  std::cout << index << " " << indexImm << " " << indexArr[i] << std::endl;
    }
    return indexArr;
}


std::bitset <pSplitSize> F_Sub_boxes (const std::bitset<pSplitSize> & text){
    size_t j{0};
    std::bitset<pSplitSize> out;

    for (int i{pSplitSize}; i > 0; i-- ){
        out[i - 1] = text[-1 * ( F_StraightBox[j] - 32)];
        j++;
    }
    return out;
} 
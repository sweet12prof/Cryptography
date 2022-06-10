#include "./Headers/Headers.hpp"
#include <iostream>
std::array <size_t, 8> getNextIndexBits (const std::bitset <ksize_o>  );
int main(){
    std::bitset<pSize> key64 = 0x1ABB09187836CCDD;  
    std::bitset <pSize> pText (0x123456ABCD132536);
    mainCipher(pText, key64);
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
    //std::cout << p_Rside << std::endl;
    for (int i{ksize_o}; i > 0; i-- ){
        out[i - 1] = p_Rside[-1 * (ExpansionD[j] - 32)];
        j++;
    }
   // std::cout << out << std::endl << std::endl << std::endl << std::endl;
   //std::cout << out << std::endl;
    return out;
}

inline std::bitset <ksize_o> Func_xor (const std::bitset<ksize_o> & key, const std::bitset <ksize_o> & p_postExp ){
    return key ^ p_postExp;
}

std::bitset <pSplitSize> F_Sub_boxes (const std::bitset<ksize_o> & postXor){
  //  std::cout << postXor << std::endl <<std::endl; 
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

    //std::cout << std::endl <<std::endl << std::endl << out << std::endl << std::endl << std::endl  ;

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
     //  std::cout << std::dec << index << " " << indexImm << " " << indexArr[i] << std::endl;
    }
    return indexArr;
}


std::bitset <pSplitSize> F_Straight_D_box (const std::bitset<pSplitSize> & text) {
    size_t j{0};
    std::bitset<pSplitSize> out;

    for (int i{pSplitSize}; i > 0; i-- ){
        out[i - 1] = text[-1 * ( F_StraightBox[j] - 32)];
        j++;
    }
    return out;
} 

std::bitset <pSplitSize> F_Top(const P_LR_BLOCK & p_lr, const std::bitset<ksize_o> & roundKey){
    // std::cout << F_Straight_D_box(F_Sub_boxes(Func_xor(F_ExpansionD(b), a)));
    return F_Straight_D_box(F_Sub_boxes(Func_xor(F_ExpansionD(p_lr.Rside), roundKey)));

}



//----------------------------------------------------------------------//
//                    Top DES Function               -------------------//
//----------------------------------------------------------------------//

void PSplit(const std::bitset<pSize> & pText, P_LR_BLOCK & p_lr){
    std::bitset<pSize> mask = 0x00000000FFFFFFFF;
    std::bitset<pSize> halfText (0);
    halfText = mask & pText;
    p_lr.Rside = halfText.to_ulong();

    mask = 0xFFFFFFFF00000000;
    halfText ^= halfText;
    halfText = mask & pText;
    halfText >>= 32;
    p_lr.Lside = halfText.to_ulong();

}


std::bitset<pSize> P_Ini_permutation (const std::bitset<pSize> & pText){
    size_t j{0};
    std::bitset<pSize> out;

    for (int i{pSize}; i > 0; i-- ){
        out[i - 1] = pText[-1 * ( P_IniPermBox[j] - 64)];
        j++;
    }
    return out;
}

void P_swapper(P_LR_BLOCK & p_lr){
    std::bitset<pSplitSize> l_buff = p_lr.Lside;
    p_lr.Lside = p_lr.Rside;
    p_lr.Rside = l_buff;
}

void P_lfxor(P_LR_BLOCK & p_lr, const std::bitset<pSplitSize> & postF){
    p_lr.Lside ^= postF;
}

std::bitset<pSize> P_Final_permutation (const std::bitset<pSize> & pText){
    size_t j{0};
    std::bitset<pSize> out;

    for (int i{pSize}; i > 0; i-- ){
        out[i - 1] = pText[-1 * ( P_FinalPermBox[j] - 64)];
        j++;
    }
    return out;
}

std::bitset<pSize> P_Combine(const P_LR_BLOCK & p_lr){
    std::bitset<pSize> merge (p_lr.Lside.to_string() + p_lr.Rside.to_string() );
    return merge;
}

//Cipher

std::bitset<pSize> mainCipher(const std::bitset<pSize> & pText, const std::bitset<pSize> & kText){
    K_LR_BLOCK k_lr;
    P_LR_BLOCK p_lr;
    std::array <std::bitset<ksize_o>, karray>  keyArray;
    Keygen(kText, k_lr, keyArray);

    std::bitset<pSize> _pText = P_Ini_permutation(pText);
    PSplit(_pText, p_lr);

    std::bitset<pSplitSize> postFunc;
     //std::cout << std::hex << p_lr.Lside.to_ulong() << " " << p_lr.Rside.to_ullong() << std::endl;
   for(size_t i{0}; i<rounds; i++){
        postFunc = 0x00000000;
        postFunc = F_Top(p_lr, keyArray[i]);
        P_lfxor(p_lr, postFunc);
       // if(rounds != 15)
        P_swapper(p_lr);
       // std::cout << std::hex << p_lr.Lside.to_ulong() << " " << p_lr.Rside.to_ullong() << " " << keyArray[i].to_ulong() << std::endl ;
   }
     P_swapper(p_lr);

    std::bitset<pSize> out(P_Combine(p_lr));
  out = P_Final_permutation(out);
  std::cout << std::hex << out.to_ulong();
    return out;
}


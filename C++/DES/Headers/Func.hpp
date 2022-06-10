
#include "./variables.hpp"





std::bitset<pSize>   Cipher(std::bitset<pSize>, const std::bitset<48> &, const size_t &);
std::bitset<pSize>   Permute(const std::bitset<pSize> &, std::array<int, pSize>);
std::bitset<ksize_o> kPermute(const std::bitset<kSize> &, std::array<int, kSize>);




void Swapper (P_LR_BLOCK &);
std::bitset <pSize> Combine(P_LR_BLOCK);


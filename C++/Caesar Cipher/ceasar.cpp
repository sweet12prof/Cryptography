#include <iostream>
#include <string>
#include <array>
#include <algorithm>

using namespace std;
string encrypt(string);
std::string decrypt(string );
int main()
{
    std::cout << "Enter string for encryption: " << std::endl;
    
   string newString, encryptedString;
   std::getline(std::cin, newString);
   encryptedString = decrypt(newString);
   cout << "Encrypted String is: "<< encryptedString <<std::endl;
  // std::cout << -1 % 26;
}

std::string encrypt(std::string somestring){
    std::string alphaArray {"abcdefghijklmnopqrstuvwxyz "}; 
    std::cout << alphaArray.size();
    std::string encryptedMessage;
    for(auto item : somestring){
        encryptedMessage += alphaArray[(alphaArray.find(item) + 3) % alphaArray.size()];
    }
        return encryptedMessage;
}   


std::string decrypt(std::string someString){
     std::string alphaArray {"abcdefghijklmnopqrstuvwxyz "}; 
     std::string decryptedMessage;
     
     for(auto item : someString){
         int pos {alphaArray.find(item)};
        //cout << "pos -3 is :" << pos - 3;       }  


         if( pos - 3 <= 0){
                
                pos += alphaArray.size() - 3;
                //cout << pos;
                decryptedMessage += alphaArray[(pos) % alphaArray.size()];
         }
         else 
                decryptedMessage += alphaArray[(pos - 3) % alphaArray.size()];
        
     }
     
        return decryptedMessage;
}
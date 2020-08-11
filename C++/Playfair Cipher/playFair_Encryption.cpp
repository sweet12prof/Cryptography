#include <iostream>
#include <string>
#include<array>

int determineCategory(const std::array<std::array<char, 5>, 5> &, std::string &);
void determineNextPair( std::string &, std::string &, int &);
void rowTransForm(const std::array<std::array<char, 5>, 5> &, std::string &, std::string & );
void columnTransform(const std::array<std::array<char, 5>, 5> &, std::string &, std::string &);
void BoxTransform(const std::array<std::array<char, 5>, 5> &, std::string &, std::string &);
void FilterMessage( std::string & );
std::string EncryptMessage(std::string );
std::string processMessage(std::string );


int Column_1, row_1, Column_2, row_2;
int TrColumn_1, Trrow_1, TrColumn_2, Trrow_2;
std::string originalMessage{"eaggerate"}; //onarmdyb
std::string result = "";
int FP, BP = 0;
int main(){
    
    while(FP < originalMessage.size()){
        std::string token = processMessage(originalMessage);
        result = result + " " + EncryptMessage(token);
         }
    
     std::cout <<std::endl  <<"Encrypted Token is : " << result << std::endl;
   
}

std::string processMessage(std::string  someMessage){
    std::string token = "";
    while(FP < someMessage.size())
        {
            if(someMessage[FP] != ' '){
                token += someMessage[FP];
                FP++;
            }
                else {
                  
                    break;
                }
                    
                   
        }
        FP++;
        std::cout << "Current Token is: " << token << std::endl;
    return token;
}

std::string EncryptMessage(std::string Input){

    std::array<std::array<char, 5>, 5> playFairTemplate {'m','o','n','a','r','c','h','y','b','d','e','f','g','i','k','l','p','q','s','t','u','v','w','x','z'};
    std::string currentPair;
    std::string message{Input};
    std::string encryptedMessage = "";
    std::string toEncrypt;
    
    int Count{0};
    int CatSwitch{0};
    int CurrentPosition{1};
    int Cursor{0};
    
    //FilterMessage(message);
    std::cout << std::endl;

    for(auto row : playFairTemplate){
        for(auto item : row)
        {
            std::cout <<item << " \t";
        }
        std::cout << std::endl;
    }  
        while(message != "") {
            
             determineNextPair(message, currentPair, Count);
            //std::cout << std::endl << std::endl << std::endl;

            CatSwitch = determineCategory(playFairTemplate, currentPair);

            switch(CatSwitch){
                case 0 : 
                    rowTransForm(playFairTemplate, encryptedMessage, currentPair);
                    break;
                case 1 : 
                    columnTransform(playFairTemplate, encryptedMessage, currentPair);
                    break;
                case 2 :
                    BoxTransform(playFairTemplate, encryptedMessage, currentPair);
                    break;
                default:
                    std::cout<<"Something is off";
                    break;
            }
            
            
        }

        //std::cout << std::endl <<encryptedMessage;
        return encryptedMessage;

}




void FilterMessage( std::string & message){
    message =  (message.size() % 2 == 1) ? (message + "x") : message ;
}


void determineNextPair(std::string & message, std::string & nextPair, int & Counter){
    int CurrentPointer {0};
    std::string CurrentMessage; 
    std::cout << std::endl <<"Current Counter is " << Counter << std::endl;
    
    if(message.size() == 1){
        FilterMessage(message);
    }


    if(message.at(CurrentPointer) == message.at(CurrentPointer + 1)){
        nextPair = "";
        nextPair = nextPair + message.at(CurrentPointer) + "x";
        CurrentMessage = message;
        message = "";
        message = CurrentMessage.size() >= 2 ?  CurrentMessage.substr(CurrentPointer + 1, CurrentMessage.size() - 1) : "";
        
        std::cout << "Current message to encrypt is : "<< CurrentMessage <<std::endl << "Pair is: " << nextPair << std::endl;
        //return CurrentPointer + 1;
        Counter+=1;
       // return message.size();
    }
    else {
        nextPair = "";
        nextPair = nextPair + message.at(CurrentPointer) + message.at(CurrentPointer + 1) ;
        CurrentMessage = message;
        message = "";
        message = CurrentMessage.size() >= 2 ?    CurrentMessage.substr(CurrentPointer + 2, CurrentMessage.size() - 1) : "";
         std::cout << "Current message to encrypt is : "<< CurrentMessage <<std::endl << "Pair: " << nextPair << std::endl;
          Counter +=2;
         // return message.size();
    }
}
    
    
int determineCategory(const std::array<std::array<char, 5>, 5> & templateT  , std::string & StringToFind){
    int Counter = 0;
    int i = 0;
    int j = 0; 
    for(auto item : StringToFind){
        //std::cout << "Current item is " << item << std::endl;
        for( i = 0; i< 5; i++){
            for( j=0; j< 5; j++){

                if(item == (char)templateT[i][j]){
                   // std::cout <<  templateT[i][j] << "is equal to" << item << std::endl;
                    //std::cout  << "Count is " << Counter<< std::endl;
                    if(Counter == 0){
                        Column_1 = j;
                        row_1 = i;
                    }
                    else 
                        {
                            Column_2 = j;
                            row_2 = i;
                        }
                }
            }
        }
        Counter++;
    }

    // std::cout<< std::endl;
    // std::cout <<"col_1 " << Column_1 << " rol_1 " << row_1 << std::endl;
    // std::cout <<"col_2 " << Column_2 << " rol_2 " << row_2 << std::endl;

    if(row_1 == row_2){
        std::cout << "elements in the same row" << std::endl;
        return 0;
    }else{
        if(Column_1 == Column_2 ){
            std::cout << "elements in the same column" << std::endl;
            return 1; }
        else {
            std::cout << "elements in box" << std::endl;
            return 2;
        }
    }
    
        
    

    // row_1 =0;
    // row_2 =0;
    // Column_1 = 0;
    // Column_2 = 0;
    // Counter = 0;
    
}
    

void rowTransForm(const std::array<std::array<char, 5>, 5> & playFairTemp, std::string & encryptMess, std::string &  currPair){
    
    int count = 0;

    Trrow_1 = row_1;
    Trrow_2 = row_2; 

    TrColumn_1 = (Column_1 < 4) ? Column_1 + 1 : ((Column_1 + 1) % 5);
    TrColumn_2 = (Column_2 < 4) ? Column_2 + 1 : ((Column_2 + 1) % 5);

    for(auto item : currPair){
        if(count == 0)
            encryptMess += playFairTemp[Trrow_1][TrColumn_1];
        else 
            encryptMess += playFairTemp[Trrow_2][TrColumn_2];
        count ++;
    }

}

void columnTransform(const std::array<std::array<char, 5>, 5> & playFairTemp, std::string & encryptMess, std::string &  currPair){
    
    int count = 0;

    Trrow_1 =      (row_1 < 4) ? row_1 + 1 : 0;
    Trrow_2 =     (row_2 < 4) ? row_2 + 1 : 0;

    TrColumn_1 = Column_1;
    TrColumn_2 = Column_2;

    for(auto item : currPair){
        if(count == 0)
            encryptMess += playFairTemp[Trrow_1][TrColumn_1];
        else 
            encryptMess += playFairTemp[Trrow_2][TrColumn_2];
        count ++;
    }

}

void BoxTransform(const std::array<std::array<char, 5>, 5> & playFairTemp, std::string & encryptMess, std::string &  currPair){
    
    int count = 0;

    Trrow_1 =  row_1;    
    Trrow_2 =  row_2;

    TrColumn_1 = Column_2;
    TrColumn_2 = Column_1;

    for(auto item : currPair){
        if(count == 0)
            encryptMess += playFairTemp[Trrow_1][TrColumn_1];
        else 
            encryptMess += playFairTemp[Trrow_2][TrColumn_2];
        count ++;
    }

}



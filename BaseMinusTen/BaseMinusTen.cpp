// BaseMinusTen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::cout << "Hello World!\n";
}


int convertTenToMinusTen(int pBaseTen) {
    //Initialization
    int baseMinusTenNumber;
    //We want the length of the number so we can iterate through it
    auto s = std::to_string(pBaseTen);
    int numberLength = s.length();
    char bonusNumber = '0';
    std::vector<char> newNumberList;
    newNumberList.assign(numberLength+2, 0); //We want to fill it with possible room for the biggest digit to be a 9

    for (int i = 0;i<numberLength ; i++) {
        //n multiplied by (-10) to the factor of 0 is n
        if (i == 0) {
            newNumberList[i] = s[i];
        }
        //if we have an even exponent, we can also keep it, except if the number is a 9
        else if(i%2 == 0){
            if (s[i] != '9' || (s[i]==9 && s[i-1]==0)) {
                if (newNumberList[i] == '0') {
                    newNumberList[i] = addNumber(s[i], bonusNumber);
                    bonusNumber = '0';
                }
                else {//The number should be 1
                    char temp = newNumberList[i];
                    newNumberList[i] = addNumber(s[i], temp);
                }
            }
            else {
                newNumberList[i] = '0';
                newNumberList[i+1] = '9';
                newNumberList[i+2] = '1';
            }
        }
        //if we have an uneven exponent, we have to do a little trick, where we will invert the number. We also add a 1 to the following digit.
        else if (i%3 == 0 || i==1) {
            if (newNumberList[i] != '9') {
                if (s[i]!='0') {
                    bonusNumber = '1';
                    newNumberList[i] = invertNumber(s[i]);
                }
                else {
                    newNumberList[i] = s[i]; //If it is 0 we keep it that way
                }
            }
            else { //'9' is expected
                char temp = newNumberList[i];
                newNumberList[i] = subtractNumber(temp, s[i]);
            }
        }
    }
    //The actual Number gets built
    auto it = newNumberList.begin();

    return baseMinusTenNumber;
}
//With uneven exponents there needs to be a little trick where we invert the number and increase the next number by one
char invertNumber(char pChar) {
    return(convertIntToChar(10 - convertCharToInt(pChar)));
}
//To add the bonus 1 we will have to tamper with the chars
char addNumber(char pX, char pY) {
    return convertIntToChar(convertCharToInt(pX) + convertCharToInt(pY));
}
char subtractNumber(char pX, char pY) {
    return convertIntToChar(convertCharToInt(pX) - convertCharToInt(pY));
}
//we want to switch around a bit hehe
char convertIntToChar(int pInt) {
    return pInt + '0';
}
int convertCharToInt(char pChar) {
    return pChar - '0';
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu


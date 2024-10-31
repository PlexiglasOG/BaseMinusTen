// BaseMinusTen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
This code was written by Vadim Kobyakov aka PlexiglasOG, I did it all. I am happy it worked.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
int convertTenToMinusTen(int pBaseTen);
char invertNumber(char pChar);
char addNumber(char pX, char pY);
char subtractNumber(char pX, char pY);
char convertIntToChar(int pInt);
int convertCharToInt(char pChar);
void calculateNumberFrom(int pNum);
bool isPrimeNumberNotTwo(int pNum);
int findLimit();

int main()
{
    int baseTenNumber;
    std::cout << "Enter a number, base ten, positive: "; //189100000 is the limit
    std::cin >> baseTenNumber;
    int baseMinusTen = convertTenToMinusTen(baseTenNumber);
    std::cout << "Your number in base minus ten form is " << baseMinusTen << std::endl;
    if ((baseMinusTen != INT_MIN) || (baseMinusTen != INT_MAX)) {
    std::cout << "Proof:" << std::endl;
    calculateNumberFrom(baseMinusTen);
    }
    else {
        std::cout << "Integer Limit reached. Try smaller number" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.ignore();
    std::cin.get();
    return 0;
}


int convertTenToMinusTen(int pBaseTen) {
    //Initialization
    int baseMinusTenNumber;
    //We want the length of the number so we can iterate through it
    auto s = std::to_string(pBaseTen);
    int numberLength = s.length();
    char bonusNumber = '0';
    std::vector<char> newNumberList;
    newNumberList.assign(numberLength+2, '0'); //We want to fill it with possible room for the biggest digit to be a 9
    std::reverse(s.begin(), s.end());
    s = s + "00";
    //std::cout << s << std::endl;
    for (int i = 0; i < newNumberList.size(); i++) {
        //std::cout << "An der Stelle in der Zahl " << i << "ist die Zahl " << s[i] << std::endl;
        //n multiplied by (-10) to the factor of 0 is n
        if (i == 0) {
            newNumberList[i] = s[i];
        }
        //if we have an even exponent, we can also keep it, except if the number is a 9
        else if(i%2 == 0){
            if (s[i] != '9' || (s[i]=='9' && s[i-1]=='0')) {
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
                //If there is a 9, we ignore the digit here and move to 2 digits following to make that 1 and add 9 to the one before. This will affect the needed number to become a 9
                newNumberList[i] = '0'; 
                newNumberList[i+1] = '9';
                newNumberList[i+2] = '1';
            }
        }
        //if we have an uneven exponent, we have to do a little trick, where we will invert the number. We also add a 1 to the following digit.
        else if (i%3 == 0 || isPrimeNumberNotTwo(i) || i==1) {
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
        //std::cout << "An der Stelle " << i << "ist die Zahl " << newNumberList[i] << std::endl;
    }
    //The actual Number gets built
    baseMinusTenNumber = 0;
    for (int n = 0; n < newNumberList.size();n++) {
        //std::cout << "Test Addition, Stelle " << n << "zahl: " << convertCharToInt(newNumberList[n]) << std::endl;
        //std::cout << "Zehnerpotent " << pow(10, n) << std::endl;
        baseMinusTenNumber = baseMinusTenNumber + (convertCharToInt(newNumberList[n]) * (pow(10,n)));
    }
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
//We want to prove that we are right. So we multiply our digits by the equivalent power of -10 and add them all up
void calculateNumberFrom(int pNum) {
    std::string s = std::to_string(pNum); 
    //Reverse String
    std::reverse(s.begin(), s.end());
    int baseTenEquivalent =0;
    for (size_t i = s.length() - 1; i != -1; i--) {
        std::cout << convertCharToInt(s[i]) << "*" << "(-10)^" <<i;
        if (i != 0) {
            std::cout << " + ";
        }
    }
    std::cout << std::endl;
    for (size_t i = s.length()-1; i !=-1; i--) {
        std::cout << convertCharToInt(s[i]) * pow(-10, i);
        baseTenEquivalent = baseTenEquivalent + convertCharToInt(s[i]) * pow(-10, i);
        if (i!=0) {
            std::cout << " + ";
        }
    }
    std::cout << " = " << baseTenEquivalent << std::endl;
}

bool isPrimeNumberNotTwo(int pNum) {
        if (pNum <= 1) return false; // Numbers less than 2 are not prime
        if (pNum == 2) return false; //We want to exclude 2 as we count it as an even number. Yes, it breaks definition, no, I don't care
        if (pNum <= 3) return true;  //3 is a prime number
        if (pNum % 2 == 0 || pNum % 3 == 0) return false; // Eliminate multiples of 2 and 3

        for (int i = 5; i * i <= pNum; i += 6) { // Check from 5 to square root of pNum
            if (pNum % i == 0 || pNum % (i + 2) == 0)
                return false;
        }
        return true;
}

int findLimit() {
    int n = 189090000; //Found this one out through trial and error
    int i = convertTenToMinusTen(n);
    std::cout << n << std::endl;
    n++;
    while ((n!= INT_MAX) or (n!= INT_MIN)) {
        std::cout << n << std::endl;
        int i = convertTenToMinusTen(n);
        if (i == INT_MAX || i == INT_MIN) {
            return n;
        }
        n++;
    }
    return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu


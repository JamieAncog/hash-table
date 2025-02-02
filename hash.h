#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <ctype.h>
#include <random>
#include <chrono>

using namespace std;

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        //Fill array of characters
        char a[28];
        int last = 27;
        for (int i = 0; i < (int) k.length(); i++){
            a[last] = k[k.length()-i-1];
            last--;
        }
        for (int j = last; j >= 0; j--){
            a[j] = '-';
        }
        int curr = 27;
        
        //Create array of 64-bit integers & initialize to 0
        unsigned long long w[5];
        for (int i = 0; i < 5; i++){
            w[i] = 0;
        }
        //Fill array of 64-bit integers
        int currW = 4;
        while (curr != last && currW >= 0){
            HASH_INDEX_T sixDigits[6];
            for (int i = 5; i >= 0; i--){
                if (curr != last){
                    sixDigits[i] = letterDigitToNumber(a[curr]);
                    curr--;
                }
                else {
                    sixDigits[i] = 0;
                }
            }
            w[currW] = ((((((sixDigits[0])*36+sixDigits[1])*36+sixDigits[2])*36+sixDigits[3])*36+sixDigits[4])*36+sixDigits[5]); //Input formula
            currW--; 
        }
        HASH_INDEX_T result = (rValues[0]*w[0] + rValues[1]*w[1] + rValues[2]*w[2] + rValues[3]*w[3] + rValues[4]*w[4]); //Input formula
        return result;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        char lower[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
                        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        char upper[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        for (HASH_INDEX_T i = 0; i < 36; i++){
            if (letter == lower[i]){
                return i;
            }
            else if (i < 26 && letter == upper[i]){
                return i;
            }
        }
        return -1;        
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif

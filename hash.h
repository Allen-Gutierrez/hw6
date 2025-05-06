#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <string> // added for the use of the string class

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

        unsigned long long w[5] = {0, 0, 0, 0, 0}; // create the initial unsigned long long with all 0's

        int len = k.length();  // For the length of the word
        int groupIdx = 4; // Filled at the end of the w[]

        // Process the string in reverse in chunck of 6 letters
        for (int i = len; i > 0 && groupIdx >= 0; i -= 6, --groupIdx) {

            unsigned long long chunkValue = 0; // the current value for chunk
            int power = 0; // power of 36 

            // Build the chunk value up to 6 characters
            for (int j = i - 1; j >= 0 && j >= i - 6; --j) {
                
                unsigned long long multiplier = 1; // setting the intial multiplier
                
                // Go through to find the correct power 
                for (int p = 0; p < power; ++p) {

                    multiplier *= 36; // Calculate the multiplier needed

                }

                chunkValue += letterDigitToNumber(k[j]) * multiplier; // character value multiplied by 36^power
                ++power; // increase the power for the next part 
            }

            w[groupIdx] = chunkValue; // Store the calculated chunk value in w[]
        }

        // Final hash 
        unsigned long long hash = 0;
        for (int i = 0; i < 5; ++i) {
            hash += rValues[i] * w[i]; // Multiply corresponding elements and add to the final hash
        }

        return static_cast<HASH_INDEX_T>(hash); // Return the final hash value as HASH_INDEX_T


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

        if (letter >= 'A' && letter <= 'Z') {
            letter = letter - 'A' + 'a';
        }

        if (letter >= 'a' && letter <= 'z') {
            return letter - 'a'; // 'a'–'z' → 0–25
        }
        else if (letter >= '0' && letter <= '9') {
            return 26 + (letter - '0'); // '0'–'9' → 26–35
        }

        return 0; // Safety but should not reach here

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

//
//  main.cpp
//
//  Created by Matthew Lei on 1/7/17.
//  Copyright © 2017 Matthew Lei. All rights reserved.
//
//  Generate a range of numbers from 1 to 100000, and for
//  each number add the digits of that number together.
//  Print the sum of those digits if the sum is a prime number.

#include <iostream>
#include <fstream>      //file output
#include <unordered_set>

using namespace std;

static bool printToStdOut = true;
static bool printToFile = false;

/** Checks if a passed in integer is prime
 *
 *  @param num Candidate prime number to be checked
 *  @return True if number is prime, else False
 */
bool isPrime(int num) {
    if (num < 3) {
        return num > 1;
    } else if ((num % 2) == 0) {
        return false;
    }
    
    bool isPrime = true;
    for (int i = 3; i <= num / 2; i+=2) {
        if (num % i == 0) {
            isPrime = false;
            break;
        }
    }
    return isPrime;
}

/** Sum of the digits of a passed in value
 *
 *  @param num Number that is summed
 *  @return True if digits sum to a prime number, else False
 */
int sumOfDigits(int num) {
    int digit;
    int sum = 0;
    
    while (num > 0) {
        digit = num % 10;
        sum += digit;
        num /= 10;
    }
    return sum;
}

void outputFile(ofstream &out, string filename) {
    out.open(filename);
    if (out.fail()) {
        throw filename;
    }
}

void printout(ofstream &os, int loop) {
    if (printToFile) {
        os << "Number: " << loop
        << ", sum of digits (prime): " << sumOfDigits(loop) << endl;
    }
    if(printToStdOut) {
        cout << "Number: " << loop
        << ", sum of digits (prime): " << sumOfDigits(loop) << endl;
    }
}

int main(int argc, const char * argv[]) {
    int sum;
    ofstream outputStream;
    unordered_set<int> primes;
    
    try {
        outputFile(outputStream, string("MatthewOutputFile.txt"));
    } catch (string e) {
        cout << "Could not create new file with name: " << e << endl;
        printToFile = false;
        printToStdOut = true;
    } catch (...) {
        cout << "Unexpected error while creating file" << endl;
        exit(-1);
    }

    for (int i = 1; i <= 100000; ++i) {
        sum = sumOfDigits(i);
        if (primes.find(sum) != primes.end()) {
            printout(outputStream, i);
        } else {
            if (isPrime(sum)) {
                printout(outputStream, i);
                primes.insert(sum);
            }
        }
    }
    
    outputStream.close();
    return 0;
}

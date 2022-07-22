// Alphabet header //
// @file alphabet.h
// @author Unai Alro
// @version 25/11/21

#ifndef ALPHABET_H
#define ALPHABET_H

#include <iostream>
#include <vector>
#include <cmath>

#include "print.h"

class Alphabet{
    public:
        unsigned short cardinality; // Cardinality of the alphabet

        std::vector<unsigned> powers; // Auxiliary computations

        Alphabet(); 
        Alphabet(unsigned short us0); 
        ~Alphabet(); 

        unsigned compact(std::vector<unsigned char> vuc0);
        void nextAzTuple(std::vector<unsigned char> &vuc0); 
};

class Metalphabet: public Alphabet{
    public: 
        unsigned short n; // Number of nodes
        std::vector<Alphabet*> alphabets; // Vector with nodes alphabets

        std::vector<unsigned long> metapowers; // Auxiliary computations

        Metalphabet();
        Metalphabet(std::vector<Alphabet*> vaz0);
        ~Metalphabet();

        unsigned metacompact(std::vector<unsigned char> vuc0);
        void nextMaz(std::vector<unsigned char> &vuc0);
        void nextMaz(std::vector<unsigned char> &vuc0,bool &b0);
        void nextMazTuple(std::vector<std::vector<unsigned char>> &vvuc0);
};

#endif
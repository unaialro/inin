// Sequence header //
// @file sequence.h
// @author Unai Alro
// @version 25/11/21

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "alphabet.h"
#include "model.h"

#include "print.h"

class Alphabet;
class Metalphabet;
class Model;

class Sequence{
    public:
        Alphabet* az; // Node's alphabet
        unsigned length; // Sequence's length
        std::vector<unsigned char> seq; // Sequence in bytes

        Sequence();
        Sequence(Alphabet* az0);
        ~Sequence();

        void fromData(std::string str0);
};

class Metasequence: public Sequence{
    public:
        Metalphabet* maz; // Nodes' metalphabet
        std::vector<Sequence*> seqs; // Vector of sequences

        Metasequence();
        Metasequence(Metalphabet* maz0,unsigned u0);
        ~Metasequence();    

        void fromSequences(std::vector<Sequence> vseq0);
        void fromModel(Model* md0);
};

class MetasequenceEnsemble{
    public:
        Metalphabet *maz; // Node's metalphabet
        std::vector<Metasequence> mseqs; // Vector of metasequences
        unsigned length; // Sum of metasequence's lengths 

        MetasequenceEnsemble();
        MetasequenceEnsemble(Metalphabet* maz0,std::vector<Metasequence> vmseq0);
        ~MetasequenceEnsemble();    
};

#endif
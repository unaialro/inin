// Interaction header //
// @file multimodel.h
// @author Unai Alro
// @version 03/12/21

#ifndef MULTIMODEL_H
#define MULTIMODEL_H

#include <vector>

#include "alphabet.h"
#include "sequence.h"
#include "model.h"

class Metalphabet;
class Metasequence;
class MetasequenceEnsemble;
class Model;

class Multimodel{
    public:
        Metalphabet* maz; // Metalphabet
        Metasequence* mseq; // Metasequence
        MetasequenceEnsemble* mens; // Metasequence ensemble

        std::vector<Model*> models; // Vector with pointer to models

        unsigned short limitorder; // Upper bound
        unsigned short trueorder; // Ground truth order
        unsigned short aicorder; // Aic order

        Multimodel();
        Multimodel(unsigned short us0,Metalphabet* maz0,Metasequence* mseq0=nullptr,MetasequenceEnsemble* ens0=nullptr,unsigned short us1=0);
        ~Multimodel();

        void getModels();
        void estimateOrder();
        void getInteractions(bool b0=0);
        void writeResults(std::string str0,bool b0=0);
};

#endif


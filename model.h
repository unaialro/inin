// Model headers //
// @file model.h
// @author Unai Alro
// @version 25/11/21

#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "distance.h"

#include "alphabet.h"
#include "sequence.h"
#include "node.h"
#include "interaction.h"

#include "print.h"

class Metalphabet;
class Metasequence;
class MetasequenceEnsemble;
class Eld;
class InteractionEnsemble;

class Model{
    public:
        Metalphabet* maz; // Pointer to model's metalphabet
        Metasequence* mseq; // Pointer to model's metasequence
        MetasequenceEnsemble* mens; // Pointer to model's ensemble

        Model* pre; // Pointer to previous order model

        unsigned short order; // Number of joint time variables
        unsigned long columns; // Number of all possible ancestors
        unsigned long parameters; // Number of parameters in the model

        Eld stats; // Statistics of variables included in the model
        std::vector<std::vector<float>> matrix; // Transition matrix of the model

        float loglikelihood; // Model's loglikelihood
        float loglikelihood0; // Loglikelihood of the first strings 
        float loglikelihood1; // Loglikelihood of the bulk 
        float aic; // AIC criterion for the model

        InteractionEnsemble iens; // Interaction ensemble compatible with the model

        Model();
        Model(unsigned short us0, Metalphabet* maz0, Metasequence* mseq0=nullptr,MetasequenceEnsemble* ens0=nullptr);
        ~Model();

        void random();

        void getStats();
        void getMatrix(); 
        void getLoglikelihood();
        void getAic();

        void getInteractionsDeterministic();
        void getInteractionsSemirandom();
        void getInteractionsRandom();

        float getDistance(std::vector<std::vector<float>> vvf0);

        void writeResults(std::string str0);
};

#endif
// Interaction header //
// @file interaction.h
// @author Unai Alro
// @version 25/11/21

#ifndef INTERACTION_H
#define INTERACTION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "combinatorics.h"
#include "distance.h"

#include "alphabet.h"

class Metalphabet;

class Interaction{
    public:
        Metalphabet* maz; // Metalphabet for node's involved in the interaction

        unsigned short maxorder; // Order of the Markov chain
        unsigned short order; // Interaction order, i.e., total number of variables
        std::vector<unsigned short> type; // Variables for each node

        float coefficient; // Coefficient in the ensemble
        std::vector<std::vector<float>> matrix; // Interaction matrix

        unsigned rows; // Number of rows
        unsigned long columns; // Number of columns
        unsigned long long parameters; // Number of free parameters
        float normalization;   // Normalization to account for types 0

        std::vector<Interaction> subinteractions; // Vector with subinteractions 
        std::vector<unsigned short> partition; // Subsystem labels

        Interaction(Metalphabet* maz0,unsigned short us0,std::vector<unsigned short> vus0);
        ~Interaction();  

        unsigned rowCompact(std::vector<unsigned char> vuc0);
        unsigned long columnCompact(std::vector<std::vector<unsigned char>> vvuc0);

        void getMatrixofones();

        void getSubInteractions();

    private:
        std::vector<unsigned> rowPowers;  // Auxiliary row computations
        std::vector<std::vector<unsigned>> columnPowers0; // Auxiliary column computations 0
        std::vector<unsigned long>columnPowers1; // Auxiliary column computations 1

        void getColumnpowers();
        std::vector<unsigned short> getComplementary(std::vector<unsigned short> vus0,unsigned short us0);

        void setSubInteractions();
        void getSubInteractions0();
        bool getSubInteractions1(unsigned short &us0);
        bool getSubInteraction(std::vector<unsigned short> vus0);
        void getSubInteractionUniform(std::vector<unsigned short> vus0);
        bool getSubInteractionNonUniform(std::vector<unsigned short> vus0);
        bool checkSubInteractions();

        void nextSubRow(std::vector<unsigned char> &vuc0);
        void nextSubRow(std::vector<unsigned char> &vuc0,bool &b1,unsigned short us1);
        void nextSubCol(std::vector<std::vector<unsigned char>> &vvuc0);        

};

class InteractionEnsemble{
    public:
        Metalphabet* maz; // Metalphabet for node's involved in the interaction

        unsigned short maxorder; // Order of the Markov chain
        unsigned long cardinality; // Total number of interactions

        std::vector<Interaction> interactions; // Interactions at the ensemble

        std::vector<std::vector<float>> distribution; // Distribution of the number of parameters 
        std::vector<std::vector<float>> cdistribution; // Cummulative distribution of the number of parameters
        float reducibility; // Average reduction in the number of parameters per interaction

        std::vector<Interaction*> elite; // Dominant Interactions

        InteractionEnsemble();
        InteractionEnsemble(Metalphabet* maz0,unsigned short us0);
        ~InteractionEnsemble();     

        void getSubInteractions();

        void getReducibility(); 
        void getDistributions();

        void getElite(float f0=0.01);

        float getDistance(InteractionEnsemble* iens0);

        void writeResults(std::string str0);

    private:
        std::vector<unsigned long> powers; // Auxiliary computations

        std::vector<unsigned short> typeDecoder(unsigned long ul0); 

};



#endif
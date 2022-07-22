// Interaction header //
// @file multimodel.cpp
// @author Unai Alro
// @version 03/12/21

#include "multimodel.h"

// Multimodel class

/**
 * Costructor I
 */
Multimodel::Multimodel(){}
/**
 * Constructor II: Define metalphabet, metasequence, metasequence ensemble and orders.
 * @param us0 Limit order
 * @param maz0 Pointer to metalphabet
 * @param mseq0 Pointer to metasequence (Default mseq0=nullptr)
 * @param mens0 Pointer to metasequence ensemble (Default mens0=nullptr)
 * @param us1 True order (Default us1=0)
 */
Multimodel::Multimodel(unsigned short us0,Metalphabet* maz0,Metasequence* mseq0, MetasequenceEnsemble* mens0,unsigned short us1){
    limitorder=us0;
    maz=maz0;
    mseq=mseq0;
    mens=mens0;
    trueorder=us1;
}
/**
 * Destructor
 */
Multimodel::~Multimodel(){}

/**
 * Compute all models 
 */
void Multimodel::getModels(){
    for(unsigned i0=0;i0!=limitorder;i0++){
        models.push_back(new Model(i0+1,maz,mseq,mens)); 
        if(i0==0){
            models[i0]->pre=nullptr;
        }else{
            models[i0]->pre=models[i0-1];
        }   
        models[i0]->getStats();
        models[i0]->getLoglikelihood();
        models[i0]->getAic();
    }
}

/**
 * Estimate real order with AIC
 */
void Multimodel::estimateOrder(){
    unsigned long ul0=4294967295;
    for(unsigned short i0=0;i0!=models.size();i0++){
        if(models[i0]->aic<ul0){
            ul0=models[i0]->aic;
            aicorder=models[i0]->order;
        }
    }
}

/**
 * Obtain interaction decomposition
 * @param b0 If false interactions are computed from the most likely model according to the AIC. 
 * If true interactions are computed from the model corresponding to the true order (Default b0=0).
 */
void Multimodel::getInteractions(bool b0){
    if(b0){
        models[trueorder-1]->getMatrix();
        models[trueorder-1]->getInteractionsDeterministic();
        models[trueorder-1]->iens.getSubInteractions();
        models[trueorder-1]->iens.getReducibility();
        models[trueorder-1]->iens.getElite(0.01);
        models[trueorder-1]->iens.getDistributions(); 
    }else{
        models[aicorder-1]->getMatrix();
        models[aicorder-1]->getInteractionsDeterministic();
        models[aicorder-1]->iens.getSubInteractions();
        models[aicorder-1]->iens.getReducibility();
        models[aicorder-1]->iens.getElite(0.01);
        models[aicorder-1]->iens.getDistributions();       
    }
} 

/**
 * Write the ensemble of interactions in files
 * @param str0 Path to the folder
 * @param b0 If false interactions are computed from the most likely model according to the AIC. 
 * If true interactions are computed from the model corresponding to the true order (Default b0=0).
 */
void Multimodel::writeResults(std::string str0,bool b0){
    if(b0){
        models[trueorder-1]->writeResults(str0);
    }else{
        models[aicorder-1]->writeResults(str0);
    }
}

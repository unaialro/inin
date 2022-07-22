// Sequence functions //
// @file sequence.cpp
// @author Unai Alro
// @version 25/11/21

#include "sequence.h"


// Sequence Class

/**
 * Constructor I
 */
Sequence::Sequence(){}
/**
 * Constructor II
 * @param az0 Pointer to alphabet
 */
Sequence::Sequence(Alphabet* az0){
    az=az0;
}
/**
 * Destructor
 */
Sequence::~Sequence(){}

/**
 * Read from data file 
 * @param str0 Path to file
 */
void Sequence::fromData(std::string str0){
    std::ifstream datin;

    seq.clear();
    datin.open(str0.c_str(), std::ios::binary);
    seq.insert(seq.begin(),std::istreambuf_iterator<char>(datin),std::istreambuf_iterator<char>());
    datin.close();

    length=seq.size();    
}

// Metasequence Class

/**
 * Constructor I
 */
Metasequence::Metasequence(){}
/**
 * Constructor II
 * @param maz0 Node's metalphabet
 * @param u0 Sequence's length
 * @param vseq0 Vector of sequences
 */
Metasequence::Metasequence(Metalphabet* maz0,unsigned u0){
    maz=maz0;
    length=u0;    
}
/**
 * Destructor
 */
Metasequence::~Metasequence(){}

/**
 * Obtain metasequence from sequences
 * @param vseq0 Vector of pointers to sequences
 */
void Metasequence::fromSequences(std::vector<Sequence> vseq0){
    unsigned u0;
    std::vector<unsigned char> vuc0;

    for(unsigned i0=0;i0!=length;i0++){
        vuc0.clear();
        for(unsigned i1=0;i1!=vseq0.size();i1++){
            vuc0.push_back(vseq0[i1].seq[i0]);
        }
        u0=maz->metacompact(vuc0);
        seq.push_back(u0);
    }
}

/**
 * Create metasequence from a model
 * @param md0 Pointer to the model
 */
void Metasequence::fromModel(Model* md0){
    bool b0;
    unsigned char uc0;
    unsigned u0;
    float f0,f1;
    std::vector<unsigned char> vuc0;

    seq.clear();
    for(short i0=0;i0!=md0->order-1;i0++){
        uc0=1.0*(maz->cardinality)*rand()/RAND_MAX;
        seq.push_back(uc0);
        vuc0.push_back(uc0);
    }
    for(unsigned i0=md0->order-1;i0!=length;i0++){
        b0=1;
        u0=maz->compact(vuc0);
        f0=1.0*rand()/RAND_MAX;
        f1=0;
        for(unsigned i1=0;i1!=maz->cardinality;i1++){
            if(f0<f1){
                uc0=i1-1;
                seq.push_back(uc0);
                b0=0;
                break;
            }else{
                f1+=md0->matrix[i1][u0];
            }
        }
        if(b0){
            uc0=maz->cardinality-1;
            seq.push_back(uc0);
        }
        vuc0.erase(vuc0.begin());
        vuc0.push_back(uc0);
    }    

}

// Ensemble Class

/**
 * Constructor I
 */
MetasequenceEnsemble::MetasequenceEnsemble(){}
/**
 * Conctructor II
 * @param maz0 Node's metalphabet
 * @param vmseq0 Vector of pointers to metasequences
 */
MetasequenceEnsemble::MetasequenceEnsemble(Metalphabet* maz0,std::vector<Metasequence> vmseq0){
    maz=maz0;
    length=0;
    mseqs.clear();
    for(unsigned i0=0;i0!=vmseq0.size();i0++){
        mseqs.push_back(vmseq0[i0]);
        length+=vmseq0[i0].length;
    }
}
/**
 * Destructor
 */
MetasequenceEnsemble::~MetasequenceEnsemble(){}        

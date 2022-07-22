// Alphabet functions //
// @file alphabet.cpp
// @author Unai Alro
// @version 25/11/21

#include "alphabet.h"



// Alphabet Class 

/**
 * Constructor I
 */
Alphabet::Alphabet(){}
/**
 * Constructor II: Defines the cardinality of the alphabet.
 * @param us0 Cardinality
 */
Alphabet::Alphabet(unsigned short us0){
    cardinality=us0;
    for(unsigned i0=0;i0!=10;i0++){
        powers.push_back(pow(cardinality,i0));
    }
}
/**
 * Destructor
 */
Alphabet::~Alphabet(){}

/**
 * Joint encoding of a tuple of elements of alphabet
 * @param vuc0 Tuple of elements of alphabet
 */
unsigned Alphabet::compact(std::vector<unsigned char> vuc0){
    unsigned u0=0;
    for(short i0=vuc0.size()-1;i0!=-1;i0--){
        u0+=vuc0[i0]*powers[-i0+vuc0.size()-1];
    }
    return u0;
}

/**
 * Alphabet tuple iterator
 * @param vuc0 Iterator state
 */
void Alphabet::nextAzTuple(std::vector<unsigned char> &vuc0){
    bool b0;
    unsigned short us0;
    b0=1;us0=0;
    while(b0){
        b0=0;
        vuc0[vuc0.size()-1-us0]++;
        if(vuc0[vuc0.size()-1-us0]==cardinality){
            vuc0[vuc0.size()-1-us0]=0x00;
            us0++;
            if(us0!=vuc0.size()){
                b0=1;
            }
        }
    }
}

// Metalphabet Class

/**
 * Constructor I
 */
Metalphabet::Metalphabet(){}
/**
 * Constructor II: Defines vector of alphabets.
 * @param vaz0 Individual alphabets
 */
Metalphabet::Metalphabet(std::vector<Alphabet*> vaz0){
    unsigned u0=1;
    cardinality=1;
    n=vaz0.size();
    for(unsigned i0=0;i0!=n;i0++){
        alphabets.push_back(vaz0[i0]);
        cardinality*=vaz0[i0]->cardinality;
    }
    for(unsigned i0=0;i0!=10;i0++){
        powers.push_back(pow(cardinality,i0));
    }
    for(unsigned i0=0;i0!=n;i0++){
        metapowers.push_back(u0);
        u0*=vaz0[n-1-i0]->cardinality;
    }
    if(cardinality > 0xff+1){
        std::cout << "The metalphabet is too large, the max cardinality is 2^8" << std::endl;
    }
}
/**
 * Destructor 
 */
Metalphabet::~Metalphabet(){}

/**
 * Joint encoding of a tuple of elements of metalphabet
 * @param vuc0 Tuple of elements of metalphabet
 */
unsigned Metalphabet::metacompact(std::vector<unsigned char> vuc0){
    unsigned u0=0;
    for(short i0=vuc0.size()-1;i0!=-1;i0--){
        u0+=vuc0[i0]*metapowers[-i0+vuc0.size()-1];
    }
    return u0;
}


/**
 * Metalphabet iterator 
 * @param vuc0 Iterator state
 */
void Metalphabet::nextMaz(std::vector<unsigned char> &vuc0){
    bool b0;
    unsigned short us0;
    b0=1;us0=0;
    while(b0){
        b0=0;
        vuc0[n-1-us0]++;
        if(vuc0[n-1-us0]==alphabets[n-1-us0]->cardinality){
            vuc0[n-1-us0]=0x00;
            us0++;
            if(us0!=n){
                b0=1;
            }
        }
    }    
}

/**
 * Metalphabet iterator 
 * @param vuc0 Iterator state
 * @param b0 N limit flag (default b0=0)
 */
void Metalphabet::nextMaz(std::vector<unsigned char> &vuc0,bool &b0){
    bool b1;
    unsigned short us0;
    b0=0;
    b1=1;us0=0;
    while(b1){
        b1=0;
        vuc0[n-1-us0]++;
        if(vuc0[n-1-us0]==alphabets[n-1-us0]->cardinality){
            vuc0[n-1-us0]=0x00;
            us0++;
            if(us0!=n){
                b1=1;
            }else{
                b0=1;
            }
        }
    }
}

/**
 * Metalphabet tuple iterator
 * @param vvuc0 Iterator state 
 */
void Metalphabet::nextMazTuple(std::vector<std::vector<unsigned char>> &vvuc0){
    bool b0;
    unsigned short us0;
    b0=1;us0=0;
    while(b0){
        nextMaz(vvuc0[vvuc0.size()-1-us0],b0);
        if(b0){
            us0++;
            if(us0==vvuc0.size()){
                b0=0;
            }
        }
    }    
}


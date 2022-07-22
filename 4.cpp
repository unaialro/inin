// EXP 4 - Musical notes  //
// @file 4.cpp
// @author Unai Alro
// @version 08/12/21

/* DESCRIPTION:
This program analyses the music dataset.
A folder is created with all the simulation results.
*/

#include "h0.h"

int main(){

    // Vars
    ofstream datout;
    bool save0=1;

    const unsigned short X=2;
    const unsigned short N=3;
    const unsigned short O=6;
    const unsigned short aus[N]={0,2,4};

    // Aux    
    unsigned u0=1;

    // Paths
    const string pth1=pth0+"4/";
    const string pth2="/home/unai/Documents/wk/rxv/kronos/data/music/bwv";
    string pth3,pth4;  

    // Read    
    vector<Alphabet*> vaz0;
    vector<Sequence> vseq0; 
    vector<Metasequence> vmseq0;    

    Alphabet az0(X);
    for(unsigned i0=0;i0!=N;i0++){
        vaz0.push_back(&az0);
    }    
    Metalphabet maz0(vaz0);     

    for(unsigned i0=0;i0!=18;i0++){
        Sequence seq0(&az0);  
        vseq0.clear();
        pth3=to_string(846+2*i0);
        for(unsigned i1=0;i1!=N;i1++){
            char c0='0'+aus[i1];
            pth4=pth2+pth3+'/'+c0+".bin";
            seq0.fromData(pth4);
            vseq0.push_back(seq0);
        }
        Metasequence mseq0(&maz0,seq0.length);
        mseq0.fromSequences(vseq0);
        vmseq0.push_back(mseq0);
        u0+=seq0.length;
    }

    MetasequenceEnsemble mens0(&maz0,vmseq0);

    // Simulations
    Multimodel mmd0(O,&maz0,nullptr,&mens0);

    mmd0.getModels();
    mmd0.estimateOrder();
    mmd0.getInteractions();

    // Save results
    if(save0){
        mmd0.writeResults(pth1);
    }

}

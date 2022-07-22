// EXP 3 - Traffic jams in Sao Paulo  //
// @file 3.cpp
// @author Unai Alro
// @version 08/12/21

/* DESCRIPTION:
This program analyses the traffic jam dataset.
A folder is created with all the simulation results.
*/

#include "h0.h"

int main(){

    // Vars
    ofstream datout;
    bool save0=1;

    const unsigned short N=5;
    const unsigned short O=7;

    string areas[N]={"OESTE","SUL","LESTE","CENTRO","NORTE"};
    Sequence data[N];

    // Paths
    const string pth1=pth0+"3/";
    const string pth2="/home/unai/Documents/wk/rxv/kronos/data/jams/";
    string pth3;  

    // Read
    Alphabet az0(2);
    Sequence seq0(&az0);   

    vector<Alphabet*> vaz0;
    vector<Sequence> vseq0;  

    for(unsigned i0=0;i0!=N;i0++){
        vaz0.push_back(&az0);
        pth3=pth2+areas[i0]+".bin";
        seq0.fromData(pth3);
        vseq0.push_back(seq0);
    }       
 
    // Simulations
    Metalphabet mlng0(vaz0);
    Metasequence msq0(&mlng0,seq0.length);
    msq0.fromSequences(vseq0);

    Multimodel mmd0(O,&mlng0,&msq0);   
    mmd0.getModels();
    mmd0.estimateOrder();
    mmd0.getInteractions();

print(mmd0.models[mmd0.aicorder-1]->iens.interactions.back().matrix,1);

    // Save results
    if(save0){
        mmd0.writeResults(pth1);
    }
}

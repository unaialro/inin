// EXP 1 - High Reducibility: Compare decomposition algorithm with a random algorithm  //
// @file 1.cpp
// @author Unai Alro
// @version 06/12/21

/* DESCRIPTION:
This program carries out the second experiment in the paper. 
It compares the reducibility of our algorithm with that of a random algorithm for random transition matrices.
The results are saved in the following text files:
r0.txt = reducibility of our algorithm 
r1.txt = reducibility of the random algorithm
*/

#include "h0.h"

int main(){

    srand(time(NULL));	

    // Vars
    ofstream datout;
    bool save0=1;

    const unsigned short X=2;
    unsigned short N;
    unsigned short O;  

    // Aux
    float f0,f1;

    // Repetition
    const unsigned short R0=1000;    

    // Exploration
    const unsigned short e0min=2; const float e0max=3; const float e0s=1; const short E0=1+(e0max-e0min)/e0s;
    const unsigned short e1min=2; const float e1max=5; const float e1s=1; const short E1=1+(e1max-e1min)/e1s;

    // Results
    float red0[E0][E1]={0};
    float red1[E0][E1]={0};

    // Paths
    const string pth1=pth0+"1/";

    // Simulations
    Alphabet az0(X);
    for(unsigned e0=0;e0!=E0;e0++){
        for(unsigned short e1=0;e1!=E1;e1++){
            O=e0min+e0*e0s;
            N=e1min+e1*e1s;
            std::vector<Alphabet*> vaz0;
            for(unsigned i0=0;i0!=N;i0++){
                vaz0.push_back(&az0);
            }    

            if(N==5 && O==3){continue;}

            Metalphabet maz0(vaz0);
            for(unsigned short r0=0;r0!=R0;r0++){
                Model md0(O,&maz0);
                md0.random();

                md0.getInteractionsDeterministic();
                md0.iens.getSubInteractions();
                md0.iens.getReducibility();
                f0=md0.iens.reducibility;   

                md0.getInteractionsRandom();
                md0.iens.getSubInteractions();
                md0.iens.getReducibility();
                f1=md0.iens.reducibility;

                red0[e0][e1]+=f0;
                red1[e0][e1]+=f1;
            }
            red0[e0][e1]/=R0;
            red1[e0][e1]/=R0;            
        }
    }  

    if(save0){
        datout.open(pth1+"r0"+".txt");
        for(unsigned e0=0;e0!=E0;e0++){
            for(unsigned e1=0;e1!=E1;e1++){
                datout << red0[e0][e1] << ' ';
            }
            datout << endl;
        }    
        datout.close();

        datout.open(pth1+"r1"+".txt");
        for(unsigned e0=0;e0!=E0;e0++){
            for(unsigned e1=0;e1!=E1;e1++){
                datout << red1[e0][e1] << ' ';
            }
            datout << endl;
        }    
        datout.close();        
    }
}

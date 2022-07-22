// EXP 2 - Scalability: Obtain distance for a fixed scale  //
// @file 2.cpp
// @author Unai Alro
// @version 06/12/21

/* DESCRIPTION:
This program carries out the second experiment in the supplemental material.
It generates random transition matrices, and applies the algorithm to obtain an interaction ensemble.
For every transition matrix it also creates sequences. The statistics of those sequences are computed, and one obtains the estimated transition matrices.
The algorithm is applied to the estimated transition matrices, and an estimated ensemble of interactions is obtained.
Finally we compute the statistical distance between the real and the estimated transition matrices, interaction coefficients and reducibility.
We generate sequences of a fixed leght, to understand how the results depend on the number of nodes and the order of the process.
The results are saved in the following text files:
sm.txt = distance between transition matrices 
si.txt = distance between interaction coefficients
sr.txt = distance between reducibilities 
M.txt = general information of the experiment 
*/

#include "h0.h"

int main(){

    srand(time(NULL));

    // Vars 
    ofstream datout;
    bool save0=1;

    unsigned short X; const unsigned short XNmax=256;
    unsigned short N;
    unsigned short O;
    unsigned long L; const unsigned long Lmax=32709000;

    const unsigned scale=1000;

    // Aux    
    char c0;

    // Repetition 
    const unsigned short R0=100;

    // Exploration 
    const unsigned short e0min=2; const short e0max=4; const float e0s=1; const short E0=1+(e0max-e0min)/e0s;
    const unsigned short e1min=2; const float e1max=4; const float e1s=1; const short E1=1+(e1max-e1min)/e1s;
    const unsigned short e2min=2; const float e2max=4; const float e2s=1; const short E2=1+(e2max-e2min)/e2s;

    // Results 
    float sm[E0][E1][E2]={0};
    float si[E0][E1][E2]={0};
    float sr[E0][E1][E2]={0};

    // Paths
    const string pth1=pth0+"2/";

    // Simulations
    for(unsigned short e0=0;e0!=E0;e0++){
        X=e0min+e0*e0s;
        Alphabet az0(X);
        for(unsigned short e1=0;e1!=E1;e1++){
            N=e1min+e1*e1s;
            std::vector<Alphabet*> vaz0;
            for(unsigned i0=0;i0!=N;i0++){
                vaz0.push_back(&az0);
            }  
            for(unsigned short e2=0;e2!=E2;e2++){
                O=e2min+e2*e2s;
                L=scale*pow(X,N*O);
                if(L>Lmax){continue;}
                if(pow(X,N)>XNmax){continue;} 

                Metalphabet maz0(vaz0);
                Metasequence mseq0(&maz0,L);

                for(unsigned short r0=0;r0!=R0;r0++){
                    Model md0(O,&maz0);
                    md0.random();
                    md0.getInteractionsDeterministic();
                    md0.iens.getSubInteractions();
                    md0.iens.getDistributions();
                    md0.iens.getReducibility();

                    mseq0.fromModel(&md0);

                    Multimodel mmd0(O,&maz0,&mseq0,nullptr,O);
                    mmd0.getModels();
                    mmd0.getInteractions(1);

                    sm[e0][e1][e2]+=mmd0.models[mmd0.trueorder-1]->getDistance(md0.matrix);
                    si[e0][e1][e2]+=mmd0.models[mmd0.trueorder-1]->iens.getDistance(&md0.iens);
                    sr[e0][e1][e2]+=abs(md0.iens.reducibility-mmd0.models[mmd0.trueorder-1]->iens.reducibility);
                }
                sm[e0][e1][e2]/=1.0*R0;
                si[e0][e1][e2]/=1.0*R0;
                sr[e0][e1][e2]/=1.0*R0; 
            }              
        }
    }

    if(save0){

	    datout.open(pth1+"M.txt");
        datout << e0min << ' ' << e0max << ' ' << e0s << ' ' << E0 << endl;
        datout << e1min << ' ' << e1max << ' ' << e1s << ' ' << E1 << endl;
        datout << e2min << ' ' << e2max << ' ' << e2s << ' ' << E2 << endl;
        datout << scale << ' ' << R0 << endl;
	    datout.close();

        for(unsigned short e0=0;e0!=E0;e0++){
            c0='2'+e0;

            datout.open(pth1+"sm"+c0+".txt");
            for(unsigned short e1=0;e1!=E1;e1++){
                for(unsigned short e2=0;e2!=E2;e2++){
                    datout << sm[e0][e1][e2] << ' ';
                }
                datout << endl;
            }
            datout.close();

            datout.open(pth1+"si"+c0+".txt");
            for(unsigned short e1=0;e1!=E1;e1++){
                for(unsigned short e2=0;e2!=E2;e2++){
                    datout << si[e0][e1][e2] << ' ';
                }
                datout << endl;
            }
            datout.close();

            datout.open(pth1+"sr"+c0+".txt");
            for(unsigned short e1=0;e1!=E1;e1++){
                for(unsigned short e2=0;e2!=E2;e2++){
                    datout << sr[e0][e1][e2] << ' ';
                }
                datout << endl;
            }
            datout.close();
        }        
    }
}

// EXP 0 - Scalability: Obtain distance for different lengths  //
// @file 0.cpp
// @author Unai Alro
// @version 06/12/21

/* DESCRIPTION:
This program carries out the first experiment in the paper and the first experiment in the supplemental material.
It generates random transition matrices, and applies the algorithm to obtain an interaction ensemble.
For every transition matrix it also creates sequences. The statistics of those sequences are computed, and one obtains the estimated transition matrices.
The algorithm is applied to the estimated transition matrices, and an estimated ensemble of interactions is obtained.
Finally we compute the statistical distance between the real and the estimated transition matrices, interaction coefficients and reducibility.
We generate sequences of different leghts, to understand how sensitive are the errors in the interaction ensemble and reducibility to the statistical distance.
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

    const unsigned short X=2;
    const unsigned short O=3; 
    unsigned short N;
    unsigned long L; const unsigned long Lmax=pow(2,12)*pow(10,4);

    unsigned scale;

    // Aux
    char c0;  

    // Repetition
    const unsigned short R0=100;

    // Exploration
    const unsigned short e0min=2; const float e0max=5; const float e0s=1; const short E0=1+(e0max-e0min)/e0s;
    const float e1min=1; const float e1max=4; const float e1s=0.5; const short E1=1+(e1max-e1min)/e1s;
  
    // Results
    float sm[E0][E1]={0};
    float si[E0][E1]={0};
    float sr[E0][E1]={0};


    // Paths
    const string pth1=pth0+"0/";
    c0='0'+X;
    const string pth2=pth1+c0+'/';
    c0='0'+O;
    const string pth3=pth2+c0+'/';

    // Simulations
    Alphabet az0(X);

    for(unsigned short e0=0;e0!=E0;e0++){
        N=e0min+e0*e0s;
        std::vector<Alphabet*> vaz0;
        for(unsigned i0=0;i0!=N;i0++){
            vaz0.push_back(&az0);
        }        

        for(unsigned short e1=0;e1!=E1;e1++){
            scale=pow(10,e1min+e1*e1s);
            L=scale*pow(X,N*O);  

            if(L>Lmax){continue;}
            if(N==5 && O==3){continue;}

            Metalphabet maz0(vaz0);
            Metasequence mseq0(&maz0,L);

            for(unsigned short r0=0;r0!=R0;r0++){
                Model md0(O,&maz0);
                md0.random();
                md0.getInteractionsDeterministic();
                md0.iens.getSubInteractions();
                md0.iens.getReducibility();
                md0.iens.getDistributions();

                mseq0.fromModel(&md0);

                Multimodel mmd0(O,&maz0,&mseq0,nullptr,O);
                mmd0.getModels();
                mmd0.getInteractions(1);

                sm[e0][e1]+=mmd0.models[mmd0.trueorder-1]->getDistance(md0.matrix);
                si[e0][e1]+=mmd0.models[mmd0.trueorder-1]->iens.getDistance(&md0.iens);
                sr[e0][e1]+=abs(md0.iens.reducibility-mmd0.models[mmd0.trueorder-1]->iens.reducibility);
            }
            sm[e0][e1]/=1.0*R0;
            si[e0][e1]/=1.0*R0;
            sr[e0][e1]/=1.0*R0;        
        }
    }


    // Save
    if(save0){

        datout.open(pth3+"sm.txt");
        for(unsigned short e0=0;e0!=E0;e0++){
            for(unsigned short e1=0;e1!=E1;e1++){
                datout << sm[e0][e1] << ' ';
            }
            datout << endl;
        }
        datout.close();

        datout.open(pth3+"si.txt");
        for(unsigned short e0=0;e0!=E0;e0++){
            for(unsigned short e1=0;e1!=E1;e1++){
                datout << si[e0][e1] << ' ';
            }
            datout << endl;
        }
        datout.close();

        datout.open(pth3+"sr.txt");
        for(unsigned short e0=0;e0!=E0;e0++){
            for(unsigned short e1=0;e1!=E1;e1++){
                datout << sr[e0][e1] << ' ';
            }
            datout << endl;
        }  
        datout.close();  

	    datout.open(pth3+"M.txt");
        datout << e0min << ' ' << e0max << ' ' << e0s << ' ' << E0 << endl;
        datout << e1min << ' ' << e1max << ' ' << e1s << ' ' << E1 << endl;
        datout << X << ' ' << O << ' ' << R0 << endl;
	    datout.close();        

    }
}

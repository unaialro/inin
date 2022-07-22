// Model headers //
// @file model.cpp
// @author Unai Alro
// @version 25/11/21

#include "model.h"

// Model class

/**
 * Constructor I
 */
Model::Model(){}
/**
 * Constructor II: Define order, metalphabet, metasequence and metasequence ensemble
 * @param us0 Model's order
 * @param maz0 Model's metalphabet
 * @param mseq0 Pointer to metasequence data
 * @param mens Pointer to metasequenceensemble data
 */
Model::Model(unsigned short us0,Metalphabet* maz0,Metasequence* mseq0,MetasequenceEnsemble* mens0){
    order=us0;
    maz=maz0;
    mseq=mseq0;
    mens=mens0;
    columns=maz->powers[order-1];
    parameters=columns*(maz->cardinality-1);
}
/**
 * Destructor
 */
Model::~Model(){}

/**
 * Assign a random transition matrix to the model
 */
void Model::random(){
    matrix.clear();
    std::vector<float> vf0,vf1;
    for(unsigned long i0=0;i0!=columns;i0++){
        vf1.push_back(0);
    }
    for(unsigned i0=0;i0!=maz->cardinality;i0++){
        vf0.clear();
        for(unsigned long i1=0;i1!=columns;i1++){
            vf0.push_back(1.0*rand()/RAND_MAX);
            vf1[i1]+=vf0[i1];
        }
        matrix.push_back(vf0);
    }
    for(unsigned short i0=0;i0!=maz->cardinality;i0++){
        for(unsigned long i1=0;i1!=columns;i1++){
            matrix[i0][i1]/=vf1[i1];
        }
    }    
}

/**
 * Compute the statistics
 */
void Model::getStats(){
    std::vector<unsigned char> vuc0;
    if(mens==nullptr){
        for(unsigned i0=0;i0!=order;i0++){
            vuc0.push_back(mseq->seq[i0]);
        }
        for(unsigned i0=0;i0!=mseq->length+1-order;i0++){
            stats.add(vuc0);
            vuc0.erase(vuc0.begin());
            vuc0.push_back(mseq->seq[i0+order]);
        }
    }else{
        for(unsigned i0=0;i0!=mens->mseqs.size();i0++){
            Model md0(order,maz,&mens->mseqs[i0]);
            md0.getStats(); 
            stats.add(&md0.stats);
        }
    }    
}

/**
 * Compute the transition matrix from the stats
 */
void Model::getMatrix(){
    unsigned u0,u1;
    Node* nd0;

    std::vector<unsigned char> vuc0,vuc1;
    std::vector<float> vf0;

    matrix.clear();
    for(unsigned long i0=0;i0!=columns;i0++){
        vf0.push_back(0);
    }
    for(unsigned i0=0;i0!=maz->cardinality;i0++){
        matrix.push_back(vf0);
    }

    for(short i0=0;i0!=order-1;i0++){
        vuc0.push_back(0x00);
        vuc1.push_back(0x00);
    }    

    for(unsigned long i0=0;i0!=columns;i0++){
        nd0=nullptr;
        if(order==1){
            nd0=&stats;
            u0=0;
        }else{
            u0=maz->compact(vuc0);
        }

        while(nd0==nullptr){
            nd0=stats.find(vuc1);
            vuc1.erase(vuc1.begin());
            if(nd0==nullptr && vuc1.size()==0){
                nd0=&stats;
                break;
            }
        }
        
        for(unsigned i1=0;i1!=nd0->pos.size();i1++){
            u1=nd0->pos[i1]->key;
            matrix[u1][u0]=1.0*(nd0->pos[i1]->freq)/nd0->freq;
        }

        if(order!=1){
            maz->nextAzTuple(vuc0);
            vuc1.clear();
            for(unsigned i1=0;i1!=vuc0.size();i1++){
                vuc1.push_back(vuc0[i1]);
            }
        }
    }    
}

/** 
 * Compute the loglikelihood
 */
void Model::getLoglikelihood(){
        std::vector<unsigned char> vuc0;
        if(mens==nullptr){
            for(unsigned short i0=0;i0!=order-1;i0++){
                vuc0.push_back(mseq->seq[i0]);
            }
            if(order==1){
                loglikelihood0=0;
            }else{
                loglikelihood0=pre->loglikelihood0 + pre->stats.loglikelihood0(vuc0);
            }
        }
        if(mseq==nullptr){
            loglikelihood0=0;
            if(order!=1){
                for(unsigned short i0=0;i0!=mens->mseqs.size();i0++){
                    vuc0.clear();
                    for(unsigned short i1=0;i1!=order-1;i1++){
                        vuc0.push_back(mens->mseqs[i0].seq[i1]);
                    }
                    loglikelihood0+=pre->loglikelihood0 + pre->stats.loglikelihood0(vuc0);                
                }
            }
        }
        loglikelihood1=stats.loglikelihood1();
        loglikelihood=loglikelihood0+loglikelihood1;
}

/**
 * Compute AIC
 */
void Model::getAic(){
    aic=2*(parameters-loglikelihood);
}

/**
 * Semirandom Decomposition algorithm
 */
void Model::getInteractionsSemirandom(){
    unsigned short us0;
    float f0,f1;

    InteractionEnsemble iens0(maz,order);
    iens=iens0;

    std::vector<std::vector<float>> replica;
    replica=matrix;    

    bool ba0[iens.cardinality]={0};
    std::vector<unsigned long> vul0;
    std::vector<float> vf0;

    std::vector<unsigned char> roCo;
    std::vector<std::vector<unsigned char>> coCo;    

    if(order==1){
        std::cout << "The code does not support order=1" << std::endl;
        return;
    }

    while(1){
        // find minimal order
        us0=maz->n*order+1;
        for(unsigned long i0=0;i0!=iens.cardinality;i0++){
            if(!ba0[i0] && iens.interactions[i0].order < us0){
                us0=iens.interactions[i0].order;
            }
        }   
        // elegible interactions
        vul0.clear();
        for(unsigned long i0=0;i0!=iens.cardinality;i0++){
            if(!ba0[i0] && iens.interactions[i0].order==us0){
                vul0.push_back(i0);
            }
        }
        // exit if none is left
        if(vul0.size()==0){
            break;
        }        
        // ranomly select an intereaction
        f0=1.0*rand()/RAND_MAX;
        us0=vul0[f0*vul0.size()];
        iens.interactions[us0].getMatrixofones();
        // initialize coordinates
        roCo.clear();
        coCo.clear();
        for(unsigned short i1=0;i1!=maz->n;i1++){
            roCo.push_back(0x00);
        }
        for(unsigned short i1=0;i1!=order-1;i1++){
            coCo.push_back(roCo);
        }
        // transverse matrix
        for(unsigned i0=0;i0!=maz->cardinality;i0++){
            for(unsigned i1=0;i1!=columns;i1++){
                if(replica[i0][i1]<iens.interactions[us0].matrix[iens.interactions[us0].rowCompact(roCo)][iens.interactions[us0].columnCompact(coCo)]){
                    iens.interactions[us0].matrix[iens.interactions[us0].rowCompact(roCo)][iens.interactions[us0].columnCompact(coCo)]=replica[i0][i1];
                }
                maz->nextMazTuple(coCo);
            }
            maz->nextMaz(roCo);
        }
        // find coeff
        f1=1;
        for(unsigned i0=0;i0!=iens.interactions[us0].columns;i0++){
            f0=0;
            for(unsigned i1=0;i1!=iens.interactions[us0].rows;i1++){
                f0+=iens.interactions[us0].matrix[i1][i0];
            }
            if(f0<f1){
                f1=f0;
            }
            if(f0<0.00001){
                ba0[us0]=1;
            }else{
                for(unsigned i1=0;i1!=iens.interactions[us0].rows;i1++){
                    iens.interactions[us0].matrix[i1][i0]/=(iens.interactions[us0].normalization*f0);
                }
            }
        }
        // normalize
        f1*=iens.interactions[us0].normalization;
        // delete tiny
        if(ba0[us0]){
            iens.interactions[us0].coefficient=0; 
            continue;
        }  
        // extract
        for(unsigned i0=0;i0!=maz->cardinality;i0++){
            for(unsigned i1=0;i1!=columns;i1++){
                replica[i0][i1]-=f1*iens.interactions[us0].matrix[iens.interactions[us0].rowCompact(roCo)][iens.interactions[us0].columnCompact(coCo)];
                maz->nextMazTuple(coCo);
            }
        maz->nextMaz(roCo);
        }          
        // close
        iens.interactions[us0].coefficient=f1;
        ba0[us0]=1;           
    }

    for(unsigned i0=0;i0!=iens.cardinality;i0++){
        if(!ba0[i0]){
            iens.interactions[i0].coefficient=0;
        }
    }
}

/**
 * Deterministic Decomposition algorithm
 */
void Model::getInteractionsDeterministic(){
    unsigned short us0;
    float f0;

    InteractionEnsemble iens0(maz,order);
    iens=iens0;

    std::vector<std::vector<float>> replica;
    replica=matrix;    

    bool ba0[iens.cardinality]={0};
    std::vector<unsigned long> vul0;
    std::vector<float> vf0;

    std::vector<unsigned char> roCo;
    std::vector<std::vector<unsigned char>> coCo;    

    if(order==1){
        std::cout << "The code does not support order=1" << std::endl;
        return;
    }
    // order by order
    for(int i0=0;i0!=maz->n*order+1;i0++){
        while(1){
            // elegible interactions
            vul0.clear();
            vf0.clear();
            for(unsigned long i1=0;i1!=iens.cardinality;i1++){
                if(!ba0[i1] && iens.interactions[i1].order==i0){
                    iens.interactions[i1].getMatrixofones();
                    vul0.push_back(i1);
                    vf0.push_back(1);
                }
            }          
            // exit if none is left
            if(vul0.size()==0){
                break;
            }   
            // initialize coordinates
            roCo.clear();
            coCo.clear();
            for(unsigned short i1=0;i1!=maz->n;i1++){
                roCo.push_back(0x00);
            }
            for(unsigned short i1=0;i1!=order-1;i1++){
                coCo.push_back(roCo);
            }
            // transverse matrix
            for(unsigned i1=0;i1!=maz->cardinality;i1++){
                for(unsigned i2=0;i2!=columns;i2++){
                    for(unsigned i3=0;i3!=vul0.size();i3++){
                        if(replica[i1][i2]<iens.interactions[vul0[i3]].matrix[iens.interactions[vul0[i3]].rowCompact(roCo)][iens.interactions[vul0[i3]].columnCompact(coCo)]){
                            iens.interactions[vul0[i3]].matrix[iens.interactions[vul0[i3]].rowCompact(roCo)][iens.interactions[vul0[i3]].columnCompact(coCo)]=replica[i1][i2];
                        }
                    }
                    maz->nextMazTuple(coCo);
                }
                maz->nextMaz(roCo);
            }
            // find allowerd max coeff
            for(unsigned i1=0;i1!=vul0.size();i1++){
                for(unsigned i2=0;i2!=iens.interactions[vul0[i1]].columns;i2++){
                    f0=0;
                    for(unsigned i3=0;i3!=iens.interactions[vul0[i1]].rows;i3++){
                        f0+=iens.interactions[vul0[i1]].matrix[i3][i2];
                    }
                    if(f0<vf0[i1]){
                        vf0[i1]=f0;
                    }
                    if(f0<0.00001){
                        ba0[vul0[i1]]=1;
                        iens.interactions[vul0[i1]].coefficient=0;
                    }else{
                        for(unsigned i3=0;i3!=iens.interactions[vul0[i1]].rows;i3++){
                            iens.interactions[vul0[i1]].matrix[i3][i2]/=(iens.interactions[vul0[i1]].normalization*f0);
                        }
                    }
                }  
                vf0[i1]*=iens.interactions[vul0[i1]].normalization;
            } 
            // check for tiny contributions   
            us0=0;
            for(unsigned i1=0;i1!=vul0.size();i1++){
                if(ba0[vul0[i1]]){
                    us0++;
                }
            }
            // exit if none is left       
            if(vul0.size()==us0){
                break;
            }       
            // find interaction with highest coeff 
            f0=0;
            us0=vul0.size();
            for(unsigned i1=0;i1!=vf0.size();i1++){
                if(vf0[i1]>f0){
                    f0=vf0[i1];
                    us0=i1;
                }
            } 
            // extract
            for(unsigned i1=0;i1!=maz->cardinality;i1++){
                for(unsigned i2=0;i2!=columns;i2++){
                    replica[i1][i2]-=vf0[us0]*iens.interactions[vul0[us0]].matrix[iens.interactions[vul0[us0]].rowCompact(roCo)][iens.interactions[vul0[us0]].columnCompact(coCo)];
                    maz->nextMazTuple(coCo);
                }
            maz->nextMaz(roCo);
            }     
            // close
            iens.interactions[vul0[us0]].coefficient=vf0[us0];
            ba0[vul0[us0]]=1; 
        }
    }
}

/**
 * Random decomposition algorithm
 */
void Model::getInteractionsRandom(){
    unsigned short us0;
    float f0,f1;

    InteractionEnsemble iens0(maz,order);
    iens=iens0;

    std::vector<std::vector<float>> replica;
    replica=matrix;    

    bool ba0[iens.cardinality]={0};
    std::vector<unsigned long> vul0;
    std::vector<float> vf0;

    std::vector<unsigned char> roCo;
    std::vector<std::vector<unsigned char>> coCo;    

    if(order==1){
        std::cout << "The code does not support order=1" << std::endl;
        return;
    }

    while(1){ 
        // elegible interactions
        vul0.clear();
        for(unsigned long i0=0;i0!=iens.cardinality;i0++){
            if(!ba0[i0]){
                vul0.push_back(i0);
            }
        }
        // exit if none is left
        if(vul0.size()==0){
            break;
        }        
        // ranomly select an intereaction
        f0=1.0*rand()/RAND_MAX;
        us0=vul0[f0*vul0.size()];
        iens.interactions[us0].getMatrixofones();
        // initialize coordinates
        roCo.clear();
        coCo.clear();
        for(unsigned short i1=0;i1!=maz->n;i1++){
            roCo.push_back(0x00);
        }
        for(unsigned short i1=0;i1!=order-1;i1++){
            coCo.push_back(roCo);
        }
        // transverse matrix
        for(unsigned i0=0;i0!=maz->cardinality;i0++){
            for(unsigned i1=0;i1!=columns;i1++){
                if(replica[i0][i1]<iens.interactions[us0].matrix[iens.interactions[us0].rowCompact(roCo)][iens.interactions[us0].columnCompact(coCo)]){
                    iens.interactions[us0].matrix[iens.interactions[us0].rowCompact(roCo)][iens.interactions[us0].columnCompact(coCo)]=replica[i0][i1];
                }
                maz->nextMazTuple(coCo);
            }
            maz->nextMaz(roCo);
        }
        // find coeff
        f1=1;
        for(unsigned i0=0;i0!=iens.interactions[us0].columns;i0++){
            f0=0;
            for(unsigned i1=0;i1!=iens.interactions[us0].rows;i1++){
                f0+=iens.interactions[us0].matrix[i1][i0];
            }
            if(f0<f1){
                f1=f0;
            }
            if(f0<0.00001){
                ba0[us0]=1;
            }else{
                for(unsigned i1=0;i1!=iens.interactions[us0].rows;i1++){
                    iens.interactions[us0].matrix[i1][i0]/=(iens.interactions[us0].normalization*f0);
                }
            }
        }
        // normalize
        f1*=iens.interactions[us0].normalization;
        // delete tiny
        if(ba0[us0]){
            iens.interactions[us0].coefficient=0; 
            continue;
        }  
        // extract
        for(unsigned i0=0;i0!=maz->cardinality;i0++){
            for(unsigned i1=0;i1!=columns;i1++){
                replica[i0][i1]-=f1*iens.interactions[us0].matrix[iens.interactions[us0].rowCompact(roCo)][iens.interactions[us0].columnCompact(coCo)];
                maz->nextMazTuple(coCo);
            }
        maz->nextMaz(roCo);
        }          
        // close
        iens.interactions[us0].coefficient=f1;
        ba0[us0]=1;           
    }

    for(unsigned i0=0;i0!=iens.cardinality;i0++){
        if(!ba0[i0]){
            iens.interactions[i0].coefficient=0;
        }
    }
}

/**
 * Compute statistical distance between transition matrices
 * @param vvf0 The matrix to compare with
 */
float Model::getDistance(std::vector<std::vector<float>> vvf0){
    Node* nd0;
    float f0,f1;
    std::vector<unsigned char> vuc0;
    std::vector<float> vf0,vf1;

    for(short i0=0;i0!=order-1;i0++){
        vuc0.push_back(0x00);
    }
    for(unsigned i1=0;i1!=maz->cardinality;i1++){
        vf0.push_back(0);
        vf1.push_back(0);        
    }

    f0=0;
    for(unsigned long i0=0;i0!=columns;i0++){
        nd0=stats.find(vuc0);
        f1=(nd0==nullptr)?0:1.0*nd0->freq/stats.freq;
        for(unsigned i1=0;i1!=maz->cardinality;i1++){
            vf0[i1]=vvf0[i1][i0];
            vf1[i1]=matrix[i1][i0];
        }
        f0+=f1*distance(vf0,vf1);
        maz->nextAzTuple(vuc0);
    }
    return f0;    
}

/**
 * Write the interaction ensemble in files
 * @param str0 Path to folder 
 */
void Model::writeResults(std::string str0){
    iens.writeResults(str0);
}

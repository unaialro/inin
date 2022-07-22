// Interaction function //
// @file interaction.cpp
// @author Unai Alro
// @version 25/11/21

#include "interaction.h"

// Interaction Class

/**
 * Constructor I
 * @param maz0 Metalphabet for node's involved in the interaction
 * @param vus0 Interaction type
 * @param us0 Maxorder
 */
Interaction::Interaction(Metalphabet* maz0,unsigned short us0,std::vector<unsigned short> vus0){
    maz=maz0;
    maxorder=us0;
    rows=1;
    columns=1;
    normalization=1;

    for(short i0=vus0.size()-1;i0!=-1;i0--){
        type.insert(type.begin(),vus0[i0]);
        order+=vus0[i0];
        if(vus0[i0]>0){
            rowPowers.insert(rowPowers.begin(),rows);
            rows*=maz->alphabets[i0]->cardinality;
            columns*=maz->alphabets[i0]->powers[vus0[i0]-1];
        }else{
            rowPowers.insert(rowPowers.begin(),0);
            normalization*=maz->alphabets[i0]->cardinality;
        }
    }
    parameters=columns*(rows-1);
    getColumnpowers();
}
/**
 * Destructor
 */
Interaction::~Interaction(){}

/**
 * Obtain the joint encoding for rows
 */
unsigned Interaction::rowCompact(std::vector<unsigned char> vuc0){
    unsigned u0=0;
    for(unsigned i0=0;i0!=type.size();i0++){
        u0+=vuc0[i0]*rowPowers[i0];
    }
    return u0;
}

/**
 * Obtain the joint encoding for columns
 */
unsigned long Interaction::columnCompact(std::vector<std::vector<unsigned char>> vvuc0){
    unsigned long ul0=0;
    unsigned au0[maxorder-1]={0};
    for(short i0=0;i0!=maxorder-1;i0++){
        for(unsigned i1=0;i1!=maz->n;i1++){
            au0[i0]+=vvuc0[i0][i1]*columnPowers0[i0][i1];
        }
    }
    for(unsigned i0=0;i0!=vvuc0.size();i0++){
        ul0+=au0[i0]*columnPowers1[i0];
    }
    return ul0;    
}


/**
 * Initialize reduced matrix
 */
void Interaction::getMatrixofones(){
    matrix.clear();
    std::vector<float> vf0;
    for(unsigned long i0=0;i0!=columns;i0++){
        vf0.push_back(1);
    }
    for(unsigned i0=0;i0!=rows;i0++){
        matrix.push_back(vf0);
    }    
}

/**
 * Compute subinteractions
 */
void Interaction::getSubInteractions(){
    setSubInteractions();
    getSubInteractions0();
}

/**
 * Auxiliary computations for column powers
 */
void Interaction::getColumnpowers(){
    unsigned u0;
    std::vector<unsigned>vu0,vu1;

    columnPowers0.clear();
    columnPowers1.clear();

    for(unsigned short i0=1;i0!=maxorder;i0++){

        u0=1;
        vu0.clear();
        for(short i1=type.size()-1;i1!=-1;i1--){
            if(type[i1]>i0){
                vu0.insert(vu0.begin(),u0);
                u0*=maz->alphabets[i1]->cardinality;
            }else{
                vu0.insert(vu0.begin(),0);
            }
        }
        columnPowers0.insert(columnPowers0.begin(),vu0);
        vu1.insert(vu1.begin(),u0);
    }

    u0=1;
    for(int i0=vu1.size()-1;i0!=-1;i0--){
        if(vu1[i0]!=1){
            columnPowers1.insert(columnPowers1.begin(),u0);
            u0*=vu1[i0];
        }else{
            columnPowers1.insert(columnPowers1.begin(),0);
        }
    }    
}

/**
 * Compute the complementary of a partition
 * @param vus0 Tuple to compute the complementary of
 * @param us0 Cardinality of the complete set
 */
std::vector<unsigned short> Interaction::getComplementary(std::vector<unsigned short> vus0,unsigned short us0){
    bool b0=1;
    std::vector<unsigned short> vus1;
    for(unsigned short i0=0;i0!=us0;i0++){
        if(b0 && vus0[0]==i0){
            vus0.erase(vus0.begin());
            if(vus0.size()==0){
                b0=0;
            }
        }else{
            vus1.push_back(i0);
        }
    }
    return vus1;
}

/**
 * Prepare Subinteractions
 */
void Interaction::setSubInteractions(){
    std::vector<unsigned short> vus0;
    for(unsigned short i0=0;i0!=maz->n;i0++){
        vus0.push_back(i0);
    }
    subinteractions.clear();
    subinteractions.push_back(*this);
    subinteractions[0].partition=vus0;    
}

/**
 * Subinteraction decomposition auxiliary 0
 */
void Interaction::getSubInteractions0(){
    bool b0=1;
    unsigned short us0=1;
    while(b0){
        b0=getSubInteractions1(us0);
    }    
}

/**
 * Subinteraction decomposition auxiliary 1
 */
bool Interaction::getSubInteractions1(unsigned short &us0){
    bool b0=0;
    // partition loop
    for(unsigned short i0=us0;i0!=round(ceil(subinteractions.back().partition.size()+1)/2.0);i0++){
        us0=i0;
        // combinations loop
        std::vector<unsigned short> vus0;
        for(unsigned short i1=0;i1!=i0;i1++){
            vus0.push_back(i1);
        }
        for(unsigned short i1=0;i1!=combinatorial(subinteractions.back().partition.size(),i0);i1++){
            b0=getSubInteraction(vus0);
            if(b0){
                return b0;
            }
            if(i1!=combinatorial(subinteractions.back().partition.size(),i0)-1){
                nextComb(vus0,subinteractions.back().partition.size());
            }
        }
    }
    return b0;    
}

/**
 * Subinteraction decomposition auxiliary 2
 */
bool Interaction::getSubInteraction(std::vector<unsigned short> vus0){
    bool b0=0;
    if(vus0.size()==1 && type[subinteractions.back().partition[vus0[0]]]==0){
        getSubInteractionUniform(vus0);
        b0=1;
    }else{
        b0=getSubInteractionNonUniform(vus0);
    }
    return b0;
}

/**
 * Subinteraction decomposition auxiliary 3a
 */
void Interaction::getSubInteractionUniform(std::vector<unsigned short> vus0){
    std::vector<unsigned short> vus1,vus2;
    std::vector<float> vf0;
    std::vector<std::vector<float>> vvf0;
    std::vector<Alphabet*> vaz0;

    vus1=getComplementary(vus0,subinteractions.back().partition.size());

    // group 1 
    vaz0.push_back(maz->alphabets[subinteractions.back().partition[vus0[0]]]);
    vus2.push_back(0);

    Interaction int1(new Metalphabet(vaz0),maxorder,vus2);

    vus2.clear();
    vus2.push_back(subinteractions.back().partition[vus0[0]]);
    int1.partition=vus2;

    vf0.push_back(1.0/maz->alphabets[subinteractions.back().partition[vus0[0]]]->cardinality);
    vvf0.push_back(vf0);
    int1.matrix=vvf0;    

    // group 2
    vaz0.clear();
    vus2.clear();
    for(unsigned i0=0;i0!=vus1.size();i0++){
        vaz0.push_back(maz->alphabets[subinteractions.back().partition[vus1[i0]]]);
        vus2.push_back(type[subinteractions.back().partition[vus1[i0]]]);
    }

    Interaction int2(new Metalphabet(vaz0),maxorder,vus2);

    vus2.clear();
    for(unsigned i0=0;i0!=vus1.size();i0++){
        vus2.push_back(subinteractions.back().partition[vus1[i0]]);
    }
    int2.partition=vus2;

    int2.getMatrixofones();
    for(unsigned i0=0;i0!=int2.rows;i0++){
        for(unsigned i1=0;i1!=int2.columns;i1++){
            int2.matrix[i0][i1]=subinteractions.back().matrix[i0][i1]/int1.matrix[0][0];
        }
    }   

    // delete old
    subinteractions.erase(subinteractions.begin()+subinteractions.size()-1);
    // bring new
    subinteractions.push_back(int1);
    subinteractions.push_back(int2);     
}

/**
 * Subinteraction decomposition auxiliary 3b
 */
bool Interaction::getSubInteractionNonUniform(std::vector<unsigned short> vus0){
    bool b0;
    float f0;

    std::vector<unsigned char> vuc0,vuc1;
    std::vector<unsigned short> vus1,vus2,vus3;
    std::vector<float> vf0;
    std::vector<std::vector<float>> vvf0;

    std::vector<Alphabet*> vaz0;

    std::vector<unsigned char> vuc0row,vuc1row,vuc2row;
    std::vector<std::vector<unsigned char>> vvuc0col,vvuc1col,vvuc2col;

    vus1=getComplementary(vus0,subinteractions.back().partition.size());

    // veryfy if uniform
    b0=0;
    for(unsigned i0=0;i0!=vus1.size();i0++){
        if(type[subinteractions.back().partition[vus1[i0]]]==0){
            return b0;
        }
    }  

    // group selection  
    vus2.clear();
    for(unsigned i1=0;i1!=vus0.size();i1++){
        vus2.push_back(vus0[i1]);
    }

    for(unsigned i0=0;i0!=subinteractions.back().type.size();i0++){
        if(vus2.size()>0){
            if(vus2[0]==i0){
                vus3.push_back(0);
                vus2.erase(vus2.begin());
            }else{
                vus3.push_back(1);
            }
        }else{
            vus3.push_back(1);
        }        
    }    

    // group 1 subinteraction
    vaz0.clear();
    vus2.clear();
    for(unsigned i0=0;i0!=vus0.size();i0++){
        vaz0.push_back(maz->alphabets[subinteractions.back().partition[vus0[i0]]]);
        vus2.push_back(type[subinteractions.back().partition[vus0[i0]]]);
    }

    Interaction int1(new Metalphabet(vaz0),maxorder,vus2);
    vus2.clear();
    for(unsigned i0=0;i0!=vus0.size();i0++){
        vus2.push_back(subinteractions.back().partition[vus0[i0]]);
    }
    int1.partition=vus2;    

    // group 2 subinteraction
    vaz0.clear();
    vus2.clear();
    for(unsigned i0=0;i0!=vus1.size();i0++){
        vaz0.push_back(maz->alphabets[subinteractions.back().partition[vus1[i0]]]);
        vus2.push_back(type[subinteractions.back().partition[vus1[i0]]]);
    }

    Interaction int2(new Metalphabet(vaz0),maxorder,vus2);
    vus2.clear();
    for(unsigned i0=0;i0!=vus1.size();i0++){
        vus2.push_back(subinteractions.back().partition[vus1[i0]]);
    }
    int2.partition=vus2;
    int2.getMatrixofones();  

    // group 1 matrix  
    for(unsigned i0=0;i0!=int2.columns;i0++){
        int1.getMatrixofones();
        for(unsigned i1=0;i1!=int1.rows;i1++){
            for(unsigned i2=0;i2!=int1.columns;i2++){
                int1.matrix[i1][i2]-=1;
                for(unsigned i3=0;i3!=int2.rows;i3++){
                    int1.matrix[i1][i2]+=subinteractions.back().matrix[i1*int2.rows+i3][i2*int2.columns+i0];
                }
            }
        }
        if(int1.checkSubInteractions()){
            break;
        }
    }     

    // group 2 matrix
    for(unsigned i0=0;i0!=int1.columns;i0++){
        int2.getMatrixofones();
        for(unsigned i1=0;i1!=int2.rows;i1++){
            for(unsigned i2=0;i2!=int2.columns;i2++){
                int2.matrix[i1][i2]-=1;
                for(unsigned i3=0;i3!=int1.rows;i3++){
                    int2.matrix[i1][i2]+=subinteractions.back().matrix[i1+i3*int2.rows][i2+i0*int2.columns];
                }
            }
        }
        if(int2.checkSubInteractions()){
            break;
        }
    }

    // initialize rows and cols
    for(unsigned i0=0;i0!=subinteractions.back().type.size();i0++){
        vuc0row.push_back(0x00);
    }
    for(short i0=0;i0!=maxorder-1;i0++){
        vvuc0col.push_back(vuc0row);
    }      

    // transverse matrix
    for(unsigned i0=0;i0!=subinteractions.back().rows;i0++){
        // find subrows
        vuc1row.clear();
        vuc2row.clear();
        for(unsigned i1=0;i1!=vuc0row.size();i1++){
            if(vus3[i1]==0){
                vuc1row.push_back(vuc0row[i1]);
            }else{
                vuc2row.push_back(vuc0row[i1]);
            }
        }     

        for(unsigned i1=0;i1!=subinteractions.back().columns;i1++){
            // find subcols
            vvuc1col.clear();
            vvuc2col.clear();       

            for(unsigned i2=0;i2!=vvuc0col.size();i2++){
                vuc0.clear();
                vuc1.clear();
                for(unsigned i3=0;i3!=vvuc0col[i2].size();i3++){
                    if(vus3[i3]==0){
                        vuc0.push_back(vvuc0col[i2][i3]);
                    }else{
                        vuc1.push_back(vvuc0col[i2][i3]);
                    }
                }
                vvuc1col.push_back(vuc0);
                vvuc2col.push_back(vuc1);
            }       

            // tensor coherence
            f0=subinteractions.back().matrix[i0][i1]-int1.matrix[int1.rowCompact(vuc1row)][int1.columnCompact(vvuc1col)]*int2.matrix[int2.rowCompact(vuc2row)][int2.columnCompact(vvuc2col)];
            if(fabs(f0)>0.00001){
                return 0;
            }        
            subinteractions.back().nextSubCol(vvuc0col);
        }
        subinteractions.back().nextSubRow(vuc0row);
    }    
    // exchange
    subinteractions.erase(subinteractions.begin()+subinteractions.size()-1);
    subinteractions.push_back(int1);
    subinteractions.push_back(int2);

    return 1; 
}

/**
 * Subinteraction decomposition auxiliary 4 
 */
bool Interaction::checkSubInteractions(){
    for(unsigned i0=0;i0!=columns;i0++){
        for(unsigned i1=0;i1!=rows;i1++){
            if(matrix[i1][i0]!=0){
                return 1;
            }
        }
    }
    return 0;
}

/**
 * Iterator over subinteraction rows
 * @param vuc0 Iterator state
 */
void Interaction::nextSubRow(std::vector<unsigned char> &vuc0){
    bool b0;
    unsigned short us0;

    b0=1;
    us0=0;
    while(b0){
        b0=0;
        if(type[type.size()-1-us0]==0){
            us0++;
            if(us0!=vuc0.size()){
                b0=1;
            }
            continue;
        }
        vuc0[vuc0.size()-1-us0]++;
        if(vuc0[vuc0.size()-1-us0]==maz->alphabets[vuc0.size()-1-us0]->cardinality){
            vuc0[vuc0.size()-1-us0]=0x00;
            us0++;
            if(us0!=vuc0.size()){
                b0=1;
            }
        }
    }    
}

/**
 * Iterator over subinteraction rows with flags
 * @param vuc0 Iterator state
 * @param b0 Flag
 * @param us1 Limit
 */
void Interaction::nextSubRow(std::vector<unsigned char> &vuc0,bool &b1,unsigned short us1){
    bool b0;
    unsigned short us0;

    b0=1;
    b1=0;
    us0=0; 
    while(b0){
        b0=0;
        if(type[type.size()-1-us0]-2<us1){
            us0++;
            if(us0!=vuc0.size()){
                b0=1;
            }else{
                b1=1;
            }
            continue;
        }
        vuc0[vuc0.size()-1-us0]++;
        if(vuc0[vuc0.size()-1-us0]==maz->alphabets[vuc0.size()-1-us0]->cardinality){
            vuc0[vuc0.size()-1-us0]=0x00;
            us0++;
            if(us0!=vuc0.size()){
                b0=1;
            }else{
                b1=1;
            }
        }
    }    
}

/**
 * Iterator over subinteraction columns
 * @param vvuc0 Iterator state
 */
void Interaction::nextSubCol(std::vector<std::vector<unsigned char>> &vvuc0){
    bool b0;
    unsigned short us0;

    b0=1;
    us0=0;
    while(b0){
        b0=0;
        nextSubRow(vvuc0[vvuc0.size()-1-us0],b0,us0);
        if(b0){
            us0++;
            if(us0==vvuc0.size()){
                b0=0;
            }
        }
    }
}




// InteractionEnsemble class

/**
 * Constructor I
 */
InteractionEnsemble::InteractionEnsemble(){}
/**
 * Constructor II
 */
InteractionEnsemble::InteractionEnsemble(Metalphabet* maz0,unsigned short us0){
    std::vector<unsigned short> vus0;

    maz=maz0;
    maxorder=us0;
    cardinality=pow(maxorder+1,maz->n);

    for(unsigned i0=0;i0!=maz->n;i0++){
        powers.push_back(pow(maxorder+1,maz->n-1-i0));
    }
    for(unsigned long i0=0;i0!=cardinality;i0++){
        vus0=typeDecoder(i0);
        Interaction int0(maz,maxorder,vus0);
        interactions.push_back(int0); 
    }  
}
/**
 * Destructor
 */
InteractionEnsemble::~InteractionEnsemble(){}

/**
 * Subinteraction decomposition algorithm
 */
void InteractionEnsemble::getSubInteractions(){
    for(unsigned i0=0;i0!=cardinality;i0++){
        if(interactions[i0].coefficient>0.00001){
            interactions[i0].getSubInteractions();
        }
    }
}

/**
 * Compute reducibility
 */
void InteractionEnsemble::getReducibility(){
    float f0=0;
    unsigned long long ull0;

    for(unsigned long i0=0;i0!=cardinality;i0++){
        ull0=0;
        for(unsigned i1=0;i1!=interactions[i0].subinteractions.size();i1++){
            ull0+=interactions[i0].subinteractions[i1].parameters;
        }
        f0+=interactions[i0].coefficient*ull0;
    }
    reducibility=1-f0/interactions[cardinality-1].parameters;
}

/**
 * Compute distributions
 */
void InteractionEnsemble::getDistributions(){
    bool b0;
    unsigned short us0;
    unsigned long long ull0;
    float f0;

    std::vector<unsigned short> vus0;
    std::vector<float> vf0,vf1,vf2,vf3;

    distribution.clear();
    cdistribution.clear();

    f0=interactions[cardinality-1].parameters;
    for(unsigned long i0=0;i0!=cardinality;i0++){
        ull0=0;
        for(unsigned i1=0;i1!=interactions[i0].subinteractions.size();i1++){
            ull0+=interactions[i0].subinteractions[i1].parameters;
        }    
        b0=1;
        for(unsigned i1=0;i1!=vf0.size();i1++){
            if(fabs(ull0/f0 -vf0[i1])<0.00001){
                vf1[i1]+=interactions[i0].coefficient;
                b0=0;
                break;
            }
        } 
        if(b0){
            vf0.push_back(ull0/f0);
            vf1.push_back(interactions[i0].coefficient);
        }                   
    }  

    for(unsigned i0=0;i0!=vf0.size();i0++){
        vus0.push_back(i0);
    }
    std::stable_sort(vus0.begin(),vus0.end(),[&vf0](unsigned i0,unsigned i1){return vf0[i0] < vf0[i1];});

    for(unsigned i0=0;i0!=vus0.size();i0++){
        vf2.push_back(vf0[vus0[i0]]);
        vf3.push_back(vf1[vus0[i0]]);
    }
    vf0.clear();
    vf1.clear();

    us0=0;
    for(unsigned short i0=1;i0!=101;i0++){
        vf0.push_back(i0/100.0);
        vf1.push_back(0);
        for(unsigned i1=us0;i1!=vf2.size();i1++){
            if(vf2[i1]<=i0/100.0 && vf2[i1]>(i0-1)/100.0){
                vf1[vf1.size()-1]+=vf3[i1];
                us0=i1;
            }
        }
    }
    distribution.push_back(vf0);
    distribution.push_back(vf1);

    vf2.clear();
    vf3.clear();
    for(unsigned i0=0;i0!=vf0.size();i0++){
        vf2.push_back(vf1[i0]);
        if(i0!=0){
            vf2[i0]+=vf2[i0-1];
        }
    }
    cdistribution.push_back(vf0);
    cdistribution.push_back(vf2);            
}

/**
 * Get dominant interactions of the ensemble
 * @param f0 Boundary coefficient (Default=0.01)
 */
void InteractionEnsemble::getElite(float f0){
    for(unsigned i0=0;i0!=cardinality;i0++){
        if(interactions[i0].coefficient>=f0){
            elite.push_back(&interactions[i0]);
        }
    }
}

/**
 * Compute the statistical distance between two interaction ensembles
 * @param iens0 Interaction ensemble to compute with
 */
float InteractionEnsemble::getDistance(InteractionEnsemble* iens0){
    std::vector<float> vf0,vf1;
    for(unsigned i0=0;i0!=cardinality;i0++){
        vf0.push_back(interactions[i0].coefficient);
        vf1.push_back(iens0->interactions[i0].coefficient);
    }
    return distance(vf0,vf1);    
}

/**
 * Write interaction ensemble in files
 * @param str0 Path to file
 */
void InteractionEnsemble::writeResults(std::string str0){

    std::ofstream datout;

    datout.open(str0+"ecoeffs"+".txt");
    for(unsigned i0=0;i0!=elite.size();i0++){
        datout << elite[i0]->coefficient << ' ';
    }
    datout.close();

    datout.open(str0+"eorders"+".txt");
    for(unsigned i0=0;i0!=elite.size();i0++){
        datout << elite[i0]->order << ' ';
    }
    datout.close();

    datout.open(str0+"etypes"+".txt");
    for(unsigned i0=0;i0!=elite.size();i0++){
        for(unsigned short i1=0;i1!=maz->n;i1++){
            datout << elite[i0]->type[i1] << ' ';
        }
        datout << std::endl;
    }
    datout.close();
 
    for(unsigned i0=0;i0!=elite.size();i0++){
        std::string str1=std::to_string(i0);
        datout.open((str0+"epartition"+str1+".txt").c_str());
        for(unsigned short i1=0;i1!=elite[i0]->subinteractions.size();i1++){
            for(unsigned short i2=0;i2!=elite[i0]->subinteractions[i1].partition.size();i2++){
                datout << elite[i0]->subinteractions[i1].partition[i2] << ' ';
            }
            datout << std::endl;
        }
        datout.close();
    }    

    for(unsigned i0=0;i0!=elite.size();i0++){
        std::string str1=std::to_string(i0);
        datout.open((str0+"esubint"+str1+".txt").c_str());
        for(unsigned short i1=0;i1!=elite[i0]->subinteractions.size();i1++){
            for(unsigned short i2=0;i2!=elite[i0]->subinteractions[i1].type.size();i2++){
                datout << elite[i0]->subinteractions[i1].type[i2] << ' ';
            }
            datout << std::endl;
        }
        datout.close();
    }    

    datout.open(str0+"distribution"+".txt");
    for(unsigned short i0=0;i0!=distribution[0].size();i0++){
        datout << distribution[0][i0] << ' ';
    }
    datout << std::endl;
    for(unsigned short i0=0;i0!=distribution[1].size();i0++){
        datout << distribution[1][i0] << ' ';
    }
    datout << std::endl;
    datout.close();

    datout.open(str0+"cdistribution"+".txt");
    for(unsigned short i0=0;i0!=cdistribution[0].size();i0++){
        datout << cdistribution[0][i0] << ' ';
    }
    datout << std::endl;
    for(unsigned short i0=0;i0!=cdistribution[1].size();i0++){
        datout << cdistribution[1][i0] << ' ';
    }
    datout << std::endl;
    datout << reducibility << std::endl;
    datout.close();


}

/**
 * Interaction type from a number
 * @param ul0 The number
 */
std::vector<unsigned short> InteractionEnsemble::typeDecoder(unsigned long ul0){
    std::vector<unsigned short> vus0;
    for(unsigned i0=0;i0!=maz->n;i0++){
        vus0.push_back(ul0/powers[i0]);
        ul0=ul0%powers[i0];
    }
    return vus0;    
}



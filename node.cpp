// Node functions //
// @file node.cpp
// @author Unai Alro
// @version 25/11/21

#include "node.h"

// Node Class 

/**
 * Constructor I
 */
Node::Node(){}
/**
 * Constructor II: Define key, node's parent and node's frequency.
 * @param uc0 Node's key
 * @param nd0 Node's parent
 * @param u0 Node's frequency (Default u0=1)
 */
Node::Node(unsigned char uc0, Node* nd0,unsigned u0){
    key=uc0;
    pre=nd0;    
    freq=u0;
}
/**
 * Destructor
 */
Node::~Node(){}

/** 
 * Add a child with a given frequency to a node 
 * @param uc0 Child's key
 * @param u0 Frequency (Default u0=1)
 * @return Pointer to child
 */
Node* Node::add(unsigned char uc0,unsigned u0){
    for(unsigned i0=0;i0!=pos.size();i0++){
        if(pos[i0]->key==uc0){
            pos[i0]->freq+=u0;
            return pos[i0];
        }
    }
    pos.push_back(new Node(uc0,this,u0));
    return pos.back();
}

/**
 * Find a node in a family
 * @param vuc0 Node's ascendant line
 * @return Pointer to node
 */
Node* Node::find(std::vector<unsigned char> vuc0){
    Node* nd0;
    if(vuc0.size()==0){
        nd0=this;
        return nd0;
    }
    for(unsigned i0=0;i0!=pos.size();i0++){
        if(pos[i0]->key==vuc0[0]){
            vuc0.erase(vuc0.begin());
            if(vuc0.size()==0){
                nd0=pos[i0];
                return nd0;
            }else{
                nd0=pos[i0]->find(vuc0);
                return nd0;
            }
        }        
    }
    return nullptr;
}

/**
 * Vector with node's ascendants
 * @param vuc0 Vector to encode ascendants
 */
void Node::pres(std::vector<unsigned char> &vuc0){
    if(pre!=nullptr){
        vuc0.insert(vuc0.begin(),key);
        pre->pres(vuc0);
    }
}

/**
 * Loglikelihood contribution of a given node
 * @param vuc0 Node's ascendant line
 */
float Node::loglikelihood0(std::vector<unsigned char> vuc0){
    float f0=0;
    for(unsigned short i0=0;i0!=pos.size();i0++){
        if(pos[i0]->key==vuc0[0]){
            vuc0.erase(vuc0.begin());
            if(vuc0.size()==0){
                f0=log(1.0*(pos[i0]->freq)/(pos[i0]->pre->freq));
                return f0;
            }else{
                f0=pos[i0]->loglikelihood0(vuc0);
                return f0;
            }
        }
    }
    return f0;
}

/**
 * Loglikelihood of all descendants
 */
float Node::loglikelihood1(){
    float f0=0;
    if(pos.size()!=0){
        for(unsigned short i0=0;i0!=pos.size();i0++){
            f0+=pos[i0]->loglikelihood1();
        }
    }else{
        f0+=freq*log(1.0*freq/pre->freq);
    }
    return f0;
}

/**
 * Print a node and all its descendants
 */
void Node::print(){
    std::vector<unsigned char> vuc0;
    pres(vuc0);
    for(unsigned i0=0;i0!=vuc0.size();i0++){
        printf("%02x",vuc0[i0]);
        std::cout << ' ';
    }    
    std::cout << ' ' << freq << std::endl;
    for(unsigned i0=0;i0!=pos.size();i0++){
        pos[i0]->print();
    }
}

// Eld class

/**
 * Constructor I
 */
Eld::Eld(){
    key=0xff;
    freq=0;
    pre=nullptr;
}
/**
 * Destructor
 */
Eld::~Eld(){}

/**
 * Add a node
 * @param nd0 Pointer to node
 */
void Eld::add(Node* nd0){
    std::vector<unsigned char> vuc0;
    if(nd0->pos.size()!=0){
        for(unsigned i0=0;i0!=nd0->pos.size();i0++){
            add(nd0->pos[i0]);
        }        
    }else{
        vuc0.clear();
        nd0->pres(vuc0);
        add(vuc0,nd0->freq);
    }
}

/**
 * Add an ascendant line
 * @param vuc0 Ascendant line
 * @param u0 Frequency (Default u0=1)
 */
void Eld::add(std::vector<unsigned char> vuc0,unsigned u0){
    Node* nd0=this;
    freq+=u0;
    for(unsigned i0=0;i0!=vuc0.size();i0++){
        nd0=nd0->add(vuc0[i0],u0);
    }
}

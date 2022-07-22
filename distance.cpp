// Distance functions //
// @file distance.cpp
// @author Unai Alro
// @version 06/12/21

#include "distance.h"

/**
 * Compute statistical distance between two probability vectors
 * @param vf0 First vector
 * @param vf1 Second vector
 */
float distance(std::vector<float> vf0, std::vector<float> vf1){
    float f0=0;
    float f1;
    for(unsigned i0=0;i0!=vf0.size();i0++){
        f1=(vf0[i0]>vf1[i0])?vf1[i0]:vf0[i0];
        f0+=f1;        
    }    
    return 1-f0;
}

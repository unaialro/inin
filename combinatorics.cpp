// Combinatorics functions //
// @file combinatorics.cpp
// @author Unai Alro
// @version 2/12/21

#include "combinatorics.h"

/**
 * Compute factorial function of a number
 * @param u0 the number
 */
unsigned long factorial(unsigned u0){
    return (u0==1||u0==0)?1:factorial(u0-1)*u0;
}

/**
 * Compute combinatorial function
 * @param u0 number on top
 * @param u1 number on bottom
 */
unsigned long long combinatorial(unsigned u0,unsigned u1){
    unsigned long long ull0=1;
    for(unsigned i0=0;i0!=u1;i0++){
        ull0*=(u0-i0);
    }
    return ull0/factorial(u1);
}

/**
 * Combinatoric iterator
 * @param vus0 state of the iterator
 * @param us0 number of items to combine
 */
void nextComb(std::vector<unsigned short> &vus0,unsigned short us0){
    unsigned short us1=vus0.size()-1;
    while(1){
        vus0[us1]++;
        if(vus0[us1]!=us0-vus0.size()+1+us1){
            break;
        }
        us1--;
    }
    for(unsigned short i0=us1+1;i0!=vus0.size();i0++){
        vus0[i0]=vus0[i0-1]+1;
    }
}
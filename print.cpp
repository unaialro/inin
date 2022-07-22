// Print functions //
// @file print.cpp
// @author Unai Alro
// @version 25/11/21

#include "print.h"

/**
 * Print boolean
 */
void print(bool b0){
    std::cout << b0 << std::endl;
}
/**
 * Print byte
 */
void print(unsigned char uc0){
    printf("%02x",uc0);
    std::cout << std::endl;
}
/**
 * Print char
 */
void print(char c0){
    std::cout << c0 << std::endl;
}
/**
 * Print unsigned short 
 */
void print(unsigned short us0){
    std::cout << us0 << std::endl;
}
/**
 * Print unsigned 
 */
void print(unsigned u0){
    std::cout << u0 << std::endl;
}
/**
 * Print unsigned long 
 */
void print(unsigned long ul0){
    std::cout << ul0 << std::endl;
}
/**
 * Print unsigned long long
 */
void print(unsigned long long ull0){
    std::cout << ull0 << std::endl;
}
/**
 * Print float
 */
void print(float f0){
    std::cout << f0 << std::endl;
}
/**
 * Print vector of bytes
 */
void print(std::vector <unsigned char> vuc0){
    for(unsigned i0=0;i0!=vuc0.size();i0++){
        printf("%02x",vuc0[i0]);
        std::cout << ' ';
    }
    std::cout << std::endl;
}
/**
 * Print vector of chars
 */
void print(std::vector <char> vc0){
    for(unsigned i0=0;i0!=vc0.size();i0++){
        std::cout << vc0[i0];
    }
    std::cout << std::endl;
}
/**
 * Print vector of unsigned shorts
 */
void print(std::vector <unsigned short> vus0){
    for(unsigned i0=0;i0!=vus0.size();i0++){
        std::cout << vus0[i0] << ' ';
    }
    std::cout << std::endl;
}
/**
 * Print vector of unsigneds
 */
void print(std::vector <unsigned> vu0){
    for(unsigned i0=0;i0!=vu0.size();i0++){
        std::cout << vu0[i0] << ' ';
    }
    std::cout << std::endl;
}
/**
 * Print vector of unsigned longs
 */
void print(std::vector <unsigned long> vul0){
    for(unsigned i0=0;i0!=vul0.size();i0++){
        std::cout << vul0[i0] << ' ';
    }
    std::cout << std::endl;
}
/**
 * Print vector of floats
 */
void print(std::vector <float> vf0){
    for(unsigned i0=0;i0!=vf0.size();i0++){
        std::cout << vf0[i0] << ' ';
    }
    std::cout << std::endl;
}
/**
 * Print vector of unsigned floats rounded to 0.01
 */
void print(std::vector <float> vf0,bool b0){
    if(!b0){
        print(vf0);
        return;
    }
    for(unsigned i0=0;i0!=vf0.size();i0++){
        std::cout << round(100*vf0[i0])/100 << ' ';
    }
    std::cout << std::endl;
}
/**
 * Print vector of vectors of bytes
 */
void print(std::vector<std::vector<unsigned char>> vvuc0){
    for(unsigned i0=0;i0!=vvuc0.size();i0++){
        for(unsigned i1=0;i1!=vvuc0[i0].size();i1++){
            printf("%02x",vvuc0[i0][i1]);
            std::cout << ' ';
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}
/**
 * Print vector of vectors of chars
 */
void print(std::vector<std::vector<char>> vvc0){
    for(unsigned i0=0;i0!=vvc0.size();i0++){
        for(unsigned i1=0;i1!=vvc0[i0].size();i1++){
            std::cout << vvc0[i0][i1];
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}
/**
 * Print vector of vectors of floats
 */
void print(std::vector<std::vector<float>> vvf0){
    std::cout << '\n';
    for(unsigned i0=0;i0!=vvf0.size();i0++){
        for(unsigned i1=0;i1!=vvf0[i0].size();i1++){
            std::cout << vvf0[i0][i1] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}
/**
 * Print vector of vectors of floats rounded to 0.01
 */
void print(std::vector<std::vector<float>> vvf0,bool b0){
    if(!b0){
        print(vvf0);
        return;
    }

    std::cout << '\n';
    for(unsigned i0=0;i0!=vvf0.size();i0++){
        for(unsigned i1=0;i1!=vvf0[i0].size();i1++){
            std::cout << round(100*vvf0[i0][i1])/100 << ' ';
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

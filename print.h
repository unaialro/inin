// Print header //
// @file print.h
// @author Unai Alro
// @version 25/11/21

#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <vector>
#include <cmath>


void print(bool b0);
void print(unsigned char uc0);
void print(char c0);
void print(unsigned short us0);
void print(unsigned u0);
void print(unsigned long ul0);
void print(unsigned long long ull0);
void print(float f0);

void print(std::vector<char> vc0);
void print(std::vector<unsigned char> vuc0);
void print(std::vector<unsigned short> vus0);
void print(std::vector<unsigned> vu0);
void print(std::vector<unsigned long> vul0);
void print(std::vector<float> vf0);
void print(std::vector<float> vf0,bool b0);

void print(std::vector<std::vector<unsigned char>> vvuc0);
void print(std::vector<std::vector<char>> vvc0);
void print(std::vector<std::vector<float>> vvf0);
void print(std::vector<std::vector<float>> vvf0,bool b0);


#endif

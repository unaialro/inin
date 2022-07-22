// Node headers //
// @file node.h
// @author Unai Alro
// @version 25/11/21

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <cmath>

class Node{
    public:
        unsigned char key; // Node's key
        unsigned freq; // Node's frequency
        Node* pre; // Node's parent
        std::vector<Node*> pos; // Node's childs

        Node();
        Node(unsigned char uc0, Node* nd0,unsigned u0=1);
        ~Node();

        Node* add(unsigned char uc0,unsigned u0=1);
        Node* find(std::vector<unsigned char> vuc0);
        void pres(std::vector<unsigned char> &vuc0);

        float loglikelihood0(std::vector<unsigned char> vuc0);
        float loglikelihood1();

        void print();
};

class Eld: public Node{
    public:
        Eld();
        ~Eld();

        void add(Node* nd0);
        void add(std::vector<unsigned char> vuc0,unsigned u0=1);
};

#endif
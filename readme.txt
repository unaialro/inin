This file contains relevant information of the code for the paper "Inference of time-ordered multibody interactions".

We can clasify the files in different groups. 

Group 0:
    We use these files to link and obtain compiled executable files.
    -mk0.mk: Makefile 
    -h0.h: Main header file. It contains the class headers as well as the main path (you should change this one to match your own).

Group 1:
    The following files contain the backbone of the protocol. 
    We use them to define classes and methods.
    In all of them we have a *.h file for the class definitions and the method declarations and a *.cpp file for the definition of the methods. 
    - alphabet.cpp/alphabet.h: 
        An alphabet is the set of all possible states of a node.
        A metalphabet is a collection of alphabets.
    - interaction.cpp/interaction.h:
        An interaction is a model to predict the time evolution of a system as a function of a certain group of variables defined by the interaction type q
        An interaction ensemble is a collection of interactions and coefficients that are equivalent to a time-ordered multibody Markov Process.
    - model.cpp/model.h:
        A model refers to the time-ordered multibody Markov Process.
    - multimodel.cpp/multimodel.h:
        A multimodel refers to the ordered collection of Markov Processes up to a given order.
    - node.cpp/node.h:
        These nodes are not to be confused with the nodes presented in the paper. 
        These are nodes of the probability tree introduced to measure the statistics of sequences. 
        The Eld class accounts for the root node.
    - sequence.cpp/sequence.h
        

Group 2:
    These contain auxiliary files. 
    They define mathematical functions necessary to implement our protocol, but they are not included in the protocol itself.
    - combinatorics.cpp/combinatorics.h
        Factorial function, Combinatorial function and a combinatorial iterator.
    - distance.cpp/distance.h
        Definition of statistical distance
    - print.cpp/print.h
        Functions to output different types of variables.
    - t0.cpp
        An empty file to test things. 
    
Group 3:
    These files were used to obtain the results of the paper.
    We have a *.cpp file for the code in c++ and a .py file to obtain the figure in python.
    - 0.cpp/0.py
        First experiment in the paper and first experiment in the supplemental material.
    - 1.cpp
        Second experiment in the paper.
    - 2.cpp/2.py
        Second experiment in the supplemental material.
    - 3.cpp/3.py
        Traffic jam analysis.
    - 4.cpp/4.py
        The Well Tempered Klavier analysis.


All class members and class methods contain a brief explanation of what they are/do.

If you have any questions please write me an email: unaialvarezr@gmail.com




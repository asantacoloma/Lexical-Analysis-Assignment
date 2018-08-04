//
//  pa3.h
//  project3prog2
//
//  Created by Alejandro Santacoloma on 4/10/17.
//  Copyright © 2017 Alejandro Santacoloma. All rights reserved.
//

#ifndef pa3_h
#define pa3_h
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;


void putifunique(string word, vector<string> &veclist);

void printvec(vector<string> veclist);

void openparenthcheck(string &codeword, int &openparenth);

void closedparenthcheck(string &codeword, int &closedparenth);

void incrementercheck(string &codeword, vector<string> &FOUNDOPERATORS);

void constantscheck(string codeword, vector<string> &FOUNDCONSTANTS);

void identifiercheck(string codeword, vector<string> &FOUNDIDENTIFIERS);

void delimitercheck(string &codeword, vector<string> &FOUNDDELIMITERS);

void operatorcheck(string &codeword, vector<string> &FOUNDOPERATORS, vector<string> &FOUNDIDENTIFIERS,vector<string> &FOUNDCONSTANTS);


#endif /* pa3_h */

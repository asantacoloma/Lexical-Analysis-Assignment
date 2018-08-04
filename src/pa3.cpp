//
//  pa3.cpp
//  pa3
//
//  Created by Alejandro Santacoloma on 4/5/17.
//  Copyright © 2017 Alejandro Santacoloma. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include "pa3.h"

//Program to go through a text file and find depth of nest for loops, syntax errors, identifiers, keywords, and constants of a "code" file


using namespace std;

void putifunique(string word, vector<string> &veclist)
{
    //method to place strings into a selected vector so it can be printed at end of main program
    bool isunique = true;
    for(int i = 0; i < veclist.size(); i++)
    {
        if(!word.compare(veclist[i]))
        {
            isunique = false;
        }
    }
    if(isunique == true)//if the word being placed is unique for the vector then it is placed in the vector
    {
        veclist.push_back(word);
    }
}

void printvec(vector<string> veclist)
{
    //method to print all strings stored in vector
    for(int i = 0; i < veclist.size(); i++)
    {
        cout<<veclist[i]<<" ";
    }
    cout<<"\n";
}

void openparenthcheck(string &codeword, int &openparenth)
{
    //check for open parenthesis
    //for loop to check character by character of string
    for(int i = 0; i < codeword.length(); i++)
    {
        if(codeword.substr(i,1).compare("(") == 0)
        {
            openparenth++;
            //cout<<codeword<<"\n";
            codeword = codeword.erase(i,0);
            // delete "(" from word so word can be later on checked to see if it is a identifier or constant without delimiters interfering with check
        }
    }
}

void closedparenthcheck(string &codeword, int &closedparenth)
{
    //check for closed parenthesis
    for(int i = 0; i < codeword.length(); i++)
    {
        if(codeword.substr(i,1).compare(")") == 0)
        {
            closedparenth++;
            codeword = codeword.erase(i,0);
            // delete ")" from word so word can be later on checked to see if it is a identifier or constant without delimiters interfering with check
            continue;
        }
    }
}

void incrementercheck(string &codeword, vector<string> &FOUNDOPERATORS)
{
    //method to find if two character operators aka incremeters or decrementers ++, --
    for(int i = 0; i < codeword.length()-1; i++)
    {
        if (codeword.substr(i,2).compare("++") == 0 )
        {
            putifunique(codeword.substr(i,2),FOUNDOPERATORS);
        }
        else if(codeword.substr(i,2).compare("--") == 0 )
        {
            putifunique(codeword.substr(i,2),FOUNDOPERATORS);
        }
    }
}


void constantscheck(string codeword, vector<string> &FOUNDCONSTANTS)
{
    //method to check if word is actually a constant
    //goes character by character until end of word is reached,
    //if any of the chars are not a digit then bool will be changed to false
    bool isconstant = true;
    for(int i = 0; i < codeword.size();i++)
    {
        if (isdigit(codeword.at(i)) == 0)
        {
            isconstant = false;
        }
    }
    if(isconstant == true)
    {
        putifunique(codeword, FOUNDCONSTANTS);
    }
}

void identifiercheck(string codeword, vector<string> &FOUNDIDENTIFIERS)
{
    //check if word is all lowercase and therefore an identifier
    bool iswordlower = true;
    for(int i = 0; i < codeword.length(); i++)
    {
        if(islower(codeword.at(i)) == false)
        {
            iswordlower = false;
            break;
        }
    }
    if(iswordlower == true)
    {
        //uses putifunique method to place codeword into FOUNDIDENTIFIERS vector if it is not already there
        putifunique(codeword, FOUNDIDENTIFIERS);
    }
    
}


void delimitercheck(string &codeword, vector<string> &FOUNDDELIMITERS)
{
    //check for delimiters
    
    //check to see if at end of word there is a ","
    if(codeword.substr(codeword.size()-1).compare(",") == 0)
    {

        putifunique(codeword.substr(codeword.size()-1),FOUNDDELIMITERS);
        codeword = codeword.substr(0,codeword.size()-1);
    }
    //check to see if at end of word there is a ";"
    else if(codeword.substr(codeword.size()-1).compare(";") == 0)
    {
        putifunique(codeword.substr(codeword.size()-1),FOUNDDELIMITERS);
        codeword = codeword.substr(0,codeword.size()-1);
    }
}

void operatorcheck(string &codeword, vector<string> &FOUNDOPERATORS, vector<string> &FOUNDIDENTIFIERS,vector<string> &FOUNDCONSTANTS)
{
    char OPERATORS[4] = {'+','-', '*','='}; //char array for operators
    
    //two for loops to iterate character by character of word, if the character
    //program is searching for
    
    for(int j = 0 ; j < 4; j++)
    {
        
        //if statement to check first char of word
        if(codeword.length()==1)
        {
            if (codeword.at(0) == OPERATORS[j])
            {
                
                putifunique(codeword.substr(0),FOUNDOPERATORS);
            }
        }
        
        if(codeword.length()>1== true)
        {
        if (codeword.at(0) == OPERATORS[j] && codeword.at(1) != OPERATORS[j])
        {
            
            putifunique(codeword.substr(0),FOUNDOPERATORS);
        }
        }
        
        //For loop to iterate character by character of word, if the character
        //program is searching for
        for(int i = 1; i < codeword.length()-1; i++)
        {
            //if statement to check if identifiers are in word
            if (codeword.at(i) == OPERATORS[j] && codeword.at(i+1) != OPERATORS[j] && codeword.at(i-1) != OPERATORS[j])
            {
                
                string wordcheck1 = codeword.substr(0,i);
                string wordcheck2 = codeword.substr(i+1,codeword.length());
                
                identifiercheck(wordcheck1, FOUNDIDENTIFIERS);
                identifiercheck(wordcheck2, FOUNDIDENTIFIERS);
                
                constantscheck(wordcheck1, FOUNDCONSTANTS);
                constantscheck(wordcheck2, FOUNDCONSTANTS);
                
                putifunique(codeword.substr(i,1),FOUNDOPERATORS);
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    
    //arrays and other variables important for debugger
    
    string KEYWORDS[3] = {"FOR", "BEGIN" ,"END"}; //string array for keywords
    
    vector<string> FOUNDIDENTIFIERS;  //empty string vector to store identifiers found during parsing through text
    
    vector<string>  FOUNDOPERATORS;   //empty string vector to store operators found during parsing through text
    
    vector<string>  FOUNDDELIMITERS;  //empty string vector to store delimiters found during parsing through text
    
    vector<string>  FOUNDCONSTANTS;   //empty string vector to store constants found during parsing through text
    
    vector<string> FOUNDSYNTAXERRORS;  //empty string vector to store syntax errors found during parsing through text
    
    
    stack<int> depthstack;  //stack to keep track of current depth of loop
    int maxdepth = 0;       //variable to keep track of current max depth
    int currdepth = 0;      // variable to keep track of current depth, looks at current size of stack
    
    
    // Variables
    //keyword bools
    bool existFOR   = false;
    bool existBEGIN = false;
    bool existEND   = false;
    
    //stack bools
    bool stackFOR   = false;
    bool stackBEGIN = false;
    bool stackEND   = false;
    
    //Parenthesis counters to help keep track if one is missing
    int openparenth = 0;
    int closedparenth = 0;
    
    cout <<"Please enter the name of the input file:\n";
    
    string filename; //string variable to hold text file name
    
    cin >> filename; //get file name from user
    //filename = "code.txt";
    
    ifstream codefile; //make file object called CodeFile
    
    codefile.open(filename,ios::in); //file is opened and set for input operations
    
    string codeword;//initialize string
    
    if (codefile.is_open() == true)
    {
        while ((codefile >> codeword) ) //while to get next string without whitespace until end of text file is reached
        {
            
            //list of commands
            openparenthcheck(codeword, openparenth);
            
            closedparenthcheck(codeword, closedparenth);
            
            incrementercheck(codeword, FOUNDOPERATORS);
            
            operatorcheck(codeword, FOUNDOPERATORS, FOUNDIDENTIFIERS, FOUNDCONSTANTS);
            
            delimitercheck(codeword, FOUNDDELIMITERS);
            
            identifiercheck(codeword, FOUNDIDENTIFIERS);
            
            constantscheck(codeword, FOUNDCONSTANTS);
            
            //check if word is in all caps
            //Had trouble implementing KEYWORD check as a function, had to keep in main
            bool iswordupper = true;
            for(int i = 0; i < codeword.length(); i++)
            {
                
                if(isupper(codeword.at(i)) == false)
                {
                    iswordupper = false;
                    break;
                }
                
            }
            
            if(iswordupper == true)
            {
                //check if its a keyword
                if(codeword.compare(KEYWORDS[0]) == 0)
                {
                    existFOR = true;
                    stackFOR = true;
                }
                else if (codeword.compare(KEYWORDS[1]) == 0)
                {
                    existBEGIN = true;
                    stackBEGIN = true;
                }
                else if (codeword.compare(KEYWORDS[2]) == 0)
                {
                    existEND = true;
                    stackEND = true;
                }
                else
                {
                    putifunique(codeword, FOUNDSYNTAXERRORS);
                }
            }
            
            
            // if statement for stack, had trouble implementing as a function had to keep in main
            //if statement to initiate psuh
            if (stackFOR == true && stackBEGIN == true)
            {
                depthstack.push(0);
                currdepth++;
                //cout<<"\n currdepth increased to "<<currdepth<<"\n";
                if(currdepth > maxdepth)
                {
                    maxdepth = currdepth;
                }
                stackFOR = false;
                stackBEGIN = false;
            }
            
            //if statement to initiate pop
            if(stackEND == true)
            {
                if (depthstack.empty() == true)//prevents pop of an empty stack
                {
                    //cout<<"error found pop an empty stack// "<<codeword<<"\n";
                    //putifunique("END", FOUNDSYNTAXERRORS);
                    stackEND = false;
                }
                else
                {
                    depthstack.pop();
                    currdepth--;
                    stackEND = false;
                }
            }
        }
        codefile.close();
    }
    else // else statement for if the file could not be opened or found
    {
        cout<<"File not able to be found or opened\n";
    }
    
    
    //Program now checks to see if any words are missing
    
    
    if(existFOR == true && existBEGIN == true && existEND == false)
    {
        //cout<<"existEND == false at end\n";
        putifunique("END", FOUNDSYNTAXERRORS);
    }
    else if(existFOR == false && existBEGIN == true && existEND == true)
    {
        putifunique("FOR", FOUNDSYNTAXERRORS);
    }
    else if(existFOR == true && existBEGIN == false && existEND == true)
    {
        putifunique("BEGIN", FOUNDSYNTAXERRORS);
    }
    
    
    //missing parenthesis check
    if(openparenth>closedparenth)
    {
        putifunique("(", FOUNDSYNTAXERRORS);
    }
    else if(openparenth<closedparenth)
    {
        putifunique(")", FOUNDSYNTAXERRORS);
    }
    //missing keyword check
    if(depthstack.size() > 0)
    {
        putifunique("END", FOUNDSYNTAXERRORS);
        maxdepth--;
    }
    
    //program output
    
    //print deepest loop depth found
    cout<<"The depth of nested loop(s) is "<<maxdepth<<"\n";
    
    //logic for printing keywords found
    cout<<"Keywords: ";
    if(existFOR)
    {
        cout <<"FOR ";
    }
    if(existBEGIN)
    {
        cout <<"BEGIN ";
    }
    if(existEND)
    {
        cout <<"END ";
    }
    cout<<"\n";
    
    //Identifier found print logic
    cout<<"Identifier: ";
    printvec(FOUNDIDENTIFIERS);
    
    //Constant print logic
    cout<<"Constant: ";
    printvec(FOUNDCONSTANTS);
    
    //Operator print logic
    cout<<"Operators: ";
    printvec(FOUNDOPERATORS);
    
    //Delimiter print logic
    cout<<"Delimiter: ";
    printvec(FOUNDDELIMITERS);
    
    //Syntax errors print
    cout<<"Syntax Error(s): ";
    if(FOUNDSYNTAXERRORS.size()==0)
    {
        cout<<"NA\n";
    }
    printvec(FOUNDSYNTAXERRORS);

    return 0;
}

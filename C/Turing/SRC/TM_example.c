#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include "tm.h"

/* From:

 https://stackoverflow.com/questions/10503377/turing-machine-simulator

 Probably C++?
 No tm.h provided?

 Oh well, just for ideas anyway

*/


using namespace std;

tm::tm(char *fn)
{
    current = "";
    readFile(fn);
}

void tm::readFile(char *fn)
{
    char temp;
    string word = "";
    ifstream indata;
    bool blank = false;
    indata.open(fn); //opens the file
    if(!indata) //error message if the file is unable to be opened
    {   
        cout << "Could not open the specified file \"" << fn << "\"" << endl;
        exit(1);
    }
    indata >> temp;
    while (!indata.eof())
    {
        if (temp == 'Q')
        {
            //cout << "Q" << endl;
            indata >> temp;
            indata >> temp; //skip the :
            while (temp != 'A')
            {
                if (temp != ',') word += temp;
                else
                {
                    QQ.push_back(word);
                    word = "";
                }
                indata >> temp;
            }
            QQ.push_back(word);
            word = "";
        }
        else if (temp == 'A')
        {
            //cout << "A" << endl;
            indata >> temp;
            indata >> temp; //skip the :
            while (temp != 'Z')
            {
                if (temp != ',') word += temp;
                else
                {
                    AA.push_back(word);
                    word = "";
                }
                indata >> temp;
            }
            AA.push_back(word);
            word = "";
        }
        else if (temp == 'Z')
        {
            //cout << "Z" << endl;
            indata >> temp;
            indata >> temp; //skip the :
            while (temp != 'T')
            {
                if (temp != ',') word += temp;
                else
                {
                    ZZ.push_back(word);
                    word = "";
                }
                indata >> temp;
            }
            ZZ.push_back(word);
            word = "";
            for (int i = 0; i < (int)ZZ.size(); i++)
                if (ZZ[i].compare(" ") == 0)
                    blank = true;
            if (blank == false) //no blanks were found in the tape alphabet
                ZZ.push_back(" ");
        }
        else if (temp == 'T')
        {
            //cout << "T" << endl;
            indata >> temp;
            indata >> temp; //skip the :
            bool wasComma = false;
            vector<string> row;
            while (temp != 'T' && temp != 'S')
            {
                if (wasComma && temp == ',') //the last one was a comma
                {
                    row.push_back(" ");
                    wasComma = false;
                }
                else if (temp != ',')
                {
                    word += temp;
                    wasComma = false;
                }
                else
                {
                    row.push_back(word);
                    word = "";
                    wasComma = true;
                }
                indata >> temp;
            }
            row.push_back(word);
            TT.push_back(row);
            word = "";
        }
        else if (temp == 'S')
        {
            //cout << "S" << endl;
            indata >> temp;
            indata >> temp; //skip the :
        while (temp != 'F')
            {
                if (temp != ',') word += temp;
                else
                {
                    SS = word;
                    word = "";
                }
                indata >> temp;
            }
            SS = word;
            word = "";
        }
        else if (temp == 'F')
        {
            //cout << "F" << endl;
            indata >> temp;
            indata >> temp; //skip the :
            while (!indata.eof())
            {
                if (temp != ',')
                    word += temp;
                else
                {
                    FF.push_back(word);
                    word = "";
                }
                indata >> temp;
            }
            FF.push_back(word);
            word = "";
        }
    }   
    indata.close();
    readInput();
    runAll();
    return;
}

void tm::readInput()
{
    int num, k;
    cin >> num;

    string temp;
    getline(cin,temp);
    getline(cin,temp);
    for (int i = 0; i < num; i++) //num is the number of rows of input to the machine
{
        vector<string> row;
        string word = "";
        for(k = 0; k < (int)temp.size(); k++)
        {
            if (temp[k] != ',')
                word += temp[k];
            else if ((int)word.size() > 0)
            {
                row.push_back(word);
                word = "";
            }
            if (k == (int)temp.size() -1 && (int)word.size() > 0)
            {
                row.push_back(word);
                word = "";
            }
    }
        if (k > 0)
            input.push_back(row);
        else //if there is an empty row of input to the machine
        {
            vector<string> row;
            row.push_back("e");
            input.push_back(row);
        }
        getline(cin,temp);
    }

    return;
}

void tm::runAll()
{
    checkForAlphabetBlanks();
    checkTransitions();
    checkStart();
    checkFinal();
    checkDeterministic();
    checkAcceptReject();
    checkInput();

    int currentPosition;
    string currentState, currentSymbol;
    bool found, first = true;
    for (int i = 0; i < (int)input.size(); i++) //for each row of the input
    {
        if (first != true)
            cout << endl;
        first = false;
        currentPosition = 0;
        currentState = SS;
        for (int k = 0; k < 1000; k++) //for each character of input, then up to 1000
        {
            if (k == 0) //the first time
            {
                if (0 < (int)input[i].size()) //we are not past the right of the tape
                    currentSymbol = input[i][0];
                else
                    currentSymbol = " ";
                cout << "()" << SS << "(";
                for (int g = 0; g < (int)input[i].size(); g++)
                {
                    cout << input[i][g];
                    if (g != (int)input[i].size() - 1) //it is not the last input
                        cout << ",";
                    else
                        cout << ")" << endl;
                }
            }
            if (currentState.compare(FF[0]) == 0) //check if we are accept
            {
                cout << "ACCEPT" << endl;
                break;
            }
            else if (currentState.compare(FF[1]) == 0) //check if we are reject
            {
                cout << "REJECT" << endl;
                break;
            }
            found = false;
            for (int g = 0; g < (int)TT.size(); g++)
            {
                if (TT[g][0].compare(currentState) == 0 && TT[g][1].compare(currentSymbol) == 0) //same state and symbol as the transition line
                {
                    found = true;
                    currentState = TT[g][2];
                    input[i][currentPosition] = TT[g][3];
                    if (TT[g][4].compare("R") == 0) currentPosition++;
                    else currentPosition--;
                    //check for out of bounds to the left
                    if (currentPosition < 0) currentPosition = 0;
                    cout << "(";
                    for (int t = 0; t < currentPosition; t++)
                    {
                        cout << input[i][t];
                        if (t != currentPosition - 1) cout << ","; //not the last one
                    }
                    cout << ")" << currentState << "(";
                    for (int t = currentPosition; t < (int)input[i].size(); t++)
                    {
                        cout << input[i][t];
                        if (t != (int)input[i].size() - 1) cout << ","; //not the last one
                    }
                    cout << ")" << endl;
                    if (currentPosition < (int)input[i].size()) currentSymbol = input[i][currentPosition]; //not past the right side of the tape
                    else
                    {
                        currentSymbol = " ";
                        input[i].push_back(" ");
                    }
                    break;
                }
            }
            if (found == true) //a transition was found
            {
                if (currentState.compare(FF[0]) == 0) //check if accept
                {
                    cout << "ACCEPT" << endl;
                    break;
                }
                else if (currentState.compare(FF[1]) == 0) //check if reject
                {
                    cout << "REJECT" << endl;
                    break;
                }
            }
            else
            {
                currentPosition++;
                cout << "(";
                for (int t = 0; t < currentPosition; t++)
                {
                    cout << input[i][t];
                    if (t != currentPosition - 1) cout << ","; //not the last one
                }
                cout << ")" << FF[1] << "(";
                for (int t = currentPosition; t < (int)input[i].size(); t++)
                {
                    cout << input[i][t];
                    if (t != (int)input[i].size() - 1) cout << ","; //not the last one
                }
                cout << ")" << endl;
                cout << "REJECT" << endl;
                break;
            }
            if (k == 999)
                cout << "DID NOT HALT" << endl;
        }
    }

    return;
}

void tm::checkForAlphabetBlanks()
{
    for (int i = 0; i < (int)AA.size(); i++)
    {
        if (AA[i].compare(" ") == 0)
        {
            cout << "The alphabet has a blank space." << endl;
            exit(1);
        }
    }
    return;
}

void tm::checkTransitions()
{
    bool state1, state2, character1, character2;

    for (int i = 0; i < (int)TT.size(); i++)
    {
    //check the direction
        if (TT[i][4].compare("R") != 0 && TT[i][4].compare("L") != 0)
        {
            cout << "The only valid directions are R and L." << endl;
            exit(1);
        }
        //check the states
        state1 = false; state2 = false;
        for (int k = 0; k < (int)QQ.size(); k++)
        {
            if (TT[i][0].compare(QQ[k]) == 0) state1 = true;
            if (TT[i][2].compare(QQ[k]) == 0) state2 = true;
        }
        if (state1 == false)
        {
            cout << "The state " << TT[i][0] << " in transition function number " << i << " is not in the list of states." << endl;
            exit(1);
        }
        if (state2 == false)
        {
            cout << "The state " << TT[i][2] << " in transition function number " << i << " is not in the list of states." << endl;
            exit(1);
        }
        //check the characters
        character1 = false; character2 = false;
        for (int k = 0; k < (int)ZZ.size(); k++)
        {
            if (TT[i][1].compare(ZZ[k]) == 0) character1 = true;
            if (TT[i][3].compare(ZZ[k]) == 0) character2 = true;
        }
        if (character1 == false)
        {
            cout << "The character '" << TT[i][1] << "' in transition function number " << i << " is not in the tape alphabet." << endl;
            exit(1);
        }
        if (character2 == false)
        {
            cout << "The character '" << TT[i][3] << "' in transition function number " << i << " is not in the tape alphabet." << endl;
            exit(1);
        }
}
    return;
}

void tm::checkStart()
{
    bool in = false;
    for (int i = 0; i < (int)QQ.size(); i++)
    {
        if (SS.compare(QQ[i]) == 0) in = true;
    }
    if (in == false)
    {
        cout << "The start state " << SS << " is not in the list of states." << endl;
        exit(1);
    }
}

void tm::checkFinal()
{
    if (FF[0].compare(FF[1]) == 0)
    {
        cout << "The accept and reject states cannot be the same." << endl;
        exit(1);
    }
    bool accept = false, reject = false;
    for (int i = 0; i < (int)QQ.size(); i++)
    {
        if (FF[0].compare(QQ[i]) == 0) accept = true;
        if (FF[1].compare(QQ[i]) == 0) reject = true;
        }
        if (accept == false)
        {
        cout << "The accept state " << FF[0] << " is not in the list of states." << endl;
        exit(1);
    }
    if (reject == false)
    {
        cout << "The reject state " << FF[1] << " is not in the list of states." << endl;
        exit(1);
    }
}

void tm::checkDeterministic()
{
    for (int i = 0; i < (int)TT.size(); i++)
        for (int k = i+1; k < (int)TT.size(); k++)
            if (TT[i][0].compare(TT[k][0]) == 0 && TT[i][1].compare(TT[k][1]) == 0)
            {
            cout << "The machine cannot proceed deterministically, transitions " << i << " and " << k << " are the same." << endl;
            exit(1);
        }
}

void tm::checkAcceptReject()
{
    for (int i = 0; i < (int)TT.size(); i++)
    {
        if (TT[i][0].compare(FF[0]) == 0 || TT[i][0].compare(FF[1]) == 0)
        {
            cout << "The machine cannot transitions from the accept or reject states." << endl;
        }
    }
}

void tm::checkInput()
{
    bool exists;
    for (int i = 0; i < (int)input.size(); i++)
    {
        for (int k = 0; k < (int)input[i].size(); k++)
        {
            exists = false;
            for (int g = 0; g < (int)AA.size(); g++)
            {
                if (input[i][k].compare(AA[g]) == 0) exists = true;
            }
            if (exists == false)
            {
                if (input[i][0].compare("e") != 0) //it is not 'e'
                {
                    cout << "The input character " << input[i][k] << " is not in the input alphabet." << endl;
                    exit(1);
                }
            }
        }
    }
}

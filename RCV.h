#pragma once
#include<string>
#include<unordered_set>
#include<vector>
#include<valarray>
#include<iostream>
#include<algorithm>
using namespace std;

struct Candidate
{
    string name;
    vector <int> nthPlaceVotes;
};

class RCV
{
public:

    

    int addCandidate(string& name);
    void addBallot(vector<string>& b);
    int addBallotsFromCSV(string& CSVinput);

    vector <pair<string, int>> getResults();

    void computeMajority();
    void computeBorda();
    void computePlurality();
    void computePluralityWithRunoff();
    
    void printResults();
    void printCandidates();
    void printCandidateData();

private:

    vector <pair<int, vector<string>>> ballots;
    vector <Candidate*> candidates;
    vector <pair<string, int>> results;
    unordered_set <string> candidates_HT;
    int numBallots = 0;
    int numCandidates = 0;

    int getCandidate(string& candName);
    static bool bordaCompare(pair <string, int> x, pair <string, int> y);

};
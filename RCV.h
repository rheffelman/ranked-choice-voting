#pragma once
#include<string>
#include<unordered_set>
#include<vector>
#include<valarray>
#include<iostream>
#include<map>
#include<algorithm>
using namespace std;

struct Candidate
{
    Candidate(string& n) { name = n; }
    Candidate(Candidate &n) { name = n.name; }
    string name;
    vector <int> nthPlaceVotes;
};

class RCV
{
public:

    int addCandidate(string& name);
    void addBallot(vector<string>& b);
    int addBallotsFromCSV(string& CSVinput);

    void computeMajority();
    void computeBorda();
    void computePlurality();
    void computePluralityWithRunoff();
    void computeIRV();
    void computeCopeland();
    void computeDowdall();
    void computeMinimax();
    void computeBaldwin();
    void computeCopelandBorda();
    void UltimateVotingSystem();

    vector <string> getCandidateNames();
    int getBallotCount();
    int getCandidateCount();
    vector <pair<string, double>> getResults();
    string getCondorcetWinner();

    void printResults();
    void printCandidates();
    void printCandidateData();

private:

    vector <vector<string>> ballots;
    vector <Candidate*> candidates;
    vector <pair<string, double>> results;

    vector <pair<int, vector<string>>> eliminatedBallots;
    unordered_set <string> candidates_HT;
    unordered_set <string> eliminated_HT;
    int numBallots = 0;
    int numCandidates = 0;

    int getCandidate(string& candName);
    static bool compare(pair <string, double> x, pair <string, double> y);
    void eliminateCandidate(Candidate* c);
    string cleanse(const string& word);
    pair<int, int> prefers(Candidate* a, Candidate* b); // a helper for Minimax and CopelandBorda

    void computeIRVHelper(vector<Candidate*>& remainingCandidates, vector<vector<string>>& remainingBallots, int rank);
    void computeBaldwinHelper(vector<Candidate*>& remainingCandidates, vector<vector<string>>& remainingBallots, int rank);

};
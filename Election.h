#pragma once
#include<string>
#include<unordered_set>
#include<vector>
#include<valarray>
#include<iostream>
using namespace std;

struct Candidate
{
    int candidateID;
    string name;
    valarray <int> nthPlaceVotes;
};

struct Ballot
{
    vector <string> v;
};

class Election
{
public:

    void addCandidate(string& name)
    {
        Candidate * temp = new Candidate;
        temp->name = name;
        temp->candidateID = numCandidates;
        numCandidates++;
        c.push_back(temp);
        cht.insert(temp);
    }

    void addBallot(vector<string>& v)
    {
        Ballot * temp = new Ballot;
        temp->v = v;
        b.push_back(temp);
    }

    unordered_set <Candidate*> cht;
    vector <Candidate*> c;
    vector <Ballot*> b;
    vector <int> electionResults;
    int numCandidates = 1;

    void computeBordaCount()
    {
        for (int i = 0; i < c.size(); i++)
        {
            c[i]->nthPlaceVotes.resize(c.size(), 0);
        }
        if (checkData())
        {

            for (int i = 0; i < b.size(); i++)
            {
                for (int j = 0; j < b[i]->v.size(); j++)
                {
                    incrementCandidate(b[i]->v[j], j);
                }
            }
            electionResults.resize(c.size(), 0);

            for (int i = 0; i < c.size(); i++)
            {
                for (int j = 0; j < c[i]->nthPlaceVotes.size(); j++)
                {
                    if (numCandidates - (j + 1) > 0)
                    {
                        electionResults[i] += c[i]->nthPlaceVotes[j] * numCandidates - (j + 1);
                    }
                }
            }

            for (int i = 0; i < electionResults.size(); i++)
            {
                printf("%d\n", electionResults[i]);
            }
        }
        else
        {
            printf("bad data!\n");
        }
    }

    bool checkData()
    {
        for (int i = 0; i < b.size(); i++)
        {
            if (b[i]->v.size() > c.size())
            {
                printf("One of your ballots votes for more candidates than the amount of candidates entered.\n");
                return false;
            }
        }
        return true;

    }
    
    void incrementCandidate(string& candidateName, int nthPlace)
    {
        for (int i = 0; i < c.size(); i++)
        {
            if (c[i]->name == candidateName)
            {
                c[i]->nthPlaceVotes[nthPlace]++;
                exit;
            }
        }
    }
    
    ~Election()
    {
        for (int i = 0; i < b.size(); i++)
        {
            delete b[i];
        }
    }
};
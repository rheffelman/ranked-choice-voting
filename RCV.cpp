#include"RCV.h"

int RCV::addCandidate(string& name)
{
    if (getCandidate(name) != -1)
    {
        printf("Candidate already exists!\n");
        return -1;
    }

    Candidate * temp = new Candidate;
    vector <int> npv;
    npv.resize(candidates.size(), 0);
    temp->name = name;
    temp->nthPlaceVotes = npv;
    candidates.push_back(temp);
    candidates_HT.insert(temp->name);
    numCandidates++;

    for (int i = 0; i < candidates.size(); i++)
    {
        candidates[i]->nthPlaceVotes.push_back(0);
    }
    return 0;
}
//--
void RCV::addBallot(vector<string>& b)
{   
    if (b.size())
    {   
        int ballotID = numBallots;
        pair <int, vector<string>> ballot;
        ballot.first = ballotID;
        ballot.second = b;
        ballots.push_back(ballot);
        numBallots++;

        int x = -1;
        for (int i = 0; i < b.size(); i++)
        {
            x = getCandidate(b[i]);
            if (x != -1)
            {
                candidates[getCandidate(b[i])]->nthPlaceVotes[i]++;
            }
        }
    }
    else
    {
        printf("Ballots must contain atleast 1 vote.\n");
    }
}
//--
int RCV::addBallotsFromCSV(string& CSVinput)
{
    if (CSVinput.size() < 2)
    {
        printf("Input too small.\n");
        return -1;
    }

    vector <string> tempBallot;
    string tempCandidateName = "";

    for (int i = 0; i < CSVinput.size(); i++)
    {
        if (CSVinput[i] == ' ')
        {
            continue;
        }
        else if (CSVinput[i] == '\n')
        {
            if (!candidates_HT.count(tempCandidateName))
            {
                addCandidate(tempCandidateName);
            }
            tempBallot.push_back(tempCandidateName);
            addBallot(tempBallot);
            tempBallot.clear();
            tempCandidateName = "";
        }
        else if (CSVinput[i] == ',')
        {
            if (!candidates_HT.count(tempCandidateName))
            {
                addCandidate(tempCandidateName);
            }
            tempBallot.push_back(tempCandidateName);
            tempCandidateName = "";
        }
        else
        {
            tempCandidateName += CSVinput[i];
        }
    }
    return 0;
}
//--
vector <pair<string, int>> RCV::getResults()
{
    return results;
}
//--
void RCV::computeMajority()
{
    if (!candidates.size())
    {
        printf("Can't do a vote with no candidates!\n");
    }

    int majorityCutoff = (ballots.size() / 2);
    results.resize(candidates.size());

    for (int i = 0; i < candidates.size(); i++)
    {
        pair <string, int> candidateResult;
        candidateResult.first = candidates[i]->name;

        if (candidates[i]->nthPlaceVotes[0] > majorityCutoff)
        {
            candidateResult.second = 1;
        }
        else
        {
            candidateResult.second = 0;
        }
        results[i] = candidateResult;
    }
    
    sort(results.begin(), results.end(), (*bordaCompare));
}
//--
void RCV::computeBorda()
{
    if (!candidates.size())
    {
        printf("Can't do a vote with no candidates!\n");
    }

    results.resize(candidates.size());

    for (int i = 0; i < candidates.size(); i++)
    {
        int x = candidates.size() - 1;
        int count = 0;
        for (int j = 0; j < candidates[i]->nthPlaceVotes.size() - 1; j++)
        {
            count += candidates[i]->nthPlaceVotes[j] * x;
            x--;
        }
        pair <string, int> candidateResult;
        candidateResult.first = candidates[i]->name;
        candidateResult.second = count;
        results[i] = candidateResult;
    }

    sort(results.begin(), results.end(), (*bordaCompare));
}
//--
void RCV::computePlurality()
{
    results.resize(candidates.size());

    for (int i = 0; i < candidates.size(); i++)
    {
        pair <string, int> candidateResult;
        candidateResult.first = candidates[i]->name;
        candidateResult.second = candidates[i]->nthPlaceVotes[0];
        results[i] = candidateResult;
    }

    sort(results.begin(), results.end(), (*bordaCompare));
}
//--
void RCV::computePluralityWithRunoff()
{
    if (candidates.size() < 2)
    {
        printf("Too few candidates to do a vote.\n");
    }
    
    results.resize(candidates.size());
    vector <pair<string, int>> pluralityOrder;
    
    for (int i = 0; i < candidates.size(); i++)
    {
        pair <string, int> candidateResult;
        candidateResult.first = candidates[i]->name;
        candidateResult.second = candidates[i]->nthPlaceVotes[0];
        pluralityOrder.push_back(candidateResult);
    }
    
    sort(pluralityOrder.begin(), pluralityOrder.end(), (*bordaCompare));
    pair <string, int> candidate1 = pluralityOrder[0];
    pair <string, int> candidate2 = pluralityOrder[1];
    int ar[2] = {0, 0};

    for (int i = 0; i < ballots.size(); i++)
    {
        for (int j = 0; j < ballots[i].second.size(); j++)
        {
            if (ballots[i].second[j] == candidate1.first)
            {
                ar[0]++;
                break;
            }
            else if (ballots[i].second[j] == candidate2.first)
            {
                ar[1]++;
                break;
            }
        }
    }
    
    pair <string, int> candidateResult;
    candidateResult.first = candidate1.first;
    candidateResult.second = ar[0];
    results[0] = candidateResult;

    pair <string, int> candidateResult2;
    candidateResult2.first = candidate2.first;
    candidateResult2.second = ar[1];
    results[1] = candidateResult2;

    for (int i = 2; i < candidates.size(); i++)
    {
        results[i] = pluralityOrder[i];
        results[i].second = 0;
    }

    sort(results.begin(), results.end(), (*bordaCompare));
}
//--
void RCV::printResults()
{
    bool noWinners = true;
    for (int i = 0; i < results.size(); i++)
    {
        if (results[i].second != 0)
        {
            noWinners = false;
        }
    }

    if (noWinners)
    {
        printf("NO CANDIDATE won the vote.\n");
    }
    else
    {
        printf("%s won the vote!\n", results[0].first.c_str());
    }

    for (int i = 0; i < results.size(); i++)
    {
        printf("#%d) %s, %d\n", i + 1, results[i].first.c_str(), results[i].second);
    }
}
//--
void RCV::printCandidates()
{
    for (int i = 0; i < candidates.size(); i++)
    {
        printf("%s\n", candidates[i]->name);
    }
}
//--
void RCV::printCandidateData()
{
    for (int i = 0; i < candidates.size(); i++)
    {
        printf("%s, ", candidates[i]->name.c_str());
        for (int j = 0; j < candidates[i]->nthPlaceVotes.size(); j++)
        {
            if (j == candidates[i]->nthPlaceVotes.size() - 1)
            {
                printf("%d\n", candidates[i]->nthPlaceVotes[j]);
            }
            else
            {
                printf("%d, ", candidates[i]->nthPlaceVotes[j]);
            }
        }
    }
    printf("\n");
}
//--
int RCV::getCandidate(string& candName)
{
    for (int i = 0; i < candidates.size(); i++)
    {
        if (candidates[i]->name == candName)
        {
            return i;
        }
    }
    return -1;
}
//--
bool RCV::bordaCompare(pair <string, int> x, pair<string, int> y)
{
    return x.second > y.second;
}
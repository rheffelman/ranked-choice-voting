#include"RCV.h"

int RCV::addCandidate(string& name)
{
    if (getCandidate(name) != -1)
    {
        printf("Candidate already exists!\n");
        return -1;
    }

    Candidate* temp = new Candidate(name);
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
        for (int i = 0; i < b.size(); i++)
        {
			b[i] = cleanse(b[i]);
		}
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
            else
            {
                addCandidate(b[i]);
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
        if (CSVinput[i] == '\n' or CSVinput[i] == ',')
		{
            if (!candidates_HT.count(tempCandidateName))
			{
				addCandidate(tempCandidateName);
			}
		}
        if (CSVinput[i] == '\n')
        {
            tempBallot.push_back(tempCandidateName);
            addBallot(tempBallot);
            tempBallot.clear();
            tempCandidateName = "";
        }
        if (CSVinput[i] == ',')
        {
            tempBallot.push_back(tempCandidateName);
            tempCandidateName = "";
        }
        if (CSVinput[i] != ',' and CSVinput[i] != '\n' and CSVinput[i] != ' ')
        {
            tempCandidateName += CSVinput[i];
        }
            
    }
    return 0;
}
//--
vector <string> RCV::getCandidateNames()
{
    vector <string> names;
    for (int i = 0; i < candidates.size(); i++)
    {
        names.push_back(candidates[i]->name);
    }
    return names;
}
//--
int RCV::getBallotCount()
{
    return ballots.size();
}
//--
int RCV::getCandidateCount()
{
    return candidates.size();
}
//--
vector <pair<string, double>> RCV::getResults()
{
    return results; 
}
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

    sort(results.begin(), results.end(), (*compare));
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

    sort(results.begin(), results.end(), (*compare));
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

    sort(results.begin(), results.end(), (*compare));
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

    sort(pluralityOrder.begin(), pluralityOrder.end(), (*compare));
    pair <string, int> candidate1 = pluralityOrder[0];
    pair <string, int> candidate2 = pluralityOrder[1];
    int ar[2] = { 0, 0 };

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

    pair <string, double> candidateResult;
    candidateResult.first = candidate1.first;
    candidateResult.second = ar[0];
    results[0] = candidateResult;

    pair <string, double> candidateResult2;
    candidateResult2.first = candidate2.first;
    candidateResult2.second = ar[1];
    results[1] = candidateResult2;

    for (int i = 2; i < candidates.size(); i++)
    {
        results[i] = pluralityOrder[i];
        results[i].second = 0;
    }

    sort(results.begin(), results.end(), (*compare));
}
//--
void RCV::computeIRV()
{
    results.clear(); 
    computeIRVHelper(candidates, ballots, 1);
    sort(results.begin(), results.end(), [](const pair<string, double>& a, const pair<string, double>& b)
    {
        return a.second > b.second;
    });
}
//--
void RCV::computeIRVHelper(vector<Candidate*>& remainingCandidates, vector<pair<int, vector<string>>>& remainingBallots, int rank)
{
    if (remainingCandidates.size() == 1)
    {
        results.push_back({ remainingCandidates[0]->name, static_cast<double>(rank) });
        return;
    }

    map<string, int> voteCount;
    for (auto& ballot : remainingBallots)
    {
        if (!ballot.second.empty())
        {
            string firstChoice = ballot.second[0];
            voteCount[firstChoice]++;
        }
    }

    string candidateToEliminate;
    int fewestVotes = INT_MAX;
    for (auto& candidate : remainingCandidates)
    {
        if (voteCount[candidate->name] < fewestVotes)
        {
            fewestVotes = voteCount[candidate->name];
            candidateToEliminate = candidate->name;
        }
    }

    vector<Candidate*> nextCandidates;
    for (auto& candidate : remainingCandidates)
    {
        if (candidate->name != candidateToEliminate)
        {
            nextCandidates.push_back(candidate);
        }
    }

    vector<pair<int, vector<string>>> nextBallots = remainingBallots;
    for (auto& ballot : nextBallots)
    {
        ballot.second.erase(remove(ballot.second.begin(), ballot.second.end(), candidateToEliminate), ballot.second.end());
    }

    computeIRVHelper(nextCandidates, nextBallots, rank + 1);
    results.push_back({ candidateToEliminate, static_cast<double>(rank) });
}
//--
void RCV::computeCopeland()
{
    if (candidates.size() < 2)
    {
        printf("Too few candidates to do a vote.\n");
        return;
    }

    map<string, double> copelandScores;

    for (auto& candidate : candidates)
    {
        copelandScores[candidate->name] = 0;
    }

    for (int i = 0; i < candidates.size(); i++)
    {
        for (int j = i + 1; j < candidates.size(); j++)
        {
            int winsI = 0, winsJ = 0;

            for (auto& ballot : ballots)
            {
                auto posI = find(ballot.second.begin(), ballot.second.end(), candidates[i]->name);
                auto posJ = find(ballot.second.begin(), ballot.second.end(), candidates[j]->name);
                if (posI < posJ)
                {
                    winsI++;
                }
                else if (posJ < posI)
                {
                    winsJ++;
                }
            }

            if (winsI > winsJ)
            {
                copelandScores[candidates[i]->name]++;
            }
            else if (winsJ > winsI)
            {
                copelandScores[candidates[j]->name]++;
            }
        }
    }

    results.clear();
    for (auto& score : copelandScores)
    {
        results.push_back(make_pair(score.first, score.second));
    }

    sort(results.begin(), results.end(), [](const pair<string, double>& a, const pair<string, double>& b)
    {
        return a.second > b.second;
    });
}
//--
void RCV::computeDowdall()
{
    if (candidates.size() < 2)
    {
        printf("Too few candidates to do a vote.\n");
        return;
    }
    
    results.resize(candidates.size());

    for (int i = 0; i < candidates.size(); i++)
    {
        pair <string, double> candidateResult;
        candidateResult.first = candidates[i]->name;
        candidateResult.second = 0;
        results[i] = candidateResult;
    }

    for (int i = 0; i < candidates.size(); i++)
    {
        for (int j = 0; j < candidates[i]->nthPlaceVotes.size(); j++)
        {
            results[i].second += static_cast<double>(candidates[i]->nthPlaceVotes[j]) / static_cast<double>(j + 1.0f);
        }
    }
    sort(results.begin(), results.end(), compare);
}
//--
void RCV::computeMinimax()
{
    if (candidates.size() < 2)
    {
        printf("Too few candidates to do a vote.\n");
        return;
    }

    results.clear();
    vector <vector<pair<int, int>>> comparisonTable;
    comparisonTable.resize(candidates.size());

    for (int i = 0; i < candidates.size(); i++)
    {
        comparisonTable[i].resize(candidates.size());
    }

    for (int i = 0; i < comparisonTable.size(); i++)
    {
        for (int j = 0; j < comparisonTable[i].size(); j++)
        {
            comparisonTable[i][j] = prefers(candidates[i], candidates[j]);
        }
    }

    for (int i = 0; i < comparisonTable.size(); i++)
    {
        int min = INT_MAX;
        for (int j = 0; j < comparisonTable[i].size(); j++)
        {
            if (i == j)
            {
                continue;
            }
            if (comparisonTable[i][j].first < min)
            {
                min = comparisonTable[i][j].first;
            }
        }
        pair <string, double> result;
        result.first = candidates[i]->name;
        result.second = static_cast<double>(min);
        results.push_back(result);
    }
    sort(results.begin(), results.end(), compare);
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
        printf("#%d) %s, %f\n", i + 1, results[i].first.c_str(), results[i].second);
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
bool RCV::compare(pair <string, double> x, pair<string, double> y)
{
    return x.second > y.second;
}
//--
void RCV::eliminateCandidate(Candidate* c)
{
    eliminated_HT.insert(c->name);

    for (int i = 0; i < eliminatedBallots.size(); i++)
    {
        for (int j = 0; j < eliminatedBallots[i].second.size(); j++)
        {
            if (eliminated_HT.count(eliminatedBallots[i].second[j]))
            {
                eliminatedBallots[i].second.erase(eliminatedBallots[i].second.begin() + j);
            }
        }
    }
}
//--
string RCV::cleanse(const string& word)
{
    string retString = "";
    int x;
    int count = 0;

    for (int i = 0; i < word.size(); i++)
    {
        x = int(word[i]);

        if ((x > 96) and (x < 123) or (x > 191) and (x < 256)) //if it's a lowercase letter or utf8 character, add it to the return string.
        {
            retString += char(x);
        }
        else if (x > 64 and x < 91) //if it's an uppercase letter, convert to it's lowercase equivalent, and add it to the return string.
        {
            retString += char(x);
        }
    }
    return retString;
}
pair<int, int> RCV::prefers(Candidate* a, Candidate* b)
{
    int tallya = 0;
    int tallyb = 0;
    
    for (int i = 0; i < ballots.size(); i++)
    {
        for (int j = 0; j < ballots[i].second.size(); j++)
        {
            if (ballots[i].second[j] == a->name)
            {
                tallya++;
                break;
            }
            else if (ballots[i].second[j] == b->name)
            {
                tallyb++;
                break;
            }
        }
    }

    pair <int, int> retPair;
    retPair.first = tallya;
    retPair.second = tallyb;
    return retPair;
}
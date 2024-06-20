#include<vector>
#include<string>
#include"RCV.h"
using namespace std;

int main()
{
    
    RCV * vote = new RCV;
    // vector <string> candidateNames = {"reeses", "kitkat", "hersheys", "york", "skittles", "starburst", "almond"};

    // for (int i = 0; i < candidateNames.size(); i++)
    // {
    //     vote->addCandidate(candidateNames[i]);
    // }

    // vector <vector<string>> v = 
    // {
    //     {"reeses", "kitkat", "hersheys", "york", "skittles", "starburst", "almond"},
    //     {"reeses", "kitkat", "york", "starburst", "skittles", "hersheys", "almond"},
    //     {"reeses", "kitkat", "york", "starburst", "skittles", "hersheys", "almond"},
    //     {"reeses", "kitkat", "hersheys", "skittles", "starburst", "almond", "york"},
    //     {"starburst", "kitkat", "skittles", "reeses", "hersheys", "york", "almond"},
    //     {"reeses", "kitkat", "almond", "york", "skittles", "hersheys", "starburst"},
    //     {"reeses", "kitkat", "almond", "york", "skittles", "hersheys", "starburst"},
    //     {"starburst", "kitkat", "hersheys", "skittles", "york", "reeses", "almond"},
    //     {"almond", "york", "hersheys", "starburst", "skittles", "reeses", "kitkat"},
    //     {"kitkat", "skittles", "reeses", "starburst", "hersheys", "almond", "york"},
    //     {"starburst", "kitkat", "hersheys", "almond", "reeses", "skittles", "york"},
    //     {"starburst", "skittles", "york", "almond", "kitkat", "reeses", "hersheys"},
    // };

    // for (int i = 0; i < v.size(); i++)
    // {
    //     vote->addBallot(v[i]);
    // }

    string CSVString = 
    "reeses,kitkat,hersheys,york,skittles,starburst,almond\n"
    "reeses,kitkat,york,starburst,skittles,hersheys,almond\n"
    "reeses,kitkat,york,starburst,skittles,hersheys,almond\n"
    "reeses,kitkat,hersheys,skittles,starburst,almond,york\n"
    "starburst,kitkat,skittles,reeses,hersheys,york,almond\n"
    "reeses,kitkat,almond,york,skittles,hersheys,starburst\n"
    "reeses,kitkat,almond,york,skittles,hersheys,starburst\n"
    "starburst,kitkat,hersheys,skittles,york,reeses,almond\n"
    "almond,york,hersheys,starburst,skittles,reeses,kitkat\n"
    "kitkat,skittles,reeses,starburst,hersheys,almond,york\n"
    "starburst,kitkat,hersheys,almond,reeses,skittles,york\n"
    "starburst,skittles,york,almond,kitkat,reeses,hersheys\n";

    vote->addBallotsFromCSV(CSVString);

    vote->printCandidateData();
    vote->computeBorda();
    vote->printResults();

}
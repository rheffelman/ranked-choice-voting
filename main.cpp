#include<iostream>
#include<vector>
#include<string>
#include"Election.h"
using namespace std;

int main()
{
    
    Election * e = new Election;
    string ar[] = {"reeses", "kitkat", "hersheys", "york", "skittles", "starburst", "almond"};

    for (int i = 0; i < 7; i++)
    {
        e->addCandidate(ar[i]);
    }

    vector <vector<string>> v = 
    {
        {"reeses", "kitkat", "hersheys", "york", "skittles", "starburst", "almond"},
        {"reeses", "kitkat", "york", "starburst", "skittles", "hersheys", "almond"},
        {"reeses", "kitkat", "york", "starburst", "skittles", "hersheys", "almond"},
        {"reeses", "kitkat", "hersheys", "skittles", "starburst", "almond", "york"},
        {"starburst", "kitkat", "skittles", "reeses", "hersheys", "york", "almond"},
        {"reeses", "kitkat", "almond", "york", "skittles", "hersheys", "starburst"},
        {"reeses", "kitkat", "almond", "york", "skittles", "hersheys", "starburst"},
        {"starburst", "kitkat", "hersheys", "skittles", "york", "reeses", "almond"},
        {"almond", "york", "hersheys", "starburst", "skittles", "reeses", "kitkat"},
        {"kitkat", "skittles", "reeses", "starburst", "hersheys", "almond", "york"},
        {"starburst", "kitkat", "hersheys", "almond", "reeses", "skittles", "york"},
        {"starburst", "skittles", "york", "almond", "kitkat", "reeses", "hersheys"},
    };

    for (int i = 0; i < v.size(); i++)
    {
        e->addBallot(v[i]);
    }
    e->computeBordaCount();


}
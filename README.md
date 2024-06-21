# A C++ Library For Ranked-Choice Voting Computations.
### [How input works.](https://github.com/rheffelman/ranked-voting-library/blob/main/input.md)
### [Supported ranked-choice voting systems and how to use them.](https://github.com/rheffelman/ranked-voting-library/blob/main/votingsystems.md)<br/>

### THIS PROJECT IS A WORK IN PROGRESS.
## What?
Ranked-choice voting is a voting system where voters provide a ranked list for their choice of candidates. For example, here's a ranked-choice voting ballot from a poll I did on people's preferences for 7 different types of candy.

```
1st Choice: Reese's
2nd Choice: KitKat
3rd Choice: Hersheys
4th Choice: York
5th Choice: Skittles
6th Choice: Starburst
7th Choice: Almond Joy
```

There is a pretty good wikipedia on the subject, [see here.](https://en.wikipedia.org/wiki/Ranked_voting)<br />

This repository provides a C++ library for performing all sorts of different ranked-choice voting computations to make it easier to implement ranked-choice voting in applications and everyday use. It currently supports 8 different ranked-voting systems, and an easy way to input and output voting data/ballots. It's also completely free and open-source.

## Why?
Ranked-choice voting is typically thought of as a "better" way to go about voting as it is able to reflect the opinions of the voters in more detail. For example, take this FPTP election (FPTP is a "typical" voting system where voters get one vote for one candidate).
```
Candidates: A, B, C, D, E, F, G

Voter 1: A
Voter 2: A
Voter 3: B
Voter 4: C
Voter 5: D
Voter 6: E
Voter 7: F
Voter 8: G

Election Results: A wins, followed by B, C, D, E, F, G all tied for last place.
```

Now, if the voters could rank their choices, the ballots could look something like this:
```
Voter 1: A, B, C, D, E, F, G
Voter 2: A, B, C, D, E, F, G
Voter 3: B, C, D, E, F, G, A
Voter 4: C, B, D, E, F, G, A
Voter 5: D, B, C, E, F, G, A
Voter 6: E, B, C, D, F, G, A
Voter 7: F, B, C, D, E, G, A
Voter 8: G, B, C, D, E, F, A
```

As you can see from this ballot, the desire of the voters is NOT to elect candidate A, 6 out of 8 voters put candidate A as the very last candidate that they would like to see elected, it would be absurd to elect candidate A. A more reasonable choice would be to elect someone like candidate B who is every voters second place choice except Voter 3 who picked candidate B as their first choice.
</br>

### This library was created to shed light on alternative, voting systems, and to inspire more mature voting practices that better reflect the desires of the voter.

## How?
Here's a full example usage of the library:
```cpp
#include<string>
#include"RCV.h"

int main()
{
    RCV * vote = new RCV; // create ranked choice voting object.

    std::string ballots = 
    "A,B,C,D,E,F,G\n"
    "A,B,C,D,E,F,G\n"
    "B,C,D,E,F,G,A\n"
    "C,B,D,E,F,G,A\n"
    "D,B,C,E,F,G,A\n"
    "E,B,C,D,F,G,A\n"
    "F,B,C,D,E,G,A\n"
    "G,B,C,D,E,F,A\n";

    vote->addBallotsFromCSV(ballots); // input your data

    vote->printCandidateData(); // print the data you just input
    vote->computeBorda(); // use one of many methods for computing results of an election using your data
    vote->printResults(); // print the results of the computation you just performed

}
```

Compile the program and link the RCV.cpp file in a terminal:
```sh
g++ main.cpp RCV.cpp
```

Run the compiled program:
```sh
./a.exe
```

And then here's what is output by the program:
```
A, 2, 0, 0, 0, 0, 0, 6
B, 1, 7, 0, 0, 0, 0, 0
C, 1, 1, 6, 0, 0, 0, 0
D, 1, 0, 2, 5, 0, 0, 0
E, 1, 0, 0, 3, 4, 0, 0
F, 1, 0, 0, 0, 4, 3, 0
G, 1, 0, 0, 0, 0, 5, 2

B won the vote!
#1) B, 41.00
#2) C, 35.00
#3) D, 29.00
#4) E, 23.00
#5) F, 17.00
#6) A, 12.00
#7) G, 11.00
```
As you can see, using the Borda Count voting method, candidate B wins the election, and candidate A gets 6th place. While ranked choice voting isn't perfect, it's a lot better 

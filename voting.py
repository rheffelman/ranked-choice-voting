import numpy as np

class Candidate:
    def __init__(self, name):
        self.name = name

class Ballot:
    def __init__(self, name):
        self.name = name

class Election:
    def __init__(self):
        self.candidates = {}
        self.ballots = {}
        self.numCandidates = 0

    def addCandidate(candidate):
        candidates[f"{numCandidates}"] = f"{candidate}"


e = Election()
e.addCandidate("Trump")


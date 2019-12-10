#include <iostream>
#include <list>

struct transition {
    int tail, head, label;
};

bool *inSplit;
int *numMarked, *markedSets, numSetsMarked = 0;
int numSets;
int *elements, *elemInv, *setMap, *setStartIndices, *setEndIndices;

void init(int size) {
    numSets = bool(size);
    elements = new int[size];
    elemInv = new int[size]; //elemInv[elements[i]] = i
    setMap = new int[size];
    setStartIndices = new int[size];
    setEndIndices = new int[size];
    for(int i = 0; i < size; ++i) {
        elements[i] = elemInv[i] = i;
        setMap[i] = 0;
    }
    if(numSets) {
        setStartIndices[0] = 0;
        setEndIndices[0] = size;
    }
}

//Marks an element of the partition
void mark(int elem) {
    int set = setMap[elem];
    int locationOf = elemInv[elem];
    int indexToPlace = setStartIndices[set] + numMarked[set];

    //Swaps marked element to the front of the set
    elements[locationOf] = elements[indexToPlace];
    elemInv[elements[locationOf]] = locationOf;
    elements[indexToPlace] = elem;
    elemInv[elem] = indexToPlace;

    numMarked[set]++;
    if(numMarked[set] == 1) { //First marked element of set
        numSetsMarked++;
        markedSets[numSetsMarked] = set;
    }
}

//For each marked block of the partition, splits it if it is not completely marked
void split() {
    while(numSetsMarked) {  //Until no marked sets remain
        int set = markedSets[--numSetsMarked];
        int unmarkedStart = setStartIndices[set] + numMarked[set];
        if(unmarkedStart == setEndIndices[set]) {   //All elements of the block are marked
            numMarked[set] = 0;
            continue;
        }

        //The smaller split set gets the new label
        if(numMarked[set] <= setEndIndices[set] - unmarkedStart) {
            setStartIndices[numSets] = setStartIndices[set];
            setEndIndices[numSets] = setStartIndices[set] = unmarkedStart;
        }
        else {
            setEndIndices[numSets] = setEndIndices[set];
            setStartIndices[numSets] = setEndIndices[set] = unmarkedStart;
        }

        //Relabeling the sets
        for( int i = setStartIndices[numSets]; i < setEndIndices[numSets]; ++i ) {
            setMap[elements[i]] = numSets;
        }
        numMarked[set] = numMarked[numSets++] = 0;
    }
}

int numStates, numLetters, q0, numFinal;
transition *trans;

int main() {
    std::cin >> numStates >> numLetters, q0, numFinal;
    int numTrans = numStates * numLetters;
    trans = new transition[numTrans];
    for(int i = 0; i < numTrans; i++) {
        transition t;
        std::cin >> t.tail >> t.label >> t.head;
        trans[i] = t;
    }



    std::cout << "Hello, World!" << std::endl;
    return 0;
}
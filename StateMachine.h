#pragma once

#include <vector>
#include <algorithm>
#include "Node.h"
#include "Config.h"

class StateMachine
{
	std::vector<Node*> states;
    std::vector<Node*> actionsBank;
    Node* node_IDLE = new Node(TEXT_IDLE);
    Node* node_Play = new Node(TEXT_PLAY);
    Node* node_Challenger = new Node(TEXT_CHALLENGER);
    Node* node_TouchGrass = new Node(TEXT_GRASS);
    Node* node_TakeShower = new Node(TEXT_SHOWER);
    int minSolutionCost = INT_MAX;

public:
	void Init(PuantMan& pm);
    std::vector<std::string> Tick(PuantMan& pm);
    ~StateMachine()
    {

        for (Node* state : states)
        {
            delete state;
        }

        for (Node* state : actionsBank)
        {
            delete state;
        }

        delete node_IDLE;
        delete node_Play;
        delete node_Challenger;
        delete node_TakeShower;
        delete node_TouchGrass;
    }

};


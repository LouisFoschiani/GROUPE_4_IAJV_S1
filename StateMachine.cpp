#include "StateMachine.h"
#include "PuantMan.h"
#include <iostream>

void StateMachine::Init(PuantMan& pm) {


	node_IDLE->AddCondition(new Condition(Null, True, -1));
	node_Play->AddCondition(new Condition(Mentalhealth, SuperiorOrEqual, MENTALHEALTH_MIN));
	node_Play->AddCondition(new Condition(Cleanliness, SuperiorOrEqual, CLEANLINESS_MIN));
	node_Challenger->AddCondition(new Condition(Elo, SuperiorOrEqual, LOL_ELO_MAX));
	node_Challenger->AddCondition(new Condition(Mentalhealth, SuperiorOrEqual, 0));
	node_Challenger->AddCondition(new Condition(Cleanliness, SuperiorOrEqual, 0));
	node_TouchGrass->AddCondition(new Condition(Mentalhealth, Inferior, MENTALHEALTH_MIN));
	node_TakeShower->AddCondition(new Condition(Cleanliness, Inferior, CLEANLINESS_MIN));

	node_Play->AddEffect(new Effect(Add, Elo, GAIN_ELO_LOL));
	node_Play->AddEffect(new Effect(Remove, Cleanliness, LOST_CLEANLINESS_LOL));
	node_Play->AddEffect(new Effect(Remove, Mentalhealth, LOST_MENTALHEALTH_LOL));
	node_TouchGrass->AddEffect(new Effect(Remove, Elo, LOST_ELO_GRASS));
	node_TouchGrass->AddEffect(new Effect(Add, Mentalhealth, GAIN_MENTALHEALTH_GRASS));
	node_TouchGrass->AddEffect(new Effect(Remove, Cleanliness, LOST_CLEANLINESS_GRASS));
	node_TakeShower->AddEffect(new Effect(Remove, Elo, LOST_ELO_SHOWER));
	node_TakeShower->AddEffect(new Effect(Add, Mentalhealth, GAIN_MENTALHEALTH_SHOWER));
	node_TakeShower->AddEffect(new Effect(Add, Cleanliness, GAIN_CLEANLINESS_SHOWER));

	node_Play->UpdateResources(pm.elo, pm.cleanliness, pm.mentalhealth);

	actionsBank.push_back(node_Play);
	actionsBank.push_back(node_Challenger);
	actionsBank.push_back(node_TouchGrass);
	actionsBank.push_back(node_TakeShower);

	states.push_back(node_Play);


}


std::vector<std::string> StateMachine::Tick(PuantMan& pm) {

	std::vector<std::string> path;

	Node* parent = nullptr;
	Node* currentNode = nullptr;

	while (!states.empty()) {

		parent = currentNode;

		std::vector<Node*>::iterator it = states.begin();

		if (std::find(states.begin(), states.end(), currentNode) == states.end()) {
			currentNode = *it;
		}

		while (it != states.end()) {

			Node* n = *it;
			if (currentNode != nullptr) {
				if (currentNode->GetCost() > n->GetCost()) {
					if (n->GetParent() == nullptr || n->GetParent()->GetCost() > currentNode->GetCost()) {
						n->SetParent(currentNode);
					}
					currentNode = n;
				}
				else if (currentNode->GetCost() == n->GetCost()) {
					if (n->GetEffectEspilon() == 0 || n->GetEffectEspilon() > currentNode->GetEffectEspilon()) {
						n->SetParent(parent);
						currentNode = n;
					}
				}
			}
			else {
				currentNode = n;
			}

			it++;
		}

		it = states.begin();
		while (it != states.end()) {
			if (*it == currentNode) {
				it = states.erase(it);
			}
			else {
				++it;
			}
		}


		currentNode->ApplyEffects(pm);


		// Si arrivé
		if (*currentNode == *node_Challenger) {

			// On backtrack le chemin
			if (currentNode->GetCost() < minSolutionCost) {
				minSolutionCost = currentNode->GetCost();
			}

			path.push_back(currentNode->GetText());
			while (currentNode->GetParent() != nullptr) {
				currentNode = currentNode->GetParent();
				path.push_back(currentNode->GetText());
			}

			// On nettoie
			for (Node* node : states) {
				delete node;
			}
			states.clear();

			while (currentNode) {
				Node* parent = currentNode->GetParent();
				delete currentNode;
				currentNode = parent;
			}

			return path;
		}

		// On cherche les possibles actions
		for (Node* n : actionsBank) {
			Node nn = *n;
			nn.UpdateResources(pm.elo, pm.cleanliness, pm.mentalhealth);

			if (nn.ConditionsOk() && nn.GetCost() < minSolutionCost) {
				Node* newNode = new Node(nn);
				newNode->SetParent(currentNode);
				states.push_back(newNode);
			}
		}
		
	}
	return std::vector<std::string>();
}
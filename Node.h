#pragma once

#include <vector>
#include <string>
class PuantMan;

class Resources {

public:
	int elo;
	int cleanliness;
	int mentalhealth;

	Resources() : elo(0), cleanliness(0), mentalhealth(0){}
	Resources(const int elo, const int cleanliness, const int mentalhealth) : elo(elo), cleanliness(cleanliness), mentalhealth(mentalhealth){}
};

enum EffectOperation {

	Add,
	Remove

};


enum ConditionOperation {

	SuperiorOrEqual,
	Inferior,
	True

};

enum ConditionResources {

	Elo,
	Cleanliness,
	Mentalhealth,
	Null

};

class Effect {

	EffectOperation operation;
	ConditionResources resource;
	int amount;
public:
	Effect(const Effect& other) : operation(other.operation), resource(other.resource), amount(other.amount) {}
	Effect(const EffectOperation operation, const ConditionResources resource, const int amount) : operation(operation), resource(resource), amount(amount){}
	int GetAmount() const {
		return amount;
	}
	EffectOperation GetOperation() const {
		return operation;
	}

	ConditionResources GetResource() const {
		return resource;
	}

};

class Condition {

	int amount;
	ConditionOperation operation;
	ConditionResources resource;

public:
	Condition(const Condition& other) : resource(other.resource), operation(other.operation), amount(other.amount) {}
	Condition(const ConditionResources resource, const ConditionOperation operation, const int amount) : resource(resource), operation(operation), amount(amount){}
	bool IsValid(const int rAmount, const int alpha = 0) const;
	ConditionResources GetType() const;
	int GetAmount() const;
};

class Node
{
	std::vector<Effect*> effects;
	std::vector<Condition*> conditions;
	Node* parent;
	Resources resources;
	std::string text;
	int cost = 0;

public:

	Node(std::string text) : text(text) {
		parent = nullptr;
	}
	Node(const Node& node);
	void AddCondition(Condition* condition);
	void AddEffect(Effect* effect);
	int GetCost() const;
	void UpdateCost();
	int GetEffectEspilon() const;
	bool ConditionsOk() const;
	void ApplyEffects(PuantMan& pm);
	Node* GetParent() const;
	void SetParent(Node* n);
	void UpdateResources(const int elo, const int cleanliness, const int mentalhealth);
	Resources GetResources() const;

	bool operator==(const Node& other) const {
		return text == other.text;
	}

	std::string GetText() const;

	~Node()
	{
		for (Condition* condition : conditions)
		{
			delete condition;
		}

		for (Effect* effect : effects)
		{
			delete effect;
		}
	}
};



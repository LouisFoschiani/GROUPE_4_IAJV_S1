#include "Node.h"
#include "PuantMan.h"

bool Condition::IsValid(const int rAmount, const int alpha) const {

	switch (operation)
	{
		case SuperiorOrEqual:
			return rAmount >= amount;
		case Inferior: {

			return rAmount < amount || rAmount - alpha < amount;

		}

		case True:
			return true;
		default:
			return false;
	}
}

ConditionResources Condition::GetType() const
{
	return resource;
}

int Condition::GetAmount() const
{
	return amount;
}


void Node::UpdateResources(const int elo, const int cleanliness, const int mentalhealth) {
	resources.elo = elo;
	resources.cleanliness = cleanliness;
	resources.mentalhealth = mentalhealth;
}

Resources Node::GetResources() const
{
	return resources;
}

std::string Node::GetText() const
{
	return text;
}

Node::Node(const Node& other)
{
	text = other.text;
	parent = other.GetParent();
	resources = other.GetResources();

	// Copie des conditions
	conditions.reserve(other.conditions.size());
	for (Condition* condition : other.conditions)
	{
		conditions.push_back(new Condition(*condition)); // Appel au constructeur de copie de Condition
	}

	// Copie des effects
	effects.reserve(other.effects.size());
	for (Effect* effect : other.effects)
	{
		effects.push_back(new Effect(*effect)); // Appel au constructeur de copie de Effect
	}

	UpdateCost();
}

void Node::AddCondition(Condition* condition) {

	conditions.push_back(condition);

}

Node* Node::GetParent() const{
	return parent;
}

void Node::SetParent(Node* n)
{
	parent = n;
}

int Node::GetCost() const{
	return cost;
}

void Node::UpdateCost()
{
	cost = 0;
	const Node* p = this;

	while (p->GetParent() != nullptr) {
		cost += p->GetParent()->GetCost();
		p = p->GetParent();
	}

	for (Condition* condition : conditions)
	{
		if (condition->GetType() == Elo && !condition->IsValid(resources.elo)) {
			cost++;
		}

		if (condition->GetType() == Cleanliness && !condition->IsValid(resources.cleanliness)) {
			cost++;
		}
		if (condition->GetType() == Mentalhealth && !condition->IsValid(resources.mentalhealth)) {
			cost++;
		}
	}
}

int Node::GetEffectEspilon() const
{

	int epsilon = 0;

	for (Effect* effect : effects) {
		if (effect->GetOperation() == Add) {
			epsilon += effect->GetAmount();
		}
		if (effect->GetOperation() == Remove) {
			epsilon -= effect->GetAmount();
		}
	}

	return epsilon;
}

bool Node::ConditionsOk() const
{
	int count = 0;
	for (Condition* condition : conditions)
	{
		if (condition->GetType() == Elo && condition->IsValid(resources.elo))
			count += 1;
		if (condition->GetType() == Cleanliness && condition->IsValid(resources.cleanliness))
			count += 1;
		if (condition->GetType() == Mentalhealth && condition->IsValid(resources.mentalhealth))
			count += 1;
	}

	return count == conditions.size();
}

void Node::AddEffect(Effect* effect) {

	effects.push_back(effect);

}

void Node::ApplyEffects(PuantMan& pm) {

	for (Effect* effect : effects) {

		switch (effect->GetOperation()) {

			case Add: {

				pm.UpdateResource(effect->GetResource(), pm.GetResource(effect->GetResource()) + effect->GetAmount());
				break;
			}

			case Remove: {
				pm.UpdateResource(effect->GetResource(), pm.GetResource(effect->GetResource()) - effect->GetAmount());
				break;
			}
		}

	}

}
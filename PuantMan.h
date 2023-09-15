#pragma once

#include "Node.h"
#include "Config.h"
#include <iostream>

class PuantMan
{
public:

	int elo;
	int cleanliness;
	int mentalhealth;

	PuantMan() : elo(LOL_ELO_START), cleanliness(CLEANLINESS_START), mentalhealth(MENTALHEALTH_START){}

	void Debug();
	int GetResource(const ConditionResources type) const;
	void UpdateResource(const ConditionResources type, const int amount);
};


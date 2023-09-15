#include "PuantMan.h"

void PuantMan::Debug()
{
	std::cout << "ELO: " << elo << " CLEAN: " << cleanliness << " MENTAL: " << mentalhealth << "\n";
}

int PuantMan::GetResource(const ConditionResources type) const {

	switch (type)
	{
		case Elo: {

			return elo;

		}

		case Cleanliness: {

			return cleanliness;

		}

		case Mentalhealth: {

			return mentalhealth;

		}

		
	}
	return -1;
}

void PuantMan::UpdateResource(const ConditionResources type, const int amount) {

	switch (type)
	{
		case Elo: {
			elo = amount;
			break;
		}

		case Cleanliness: {
			cleanliness = amount;
			break;
		}

		case Mentalhealth: {
			mentalhealth = amount;
			break;
		}

	}

}
#pragma once

#include <iostream>;

class State {
public:
	int mentalHealth;
	int elo;
	int cleanliness;

	virtual ~State() {} // Destructeur virtuel
	void virtual Execute() const;

};

class State_Play : State {

	void virtual Execute()const override;
	 
};


class State_Heal : State {

	void virtual Execute()const override;

};


class State_IDLE : State {

	void virtual Execute()const override;

};


class State_Challenger : State {

	void virtual Execute()const override;

};
#pragma once

class State {
private:
	int mentalHealth;
	int elo;

	void virtual Execute() const;

};

class State_Play : State {

	void virtual Execute()const override;
	 
};


class State_Shower : State {

	void virtual Execute()const override;

};

class State_TouchGrass : State {

	void virtual Execute()const override;

};


class State_IDLE : State {

	void virtual Execute()const override;

};


class State_Challenger : State {

	void virtual Execute()const override;

};
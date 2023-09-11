#include "State.h"


void State::Execute() const {
    std::cout << "State" << std::endl;
}

void State_Play::Execute() const {
    std::cout << "Pue sur lol" << std::endl;
}

void State_Heal::Execute() const {
    std::cout << "Se soigne" << std::endl;
}

void State_IDLE::Execute() const {
    std::cout << "Idle" << std::endl;
}

void State_Challenger::Execute() const {
    std::cout << "Bien joué le boss" << std::endl;
}
#include "Action.h"


void GoOutsideAction::Execute(State& state) {
    // Lorsque le joueur sort à l'extérieur, il perd de l'ELO, gagne en propreté et en santé mentale
    state.elo -= 10;
    state.cleanliness += 7;
    state.mentalHealth += 15;
}

void TakeShowerAction::Execute(State& state) {
    // Lorsque le joueur prend une douche, il gagne en propreté et en santé mentale, mais perd de l'ELO
    state.cleanliness += 15;
    state.mentalHealth += 10;
    state.elo -= 15;
}

void PlayAction::Execute(State& state) {
    // Lorsque le joueur joue , il gagne de l'ELO, mais perd de la santé mentale et de la propreté
    state.elo += 10;
    state.mentalHealth -= 10;
    state.cleanliness -= 5;
}


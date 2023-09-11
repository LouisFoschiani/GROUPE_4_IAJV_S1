#include "Action.h"


void GoOutsideAction::Execute(State& state) {
    // Lorsque le joueur sort � l'ext�rieur, il perd de l'ELO, gagne en propret� et en sant� mentale
    state.elo -= 10;
    state.cleanliness += 7;
    state.mentalHealth += 15;
}

void TakeShowerAction::Execute(State& state) {
    // Lorsque le joueur prend une douche, il gagne en propret� et en sant� mentale, mais perd de l'ELO
    state.cleanliness += 15;
    state.mentalHealth += 10;
    state.elo -= 15;
}

void PlayAction::Execute(State& state) {
    // Lorsque le joueur joue , il gagne de l'ELO, mais perd de la sant� mentale et de la propret�
    state.elo += 10;
    state.mentalHealth -= 10;
    state.cleanliness -= 5;
}


#pragma once

#include "State.h" // Incluez le fichier qui d�finit PlayerState si n�cessaire



// Structure pour repr�senter les pr�conditions d'une action
struct Preconditions {
    int eloRequirement;
    int cleanlinessRequirement;
    int mentalHealthRequirement;
};

// Structure pour repr�senter les effets d'une action
struct Effects {
    int elo;
    int cleanliness;
    int mentalHealth;
};

class Action {
public:
    virtual void Execute(State& state) = 0;
};

class GoOutsideAction : public Action {
public:
    void Execute(State& state) override;
};

class TakeShowerAction : public Action {
public:
    void Execute(State& state) override;
};

class PlayAction : public Action {
public:
    void Execute(State& state) override;
};

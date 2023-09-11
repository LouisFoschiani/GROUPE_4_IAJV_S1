#pragma once

#include "State.h" // Incluez le fichier qui d�finit PlayerState si n�cessaire

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

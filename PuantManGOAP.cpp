#include <vector>
#include <windows.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <functional>
#include "StateMachine.h"
#include "PuantMan.h"

int main() {
  
    StateMachine* sm = new StateMachine();
    PuantMan* pm = new PuantMan();

    sm->Init(*pm);

    std::cout << "Etat du joueur au debut: \n\n";
    pm->Debug();
    std::cout << "\n\n";

    std::vector<std::string> path = sm->Tick(*pm);

    std::vector<std::string>::iterator it = path.end();

    std::cout << "Chemin depuis le debut vers l'arrivee: \n\n";
    
    while (it != path.begin())
    {
        --it;
        std::cout << *it << "\n";
        Sleep(100);
    }

    std::cout << "\nEtat du joueur a la fin: \n\n";
    pm->Debug();

    delete sm;
    delete pm;

    return 0;
}

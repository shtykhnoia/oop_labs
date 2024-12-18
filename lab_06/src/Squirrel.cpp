#include "Squirrel.h"
#include "Knight.h"
#include "SlaveTrader.h"

Squirrel::Squirrel(const std::string& name, double x, double y)
    : NPC(name, x, y) {}

void Squirrel::interact(NPC& other) {
    if (!other.isAlive()) {
        return;
    }
    other.interactWith(*this);
}

void Squirrel::interactWith(Knight& knight) {
    // Белки не взаимодействуют с Рыцарями
}

void Squirrel::interactWith(Squirrel& squirrel) {
    if(!squirrel.isAlive()){
        return;
    }
    std::string message = getType() + " " + getName() + " убила " + squirrel.getType() + " " + squirrel.getName();
    notifyObservers(message);
    squirrel.die();
}

void Squirrel::interactWith(SlaveTrader& slaveTrader) {
    //белки не взаимодействуют с работорговцами
}

std::string Squirrel::getType() const {
    return "Squirrel";
}
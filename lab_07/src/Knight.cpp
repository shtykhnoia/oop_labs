#include "Knight.h"
#include "Squirrel.h"
#include "SlaveTrader.h"

Knight::Knight(const std::string& name, double x, double y)
    : NPC(name, x, y) {}

void Knight::interact(NPC& other) {
    if (!other.isAlive()) {
        return;
    }
    other.interactWith(*this);
}

void Knight::interactWith(Knight& knight) {

}

void Knight::interactWith(Squirrel& squirrel) {
    
}

void Knight::interactWith(SlaveTrader& slaveTrader) {
    if (!slaveTrader.isAlive()) {
        return;
    }
    std::string message = getType() + " " + getName() + " убил " + slaveTrader.getType() + " " + slaveTrader.getName();
    notifyObservers(message);
    slaveTrader.die();
}

std::string Knight::getType() const {
    return "Knight";
}
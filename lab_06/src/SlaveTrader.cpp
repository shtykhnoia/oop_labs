#include "SlaveTrader.h"
#include "Knight.h"
#include "Squirrel.h"

SlaveTrader::SlaveTrader(const std::string& name, double x, double y)
    : NPC(name, x, y) {}

void SlaveTrader::interact(NPC& other) {
    if (!other.isAlive()) {
        return;
    }
    other.interactWith(*this);
}

void SlaveTrader::interactWith(Knight& knight) {
}

void SlaveTrader::interactWith(Squirrel& squirrel) {
    if(!squirrel.isAlive()){
        return;
    }
    std::string message = getType() + " " + getName() + " убил " + squirrel.getType() + " " + squirrel.getName();
    notifyObservers(message);
    squirrel.die();
}

void SlaveTrader::interactWith(SlaveTrader& slaveTrader) {
}

std::string SlaveTrader::getType() const {
    return "SlaveTrader";
}
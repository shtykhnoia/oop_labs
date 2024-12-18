#ifndef SLAVETRADER_H
#define SLAVETRADER_H

#include "NPC.h"

class SlaveTrader : public NPC {
public:
    SlaveTrader(const std::string& name, double x, double y);

    void interact(NPC& other) override;
    void interactWith(Knight& knight) override;
    void interactWith(Squirrel& squirrel) override;
    void interactWith(SlaveTrader& SlaveTrader) override;

    std::string getType() const override;
};

#endif
#ifndef PELLET_H
#define PELLET_H

#include "item.h"
#include "../../gameaux.h"

class Pellet: public Item {
    Q_OBJECT
public:
    Pellet(GameAux *parent_ipt);

    void eaten();

signals:
    void pelletEaten();

public slots:
    void shine();

private:
    GameAux *parent;
    bool visible;
};

#endif // PELLET_H

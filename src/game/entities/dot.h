#ifndef DOT_H
#define DOT_H

#include "item.h"
#include "../../gameaux.h"

class Dot: public Item {
    Q_OBJECT
public:
    Dot(GameAux *parent_ipt);

    void eaten();
    void shine();

signals:
    void dotEaten();

private:
    GameAux *parent;
};

#endif // DOT_H

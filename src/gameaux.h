#ifndef GameAux_H
#define GameAux_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include "game/entities/character.h"
#include "game/compass.h"
#include "game/entities/item.h"
#include "game/dashboard.h"
#include "game/entities/ghost.h"
#include "game/entities/blinky.h"
#include "game/entities/pinky.h"
#include "game/entities/inky.h"
#include "game/entities/clyde.h"
#include "game/button.h"
#include "game/animaterect.h"

#include "gameover.h"

class GameAux: public QGraphicsView {
    Q_OBJECT
public:
    GameAux();

    void keyPressEvent(QKeyEvent *event);
    void putDots();
    void clearDots();
    void pause();
    void resume();

    void wait(qreal msec);

    // panel control
    void menuPanel(bool ipt);
    void playPanel(bool ipt);
    void pausePanel(bool ipt);

    // mode control
    void gameClear();

    Dashboard *board;

public slots:
    void itemEat(QPoint pos);
    void dotsAte();
    void pelletAte();
    void countDown();
    void ghostKill(Ghost *ghost);

    // end game control
    void gameStart();
    void gameFail();
    void gamePause();

private:
    const int width = 448;
    const int height = 564;

    int mode;
    int remainDots;
    int times;

    QGraphicsScene *scene;
    Item *item[31][28];

    // title
    QGraphicsPixmapItem *title;
    Button *play, *quit;

    // for game playing
    Character *player, *blinky, *inky, *clyde, *pinky;
    Compass *compass;
    QTimer *pacmanMove, *shine, *ghostMove, *lag;

    // for result showing
    QGraphicsTextItem *result, *score;
    Button *again, *back;

    // for pause showing
    QGraphicsTextItem *message;
    Button *conti;

    AnimateRect *background;
};

enum Mode {
    Menu, Pause, Play, Result
};

#endif // GameAux_H

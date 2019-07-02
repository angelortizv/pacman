#include "gameaux.h"
#include "game/entities/pacman.h"
#include "game/entities/dot.h"
#include "game/entities/pellet.h"
#include "game/entities/ghost.h"
#include <QDebug>
#include <QEventLoop>

GameAux::GameAux() {
    // set up the widow
    setFixedSize(width, height);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // create the scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, width, height);
    scene->setBackgroundBrush(QPixmap(":/img/map/map_pure.png").scaledToHeight(564));
    setScene(scene);

    // create the compass item
    compass = new Compass(this);
    connect(compass, SIGNAL(eat(QPoint)), this, SLOT(itemEat(QPoint)));

    mode = Mode::Menu;

    // create the shining timer for power pellets shine
    shine = new QTimer(this);

    // create the lag timer for anytime the game should pause a little
    lag = new QTimer(this);

    // create the pacman (the player)
    player = new Pacman(compass);
    scene->addItem(player);
    player->hide();

    // create the ghost
    blinky = new Blinky(compass);
    scene->addItem(blinky);
    blinky->setPos(32, 51);

    pinky = new Pinky(compass);
    scene->addItem(pinky);
    pinky->setPos(416, 51);

    inky = new Inky(compass);
    scene->addItem(inky);
    inky->setPos(16, 499);

    clyde = new Clyde(compass);
    scene->addItem(clyde);
    clyde->setPos(416, 499);

    // create the move timer
    pacmanMove = new QTimer(this);

    // player move
    connect(pacmanMove, SIGNAL(timeout()), player, SLOT(move()));

    ghostMove = new QTimer(this);

    // ghost move
    connect(ghostMove, SIGNAL(timeout()), blinky, SLOT(move()));
    connect(ghostMove, SIGNAL(timeout()), pinky, SLOT(move()));
    connect(ghostMove, SIGNAL(timeout()), inky, SLOT(move()));
    connect(ghostMove, SIGNAL(timeout()), clyde, SLOT(move()));

    connect(blinky, SIGNAL(fail()), this, SLOT(gameFail()));
    connect(pinky, SIGNAL(fail()), this, SLOT(gameFail()));
    connect(inky, SIGNAL(fail()), this, SLOT(gameFail()));
    connect(clyde, SIGNAL(fail()), this, SLOT(gameFail()));

    connect(blinky, SIGNAL(collide(Ghost *)), this, SLOT(ghostKill(Ghost *)));
    connect(pinky, SIGNAL(collide(Ghost *)), this, SLOT(ghostKill(Ghost *)));
    connect(inky, SIGNAL(collide(Ghost *)), this, SLOT(ghostKill(Ghost *)));
    connect(clyde, SIGNAL(collide(Ghost *)), this, SLOT(ghostKill(Ghost *)));

    // create the dashboard
    board = new Dashboard(this);
    scene->addItem(board);
    board->hide();

    // initialize the result panel
    result = new QGraphicsTextItem();
    score = new QGraphicsTextItem();
    result->setFont(QFont("Joystix", 50));
    result->setDefaultTextColor(Qt::white);
    scene->addItem(result);
    score->setFont(QFont("Joystix", 25));
    score->setDefaultTextColor(Qt::white);
    scene->addItem(score);

    // pause panel initialize
    message = new QGraphicsTextItem();
    message->setDefaultTextColor(Qt::white);
    message->setFont(QFont("Joystix", 50));
    message->setPlainText("pause");
    scene->addItem(message);
    message->hide();

    conti = new Button("resume", 30);
    scene->addItem(conti);
    conti->hide();

    conti->setZValue(2);

    connect(conti, SIGNAL(clicked()), this, SLOT(gamePause()));

    message->setPos(width / 2 - message->boundingRect().width() / 2, 100);
    message->setZValue(2);

    background = new AnimateRect(width, height);
    scene->addItem(background);
    background->setZValue(1);

    show();
}

void GameAux::keyPressEvent(QKeyEvent *event) {
    if (mode == Mode::Play) {
        if (event->key() == Qt::Key_Up)
            player->setDirection(Dir::Up);
        else if (event->key() == Qt::Key_Down)
            player->setDirection(Dir::Down);
        else if (event->key() == Qt::Key_Left)
            player->setDirection(Dir::Left);
        else if (event->key() == Qt::Key_Right)
            player->setDirection(Dir::Right);
    }
}

void GameAux::putDots() {
    QList <QPoint> list = compass->dots();
    foreach(QPoint pos, list) {
        item[pos.x()][pos.y()] = new Dot(this);
        item[pos.x()][pos.y()]->setPos(16 * pos.y(), 35 + 16 * pos.x());
        scene->addItem(item[pos.x()][pos.y()]);
        connect(item[pos.x()][pos.y()], SIGNAL(dotEaten()), this, SLOT(dotsAte()));
    }

    list = compass->pellets();
    foreach(QPoint pos, list) {
        item[pos.x()][pos.y()] = new Pellet(this);
        item[pos.x()][pos.y()]->setPos(16 * pos.y(), 35 + 16 * pos.x());
        scene->addItem(item[pos.x()][pos.y()]);
        connect(shine, SIGNAL(timeout()), item[pos.x()][pos.y()], SLOT(shine()));
        connect(item[pos.x()][pos.y()], SIGNAL(pelletEaten()), this, SLOT(pelletAte()));
    }

}

void GameAux::itemEat(QPoint pos) {
    if (mode == Mode::Play) {
        item[pos.x()][pos.y()]->eaten();
    }
}

void GameAux::pause() {
    pacmanMove->stop();
    ghostMove->stop();
    shine->stop();

    // turn off the timer on the character
    player->pause();
    blinky->pause();
    inky->pause();
    pinky->pause();
    clyde->pause();
}

void GameAux::resume() {
    pacmanMove->start();
    ghostMove->start();
    shine->start();

    // turn on all timers on the objects
    player->start();
    blinky->start();
    inky->start();
    pinky->start();
    clyde->start();
}

void GameAux::dotsAte() {
    board->addScore(10);
    remainDots --;
}

void GameAux::pelletAte() {
    board->addScore(50);
    times = 0;
}

void GameAux::gameStart() {
    if (mode == Mode::Result)
        background->fadeOut();
    // change mode
    mode = Mode::Play;

    // put the dots and pellets on the map
    compass->initMap();
    putDots();

    // set timer start
    pacmanMove->start(20);
    ghostMove->start(11);
    shine->start(300);

    // set the characters' pos
    player->setPos(width / 2 - player->boundingRect().width() / 2 + 7, 403);
    blinky->setPos(width / 2 - blinky->boundingRect().width() / 2 + 8, 211);
    pinky->setPos(width / 2 - pinky->boundingRect().width() / 2 + 8, 259);
    inky->setPos(width / 2 - pinky->boundingRect().width() / 2 - 24, 259);
    clyde->setPos(width / 2 - pinky->boundingRect().width() / 2 + 40, 259);

    remainDots = 240;

    board->reset();

    player->restore();
    blinky->restore();
    pinky->restore();
    clyde->restore();
    inky->restore();

    connect(lag, SIGNAL(timeout()), this, SLOT(countDown()));

    wait(0.5);
}

void GameAux::gameFail() {
    disconnect(lag, SIGNAL(timeout()), this, SLOT(countDown()));

    player->die();
    clearDots();
    background->fadeIn();

    this->close();
    GameOver gameover;
    gameover.setModal(true);
    gameover.exec();
}

void GameAux::clearDots() {
    QList <QPoint> list = compass->remainDots();
    foreach(QPoint pos, list) {
        delete item[pos.x()][pos.y()];
    }
}

void GameAux::wait(qreal msec) {
    if (mode != Mode::Play)
        return;
    mode = Mode::Pause;
    lag->start(int(1000 * msec));
    pause();
}

void GameAux::countDown() {
    mode = Mode::Play;
    player->show();
    lag->stop();
    resume();
}

void GameAux::ghostKill(Ghost *ghost) {
    wait(0.5);
    player->hide();
    ghost->setPixmap(QPixmap(":/img/item/score/" + QString::number(times) + ".png").scaledToHeight(32));
    board->addScore(int(pow(2, ++ times) * 100));
}

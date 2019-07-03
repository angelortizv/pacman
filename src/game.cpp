#include "game.h"
//#include "ui_game.h"
#include "game/entities/pacman.h"
#include "game/entities/dot.h"
#include "game/entities/pellet.h"

Game::Game()
//    ui(new Ui::Game)
{
//    ui->setupUi(this);
    loadUI();
    loadGameEntities();
}

void Game::loadUI(){
//    QFontDatabase::addApplicationFont(":/font/pixel.ttf");
//    ui->scoreCounter->setFont(QFont(font_family, font_size));
//    ui->label_lives->setFont(QFont(font_family, font_size));
//    ui->label_score->setFont(QFont(font_family, font_size));
}

void Game::loadGameEntities(){

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

    background = new AnimateRect(width, height);
    scene->addItem(background);
    background->setZValue(1);

    show();
}


void Game::keyPressEvent(QKeyEvent *event) {
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

void Game::putDots() {
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

void Game::itemEat(QPoint pos) {
    if (mode == Mode::Play) {
        item[pos.x()][pos.y()]->eaten();
    }
}

void Game::pause() {
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

void Game::resume() {
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

void Game::dotsAte() {
    board->addScore(10);
    remainDots --;
}

void Game::pelletAte() {
    board->addScore(50);
    times = 0;
}

void Game::gameStart() {
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

void Game::gameFail() {
    disconnect(lag, SIGNAL(timeout()), this, SLOT(countDown()));

    player->die();
    clearDots();
    background->fadeIn();

    this->close();
    GameOver gameover;
    gameover.setModal(true);
    gameover.exec();
}

void Game::clearDots() {
    QList <QPoint> list = compass->remainDots();
    foreach(QPoint pos, list) {
        delete item[pos.x()][pos.y()];
    }
}

void Game::wait(qreal msec) {
    if (mode != Mode::Play)
        return;
    mode = Mode::Pause;
    lag->start(int(1000 * msec));
    pause();
}

void Game::countDown() {
    mode = Mode::Play;
    player->show();
    lag->stop();
    resume();
}

void Game::ghostKill(Ghost *ghost) {
    wait(0.5);
    player->hide();
    ghost->setPixmap(QPixmap(":/img/item/score/" + QString::number(times) + ".png").scaledToHeight(32));
    board->addScore(int(pow(2, ++ times) * 100));
}

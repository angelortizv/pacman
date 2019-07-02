#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include "gameover.h"

namespace Ui {
class Game;
}

class Game : public QDialog
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();

private slots:
    void on_testButton_clicked();

private:
    Ui::Game *ui;
    int live = 3;

    void livesManager();
};

#endif // GAME_H

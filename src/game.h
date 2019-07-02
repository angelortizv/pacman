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
    static const int font_size = 20;
    static const int font_size_2 = 8;
    const QString font_family = "Joystix";
    void loadUI();
};

#endif // GAME_H

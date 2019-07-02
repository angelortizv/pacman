#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>
#include <QMovie>
#include "mainwindow.h"

namespace Ui {
class GameOver;
}

class GameOver : public QDialog
{
    Q_OBJECT

public:
    explicit GameOver(QWidget *parent = 0);
    ~GameOver();

private slots:
    void on_goback_button_clicked();

private:
    Ui::GameOver *ui;
    void loadGif();
};

#endif // GAMEOVER_H

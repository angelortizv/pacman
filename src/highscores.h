#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class HighScores;
}

class HighScores : public QDialog
{
    Q_OBJECT

public:
    explicit HighScores(QWidget *parent = 0);
    ~HighScores();

private slots:
    void on_goback_button_clicked();

private:
    Ui::HighScores *ui;
};

#endif // HIGHSCORES_H

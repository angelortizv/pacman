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
    static const int font_size = 15;
    static const int font_size_2 = 8;
    const QString font_family = "Joystix";
    void loadUI();
};

#endif // HIGHSCORES_H

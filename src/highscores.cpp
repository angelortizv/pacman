#include "highscores.h"
#include "ui_highscores.h"

HighScores::HighScores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HighScores)
{
    ui->setupUi(this);
    loadUI();
}

HighScores::~HighScores()
{
    delete ui;
}

void HighScores::loadUI(){
    QFontDatabase::addApplicationFont(":/font/pixel.ttf");
    ui->goback_button->setFont(QFont(font_family, font_size));
}

void HighScores::on_goback_button_clicked()
{
    close();
    MainWindow *w = new MainWindow();
    w->show();
}

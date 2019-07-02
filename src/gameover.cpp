#include "gameover.h"
#include "ui_gameover.h"

GameOver::GameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);
    loadGif();
}

GameOver::~GameOver()
{
    delete ui;
}

void GameOver::loadGif(){
    QMovie *movie=new QMovie(":/img/initial_gif.gif");
    ui->initial_gif_label->setMovie(movie);
    movie->start();
}

void GameOver::on_goback_button_clicked()
{
    close();
    MainWindow *w = new MainWindow();
    w->show();
}


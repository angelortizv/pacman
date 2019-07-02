#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    livesManager();
}

Game::~Game()
{
    delete ui;
}

void Game::livesManager(){
    if(live == 3){ui->livesCounter->setStyleSheet("image: url(:/img/lives_3);");}
    if(live == 2){ui->livesCounter->setStyleSheet("image: url(:/img/lives_2);");}
    if(live == 1){ui->livesCounter->setStyleSheet("image: url(:/img/lives_1);");}
}

void Game::on_testButton_clicked()
{
    close();
    GameOver gameover;
    gameover.setModal(true);
    gameover.exec();
}

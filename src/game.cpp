#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    loadUI();
}

Game::~Game()
{
    delete ui;
}

void Game::loadUI(){
    QFontDatabase::addApplicationFont(":/font/pixel.ttf");
    ui->scoreCounter->setFont(QFont(font_family, font_size));
    ui->label_lives->setFont(QFont(font_family, font_size));
    ui->label_score->setFont(QFont(font_family, font_size));
}

void Game::on_testButton_clicked()
{
    close();
    GameOver gameover;
    gameover.setModal(true);
    gameover.exec();
}

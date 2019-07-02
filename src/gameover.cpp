#include "gameover.h"
#include "ui_gameover.h"

GameOver::GameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);
    loadUI();
}

GameOver::~GameOver()
{
    delete ui;
}

void GameOver::loadUI(){
    QMovie *movie=new QMovie(":/img/initial_gif.gif");
    ui->initial_gif_label->setMovie(movie);
    movie->start();
    QFontDatabase::addApplicationFont(":/font/pixel.ttf");
    ui->label_3->setFont(QFont(font_family, font_size));
    ui->label_4->setFont(QFont(font_family, font_size));
    ui->goback_button->setFont(QFont(font_family, font_size));
    ui->ok_button->setFont(QFont(font_family, font_size));
    ui->textEdit->setFont(QFont(font_family, font_size));
}

void GameOver::on_goback_button_clicked()
{
    close();
    MainWindow *w = new MainWindow();
    w->show();
}


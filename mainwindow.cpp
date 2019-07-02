#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadGif();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadGif(){
    QMovie *movie=new QMovie(":/img/initial_gif.gif");
    ui->initial_gif_label->setMovie(movie);
    movie->start();
}

void MainWindow::on_highscores_button_clicked()
{
    close();
    HighScores highscores;
    highscores.setModal(true);
    highscores.exec();
}

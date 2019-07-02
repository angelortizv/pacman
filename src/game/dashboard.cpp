#include "dashboard.h"

Dashboard::Dashboard(QObject *parent): QObject (parent) {
    // initialize the score data
    score = 0;
    high = 0;

    // create the textItem
    text_high = new QGraphicsTextItem(QString::number(high), this);
    text_score = new QGraphicsTextItem(QString::number(score), this);
    text_high->setDefaultTextColor(Qt::white);
    text_score->setDefaultTextColor(Qt::white);

    text_high->setPos(224 - text_high->boundingRect().width() / 2, 0);
    text_score->setPos(448 - text_score->boundingRect().width() - 10, 0);

    // set the font
    QFontDatabase::addApplicationFont(":/font/pixel.ttf");
    text_high->setFont(QFont(font_family, font_size));
    text_score->setFont(QFont(font_family, font_size));

}

void Dashboard::addScore(int ipt) {
    // update the exact data
    score += ipt;
    high = max(score, high);

    // update the graphics data
    text_score->setPlainText(QString::number(score));
    text_high->setPlainText(QString::number(high));

    text_high->setPos(224 - text_high->boundingRect().width() / 2, 0);
    text_score->setPos(448 - text_score->boundingRect().width() - 10, 0);
}

void Dashboard::reset() {
    score = 0;
    text_score->setPlainText(QString::number(score));
    text_score->setPos(448 - text_score->boundingRect().width() - 5, 0);
}

int Dashboard::getScore() {
    return score;
}

int Dashboard::getHighScore() {
    return high;
}

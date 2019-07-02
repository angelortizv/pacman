#include "button.h"
#include <QFont>
#include <QDebug>

Button::Button(QString text_ipt, int font_size_ipt): font_size(font_size_ipt) {
    setAcceptHoverEvents(true);

    text = new QGraphicsTextItem(text_ipt, this);
    text->setFont(QFont(font_family, font_size));

    for (int i = 0; i < 3; i ++) {
        pic[i].load(":/img/pacman/" + QString::number(i) + ".png");
        pic[i] = pic[i].scaledToHeight(text->boundingRect().height() - 15);
    }
    icon = new QGraphicsPixmapItem(pic[1], this);

    text->setDefaultTextColor(Qt::white);
    text->setPos(icon->boundingRect().width() - 2, 0);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(change()));
    timer->setInterval(100);

    icon->setY(text->boundingRect().height() / 2 - icon->boundingRect().height() / 2);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    timer->start();
    text->setFont(QFont(font_family, font_size + 3));
    icon->setY(text->boundingRect().height() / 2 - icon->boundingRect().height() / 2);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    timer->stop();
    icon->setPixmap(pic[1]);
    text->setFont(QFont(font_family, font_size));
    icon->setY(text->boundingRect().height() / 2 - icon->boundingRect().height() / 2);
}

qreal Button::width() {
    return text->boundingRect().width() + icon->boundingRect().width() + 10;
}

qreal Button::height() {
    return text->boundingRect().height();
}

void Button::change() {
    static int i = 1, add = 1;
    icon->setPixmap(pic[i]);
    i += add;
    if (i <= 0 || i >= 2)
        add = -add;
}

void Button::restore() {
    timer->stop();
    icon->setPixmap(pic[1]);
    text->setFont(QFont(font_family, font_size));
    icon->setY(text->boundingRect().height() / 2 - icon->boundingRect().height() / 2);
}

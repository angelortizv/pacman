#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QTimer>

class Button: public QObject, public QGraphicsItemGroup {
    Q_OBJECT
public:
    Button(QString text_ipt, int font_size_ipt);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    void restore();

    qreal width();
    qreal height();

signals:
    void clicked();

public slots:
    void change();

private:
    QGraphicsTextItem *text;
    QGraphicsPixmapItem *icon;
    const QString font_family = "Joystix";
    int font_size;
    QTimer *timer;
    QPixmap pic[3];
};

#endif // BUTTON_H

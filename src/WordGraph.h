#ifndef DDD_H
#define DDD_H

#include <QWidget>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include "mainwindow.h"

namespace Ui {
class WordGraph;
}

class WordGraph : public QWidget
{
    Q_OBJECT

public:
    explicit WordGraph(QWidget *parent = 0);
    ~WordGraph();

    QPoint m_start_point;
    QPoint m_end_point;
    QVector<QLine> lines;

    void setxxyy(QLabel* x,QLabel* y){xx=x;yy=y;}
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent*);

    bool is;
private:
    Ui::WordGraph *ui;
    QLabel* xx;
    QLabel* yy;
};

#endif // DDD_H

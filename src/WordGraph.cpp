#include "WordGraph.h"
#include "ui_WordGraph.h"
#include <QDebug>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>
#include "Blackline.h"
#include "Arc_utils.h"
WordGraph::WordGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WordGraph)
{
    ui->setupUi(this);
    is=false;
}

WordGraph::~WordGraph()
{
    delete ui;
}

void WordGraph::mousePressEvent(QMouseEvent* event)
{
    if (Qt ::LeftButton == event->button()){
        if (is)
        {
            setMouseTracking(true);
            is=false;
        }
        else
        {
            m_start_point = m_end_point = event->pos();
            setMouseTracking(true);
            is=true;
            update();
        }
    }
    else if(Qt ::RightButton == event->button()){
        if(is){
            is=false;
            m_start_point=m_end_point=QPoint(0,0);
            update();
        }
        else{
            if(!lines.empty())
            lines.pop_back();
            update();
        }
    }
}

void WordGraph::mouseReleaseEvent(QMouseEvent* event){
    if (Qt ::LeftButton == event->button()){
        if(is){}
        else{
            lines.append(Blackline(QLine(m_start_point,m_end_point)).qline());
            update();
            qDebug()<<lines.size()<<"    "<<(lines.end()-1)->x1()<<(lines.end()-1)->y1()<<(lines.end()-1)->x2()<<(lines.end()-1)->y2();
        }
    }
}

void WordGraph::mouseMoveEvent(QMouseEvent* event)
{
    m_end_point = event->pos();
    if(is)
        update();

    double x = event->pos().x();
    double y = event->pos().y();
    to_arc_num(x,y);
    xx->setText(QString::number(x,10,2));
    yy->setText(QString::number(y,10,2));
}

void WordGraph::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QPen pen;//画笔对象
    QBrush brush;//填充对象
    p.setRenderHint(QPainter::Antialiasing, true);
    pen.setColor(QColor(158,138,165,255));//画笔颜色
    pen.setWidth(7);//画笔粗细
    brush.setColor(Qt::red);//填充颜色
    brush.setStyle(Qt::SolidPattern);//填充类型
    p.setBrush(brush);//给p绑定一个填充对象brush
    p.setPen(pen);//给p绑定一个指定的画笔pen
    p.drawLines(lines);
    if(is)
        p.drawLine(m_start_point,m_end_point);

}

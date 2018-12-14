#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "WordGraph.h"
#include "Blackline.h"
#include "Aff.h"
#include <exception>
#include<QMessageBox>
#include<algorithm>
#include<QDebug>
#include <QClipboard>
#include <fstream>
#include <vector>
#include <algorithm>
using std::sort;
using std::for_each;
using std::ostringstream;
using std::stringstream;
using std::vector;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pingyi_time=0;
    wucha_time=0;
    biansu_beilv=1;
    ui->widget->setAutoFillBackground(true);
    QImage image;
    QPalette palette;

    image.load(":/img/bg.png");
    palette.setBrush(ui->widget->backgroundRole(),QBrush(image));
    ui->widget->setPalette(palette);
    ui->widget->setxxyy(ui->label_4,ui->label_5);
    ori_move_x_num=ori_move_y_num=0;
    ori_up_num=ori_down_num=ori_left_num=ori_right_num=0;
    this->setFixedSize(this->size());

    ui->label_11->setVisible(false);
    ui->label_12->setVisible(false);
    ui->is_blackline->setVisible(false);
    ui->split_num->setVisible(false);
    ui->split_bili->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_widget(){
        ui->widget->m_start_point=QPoint(0,0);
        ui->widget->m_end_point=QPoint(0,0);
        ui->widget->is=false;
        ui->widget->update();

}

void MainWindow::on_text_to_pic_clicked()
{
    QString input = ui->textEdit->toPlainText();
    ui->widget->lines.clear();
    ui->move_x_check->setChecked(false);
    ui->move_x_num->setValue(0);
    ui->move_y_check->setChecked(false);
    ui->move_y_num->setValue(0);
    ui->up_suofang->setChecked(false);
    ui->up_num->setValue(1);
    ui->down_suofang->setChecked(false);
    ui->down_num->setValue(1);
    ui->left_suofang->setChecked(false);
    ui->left_num->setValue(1);
    ui->right_suofang->setChecked(false);
    ui->right_num->setValue(1);

    string in;
    std::stringstream iss;
    iss<<input.toStdString();
    try{
        while(iss>>in){
            ui->widget->lines.push_back(Blackline(in).qline());
        }
    }
    catch(std::exception &e){
        QMessageBox::warning(this,"转换错误", "转换错误!\n请检查你的谱面!");
        return;
    }
    update_widget();
}

void MainWindow::on_pic_to_text_clicked()
{
    update_widget();
    auto& lines = ui->widget->lines;
    std::ostringstream oss;
    for(auto i: lines){
        auto temp=Blackline(i);
        temp.start_time=temp.end_time=ui->time_point->value();
        oss<<temp.str()<<"\n";
    }
    ui->textEdit->setPlainText(QString::fromStdString(oss.str()));
}

void MainWindow::on_move_x_check_stateChanged(int arg1)
{
    auto& lines = ui->widget->lines;
    double val=ui->move_x_num->value();
    if(arg1==2){
        ori_move_x_vec = lines;
        ori_move_x_num=val;
        qDebug()<<"ori_move_x_num is "<<ori_move_x_num;
        for_each(lines.begin(),lines.end(),
                 [val](QLine &l){
            l=Blackline(l).move_x(val).qline();

        });
        update_widget();
    }
    if(arg1==0){
//        for_each(lines.begin(),lines.end(),
//                 [val](QLine &l){
//            l=Blackline(l).move_x(-val).qline();

        //});
    lines = ori_move_x_vec;
        update_widget();
    }

}

void MainWindow::on_move_x_num_valueChanged(double arg1)
{
    if(ui->move_x_check->isChecked()){

        auto& lines = ui->widget->lines;
        double val=arg1-ori_move_x_num;
        qDebug()<<"val is "<<val;
        ori_move_x_num=arg1;
        qDebug()<<"ori_move_x_num is "<<ori_move_x_num;
        for_each(lines.begin(),lines.end(),
                 [val](QLine &l){
            l=Blackline(l).move_x(val).qline();
        });
        update_widget();
    }
}

void MainWindow::on_move_y_check_stateChanged(int arg1)
{
    auto& lines = ui->widget->lines;
    double val=ui->move_y_num->value();
    if(arg1==2){
        ori_move_y_vec = lines;
        ori_move_y_num=val;
        qDebug()<<"ori_move_y_num is "<<ori_move_x_num;
        for_each(lines.begin(),lines.end(),
                 [val](QLine &l){
            l=Blackline(l).move_y(val).qline();

        });
        update_widget();
    }
    if(arg1==0){
//        for_each(lines.begin(),lines.end(),
//                 [val](QLine &l){
//            l=Blackline(l).move_y(-val).qline();
//        });
    lines = ori_move_y_vec;
        update_widget();
    }

}

void MainWindow::on_move_y_num_valueChanged(double arg1)
{
    if(ui->move_y_check->isChecked()){

        auto& lines = ui->widget->lines;
        double val=arg1-ori_move_y_num;
        qDebug()<<"val is "<<val;
        ori_move_y_num=arg1;
        qDebug()<<"ori_move_y_num is "<<ori_move_y_num;
        for_each(lines.begin(),lines.end(),
                 [val](QLine &l){
            auto temp=Blackline(l);
            qDebug()<<"y_s is "<<temp.y_s<<" y_e is "<<temp.y_e;
            temp.move_y(val);
            qDebug()<<"after move y_s is "<<temp.y_s<<" y_e is "<<temp.y_e<<"\n\n";
            l=Blackline(l).move_y(val).qline();
        });
        update_widget();
    }
}

void MainWindow::on_up_suofang_stateChanged(int arg1)
{
    auto& lines = ui->widget->lines;
    double val=ui->up_num->value();
    if(arg1==2){
        ori_up_vec = lines;
        ori_up_num=val;
        //qDebug()<<"ori_move_x_num is "<<ori_move_x_num;
        for_each(lines.begin(),lines.end(),
                 [val](QLine &l){
            l=Blackline(l).up(val).qline();

        });
        update_widget();
    }
    if(arg1==0){
//        for_each(lines.begin(),lines.end(),
//                 [val](QLine &l){
//            l=Blackline(l).up(1.0/val).qline();
//        });
    lines = ori_up_vec;
        update_widget();
    }
}

void MainWindow::on_down_suofang_stateChanged(int arg1)
{
    auto& lines = ui->widget->lines;
    double val=ui->down_num->value();
    if(arg1==2){
        ori_down_vec = lines;
        ori_down_num=val;
        //qDebug()<<"ori_move_x_num is "<<ori_move_x_num;
        for_each(lines.begin(),lines.end(),
                 [val](QLine &l){
            l=Blackline(l).down(val).qline();

        });
        update_widget();
    }
    if(arg1==0){
//        for_each(lines.begin(),lines.end(),
//                 [val](QLine &l){
//            l=Blackline(l).down(1.0/val).qline();
//        });
    lines = ori_down_vec;
        update_widget();
    }
}

void MainWindow::on_left_suofang_stateChanged(int arg1)
{
    auto& lines = ui->widget->lines;
    double val=ui->left_num->value();
    if(arg1==2){
        ori_left_vec = lines;
        ori_left_num=val;
        //qDebug()<<"ori_move_x_num is "<<ori_move_x_num;
        for_each(lines.begin(),lines.end(),
                 [val](QLine &l){
            l=Blackline(l).left(val).qline();

        });
        update_widget();
    }
    if(arg1==0){
//        for_each(lines.begin(),lines.end(),
//                 [val](QLine &l){
//            l=Blackline(l).left(1.0/val).qline();
//        });
    lines = ori_left_vec;
        update_widget();
    }
}

void MainWindow::on_right_suofang_stateChanged(int arg1)
{
    auto& lines = ui->widget->lines;
    double val=ui->right_num->value();
    if(arg1==2){
        ori_right_vec = lines;
        ori_right_num=val;
        //qDebug()<<"ori_move_x_num is "<<ori_move_x_num;
        for_each(lines.begin(),lines.end(),
                 [val](QLine &l){
            l=Blackline(l).right(val).qline();

        });
        update_widget();
    }
    if(arg1==0){
//        for_each(lines.begin(),lines.end(),
//                 [val](QLine &l){
//            l=Blackline(l).right(1.0/val).qline();
//        });
    lines = ori_right_vec;
        update_widget();
    }
}

void MainWindow::on_up_num_valueChanged(double arg1)
{
    if(ui->up_suofang->isChecked()){

        auto& lines = ui->widget->lines;
        double val=arg1/ori_up_num;
        ori_up_num=arg1;
        for_each(lines.begin(),lines.end(),
                 [val](QLine &l){
            l=Blackline(l).up(val).qline();
        });
        update_widget();
    }
}

void MainWindow::on_down_num_valueChanged(double arg1)
{
    if(ui->down_suofang->isChecked()){

        auto& lines = ui->widget->lines;
        double val=arg1/ori_down_num;
        ori_down_num=arg1;
        for_each(lines.begin(),lines.end(),
                 [val](QLine &l){
            l=Blackline(l).down(val).qline();
        });
        update_widget();
    }
}

void MainWindow::on_left_num_valueChanged(double arg1)
{
    if(ui->left_suofang->isChecked()){

        auto& lines = ui->widget->lines;
        double val=arg1/ori_left_num;
        ori_left_num=arg1;
        for_each(lines.begin(),lines.end(),
                 [val](QLine &l){
            l=Blackline(l).left(val).qline();
        });
        update_widget();
    }
}

void MainWindow::on_right_num_valueChanged(double arg1)
{
    if(ui->right_suofang->isChecked()){

        auto& lines = ui->widget->lines;
        double val=arg1/ori_right_num;
        ori_right_num=arg1;
        for_each(lines.begin(),lines.end(),
                 [val](QLine &l){
            l=Blackline(l).right(val).qline();
        });
        update_widget();
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->widget->lines.clear();
    update_widget();
}



void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->setPlainText(QString(""));
}

void MainWindow::on_pushButton_3_clicked()
{
     QClipboard *cb = QGuiApplication::clipboard();
     QString text = ui->textafter->toPlainText();
     if(text != ""){
     cb->setText(ui->textEdit->toPlainText());
     ui->pushButton_3->setText("已复制");
     }

}

void MainWindow::on_textEdit_textChanged()
{
    ui->pushButton_3->setText("复制全部");
}

void MainWindow::on_process_clicked()
{
    try {
    QString input = ui->textbefore->toPlainText();
    if(ui->pingyi->isChecked())
        pingyi_time=ui->pingyitime->value();
    else
        pingyi_time=0;
    if(ui->biansu->isChecked())
        biansu_beilv=ui->biansubeisu->value();
    else
        biansu_beilv=1;
    if(ui->duiqi->isChecked())
        wucha_time=ui->duiqitime->value();
    else
        wucha_time=0;
    bool mirror = ui->jingxiang->isChecked();

    string in;
    stringstream iss0;
    ostringstream oss0;
    iss0<<input.toStdString();
    //连接
    if(ui->linksnake->isChecked()){
        //qDebug()<<"fuck";
    vector<Snake> snake_vector;
    while(iss0>>in)
        snake_vector.push_back(Snake(in));
    vector<Snake> b_snake;
    vector<Snake> r_snake;
    for(auto &i: snake_vector)
        if(i.color==0)
            b_snake.push_back(i);
        else
            r_snake.push_back(i);
    sort(b_snake.begin(),b_snake.end(),[](Snake& l,Snake& r){return l.start_time<r.start_time;});
    sort(r_snake.begin(),r_snake.end(),[](Snake& l,Snake& r){return l.start_time<r.start_time;});
    for(auto i = b_snake.begin();i!=b_snake.end();i++){
        i->print(oss0);
        auto j=i+1;
        if(j != b_snake.end()){
            if(i->mark=="false" && j->mark=="false"){
                Snake newsnake(i->end_time,j->start_time,i->x_e,j->x_s,"s",i->y_e,j->y_s,i->color,"false");
                newsnake.print(oss0);
            }
            else{
                Snake newsnake(i->end_time,j->start_time,i->x_e,j->x_s,"s",i->y_e,j->y_s,i->color,"true");
                newsnake.print(oss0);
            }
        }

        else
            break;
    }
    for(auto i = r_snake.begin();i!=r_snake.end();i++){
        i->print(oss0);
        auto j=i+1;
        if(j != r_snake.end()){
            if(i->mark=="false" && j->mark=="false"){
                Snake newsnake(i->end_time,j->start_time,i->x_e,j->x_s,"s",i->y_e,j->y_s,i->color,"false");
                newsnake.print(oss0);
            }
            else{
                Snake newsnake(i->end_time,j->start_time,i->x_e,j->x_s,"s",i->y_e,j->y_s,i->color,"true");
                newsnake.print(oss0);
            }
        }
        else
            break;
    }}
    //拆分
    if(ui->splitsnake->isChecked()){
        bool is_blackline = ui->is_blackline->isChecked();
        double split_num = ui->split_num->value();
        double split_bili = double(ui->split_bili->value())/100;

        vector<Snake> snake_vector;
        while(iss0>>in)
            snake_vector.push_back(Snake(in));

        for(auto & i :snake_vector){
            string mark=i.mark;
            string bl_mark="false";
            if(mark[0]=='f')    bl_mark="true";
            int color = i.color;
            double start_time=i.start_time;
            double add_step_time = double(i.end_time - i.start_time)/split_num;
            qDebug()<<"add_time is "<<add_step_time;
            double start_x_pos = i.x_s;
            double add_step_x = (i.x_e-i.x_s)/split_num;
             qDebug()<<"add_x is "<<add_step_x;
            double start_y_pos = i.y_s;
            double add_step_y= (i.y_e-i.y_s)/split_num;
            qDebug()<<"add_y is "<<add_step_y;
            for(int j=0;j<split_num;j++){
                Snake newsnake(start_time+j*add_step_time,
                               start_time+(j+split_bili)*add_step_time,
                               start_x_pos+j*add_step_x,
                               start_x_pos+(j+split_bili)*add_step_x,
                               "s",
                               start_y_pos+j*add_step_y,
                               start_y_pos+(j+split_bili)*add_step_y,
                               color,mark);
                newsnake.print(oss0);
                if(is_blackline){
                    Snake newsnake(start_time+(j+split_bili)*add_step_time,
                                   start_time+(j+1)*add_step_time,
                                   start_x_pos+(j+split_bili)*add_step_x,
                                   start_x_pos+(j+1)*add_step_x,
                                   "s",
                                   start_y_pos+(j+split_bili)*add_step_y,
                                   start_y_pos+(j+1)*add_step_y,
                                   color,bl_mark);
                    newsnake.print(oss0);
                }
            }

        }

    }
    //平移
    stringstream iss1;
    ostringstream oss1;
    if(ui->linksnake->isChecked() || ui->splitsnake->isChecked())
        iss1<<oss0.str();
    else
        iss1<<input.toStdString();
    while (iss1>>in) {
        switch (in[0])
        {
        case'(':
            Note(in).move(pingyi_time).print(oss1);
            break;
        case't':
            Timing(in).move(pingyi_time).print(oss1);
            break;
        case'h':
            Hold(in).move(pingyi_time).print(oss1);
            break;
        case'a':
            if (in.find('[') == string::npos)
                Snake(in).move(pingyi_time).print(oss1);
            else
                Skynote(in).move(pingyi_time).print(oss1);
            break;
        default:
            oss1 << in << "\n";
            break;
        }
    }

    //变速
    stringstream iss2;
    ostringstream oss2;
    iss2<<oss1.str();
    while (iss2>>in) {
        switch (in[0])
        {
        case'A':
            Offset(in).speed(biansu_beilv).print(oss2);
            break;
        case'(':
            Note(in).speed(biansu_beilv).print(oss2);
            break;
        case't':
            Timing(in).speed(biansu_beilv).print(oss2);
            break;
        case'h':
            Hold(in).speed(biansu_beilv).print(oss2);
            break;
        case'a':
            if (in.find('[') == string::npos)
                Snake(in).speed(biansu_beilv).print(oss2);
            else
                Skynote(in).speed(biansu_beilv).print(oss2);
            break;
        default:
            oss2 << in << "\n";
            break;
        }
    }

    //误差
    stringstream iss3;
    ostringstream oss3;
    iss3<<oss2.str();
    vector<int> arctap_time;
    while (iss3>>in) {
        if (in[0] == 'a' && (in.find('[') != string::npos)) {
            auto temp = Skynote(in).tap;
            for (auto i : temp)
                arctap_time.push_back(i);
        }
    }

    stringstream isst;
    isst<<oss2.str();
    while (isst>>in) {
        if (in[0] == '(') {
            auto temp = Note(in);
            for (auto i : arctap_time)
                if (abs(temp.time - i) == wucha_time) {
                    temp.time = i;
                    break;
                }
            temp.print(oss3);
        }
        else
            oss3 << in << "\n";
    }

    //镜像
    if(mirror){
        stringstream iss4;
        ostringstream oss4;
        iss4<<oss3.str();
        while (iss4>>in) {
                switch (in[0])
                {
                case'(':
                    Note(in).mirror().print(oss4);
                    break;
                case'h':
                    Hold(in).mirror().print(oss4);
                    break;
                case'a':
                    if (in.find('[') == string::npos)
                        Snake(in).mirror().print(oss4);
                    else
                        Skynote(in).mirror().print(oss4);
                    break;
                default:
                    oss4 << in << "\n";
                    break;
                }
            }
        string results(oss4.str());
        QString output = QString::fromStdString(results);
        ui->textafter->setPlainText(output);
    }
    else{
        string results(oss3.str());
        QString output = QString::fromStdString(results);
        ui->textafter->setPlainText(output);
    }
    }
    catch(std::exception & e){
        QMessageBox::warning(this,"处理出错!", "处理出错!\n请检查你的谱面!");
        return;
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    //选择性的code？先注释了
//    QString input = ui->textEdit->toPlainText();
//    if(input == "")
//        ui->textbefore->setPlainText(QString("粘贴你要处理的谱面OvO"));
//    else
//    ui->textbefore->setPlainText(ui->textEdit->toPlainText());
}

void MainWindow::on_pushButton_5_clicked()
{
    QClipboard *cb = QGuiApplication::clipboard();
    QString text = ui->textafter->toPlainText();
    if(text != ""){
    cb->setText(ui->textafter->toPlainText());
    ui->pushButton_5->setText("已复制");
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_textafter_textChanged()
{
    ui->pushButton_5->setText("复制全部");
}

void MainWindow::on_linksnake_stateChanged(int arg1)
{
    if(arg1 == 2)
        ui->splitsnake->setChecked(false);


}

void MainWindow::on_splitsnake_stateChanged(int arg1)
{
    if(arg1 == 2){
        ui->linksnake->setChecked(false);
        ui->label_11->setVisible(true);
        ui->label_12->setVisible(true);
        ui->is_blackline->setVisible(true);
        ui->split_num->setVisible(true);
        ui->split_bili->setVisible(true);

    }
    if(arg1==0){
        ui->is_blackline->setChecked(false);
        ui->linksnake->setChecked(false);
        ui->label_11->setVisible(false);
        ui->label_12->setVisible(false);
        ui->is_blackline->setVisible(false);
        ui->is_blackline->setChecked(false);
        ui->split_num->setVisible(false);
        ui->split_num->setValue(1);
        ui->split_bili->setVisible(false);
        ui->split_bili->setValue(50);

    }
}

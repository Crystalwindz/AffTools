#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLine>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_text_to_pic_clicked();

    void on_pic_to_text_clicked();

    void on_move_x_check_stateChanged(int arg1);

    void on_move_x_num_valueChanged(double arg1);

    void on_move_y_check_stateChanged(int arg1);

    void on_move_y_num_valueChanged(double arg1);

    void on_up_suofang_stateChanged(int arg1);

    void on_down_suofang_stateChanged(int arg1);

    void on_left_suofang_stateChanged(int arg1);

    void on_right_suofang_stateChanged(int arg1);

    void on_up_num_valueChanged(double arg1);

    void on_down_num_valueChanged(double arg1);

    void on_left_num_valueChanged(double arg1);

    void on_right_num_valueChanged(double arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_textEdit_textChanged();

    void on_process_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_textafter_textChanged();

    void on_linksnake_stateChanged(int arg1);

    void on_splitsnake_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    double ori_move_x_num;
    double ori_move_y_num;
    double ori_up_num;
    double ori_down_num;
    double ori_left_num;
    double ori_right_num;

    QVector<QLine> ori_move_x_vec;
    QVector<QLine> ori_move_y_vec;
    QVector<QLine> ori_up_vec;
    QVector<QLine> ori_down_vec;
    QVector<QLine> ori_left_vec;
    QVector<QLine> ori_right_vec;

    int pingyi_time;
    int wucha_time;
    double biansu_beilv;

    void update_widget();
};

#endif // MAINWINDOW_H

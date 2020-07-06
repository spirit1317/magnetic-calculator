#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

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
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_checkBox_2_clicked();
    void on_toolButton_4_clicked();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_checkBox_clicked();

    void on_toolButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_9_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene_wiz;
    QGraphicsPixmapItem item_wiz;
    QGraphicsScene scene_logo;
    QGraphicsPixmapItem item_logo;
    std::string viewed_img_path;
};

#endif // MAINWINDOW_H

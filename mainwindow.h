#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include "shine.h"
#include "ipblock.h"
#include "system.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_AddBlock_clicked();

    void on_pushButton_AddBus_clicked();

private:
    Ui::MainWindow *ui;
    QVector <Shine> BusInBlock;
    System System;
    QGraphicsScene *scene;

    void DrawingBlock(int x, int y);
    void DrawingSystem();
    void DrawingConnection();

    int WIDTH = 500;
    int HEIGHT = 800;

    int HeightDrawing = 20;
    int Step = 20;

    int counterIdBus = 0;

};
#endif // MAINWINDOW_H

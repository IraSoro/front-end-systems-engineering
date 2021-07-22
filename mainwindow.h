#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>

#include "system.h"
#include "drawingobjects.h"
#include "drawingconnections.h"
#include "clickpoint.h"
#include "clickconnection.h"
#include "mainwindowblock.h"

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

    void slotFromPoint();
    void slotFromBlock();

    void on_action_triggered();
    void on_action_2_triggered();

private:
    Ui::MainWindow *ui;
    QVector <Bus> busInBlock;
    System system;
    QGraphicsScene *scene;
    ClickPoint *point;
    MainWindowBlock *windowBlock;

    void DrawingBlock(int x, int y, int index);
    void DrawingSystem();
    void DrawingConnection(int index);
    void displayTaggedLinks();

    int const WIDTH = 600;
    int const HEIGHT = 800;
    int const step = 20;

    int heightDrawing = 20;
    int counterIdBus = 0;

};
#endif // MAINWINDOW_H

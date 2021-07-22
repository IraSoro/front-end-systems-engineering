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
    QVector <Bus> busInBlock;       ///<временный вектор шин, который добавится в блок, после добавления блока в систему
    System system;                  ///<вся система
    QGraphicsScene *scene;          ///<указатель на сцену
    ClickPoint *point;              ///<указаель на класс, отвечающий за события нажатия мыши
    MainWindowBlock *windowBlock;   ///<указатель на окно, которое открывается после нажатия на блок

    /*!
     * \brief отображение блока после добавления его в систему (только название его состовных частей)
     * \param x - координата разположения блока на сцене
     * \param y - координата разположения блока на сцене
     * \param index - индекс добавляемого блока
     */
    void DrawingBlock(int x, int y, int index);

    /*!
     * \brief инициализация сцены
     */
    void DrawingSystem();

    /*!
     * \brief отображение возможных связей нового блока с имеющимися
     * \param индекст добавляемого блока
     */
    void DrawingConnection(int index);

    /*!
     * \brief отображение и редактирование системы после пометки связей
     */
    void displayTaggedLinks();

    int const WIDTH = 600;
    int const HEIGHT = 800;
    int const step = 20;

    int heightDrawing = 20;
    int counterIdBus = 0;

};
#endif // MAINWINDOW_H

#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QObject>
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


class GraphicsScene: public QObject
{
Q_OBJECT

private:
    System system;                  ///<вся система
    ClickPoint *point;              ///<указаель на класс, отвечающий за события нажатия мыши
    MainWindowBlock *windowBlock;   ///<указатель на окно, которое открывается после нажатия на блок
    QVector <Bus> busInBlock;       ///<временный вектор шин, который добавится в блок, после добавления блока в систему

private slots:
    void slotFromPoint();
    void slotFromBlock();

public:
    QGraphicsScene *scene;          ///<указатель на сцену
    GraphicsScene();
    ~GraphicsScene();


    void addBus(QString nameBus, int typeBus, int bitness, QString startAddress, QString finishAddress);
    void addBlock(QString nameBlock);

    /*!
     * \brief отображение блока после добавления его в систему (только название его составных частей)
     * \param x - координата разположения блока на сцене
     * \param y - координата разположения блока на сцене
     * \param index - индекс добавляемого блока
     */
    void DrawingBlock(int x, int y, int index);

    /*!
     * \brief отображает возможные соединения шин нового блока с имеющимися
     * \param индекст добавляемого блока
     */
    void DrawingConnection(int index);

    /*!
     * \brief отображение и редактирование системы после связывания(разъединения) шин
     */
    void displayTaggedLinks();

    void deleteSystem();

    void writtingToFile();

    void readingFile();

    int const WIDTH = 600;
    int const HEIGHT = 800;
    int const step = 20;
    int counterIdBus = 0;
};

#endif // GRAPHICKSSCENE_H

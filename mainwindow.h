#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QStringList>
#include <QMessageBox>

#include "graphicsscene.h"

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

    void on_action_triggered();
    void on_action_2_triggered();

    void on_action_4_triggered();

private:
    Ui::MainWindow *ui;
    GraphicsScene graphScene;

    int const WIDTH = 600;
    int const HEIGHT = 800;

    /*!
     * \brief инициализация сцены
     */
    void drawingSystem();

    /*!
     * \brief очистка системы
     */
    void deleteSystem();

};
#endif // MAINWINDOW_H

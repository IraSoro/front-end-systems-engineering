#ifndef MAINWINDOWBLOCK_H
#define MAINWINDOWBLOCK_H

#include <QMainWindow>
#include <QVector>

#include "shine.h"

namespace Ui {
class MainWindowBlock;
}

class MainWindowBlock : public QMainWindow
{
    Q_OBJECT

signals:
    void firstWindow();

public:
    explicit MainWindowBlock(QWidget *parent = nullptr);
    ~MainWindowBlock();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_AddBus_clicked();

private:
    Ui::MainWindowBlock *ui;

    QVector <Shine> BusInBlock;
};

#endif // MAINWINDOWBLOCK_H

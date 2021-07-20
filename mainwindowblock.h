#ifndef MAINWINDOWBLOCK_H
#define MAINWINDOWBLOCK_H

#include <QMainWindow>

namespace Ui {
class MainWindowBlock;
}

class MainWindowBlock : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowBlock(QWidget *parent = nullptr);
    ~MainWindowBlock();

private:
    Ui::MainWindowBlock *ui;
};

#endif // MAINWINDOWBLOCK_H

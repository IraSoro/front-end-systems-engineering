#ifndef MAINWINDOWBLOCK_H
#define MAINWINDOWBLOCK_H

#include <QMainWindow>

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

private:
    Ui::MainWindowBlock *ui;
};

#endif // MAINWINDOWBLOCK_H

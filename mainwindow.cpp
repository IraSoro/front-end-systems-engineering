#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    WindowBlock = new MainWindowBlock();
    connect(WindowBlock, &MainWindowBlock::firstWindow, this, &MainWindow::show);
    WindowBlock->show();
    this->close();
}

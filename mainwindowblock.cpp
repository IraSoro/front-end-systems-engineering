#include "mainwindowblock.h"
#include "ui_mainwindowblock.h"

MainWindowBlock::MainWindowBlock(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowBlock)
{
    ui->setupUi(this);
}

MainWindowBlock::~MainWindowBlock()
{
    delete ui;
}

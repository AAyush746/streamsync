#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),dialog(new Dialog(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::openNewPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::openNewPage() {
    // Create and show the new page
    dialog->exec();
    //std::cout<<"hello";
}


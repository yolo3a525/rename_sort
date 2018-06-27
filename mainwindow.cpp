#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include <iostream>
#include <string>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    QString filePath = ui->lineEdit->text();

    QDir dir(filePath);
    dir.exists(); /*判断文件夹是否存在*/
    dir.setFilter(QDir::Files); /*设置dir的过滤模式,表示只遍历本文件夹内的文件*/
    QFileInfoList fileList = dir.entryInfoList();  /*获取本文件夹内所有文件的信息*/
    int fileCount = fileList.count(); /*获取本文件夹内的文件个数*/
    for(int i=0;i<fileCount;i++)  /*遍历每个文件*/
    {
        QFileInfo fileInfo = fileList[i]; /*获取每个文件信息*/
        QString suffix = fileInfo.suffix(); /*获取文件后缀名*/
        QFile file(fileInfo.path());
        QString expre = ui->expre->text();
        expre = expre.replace(expre.indexOf('#'),1,QString::number(i +  ui->startNumber->text().toInt(), 10));

        bool a = file.rename(fileInfo.absoluteFilePath(),fileInfo.absoluteDir().absolutePath() + "/" + expre);
        std::cout << fileInfo.absoluteFilePath().toStdString() << std::endl;
        std::cout << fileInfo.absoluteDir().absolutePath().toStdString() + "/" + QString::number(i +  ui->startNumber->text().toInt(), 10).toStdString() << std::endl;
        std::cout << a << std::endl;
        std::cout.flush();
    }
    QMessageBox::information(NULL, "重命名", "完成", QMessageBox::Ok);
}

void MainWindow::on_lineEdit_selectionChanged()
{
    QString fileName = QFileDialog::getExistingDirectory(this);
    ui->lineEdit->setText(fileName);
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>
#include <QRegExp>
#include <QString>
#include <QTextBrowser>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindow::deleteNote);
    connect(ui->pasteBtn,&QPushButton::clicked,ui->textEdit,&QTextEdit::paste);
    connect(ui->copyBtn,&QPushButton::clicked,[=](){
                                                    ui->textBrowser->selectAll();
                                                    ui->textBrowser->copy();
                                                    });
    //setWindowIcon(QIcon(":/xxx.png"));
    QLabel* myLable = new QLabel;
    myLable->setText(tr(" Apache License © liukanshan1 https://github.com/liukanshan1"));
    statusBar()->addWidget(myLable);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deleteNote()
{
    this->ui->textBrowser->clear();
    QString str = ui->textEdit->toPlainText();
    QStringList strList = str.split(QLatin1Char('\n'),Qt::SkipEmptyParts);
    bool flag = false;
    //qDebug()<< "list ="<< strList;
    for(int i = 0; i< strList.size();++i)
    {
        QString temp=QString::fromStdString(deleteLine(strList.at(i).toStdString(),flag));
        if (temp.length()!=0)
        {
            this->ui->textBrowser->append(temp);
        }
    }

}

std::string MainWindow::deleteLine(std::string s,bool& flag)
{
    int i;
    int j;
    if (!flag && (i = s.find("/*")) != -1)
    {
        if ((j = s.rfind("*/",s.length()-1)) == -1)
        {
            flag = true;
            s.erase(i);
            if (s.length()!=0)
            {
                return s;
            }
            return "";
        }
        else
        {
            flag = false;
            s.erase(i,j-i+2);
            if (s.length()!=0)
            {
                return s;
            }
            return "";
        }
    }
    if (flag &&  s.find("*/") == std::string::npos)
    {
        return "";
    }
    if (flag &&  (i=s.find("*/")) != -1)
    {
        flag = false;
        s.erase(0, i+2);
        if (s.length() != 0)
        {
            return s;
        }
        return "";
    }
    if (((i = s.find("//"))) != -1)
    {
        s.erase(i);
        if (s.length() != 0)
        {
            return s ;
        }
        return "";
    }
    return s;
}

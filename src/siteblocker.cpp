#include "../headers/siteblocker.h"
#include "ui_siteblocker.h"
#include <QApplication>
#include <iostream>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <QCloseEvent>
#include <QListWidgetItem>
using namespace std;
QListWidgetItem* item[100];
string backuplines;
int itemNum = 0;
bool saved = true;
QString selectedWebsites[100];
siteblocker::siteblocker(QWidget *parent) :
    DMainWindow(parent),
    ui(new Ui::siteblocker)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->gridLayoutWidget);
    QFont font;
    font.setFamily("droid sans");
    font.setPointSize(9);
    ui->pushButton->setFont(font);
    siteblocker::setFont(font);
    ui->pushButton_2->setFont(font);
    ui->lineEdit->setFont(font);
    ui->lineEdit->setPlaceholderText("Enter a website e.g. www.example.com");
    ui->listWidget->setFont(font);
    string line;
    string temp[2];
    QString website;
    string oldwebsite;
//    bool shouldBackup = true;
#ifdef Q_OS_LINUX
    ifstream host("/etc/hosts");
    ofstream backup("/tmp/hostsbackuplines.txt");
#endif
#ifdef Q_OS_WIN
    ifstream host("C:\\Windows\\System32\\Drivers\\etc\\hosts");
    ofstream backup("C:\\Temp\\hostsbackuplines.txt");
#endif
    while (getline(host, line)) {
        stringstream hosts(line);
        hosts >> temp[0];
        if(temp[0] != "127.0.0.1"){
            hosts >> temp[1];
            backup << line << endl;
            if(temp[0] == "#127.0.0.1"){
                if(temp[1] != oldwebsite && temp[1] != "localhost"){
                    oldwebsite = temp[1];
                    website = QString(temp[1].c_str());
                    item[itemNum] = new QListWidgetItem(website, ui->listWidget);
                    selectedWebsites[itemNum] = website;
                    item[itemNum]->setFlags(item[itemNum]->flags() | Qt::ItemIsUserCheckable);
                    item[itemNum]->setCheckState(Qt::Unchecked);
                    itemNum++;
                    //shouldBackup = false;
            }
            }
        }else{
            hosts >> temp[1];
            if(temp[1] == "www.redtube.com"){
                backup << line << endl;
            }
            if(temp[1] == "www.xnxx.com"){
                backup << line << endl;
            }
            if(temp[1] != oldwebsite && temp[1] != "localhost" && temp[1] != "www.redtube.com" && temp[1] != "www.xnxx.com"){
                oldwebsite = temp[1];
                website = QString(temp[1].c_str());
                item[itemNum] = new QListWidgetItem(website, ui->listWidget);
                selectedWebsites[itemNum] = website;
                item[itemNum]->setFlags(item[itemNum]->flags() | Qt::ItemIsUserCheckable);
                item[itemNum]->setCheckState(Qt::Checked);
                itemNum++;
       }
     }

    }
    host.close();
    backup.close();
}

siteblocker::~siteblocker()
{
    delete ui;
}

void siteblocker::closeEvent(QCloseEvent *event){
    if(saved){
        event->accept();
    }else{
        QMessageBox bt;
        bt.setWindowTitle("Not saved");
        bt.setIcon(QMessageBox::Icon::Warning);
        bt.setText("You haven't saved the list. Would you like to save and close the program?");
        bt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        bt.setDefaultButton(QMessageBox::Yes);
        int buttons = bt.exec();
        switch(buttons){
        case QMessageBox::Yes:
            siteblocker::on_pushButton_2_clicked();
            break;
        case QMessageBox::No:
            event->accept();
            break;
        }
    }
}

QString textofline;

void siteblocker::on_pushButton_clicked()
{

    if(ui->lineEdit->text() != nullptr){
    textofline = ui->lineEdit->text();

    item[itemNum] = new QListWidgetItem(textofline, ui->listWidget);
    selectedWebsites[itemNum] = textofline;
    item[itemNum]->setFlags(item[itemNum]->flags() | Qt::ItemIsUserCheckable);
    item[itemNum]->setCheckState(Qt::Checked);
    itemNum++;
    saved = false;
    }
    ui->lineEdit->setText("");
    
}


void siteblocker::on_pushButton_2_clicked()
{
    bool success = false;
    string line;
#ifdef Q_OS_LINUX
    ofstream host;
    host.open("/etc/hosts");
    ifstream backup;
    backup.open("/tmp/hostsbackuplines.txt");
#endif
#ifdef Q_OS_WIN
    ofstream host("C:\\Windows\\System32\\Drivers\\etc\\hosts");
    ifstream backup("C:\\Temp\\hostsbackuplines.txt");
#endif
    while (getline(backup, line)) {
        if(host << line << endl){
            success = true;
        }else{
            success = false;
        }
    }
    backup.close();
    for(int x = 0; x<itemNum; x++){
        if(item[x]->checkState()){
            cout << selectedWebsites[x].toStdString() << endl;
            if(host << "127.0.0.1 " << selectedWebsites[x].toStdString() << endl){
                success = true;
            }else{
                success = false;
            }
        }
    }
    QFont font;
    font.setPointSize(9);
    font.setFamily("droid sans");
    font.setBold(false);
    QMessageBox message;
    message.setFont(font);
    message.setStandardButtons(QMessageBox::Ok);
    //message.setStyleSheet("QLabel{min-width:300 px;} QPushButton{ width:55px; font-size: 18px; }");

        if(success){
            message.setWindowTitle("Success");
            message.setText("Done");
            message.exec();
        }else{
            message.setWindowTitle("Failed");
            message.setText("You should have administrative privileges to do so");
            message.setIcon(QMessageBox::Icon::Critical);
            message.exec();

        }
        host.close();
        backup.close();
        saved = true;
}

void siteblocker::on_lineEdit_returnPressed()
{
    siteblocker::on_pushButton_clicked();
}

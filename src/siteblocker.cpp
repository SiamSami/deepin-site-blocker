#include "../headers/siteblocker.h"
#include "ui_siteblocker.h"
#include <DApplication>
#include <iostream>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <QListWidgetItem>
using namespace std;
int storage = 1;
QListWidgetItem* item[100];
string backuplines;
int itemNum = 0;
QString selectedWebsites[100];
siteblocker::siteblocker(QWidget *parent) :
    DMainWindow(parent),
    ui(new Ui::siteblocker)
{
    ui->setupUi(this);
    string line;
    string temp[2];
    QString website;
    string oldwebsite;
    ifstream host("/etc/hosts");
    ofstream backup("/tmp/hosts backup lines.txt");
    while (getline(host, line)) {
        stringstream hosts(line);
        hosts >> temp[0];
        if(temp[0] != "127.0.0.1" || line == "127.0.0.1\tlocalhost"){
           backup << line << endl;
        }else{
            hosts >> temp[1];
            if(temp[1] != oldwebsite && temp[1] != "localhost"){
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
    cout << itemNum << endl;
    host.close();
    backup.close();
}

siteblocker::~siteblocker()
{
    delete ui;
}

QString textofline;

void siteblocker::on_pushButton_clicked()
{
    if(ui->lineEdit->text() != NULL){
    textofline = ui->lineEdit->text();

    item[itemNum] = new QListWidgetItem(textofline, ui->listWidget);
    selectedWebsites[itemNum] = textofline;
    item[itemNum]->setFlags(item[itemNum]->flags() | Qt::ItemIsUserCheckable);
    item[itemNum]->setCheckState(Qt::Checked);
    itemNum++;
    }
    
}

void listWidgets(){

}

void siteblocker::on_pushButton_2_clicked()
{
    bool success;
    string line;
    ofstream host("/etc/hosts");
    ifstream backup("/tmp/hosts backup lines.txt");
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
        if(success){
            QMessageBox done;
            done.setWindowTitle("Message");
            done.setText("Done");
            done.setStandardButtons(QMessageBox::Ok);
            done.exec();
        }else{
            QMessageBox undone;
            undone.setWindowTitle("Message");
            undone.setText("For some reason, it failed :(");
            undone.setStandardButtons(QMessageBox::Ok);
            undone.exec();

        }
        host.close();
}

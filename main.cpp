#include "siteblocker.h"
#include <DApplication>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE

int main(int argc, char *argv[])
{

    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    a.setApplicationName("Deepin site blocker");
    a.setApplicationVersion("Beta");
    if(geteuid() == 0){
        std::cout << "You are root\n";
    }else{
        std::cout << "Not root!\n";
    }
    siteblocker w;
    w.setWindowTitle("Deepin site blocker");
    w.show();

    return a.exec();
}

#include "../headers/siteblocker.h"
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
    a.setWindowIcon(QIcon("/home/toor/Desktop/Programming/deepin-site-blocker-beta/Icon.png"));
    a.setApplicationName("Site blocker");
    a.setApplicationVersion("1.0");
    a.setApplicationDescription("It is a simple site blocking program written in DTK (Deepin Tool Kit) & Qt");
    a.setProductIcon(QIcon("/home/toor/Desktop/Programming/deepin-site-blocker-beta/Icon.png"));
    a.setProductName("Site blocker");
    a.setApplicationLicense("GNU GPL 3");
    a.setApplicationHomePage("https://github.com/SiamSami/site-blocker");
    a.setApplicationAcknowledgementPage("https://github.com/SiamSami/site-blocker");
#ifdef Q_OS_LINUX
    if(geteuid() == 0){
        std::cout << "You are root\n";
    }else{
        std::cout << "Not root!\n";
        //exit(1);
    }
#endif
    siteblocker w;
    w.setWindowTitle("Site blocker");
    w.show();

    return a.exec();
}

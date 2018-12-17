#include "../headers/siteblocker.h"
#include <DApplication>
#include <DAboutDialog>
#include <unistd.h>
#include <DWidgetUtil>
#include <QMessageBox>
#include <iostream>
#include <sys/types.h>
DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE

int main(int argc, char *argv[])
{

    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    DAboutDialog dialog;
    QFont font;
    font.setFamily("droid sans");
    font.setPointSize(9);
    dialog.setWebsiteLink("https://github.com/SiamSami/site-blocker");
    dialog.setFont(font);
    dialog.setLicense("Licensed under GNU GPL 3");
    dialog.setVersion("Version 1.0");
    dialog.setProductName("Site blocker");
    dialog.setWebsiteName("Made by Siam Sami");
    dialog.setAcknowledgementVisible(false);
    dialog.setCompanyLogo(QPixmap());
    a.setAboutDialog(&dialog);
    a.setFont(font);
    a.setApplicationName("Site blocker");
    a.setStyle("dlight");

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

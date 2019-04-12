#ifndef SITEBLOCKER_H
#define SITEBLOCKER_H

#include <DMainWindow>
DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE

namespace Ui {
class siteblocker;
}

class siteblocker : public DMainWindow
{
    Q_OBJECT

public:
    explicit siteblocker(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event);
    ~siteblocker();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_lineEdit_returnPressed();

private:
    Ui::siteblocker *ui;
};

#endif // SITEBLOCKER_H

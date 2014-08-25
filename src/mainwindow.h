#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <o2.h>
#include <o2requestor.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onOpenBrowser(QUrl url);

private:
    Ui::MainWindow *ui;
    O2 *hubicCon;
    O2Requestor *hubicReq;
private slots:
    void onHubicPressed();
};

#endif // MAINWINDOW_H

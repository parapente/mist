#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include "hubicconnection.h"
#include "mistremotefsmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    HubicConnection *hubicCon;
    mistRemoteFSModel *model;

public slots:
    void hubicLinkToggle(void);

private slots:
    void treeViewContextMenu(const QPoint& pos);
};

#endif // MAINWINDOW_H

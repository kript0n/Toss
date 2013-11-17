#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include "toss.h"

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
    toss* draw;

    void writeTeamsList(QStringList teamsList);
    int tossNumber;

private slots:
    void getAddTeamButtonClicked();
    void getTossButtonClicked();
};

#endif // MAINWINDOW_H

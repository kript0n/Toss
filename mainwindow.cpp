#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromUtf8("Программа жеребьевки"));
    draw = new toss();
    ui->teamsTable->setColumnCount(1);
    ui->teamsTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromUtf8("Название")));
    QObject::connect(ui->addTeamButton, SIGNAL(clicked()), this, SLOT(getAddTeamButtonClicked()));
    QObject::connect(ui->tossButton, SIGNAL(clicked()), this, SLOT(getTossButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getAddTeamButtonClicked() {
    QString teamName= ui->teamName->text();
    if(teamName != "") {
        if(draw->addTeam(teamName) == -1) {
            QMessageBox* mess = new QMessageBox();
            mess->setWindowTitle(QString::fromUtf8("Ошибка"));
            mess->setText(QString::fromUtf8("Команда с таким названием уже существует"));
            mess->setStandardButtons(QMessageBox::Ok);
            mess->setDefaultButton(QMessageBox::Ok);
            mess->exec();
            delete mess;
            return;
        }
        ui->teamName->setText("");
        QStringList teamList = draw->getTeamList();
        writeTeamsList(teamList);
        tossNumber = 0;
    }
    return;
}

void MainWindow::getTossButtonClicked() {
    tossResult _tossResult = draw->tossTeams();
    tossNumber++;
    QFile roundFile(QString("тур%1.html").arg(tossNumber));
    roundFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&roundFile);
    while(_tossResult.haveAliances()) {
        out<<QString("<html><head><title>Тур %1</title></head><body><table border=\"1px\" align=\"center\"><tr><td>Первый альянс</td><td>Второй альянс</td></tr>").arg(tossNumber);
        out<<"<tr>";

        QPair<aliance, aliance> opponents = _tossResult.getOneOpponents();
        QString firstAlianceFirstTeamName = opponents.first.getFirstTeamName();
        QString firstAlianceSecondTeamName = opponents.first.getSecondTeamName();
        QString secondAlianceFirstTeamName = opponents.second.getFirstTeamName();
        QString secondAlianceSecondTeamName = opponents.second.getSecondTeamName();

        out<<QString("<td>%1<br />%2</td>").arg(firstAlianceFirstTeamName).arg(firstAlianceSecondTeamName);
        out<<QString("<td>%1<br />%2</td>").arg(secondAlianceFirstTeamName).arg(secondAlianceSecondTeamName);

        out <<"</tr>";
    }
    out << "</table></body></html>";
    roundFile.close();
}

void MainWindow::writeTeamsList(QStringList teamsList) {
    ui->teamsTable->setRowCount(teamsList.size());
    for(int i=0;i<teamsList.size();i++) {
        QTableWidgetItem* teamName = new QTableWidgetItem(teamsList.at(i));
        ui->teamsTable->setItem(i, 0, teamName);
    }
}

#ifndef TOSS_H
#define TOSS_H

#include <QPair>
#include <QMessageBox>
#include <QTime>
#include <utility>

#include "structs.h"

class toss {

public:
    toss();
    ~toss();

    int addTeam(QString name);
    void deleteTeam(QString teamName);
    void deleteTeam(int teamID);
    tossResult tossTeams();
    int getTossNum() const;
    QVector<aliance> getAliances();
    QStringList getTeamList();

private:

    QVector<team> teams;
    QVector <aliance> aliances;
    QVector< QPair<aliance, aliance> > aliancesOpponents;

    int teamNum;
};

#endif // TOSS_H

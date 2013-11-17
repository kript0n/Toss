#include "toss.h"

toss::toss() {
    teamNum = 0;
}

toss::~toss() {
}

int toss::addTeam(QString teamName) {
    QString buf= "";
    for(int i=0;i<teams.size();i++){
        buf = teams.at(i).getTeamName();
        if(QString::compare(teamName, buf) == 0) {
            return -1;
        }
    }
    team newTeam;
    newTeam.setTeamName(teamName);
    newTeam.setID(teamNum++);
    teams.push_back(newTeam);
    return 0;
}

void toss::deleteTeam(QString teamName) {
    QString buf = "";
    for(int i=0;i<teams.size();i++) {
        buf = teams.at(i).getTeamName();
        if(QString::compare(teamName, buf) == 0) {
            //teams.erase(curr);
            return;
        }
    }

}

void toss::deleteTeam(int teamID){
    return;
}

QVector<aliance> toss::getAliances() {
    QVector< aliance > _aliances;
    QVector< team > usedTeams;
    QVector< team > possibleTeams;

    QVector< team >::Iterator firstTeamIter;
    for(firstTeamIter=teams.begin();firstTeamIter<teams.end();firstTeamIter++) {

        team firstAlianceTeam = *firstTeamIter;

        QVector< team >::Iterator usedTeamsIter;
        bool existFirstTeam = false;
        for(usedTeamsIter=usedTeams.begin();usedTeamsIter<usedTeams.end();usedTeamsIter++) {
            if(firstAlianceTeam == (*usedTeamsIter)) {
                existFirstTeam = true;
                break;
            }
        }
        if(existFirstTeam) {
            continue;
        }

        QVector< team >::Iterator secondTeamIter;
        for(secondTeamIter=teams.begin();secondTeamIter<teams.end();secondTeamIter++) {
            if(firstTeamIter != secondTeamIter) {

                team curOpponentTeam = *secondTeamIter;

                bool existSecondTeam = false;
                for(usedTeamsIter=usedTeams.begin();usedTeamsIter<usedTeams.end();usedTeamsIter++) {
                    if((*usedTeamsIter) == curOpponentTeam) {
                        existSecondTeam = true;
                        break;
                    }
                }
                if(existSecondTeam) {
                    continue;
                }


                QVector< aliance >::Iterator iter;
                aliance alianceforCheck;
                alianceforCheck.setFirstTeam(firstAlianceTeam);
                alianceforCheck.setSecondTeam(curOpponentTeam);

                bool existAliance = false;
                for(iter=aliances.begin();iter<aliances.end();iter++) {
                    if((*iter) == alianceforCheck)
                    {
                        existAliance = true;
                        break;
                    }
                }
                if(existAliance) {
                    continue;
                }

                team newPossibleTeam = curOpponentTeam;
                possibleTeams.push_back(newPossibleTeam);
            }
        }

        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        int randRange = possibleTeams.size();
        int opponentIndex;
        if(randRange != 0) {
             opponentIndex = qrand()%randRange;
        }
        else {
            possibleTeams.clear();
            continue;
        }

        team secondAlianceTeam = possibleTeams.at(opponentIndex);

        aliance newAliance;
        newAliance.setFirstTeam(firstAlianceTeam);
        newAliance.setSecondTeam(secondAlianceTeam);

        _aliances.push_back(newAliance);
        aliances.push_back(newAliance);

        usedTeams.push_back(firstAlianceTeam);
        usedTeams.push_back(secondAlianceTeam);

        QMessageBox mess;
        mess.setText(QString("Первая команда %2\r\nВторая команда %3").arg(firstAlianceTeam.getTeamName()).arg(secondAlianceTeam.getTeamName()));
        mess.exec();
        possibleTeams.clear();

    }
    return _aliances;
}

tossResult toss::tossTeams() {
    tossResult _tossResult;
    QVector< aliance > possibleAliances;
    QVector< aliance > usedAliances;
    QVector< aliance > _aliances;
    _aliances = getAliances();
    for(int i=0;i<_aliances.size();i++) {

        aliance firstAliance = _aliances.at(i);

        QVector< aliance >::Iterator usedAliancesIter;
        bool firstAlianceExist = false;
        for(usedAliancesIter=usedAliances.begin();usedAliancesIter<usedAliances.end();usedAliancesIter++) {
            if(*usedAliancesIter == firstAliance) {
                firstAlianceExist = true;
                break;
            }
        }
        if(firstAlianceExist) {
            continue;
        }


        for(int j=0;j<_aliances.size();j++) {

            if(i!=j) {

                aliance curSecondAliance = _aliances.at(j);

                bool secondAlianceExist = false;
                for(usedAliancesIter=usedAliances.begin();usedAliancesIter<usedAliances.end();usedAliancesIter++) {
                    if(*usedAliancesIter == curSecondAliance) {
                        secondAlianceExist = true;
                    }
                }
                if(secondAlianceExist) {
                    continue;
                }

                bool exist = false;
                QVector< QPair<aliance, aliance> >::Iterator iter;
                for(iter=aliancesOpponents.begin();iter<aliancesOpponents.end();iter++) {
                    if(((*iter).first == firstAliance && (*iter).second == curSecondAliance)
                            || ((*iter).first == curSecondAliance && (*iter).second == firstAliance))
                    {
                           exist = true;
                           break;
                    }
                }
                if(exist) {
                    continue;
                }

                aliance newPossibleAliance = curSecondAliance;
                possibleAliances.push_back(newPossibleAliance);
            }
        }

        int randRange = possibleAliances.size();
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        int secondOpponentID;
        if(randRange!=0) {
            secondOpponentID = qrand()%randRange;
        }
        else {
            possibleAliances.clear();
            continue;
        }

        aliance secondAliance = possibleAliances.at(secondOpponentID);

        QPair<aliance, aliance> newOpponents;
        newOpponents.first = firstAliance;
        newOpponents.second = secondAliance;
        aliancesOpponents.push_back(newOpponents);

        _tossResult.setAliances(firstAliance, secondAliance);

        usedAliances.push_back(firstAliance);
        usedAliances.push_back(secondAliance);

        possibleAliances.clear();

    }
    return _tossResult;
}


QStringList toss::getTeamList() {
    QStringList teamsList;
    for(int i=0;i<teams.size();i++) {
        QString teamName = teams.at(i).getTeamName();
        teamsList.push_back(teamName);
    }
    return teamsList;
}


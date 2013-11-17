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
    int alianceNum = 0;
    QVector< aliance > _aliances;
    QVector < aliance > aliancesBuffer;
    QVector< team > usedTeams;
    QVector< team > possibleTeams;

    while(alianceNum < teams.size()/2) {

        _aliances.clear();
        aliancesBuffer.clear();
        usedTeams.clear();
        possibleTeams.clear();

        QVector< team >::Iterator firstTeamIter;
        for(firstTeamIter=teams.begin();firstTeamIter<teams.end();firstTeamIter++) {

            team firstAlianceTeam = *firstTeamIter;
            int firstTeamGames = firstAlianceTeam.getGamesNum();

            if(firstAlianceTeam.getGamesNum() == 5) {
                continue;
            }

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

                    if(curOpponentTeam.getGamesNum() == 5 ) {
                        continue;
                    }

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
                    if(!existAliance) {
                        for(iter=aliancesBuffer.begin();iter<aliancesBuffer.end();iter++) {
                            if(*iter == alianceforCheck) {
                                existAliance = true;
                                break;
                            }
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

            QVector<team> possibleTeamsMin;
            QVector<team>::Iterator teamsMinIter;
            for(teamsMinIter=possibleTeams.begin();teamsMinIter<possibleTeams.end();teamsMinIter++) {
                if(teamsMinIter->getGamesNum() < firstTeamGames) {
                    possibleTeamsMin.push_back(*teamsMinIter);
                }
            }

            int randRange;

            bool minExist = false;
            if(possibleTeamsMin.size() > 0) {
                randRange = possibleTeamsMin.size();
                minExist = true;
            }
            else {
                randRange = possibleTeams.size();
            }

            int opponentIndex;
            if(randRange != 0) {
                 opponentIndex = qrand()%randRange;
            }
            else {
                possibleTeams.clear();
                continue;
            }

            team secondAlianceTeam = (minExist) ? possibleTeamsMin.at(opponentIndex) : possibleTeams.at(opponentIndex);

            aliance newAliance;
            newAliance.setFirstTeam(firstAlianceTeam);
            newAliance.setSecondTeam(secondAlianceTeam);

            _aliances.push_back(newAliance);
            aliancesBuffer.push_back(newAliance);

            usedTeams.push_back(firstAlianceTeam);
            usedTeams.push_back(secondAlianceTeam);

            alianceNum++;

            QMessageBox mess;
            mess.setText(QString("Первая команда %2\r\nВторая команда %3").arg(firstAlianceTeam.getTeamName()).arg(secondAlianceTeam.getTeamName()));
            mess.exec();

            possibleTeams.clear();
            possibleTeamsMin.clear();

        }
    }

    QVector< aliance >::Iterator copyIter;
    for(copyIter=aliancesBuffer.begin();copyIter<aliancesBuffer.end();copyIter++) {
        aliances.push_back(*copyIter);
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
        int firstAlianceGames = firstAliance.getAlianceGamesSum();

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


        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

        QVector < aliance > possibleAliancesMin;
        QVector< aliance >::Iterator aliancesMinIter;
        for(aliancesMinIter=possibleAliances.begin();aliancesMinIter<possibleAliances.end();aliancesMinIter++) {
            if(aliancesMinIter->getAlianceGamesSum() < firstAlianceGames) {
                possibleAliancesMin.push_back(*aliancesMinIter);
            }
        }


        int randRange;
        bool minExist = false;
        if(possibleAliancesMin.size()>0) {
            randRange = possibleAliancesMin.size();
            minExist = true;
        }
        else {
            randRange = possibleAliances.size();
        }

        int secondOpponentID;
        if(randRange!=0) {
            secondOpponentID = qrand()%randRange;
        }
        else {
            possibleAliances.clear();
            continue;
        }

        aliance secondAliance = (minExist) ? possibleAliancesMin.at(secondOpponentID) : possibleAliances.at(secondOpponentID);

        QVector<team>::Iterator incGamesIter;

        for(incGamesIter=teams.begin();incGamesIter<teams.end();incGamesIter++) {
            if((*incGamesIter) == firstAliance.getFirstTeam() || (*incGamesIter) == firstAliance.getSecondTeam()) {
                incGamesIter->incGames();
            }
            if((*incGamesIter) == secondAliance.getFirstTeam() || (*incGamesIter) == secondAliance.getSecondTeam()) {
                incGamesIter->incGames();
            }
        }

        QPair<aliance, aliance> newOpponents;
        newOpponents.first = firstAliance;
        newOpponents.second = secondAliance;
        aliancesOpponents.push_back(newOpponents);

        _tossResult.setAliances(firstAliance, secondAliance);

        usedAliances.push_back(firstAliance);
        usedAliances.push_back(secondAliance);

        possibleAliances.clear();
        possibleAliancesMin.clear();

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


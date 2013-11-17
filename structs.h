#ifndef STRUCTS_H
#define STRUCTS_H

#include <QVector>
#include <QString>
#include <QStringList>

struct team {

private:
    QString teamName;
    int teamID;
    int games;

public:

    team() {
        games = 0;
    }

    ~team() {

    }

    bool operator== (const team &_team){
        return teamName == _team.getTeamName();
    }

    void setTeamName(QString _teamName) {
        teamName = _teamName;
    }

    void setID(int ID) {
        teamID = ID;
    }

    QString getTeamName() const {
        return teamName;
    }

    int getTeamID() const {
        return teamID;
    }

    int getGamesNum() const {
        return games;
    }

    void incGames() {
        games++;
    }

};








struct aliance {

private:
    team firstTeam;
    team secondTeam;


public:

    aliance() {

    }

    ~aliance() {

    }
public:


    bool operator== (const aliance& _aliance) {
        return ((getFirstTeamName() == _aliance.getFirstTeamName() && getSecondTeamName() == _aliance.getSecondTeamName()) ||
                (getSecondTeamName() == _aliance.getFirstTeamName() && getFirstTeamName() == _aliance.getSecondTeamName()));
    }



    QString getFirstTeamName () const {
       return firstTeam.getTeamName();
    }



    QString getSecondTeamName() const {
        return secondTeam.getTeamName();
    }



    int getFirstTeamID () {
        return firstTeam.getTeamID();
    }



    int getSecondTeamID() {
         return secondTeam.getTeamID();
    }



    void setFirstTeam(const team& _team) {
        this->firstTeam = _team;
    }



    void setSecondTeam(const team& _team) {
        secondTeam = _team;
    }

    int getAlianceGamesSum() const {
        return firstTeam.getGamesNum() + secondTeam.getGamesNum();
    }

    team getFirstTeam() const {
        return firstTeam;
    }

    team getSecondTeam() const {
        return secondTeam;
    }


};







struct tossResult {

private:
    QVector< QPair<aliance, aliance> > _tossResult;

public:

    tossResult(){

    }

    ~tossResult() {

    }

    void setAliances(aliance firstAliance, aliance secondAliance) {
        QPair< aliance, aliance > opponents;
        opponents.first = firstAliance;
        opponents.second = secondAliance;
        _tossResult.push_back(opponents);
    }

    QPair<aliance, aliance> getOneOpponents() {
        QPair<aliance, aliance> opponents;
        if(!_tossResult.isEmpty()) {
            opponents = _tossResult.last();
            _tossResult.pop_back();
        }
        return opponents;

    }

    bool haveAliances() {
        if(_tossResult.isEmpty()) {
            return false;
        }
        else {
            return true;
        }
    }
};

#endif // STRUCTS_H

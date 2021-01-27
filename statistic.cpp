#include "statistic.h"

Statistic::Statistic(QObject *parent) : QObject(parent),
    points_(0),encountered_passengers(0)
{
    readScoreFile(SCOREFILE);
}

Statistic::~Statistic()
{
    writeScoreFile(SCOREFILE);
}

void Statistic::readScoreFile(std::string filename)
{
    std::ifstream input(filename);
    // checks that file exists
    if(input.is_open()){
        std::string row;
        while (std::getline(input,row)){
            std::vector<std::string> v = split(row,':',false);
            int p = std::stoi(v.at(1));
            QString n = QString::fromStdString(v.at(0));
            QTime t = QTime(0,std::stoi(v.at(2)),std::stoi(v.at(3)));
            result r = {p,n,t};
            result_list.push_back(r);
        }
        input.close();
        qDebug()<<"SCOREFILE READ";
    }else{
        qDebug()<<"NOT FOUND FILE"<<QString::fromStdString(filename);
    }
}

void Statistic::writeScoreFile(std::string filename)
{
    qDebug()<<"SCOREFILE WRITING";
    std::ofstream file(filename);
        for (auto result : result_list){
            file<<result.nick.toStdString()<<":"<<result.points<<":"
               <<result.time.minute()<<":"<<result.time.second()<<"\n";
        }
        file.close();
}

void Statistic::clear()
{
    points_ = 0;
    nick_name = "";
    encountered_passengers=0;
    emit displayPoints(points_);
}

void Statistic::setGame(bool mode, QString nick)
{
    isCompetitive = mode;
    nick_name = nick;
}

bool Statistic::IsCompetitive() const
{
    return isCompetitive;
}

Statistic::result Statistic::getResult()
{
    return latest_result;
}

std::vector<Statistic::result> Statistic::getResultList()
{
    return result_list;
}

void Statistic::finalizeResult(QTime time)
{
    latest_result = {points_,nick_name,time};
}

std::vector<std::string> Statistic::split(const std::string &s,
                                       const char delimiter, bool ignore_empty)
{
    std::vector<std::string> result;
        std::string tmp = s;

        while(tmp.find(delimiter) != std::string::npos){
            std::string new_part = tmp.substr(0, tmp.find(delimiter));
            tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
            if(not (ignore_empty and new_part.empty())){
                result.push_back(new_part);
            }
        }
        if(not (ignore_empty and tmp.empty())){
            result.push_back(tmp);
        }
        return result;
}

void Statistic::pointsCollected(int value)
{
    points_ += value;
    emit displayPoints(points_);
}

void Statistic::saveResult(bool save)
{
    if (save and isCompetitive){
        result_list.push_back(latest_result);
    }
}

void Statistic::passengersEncountered(int amount)
{
    encountered_passengers += amount;
}

#ifndef STATISTIC_H
#define STATISTIC_H

#include <QObject>
#include <QDebug>
#include <fstream>
#include <QTime>
#include <string>

const std::string SCOREFILE = ".scores.txt";

/*!
 * \brief The Statistic class. Keeps track of points,
 * player nickname, and deals with result saving.
 * Reads and writes top 10 scorefile.
 */
class Statistic : public QObject
{
    Q_OBJECT
public:  
    struct result { // for saving results
        int points;
        QString nick;
        QTime time;
    };

    /*!
     * \brief constructor of Statistic class
     * \param parent object
     * calls readscorefile
     */
    explicit Statistic(QObject *parent = nullptr);

    /*!
     * \brief destructor
     * calls write scorefile
     */
    ~Statistic();

    /*!
     * \brief readScoreFile function reads scorefile
     * \param filename, file that is the scorefile
     * fileformat: .txt and rows like
     * nickname:points:time minutes:time seconds
     * example:
     * Teemu:156:3:10
     */
    void readScoreFile(std::string filename);

    /*!
     * \brief writeScoreFile fuction writes scorefile
     * \param filename, file to write on
     * Writen fileformat is same as in readScoreFile.
     */
    void writeScoreFile(std::string filename);

    /*!
     * \brief clears Statistics private values:
     * points, encountered passengers, nickname
     */
    void clear();

    /*!
     * \brief setGame sets up current game
     * \param mode, game mode true if competitive
     * \param nick, players nickname
     */
    void setGame(bool mode,QString nick);

    /*!
     * \brief IsCompetitive
     * \return true if competitive
     */
    bool IsCompetitive() const;

    /*!
     * \brief getResult
     * \return returns latest result that is finalized
     */
    result getResult();

    /*!
     * \brief getResultList
     * \return returns full list of results
     */
    std::vector<result> getResultList();

    /*!
     * \brief finalizeResult
     * \param time, gametime of current game
     * sets latest_result to current game result
     */
    void finalizeResult(QTime time);

    /**
         * @brief good old split function. Splits string into vector
         * @param string to split
         * @param delimiter of splitting
         * @param save emptys to vector?
         */
    std::vector<std::string> split(const std::string& s, const char delimiter,
                             bool ignore_empty=true);
public slots:
    /*!
     * \brief pointsCollected
     * \param value of points
     * adds poits and emits display points
     */
    void pointsCollected(int value);

    /*!
     * \brief passengersEncountered
     * \param amount of passengers
     */
    void passengersEncountered(int amount);

    /*!
     * \brief saveResult
     * \param save true if want to save
     * adds latest result to list if needed
     */
    void saveResult(bool save);

signals:
    /*!
     * \brief displayPoints emited when points are changed
     * \param points, amount of points
     */
    void displayPoints(int points);

private:
    std::vector<result> result_list;
    int points_;
    QString nick_name;
    bool isCompetitive;
    result latest_result;
    int encountered_passengers;
};

#endif // STATISTIC_H

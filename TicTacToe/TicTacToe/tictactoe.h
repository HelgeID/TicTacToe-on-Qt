#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QtDebug>
#include <QTime>
#include <QMap>
#include <QMessageBox>
#include <QIcon>

#include <algorithm>

namespace tictactoe {
    enum flag {NO, YES};
    class TicTacToe
    {
    private:
        void overwrite_index(int**);
        void overwrite_comb(QMap<QString, QChar>, QChar**);
        unsigned int player;
        bool stats;
        QChar tic;
        QChar toe;
        int counterX;
        int counter0;

    public:
        QMap<QString, QChar> map;
        QChar Step();
        void setActive(QChar);
        QChar takeTic() {return tic;}
        QChar takeToe() {return toe;}

        //methods for counter
        void winTic() {counterX++;}
        void winToe() {counter0++;}
        void reset_count() {counterX = 0; counter0 = 0;}
        int get_count_tic() {return counterX;}
        int get_count_toe() {return counter0;}

        void setPlayer(unsigned int);
        void setStats(bool);
        unsigned int getPlayer();
        bool getStats();
        void processingGame();
        uint ai(QMap<QString, QChar>, QChar);

    public:
        bool win;
        bool draw;
        bool move_pc;
        TicTacToe(void):
            //initialization:
            player(2),
            stats(false),
            tic(' '), toe('0'),
            win(false), draw(false), move_pc(false)
        {
//            QTime t(0,0,0);
//            qsrand(t.secsTo(QTime::currentTime()));
//            (qrand()&1)?qDebug()<<true:qDebug()<<false;
            map["1"] = '1';
            map["2"] = '2';
            map["3"] = '3';
            map["4"] = '4';
            map["5"] = '5';
            map["6"] = '6';
            map["7"] = '7';
            map["8"] = '8';
            map["9"] = '9';

            counterX = 0;
            counter0 = 0;
        }

        ~TicTacToe(void)
        {
        }
    };
}

#endif // TICTACTOE_H

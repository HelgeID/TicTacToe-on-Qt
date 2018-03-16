#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QTimer>
#include <QPushButton>
#include <QMessageBox>
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>
#include <QLabel>

#include "tictactoe.h"
#include "about.h"

#define stepPC "move pc ..."
#define stepPlayer "your move ..."
#define stepX "move tic (X) ..."
#define step0 "move toe (0) ..."
#define stepNewGame "please start a new game..."

using tictactoe::TicTacToe;

namespace Ui {
    class MainWindow;
}

class MyThread: public QThread
{
    Q_OBJECT

public:
    bool expectf;
    void run();
};

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(TicTacToe &object, QWidget *parent = 0);
    ~MainWindow();

    void ShowMsg()
    {
        QMessageBox msg;
        msg.setText("MSG");
        msg.exec();
    }

    TicTacToe *object;
    QTimer *timer;
    MyThread *thread;

    QString processing_text(QString, QString);

    void clickedBtn(const int, bool&);
    void clickedBtn_finish();
    void lockedBtn(Ui::MainWindow*);
    void unlockedBtn(Ui::MainWindow*);
    void cleartextBtn();

    void CreatingMenus();
    void Initialization();
    void UpdateStatistics();

    void step();
    void block();
    void unblock();

private:
    Ui::MainWindow *ui;
    const int size;
    QPushButton **arrBtns;

    QAction *game_new;
    QAction *game_exit;
    QAction *options_parameters;
    QAction *help_about;

    About *aboutWindow;

    QLabel *sb_text;

private slots:
    void AutoClickReceived(uint);
    void OptClicked();
    void OkClicked();
    void CancelClicked();

    void on_btn1_clicked(bool autoflg=0);
    void on_btn2_clicked(bool autoflg=0);
    void on_btn3_clicked(bool autoflg=0);
    void on_btn4_clicked(bool autoflg=0);
    void on_btn5_clicked(bool autoflg=0);
    void on_btn6_clicked(bool autoflg=0);
    void on_btn7_clicked(bool autoflg=0);
    void on_btn8_clicked(bool autoflg=0);
    void on_btn9_clicked(bool autoflg=0);

    void GameNew();
    void GameExit();
    void OptionsParameters();
    void HelpAbout();

public slots:
    void MainUpdate();

signals:
    void AutoClickSent(uint);
    void Exit();
};

#endif // MAINWINDOW_H

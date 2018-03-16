#include "mainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(TicTacToe &object, QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), size(9)
{
    this->object = &object;

    //create timer for update programs
    timer = new QTimer;
    timer->start(1000);//set time of the timer (in ms)
    connect(timer, SIGNAL(timeout()), this, SLOT(MainUpdate()));

    //create a second thread
    thread = new MyThread;
    thread->start();

    //create text for statusbar
    sb_text = new QLabel("load game...");
    statusBar()->addWidget(sb_text, 1);
    /*statusBar()->showMessage("load game...", 3000);*/

    ui->setupUi(this);
    this->CreatingMenus();
    this->Initialization();

    arrBtns = new QPushButton* [size];
    *arrBtns = ui->btn1; ++arrBtns;
    *arrBtns = ui->btn2; ++arrBtns;
    *arrBtns = ui->btn3; ++arrBtns;
    *arrBtns = ui->btn4; ++arrBtns;
    *arrBtns = ui->btn5; ++arrBtns;
    *arrBtns = ui->btn6; ++arrBtns;
    *arrBtns = ui->btn7; ++arrBtns;
    *arrBtns = ui->btn8; ++arrBtns;
    *arrBtns = ui->btn9; arrBtns-=(size-1);

    connect(this, SIGNAL(AutoClickSent(uint)), this, SLOT(AutoClickReceived(uint)));

    connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(OkClicked()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(CancelClicked()));
    connect(ui->btnOpt, SIGNAL(clicked()), this, SLOT(OptClicked()));

    connect(game_new, SIGNAL(triggered()), this, SLOT(GameNew()));
    connect(game_exit, SIGNAL(triggered()), this, SLOT(GameExit()));
    connect(options_parameters, SIGNAL(triggered()), this, SLOT(OptionsParameters()));
    connect(help_about, SIGNAL(triggered()), this, SLOT(HelpAbout()));
}

MainWindow::~MainWindow()
{
    delete [] arrBtns;
    delete ui;
}

QString MainWindow::processing_text(QString str, QString who)
{
    int count;
    if (who=="Tic")
        count = this->object->get_count_tic();
    if (who=="Toe")
        count = this->object->get_count_toe();

    QString s;
    if (count>9&&count<100)
        s = QString::number(count);
    else {
        s = QString::number(count);
        s = "0" + s;
    }
    for (int i=0; i<str.size(); ++i) {
        if (str.at(i)==QChar('0')&&str.at(i+1)==QChar('0')) {
            str[i+0] = s[0];
            str[i+1] = s[1];
            break;
        }
    }

    return str;
}

void MainWindow::Initialization()
{
    ui->btnOk->setDefault(true);
    ui->rbtn2->toggle();
    ui->widLayout2->hide();
    ui->widLayout3->hide();
    setFixedSize(157, 245);
    setWindowTitle(" ");
    setWindowIcon(QIcon(":/images/icon.png"));
    block();
}

void MainWindow::UpdateStatistics()
{
    if (this->object->getStats()==false) {
        QString str("<h2><i><font color=blue><font size=8>T</font><font size=6>ic</font></font><font color=grey><font size=8>T</font><font size=6>ac</font></font><font color=red><font size=8>T</font><font size=6>oe</font></font></i></h2>");
        ui->statisticslbl_main->setText(str);
        ui->statisticslbl_second->setText("");
    }
    else {
        QString str1("<h2><div align=left><i><font color=blue size=8>X</font><font color=black size=6>: 00 </font></i></div></h2>");
        QString str2("<h2><div align=right><i><font color=red size=8>0</font><font color=black size=6>: 00 </font></i></div></h2>");
        ui->statisticslbl_main->setText(processing_text(str1, "Tic"));
        ui->statisticslbl_second->setText(processing_text(str2, "Toe"));
    }
}

void MainWindow::step()
{
    if (!this->object->win && !this->object->draw) {
        if (this->object->takeTic() == ' ' && this->object->takeToe() == '0' && this->object->getPlayer() == 2)
            sb_text->setText(stepX);
        else
        if (this->object->takeTic() == 'X' && this->object->takeToe() == ' ' && this->object->getPlayer() == 2)
            sb_text->setText(step0);
        else
        if (this->object->takeTic() == ' ' && this->object->takeToe() == '0' && this->object->getPlayer() == 1)
            sb_text->setText(stepPlayer);
        else
        if (this->object->takeTic() == 'X' && this->object->takeToe() == ' ' && this->object->getPlayer() == 1)
            sb_text->setText(stepPC);
    }
    else
        sb_text->setText(stepNewGame);
}

void MainWindow::block()
{
    ui->widLayout1->setDisabled(true);
    menuBar()->setEnabled(false);
    QString str("<h2><i><font color=grey><font size=8>T</font><font size=6>ic</font><font size=8>T</font><font size=6>ac</font><font size=8>T</font><font size=6>oe</font></font></i></h2>");
    ui->statisticslbl_main->setText(str);
    ui->statisticslbl_second->setText("");
}

void MainWindow::unblock()
{
    ui->widLayout1->setDisabled(false);
    menuBar()->setEnabled(true);
    QString str("<h2><i><font color=blue><font size=8>T</font><font size=6>ic</font></font><font color=grey><font size=8>T</font><font size=6>ac</font></font><font color=red><font size=8>T</font><font size=6>oe</font></font></i></h2>");
    ui->statisticslbl_main->setText(str);
    ui->statisticslbl_second->setText("");
}

void MainWindow::OptClicked()
{
    if (this->object->getPlayer()==1)
        ui->rbtn1->toggle();

    if (this->object->getPlayer()==2)
        ui->rbtn2->toggle();

    if (this->object->getStats())
        ui->cb->setChecked(true);
    else
        ui->cb->setChecked(false);

    ui->widLayout2->hide();
    ui->widLayout3->hide();
    setFixedSize(157, 245);
    game_new->setVisible(true);

    if (!this->object->win && !this->object->draw)
        ui->widLayout1->setEnabled(true);

    if (this->object->getStats()==false) {
        QString str("<h2><i><font color=blue><font size=8>T</font><font size=6>ic</font></font><font color=grey><font size=8>T</font><font size=6>ac</font></font><font color=red><font size=8>T</font><font size=6>oe</font></font></i></h2>");
        ui->statisticslbl_main->setText(str);
        ui->statisticslbl_second->setText("");
    }
    else {
        QString str1("<h2><div align=left><i><font color=blue size=8>X</font><font color=black size=6>: 00 </font></i></div></h2>");
        QString str2("<h2><div align=right><i><font color=red size=8>0</font><font color=black size=6>: 00 </font></i></div></h2>");
        ui->statisticslbl_main->setText(processing_text(str1, "Tic"));
        ui->statisticslbl_second->setText(processing_text(str2, "Toe"));
    }
}

void MainWindow::OkClicked()
{
    QMessageBox::information(this, "TicTacToe", "The game is restarted!");

    if (ui->rbtn1->isChecked())
        this->object->setPlayer(1);

    if (ui->rbtn2->isChecked())
        this->object->setPlayer(2);

    if (ui->cb->isChecked())
        this->object->setStats(true);
    else
        this->object->setStats(false);

    ui->widLayout2->hide();
    ui->widLayout3->hide();
    setFixedSize(157, 245);
    game_new->setVisible(true);

    this->GameNew();
    this->object->reset_count();

    if (this->object->getStats()==false) {
        QString str("<h2><i><font color=blue><font size=8>T</font><font size=6>ic</font></font><font color=grey><font size=8>T</font><font size=6>ac</font></font><font color=red><font size=8>T</font><font size=6>oe</font></font></i></h2>");
        ui->statisticslbl_main->setText(str);
        ui->statisticslbl_second->setText("");
    }
    else {
        QString str1("<h2><div align=left><i><font color=blue size=8>X</font><font color=black size=6>: 00 </font></i></div></h2>");
        QString str2("<h2><div align=right><i><font color=red size=8>0</font><font color=black size=6>: 00 </font></i></div></h2>");
        ui->statisticslbl_main->setText(str1);
        ui->statisticslbl_second->setText(str2);
    }
}

void MainWindow::CancelClicked()
{
    OptClicked();
}

void MainWindow::AutoClickReceived(uint value)
{
    switch (value) {
        case 1: this->on_btn1_clicked(true); goto exit;
        case 2: this->on_btn2_clicked(true); goto exit;
        case 3: this->on_btn3_clicked(true); goto exit;
        case 4: this->on_btn4_clicked(true); goto exit;
        case 5: this->on_btn5_clicked(true); goto exit;
        case 6: this->on_btn6_clicked(true); goto exit;
        case 7: this->on_btn7_clicked(true); goto exit;
        case 8: this->on_btn8_clicked(true); goto exit;
        case 9: this->on_btn9_clicked(true); goto exit;
        default: goto exit;
    }
    exit:
    ;
}

//second new thread
void MyThread::run()
{
    expectf = false;
    QTime time;
    time.start();
    while (true) {
        while (time.elapsed()<6000)
            ;
        //executed after the inner loop
        {
            if (expectf) {
                expectf = false;
            }
        }
        time.start();
    }
}

void MainWindow::MainUpdate()
{
    {
        //read once at the start, after 3rd seconds
        static int unblock_f(0);
        if (unblock_f<2)
            unblock_f++;
        else if (unblock_f==2) {
            unblock();
            this->step();
            unblock_f++;
        }
    }

    static bool await(false);
    if (!this->object->win && !this->object->draw) {
        if (this->object->getPlayer()==1 && this->object->move_pc) {
            this->object->move_pc = false;
            thread->expectf = true;
            await = true;
            menuBar()->setEnabled(false);
        }

        if (await && !thread->expectf) {
            uint move = this->object->ai(this->object->map, '0');
            emit AutoClickReceived(move);
            if (!this->object->win && !this->object->draw)
                ui->widLayout1->setDisabled(false);
            await = false;
            menuBar()->setEnabled(true);
        }
    }
}

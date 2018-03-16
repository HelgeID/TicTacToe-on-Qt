#include "mainWindow.h"
#include "ui_mainwindow.h"

void MainWindow::CreatingMenus()
{
    QMenu *game = ui->menuBar->addMenu(tr("Game"));
    QMenu *options = ui->menuBar->addMenu(tr("Options"));
    QMenu *help = ui->menuBar->addMenu(tr("?"));

    game_new = new QAction(tr("New game"), this);
    game_new->setShortcut(QKeySequence::New);
    game->addAction(game_new);
    game_exit = new QAction(tr("Exit"), this);
    game->addAction(game_exit);

    options_parameters = new QAction(tr("Parameters of games"), this);
    options->addAction(options_parameters);

    help_about = new QAction(tr("About the program"), this);
    help->addAction(help_about);
}

//Slots Menus
void MainWindow::GameNew()
{
    QTime t(0,0,0);
    qsrand(t.secsTo(QTime::currentTime()));

    unlockedBtn(ui);
    cleartextBtn();

    QMap<QString, QChar>::iterator it = this->object->map.begin();
    char counter('0');
    for (; it!=this->object->map.end(); ++it)
        it.value() = QChar(++counter);

    this->object->win = false;
    this->object->draw = false;

    if (this->object->getPlayer()==1)
        (qrand()&1) ? this->object->move_pc = true : this->object->move_pc = false;

    if (this->object->move_pc) {
        ui->widLayout1->setDisabled(true);
        this->object->setActive('0');
    }
    else
        this->object->setActive('X');

    this->step();
}

void MainWindow::GameExit()
{
    emit Exit();
}

void MainWindow::OptionsParameters()
{
    ui->widLayout2->show();
    ui->widLayout3->show();
    setFixedSize(370, 245);
    game_new->setVisible(false);

    if (!this->object->win || !this->object->draw)
        ui->widLayout1->setEnabled(false);

    if (this->object->getStats()==false) {
        QString str("<h2><i><font color=grey><font size=8>T</font><font size=6>ic</font><font size=8>T</font><font size=6>ac</font><font size=8>T</font><font size=6>oe</font></font></i></h2>");
        ui->statisticslbl_main->setText(str);
        ui->statisticslbl_second->setText("");
    }
    else {
        QString str1("<h2><div align=left><i><font color=grey><font size=8>X</font><font size=6>: 00 </font></font></i></div></h2>");
        QString str2("<h2><div align=right><i><font color=grey><font size=8>0</font><font size=6>: 00 </font></font></i></div></h2>");
        ui->statisticslbl_main->setText(str1);
        ui->statisticslbl_second->setText(str2);
    }

}

void MainWindow::HelpAbout()
{
    aboutWindow = new About;
    aboutWindow->setModal(true);
    aboutWindow->exec();
}

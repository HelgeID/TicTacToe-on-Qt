#include "mainWindow.h"
#include "ui_mainwindow.h"

void MainWindow::clickedBtn(int const btn, bool &autoflg)
{
    QString paramBtn, textBtn;
    if (this->object->takeTic() == ' ') {
        paramBtn = "QPushButton {color: blue; font: 32px;}";
        textBtn = "X";
    }

    if (this->object->takeToe() == ' ') {
        paramBtn = "QPushButton {color: red; font: 32px;}";
        textBtn = "0";
    }

    for (int i(0); i<size; i++) {
        if (btn==i+1) {
            arrBtns[i]->setStyleSheet(paramBtn);
            arrBtns[i]->setText(textBtn);
            arrBtns[i]->setDisabled(true);
        }
    }
    //move pc
    if (this->object->getPlayer()==1 && !autoflg) {
        this->object->move_pc = true;
        ui->widLayout1->setDisabled(true);
    }
}

void MainWindow::clickedBtn_finish()
{
    this->object->processingGame();
    lockedBtn(ui);

    if (this->object->win)
        UpdateStatistics();
    this->step();
}

void MainWindow::on_btn1_clicked(bool autoflg)
{
    clickedBtn(1, autoflg);
    this->object->map["1"] = this->object->Step();
    clickedBtn_finish();
}

void MainWindow::on_btn2_clicked(bool autoflg)
{
    clickedBtn(2, autoflg);
    this->object->map["2"] = this->object->Step();
    clickedBtn_finish();
}

void MainWindow::on_btn3_clicked(bool autoflg)
{
    clickedBtn(3, autoflg);
    this->object->map["3"] = this->object->Step();
    clickedBtn_finish();
}

void MainWindow::on_btn4_clicked(bool autoflg)
{
    clickedBtn(4, autoflg);
    this->object->map["4"] = this->object->Step();
    clickedBtn_finish();
}

void MainWindow::on_btn5_clicked(bool autoflg)
{
    clickedBtn(5, autoflg);
    this->object->map["5"] = this->object->Step();
    clickedBtn_finish();
}

void MainWindow::on_btn6_clicked(bool autoflg)
{
    clickedBtn(6, autoflg);
    this->object->map["6"] = this->object->Step();
    clickedBtn_finish();
}

void MainWindow::on_btn7_clicked(bool autoflg)
{
    clickedBtn(7, autoflg);
    this->object->map["7"] = this->object->Step();
    clickedBtn_finish();
}

void MainWindow::on_btn8_clicked(bool autoflg)
{
    clickedBtn(8, autoflg);
    this->object->map["8"] = this->object->Step();
    clickedBtn_finish();
}

void MainWindow::on_btn9_clicked(bool autoflg)
{
    clickedBtn(9, autoflg);
    this->object->map["9"] = this->object->Step();
    clickedBtn_finish();
}

void MainWindow::lockedBtn(Ui::MainWindow *ui)
{
    if (this->object->win||this->object->draw)
        ui->widLayout1->setDisabled(true);
}

void MainWindow::unlockedBtn(Ui::MainWindow *ui)
{
    ui->widLayout1->setDisabled(false);
    for (int i(0); i<size; i++)
        arrBtns[i]->setEnabled(true);
}

void MainWindow::cleartextBtn()
{
    for (int i(0); i<size; i++)
        arrBtns[i]->setText("");
}

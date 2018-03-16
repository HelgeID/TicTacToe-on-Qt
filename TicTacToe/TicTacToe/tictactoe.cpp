#include <tictactoe.h>

QChar tictactoe::TicTacToe::Step()
{
    if (tic == 'X' && toe == ' ') {
        tic = ' '; toe = '0';
        return toe;
    }
    if (tic == ' ' && toe =='0') {
        tic = 'X'; toe = ' ';
        return tic;
    }
    return ' ';
}

void tictactoe::TicTacToe::setActive(QChar value)
{
    if (value != 'X') {
        tic = 'X'; toe = ' ';
        return;
    }
    if (value != '0') {
        tic = ' '; toe = '0';
        return;
    }
}

void tictactoe::TicTacToe::setPlayer(unsigned int player)
{
    this->player = player;
}

void tictactoe::TicTacToe::setStats(bool stats)
{
    this->stats = stats;
}

unsigned int tictactoe::TicTacToe::getPlayer()
{
    return this->player;
}

bool tictactoe::TicTacToe::getStats()
{
    return this->stats;
}

void tictactoe::TicTacToe::processingGame()
{
    if ((map["1"]==map["2"]&&map["2"]==map["3"])||
        (map["4"]==map["5"]&&map["5"]==map["6"])||
        (map["7"]==map["8"]&&map["8"]==map["9"])||
        (map["1"]==map["4"]&&map["4"]==map["7"])||
        (map["2"]==map["5"]&&map["5"]==map["8"])||
        (map["3"]==map["6"]&&map["6"]==map["9"])||
        (map["1"]==map["5"]&&map["5"]==map["9"])||
        (map["3"]==map["5"]&&map["5"]==map["7"]))
    {
        QMessageBox msgBox;
        QString text;
        if (takeTic()=='X') {
            text="<h2><font color=blue><i>Tic win!</i></font></h2>";
            msgBox.setIconPixmap(QPixmap(":/images/x.png"));
            winTic();
        }
        if (takeToe()=='0') {
            text="<h2><font color=red><i>Toe win!</i></font></h2>";
            msgBox.setIconPixmap(QPixmap(":/images/o.png"));
            winToe();
        }
        msgBox.setText(text);
        msgBox.setWindowIcon(QIcon(":/images/icon.png"));
        msgBox.setInformativeText("For a new game, press Ctrl+N");
        msgBox.setStandardButtons(QMessageBox::Ok); win = true;
        msgBox.exec();
//        int ret = msgBox.exec();
//        if (ret==QMessageBox::Ok)
//            win=true;
    }

    if (!win) {
        QMap<QString, QChar>::iterator it = map.begin();
        unsigned int counter(0);
        for (; it!=map.end(); ++it) {
            if (it.value()>='1'&&it.value()<='9')
                ++counter;
        }
        if (!counter) {
            QMessageBox msgBox;
            QString text;
            text="<h2><font color=grey><i>Nobody win!</i></font></h2>";
            msgBox.setText(text);
            msgBox.setWindowIcon(QIcon(":/images/icon.png"));
            msgBox.setInformativeText("For a new game, press Ctrl+N");
            msgBox.setIconPixmap(QPixmap(":/images/x_o.png"));
            msgBox.setStandardButtons(QMessageBox::Ok); draw = true;
            msgBox.exec();
//            int ret = msgBox.exec();
//            if (ret==QMessageBox::Ok)
//                draw=true;
        }
    }

    if (get_count_tic()>99||get_count_toe()>99)
        reset_count();
}

void tictactoe::TicTacToe::overwrite_index(int **ind)
{
    ind[0][0] = 1; ind[0][1] = 2; ind[0][2] = 3;
    ind[1][0] = 4; ind[1][1] = 5; ind[1][2] = 6;
    ind[2][0] = 7; ind[2][1] = 8; ind[2][2] = 9;
    ind[3][0] = 1; ind[3][1] = 4; ind[3][2] = 7;
    ind[4][0] = 2; ind[4][1] = 5; ind[4][2] = 8;
    ind[5][0] = 3; ind[5][1] = 6; ind[5][2] = 9;
    ind[6][0] = 3; ind[6][1] = 5; ind[6][2] = 7;
    ind[7][0] = 1; ind[7][1] = 5; ind[7][2] = 9;
}

void tictactoe::TicTacToe::overwrite_comb(QMap<QString, QChar> map, QChar **comb)
{
    comb[0][0] = map.value("1"); comb[0][1] = map.value("2"); comb[0][2] = map.value("3");
    comb[1][0] = map.value("4"); comb[1][1] = map.value("5"); comb[1][2] = map.value("6");
    comb[2][0] = map.value("7"); comb[2][1] = map.value("8"); comb[2][2] = map.value("9");
    comb[3][0] = map.value("1"); comb[3][1] = map.value("4"); comb[3][2] = map.value("7");
    comb[4][0] = map.value("2"); comb[4][1] = map.value("5"); comb[4][2] = map.value("8");
    comb[5][0] = map.value("3"); comb[5][1] = map.value("6"); comb[5][2] = map.value("9");
    comb[6][0] = map.value("3"); comb[6][1] = map.value("5"); comb[6][2] = map.value("7");
    comb[7][0] = map.value("1"); comb[7][1] = map.value("5"); comb[7][2] = map.value("9");
}

uint tictactoe::TicTacToe::ai(QMap<QString, QChar> map, QChar pmove)
{
    QTime t(0,0,0);
    qsrand(t.secsTo(QTime::currentTime()));

    const int number_cells(9);
    const int size(8);

    QMap<QString, QChar>::iterator it = map.begin();
    for (; it!=map.end(); ++it)
        if (it.value()>='1'&&it.value()<='9')
            it.value()=' ';

    char player, pc;
    if (pmove=='X') {
        pc='X'; player='0';
    }
    if (pmove=='0') {
        pc='0'; player='X';
    }

    int array_moves[size];

    int **ind = (int**)malloc(size*sizeof(int*));
    for (int i(0); i<size; ++i)
        *(ind+i) = (int*)malloc(3*sizeof(int));

    QChar **comb = (QChar**)malloc(size*sizeof(QChar*));
    for (int i(0); i<size; ++i)
        *(comb+i) = (QChar*)malloc(3*sizeof(QChar));

    for (int i(0); i<size; ++i) {
        array_moves[i]=0;
        for (int j(0); j<3; ++j) {
            ind[i][j]=0;
            comb[i][j]=0;
        }
    }

    overwrite_index(ind);
    overwrite_comb(map, comb);

    bool move_pc=false;
    int count=0;

    if (!move_pc) {
        for (int i(0); i<size; ++i) {
            if (comb[i][0]==pc&&comb[i][1]==pc&&comb[i][2]==' ')
                {array_moves[count++]=ind[i][2]; move_pc=true;}
            else
            if (comb[i][0]==pc&&comb[i][1]==' '&&comb[i][2]==pc)
                {array_moves[count++]=ind[i][1]; move_pc=true;}
            else
            if (comb[i][0]==' '&&comb[i][1]==pc&&comb[i][2]==pc)
                {array_moves[count++]=ind[i][0]; move_pc=true;}
        }
        count=0;
    }

    if (!move_pc) {
        for (int i(0); i<size; ++i) {
            if (comb[i][0]==player&&comb[i][1]==player&&comb[i][2]==' ')
                {array_moves[count++]=ind[i][2]; move_pc=true;}
            else
            if (comb[i][0]==player&&comb[i][1]==' '&&comb[i][2]==player)
                {array_moves[count++]=ind[i][1]; move_pc=true;}
            else
            if (comb[i][0]==' '&&comb[i][1]==player&&comb[i][2]==player)
                {array_moves[count++]=ind[i][0]; move_pc=true;}
        }
        count=0;
    }

    if (!move_pc) {
        for (int i(0); i<size; ++i) {
            if (comb[i][0]==pc&&comb[i][1]==' '&&comb[i][2]==' ') {
                if (qrand()&1)
                    {array_moves[count++]=ind[i][1]; move_pc=true;}
                else
                    {array_moves[count++]=ind[i][2]; move_pc=true;}
            }
            else
            if (comb[i][0]==' '&&comb[i][1]==pc&&comb[i][2]==' ') {
                if (qrand()&1)
                    {array_moves[count++]=ind[i][0]; move_pc=true;}
                else
                    {array_moves[count++]=ind[i][2]; move_pc=true;}
            }
            else
            if (comb[i][0]==' '&&comb[i][1]==' '&&comb[i][2]==pc) {
                if (qrand()&1)
                    {array_moves[count++]=ind[i][0]; move_pc=true;}
                else
                    {array_moves[count++]=ind[i][1]; move_pc=true;}
            }
        }
        count=0;
    }

    if (!move_pc) {
        int val=0;

        it = map.begin();
        for (; it!=map.end(); ++it) {
            if (it.value()==' ')
                count++;
        }

        if (count==number_cells) {
            count=0;
            val=qrand()%number_cells+1;
        } else
            count=0;

        it = map.begin();
        for (int i(0); it!=map.end(); ++it, ++i) {
            if (val&&i==val-1)
                continue;
            if (it.value()==' ') {
                array_moves[count++]=i+1;
                move_pc=true;
            }
        }
        count=0;
    }

    move_pc=false;

    for (int i(0); i<size; ++i)
        free(ind[i]);
    free(ind);

    for (int i(0); i<size; ++i)
        free(comb[i]);
    free(comb);

    bool flag=false;
    uint value;
    int tmp[number_cells]={0};
    std::sort(array_moves, array_moves+size);

    for (int i(1); i<size; i++) {
        if (array_moves[i-1]==array_moves[i]&&array_moves[i-1]!=0&&array_moves[i]!=0) {
            flag=true;
            break;
        }
    }

    count=0;
    for (int i(1); i<=number_cells; i++) {
        for (int n(0); n<size; n++) {
            if (array_moves[n]==i)
                count++;
        }
        if (count>1&&flag)
            {tmp[i-1]=count;}
        else
        if (count==1&&!flag)
            {tmp[i-1]=count;}
        count=0;
    }

    int num_MAX=0;
    int MAX=tmp[0];
    for (int i(1); i<number_cells; i++) {
        if (tmp[i]>MAX)
            MAX=tmp[i];
    }
    for (int i(0); i<number_cells; i++) {
        if (tmp[i]==MAX) {
            num_MAX+=1;
        }
    }
    {
        int count=0;
        uint *arr = new uint[num_MAX];
        for (int i(0); i<number_cells; i++) {
            if (tmp[i]==MAX)
                arr[count++]=uint(i+1);
        }
        value = arr[qrand()%num_MAX];
        delete [] arr;
    }
    uint move(value);
    return move;
}

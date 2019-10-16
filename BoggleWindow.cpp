#include "BoggleWindow.h"
#include "lexicon.h"

#include <QFile>
#include <QHBoxLayout>
#include <QTextEdit>
#include <iostream>
BoggleWindow::BoggleWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("QBoggle!");
    this->setFixedSize(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    count = 0;
    me = new WordListWidget(this, "Me");
    computer = new WordListWidget(this, "Computer");
    board = new Board(this);
    console = new Console(this);
    timer = new QTimer;

    me->setGeometry(20, 20, 230, 300);
    board->setGeometry(230, 0, 300, 300);
    computer->setGeometry(800 - 50 - 200, 20, 230, 300);
    console->setGeometry(30, 320, 740, 260);
    isVisited = new bool[25]{0};
    QFile qFile(":/res/EnglishWords.txt");
    if (!qFile.open(QIODevice::ReadOnly))
    {
        throw new std::runtime_error("Resource file not found!");
    }
    lexicon = new Lexicon(qFile);
    for (int i = 0; i < 25; ++i)
        connect(this->board->getCube(i), SIGNAL(mouseClick(int, QString)), this, SLOT(mouseClick(int, QString)));
    connect(console, SIGNAL(newLineWritten(QString)), this, SLOT(personTurn(QString)));
    connect(console, SIGNAL(computerRound()), this, SLOT(computerTurn()));

    //    for (std::string s: lex) {
    //        std::cout << s << std::endl;
    //    }

    console->write("Welcome to the game Boggle!\n Input '.' to end.\n");
}

BoggleWindow::~BoggleWindow()
{
}

bool BoggleWindow::wordContained(QString word)
{
    for (int i = 0; i < wordFound.size(); i++)
    {
        if (wordFound[i] == word.toUpper())
            return true;
    }
    return false;
}

void BoggleWindow::personTurn(QString line)
{

    if (line.length() < 4)
    {
        console->write("Please input 4 letters at least.");
        return;
    }
    if (wordContained(line))
    {
        console->write("this word has been found.");
    }
    else if (lexicon->contains(line.toStdString()))
    {
        bool flag;
        flag = false;
        count = 0;
        for (int i = 0; i < 5 * 5 && !count; i++)
        {
            if ((board->getCube(i)->letter == line[0].toUpper() && board->getCube(i)->letter != "Qu") || (board->getCube(i)->letter.toUpper() == line.mid(0, 2).toUpper() && board->getCube(i)->letter == "Qu"))
            {
                if (isVisited != nullptr)
                    delete isVisited;
                isVisited = new bool[25]{0};
                //                for(int j = 0;j < 5 * 5;j ++){
                //                    isVisited[j] = false;
                //                }
                QVector<int> wordpath;
                searchBoard(line, i, 0, wordpath);
            }
        }
        if (!count)
            console->write("can't find!");
    }
    else
    {
        console->write("can't find!");
        return;
    }
}

void BoggleWindow::computerTurn()
{
    //    if(isVisited != nullptr) delete isVisited;
    //    isVisited = new bool[25]{0};
    if (isVisited == nullptr)
        isVisited = new bool[25]{0};
    for (int i = 0; i < 5 * 5; i++)
    {

        isVisited[i] = 1;
        QString word = "";
        for (int j = 0; j < 3; j++)
        {
            computerSearchWord(i, word);
        }
        isVisited[i] = 0;
    }
}

void BoggleWindow::computerSearchWord(int pos, QString word)
{
    QString current = word + this->board->getCube(pos)->letter;
    //前缀
    if (!lexicon->containsPrefix(word.toStdString()))
    {
        return;
    }
    //找到！
    if (current.length() >= 4 && lexicon->contains(current.toStdString()) &&
        !wordContained(current))
    {
        wordFound.push_back(current.toUpper());
        computer->addScore(current.length() - 3);
        computer->addWord(current.toLower());
        return;
    }

    //dfs
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
        {
            int r = pos / 5;
            int c = pos % 5;
            if (r + i >= 0 && r + i < 5 && c + j >= 0 && c + j < 5 &&
                isVisited[(r + i) * 5 + (c + j)] != 1 &&
                !(i == 0 && j == 0))
            {
                isVisited[(r + i) * 5 + (c + j)] = 1;
                computerSearchWord((r + i) * 5 + (c + j), current);
                isVisited[(r + i) * 5 + (c + j)] = 0;
            }
        }
}

void BoggleWindow::mouseClick(int x, QString word)
{
    if (!clickIndex.empty() && (abs(x - clickIndex[clickIndex.size() - 1]) != 1 && abs(x - clickIndex[clickIndex.size() - 1]) != 4 && abs(x - clickIndex[clickIndex.size() - 1]) != 5 && abs(x - clickIndex[clickIndex.size() - 1]) != 6))
    {
        console->write("The letter is not consequent!");
        return;
    }
    //多次判断
    for (int i = 0; i < clickIndex.size(); i++)
    {
        if (clickIndex[i] == x)
        {
            console->write("You have already clicked.");
            return;
        }
    }

    board->getCube(x)->label->setStyleSheet("background-color: red; border-radius: 15px; border: 2px solid");
    clickLine = clickLine + word;
    clickIndex.push_back(x);
    if (!lexicon->containsPrefix(clickLine.toStdString()))
    {
        console->write("Can't find this prefix.");
        for (int i = 0; i < clickIndex.size(); ++i)
            this->board->getCube(clickIndex[i])->label->setStyleSheet("background-color: grey; border-radius: 15px; border: 2px solid");
        clickLine.clear();
        clickIndex.clear();
        return;
    }
    if (lexicon->contains(clickLine.toStdString()) && clickLine.length() >= 4)
    {
        if (!wordContained(clickLine)){
            wordFound.push_back(clickLine.toUpper());
            for (int i = 0; i < clickIndex.size(); ++i)
                this->board->getCube(clickIndex.at(i))->label->setStyleSheet("background-color: grey; border-radius: 15px; border: 2px solid");
            me->addWord(clickLine.toLower());
            me->addScore(clickLine.length() - 3);
            clickIndex.clear();
            clickLine.clear();
            console->write("good!");
        }
    }
}

void BoggleWindow::searchBoard(QString word, int pos, int index, QVector<int> wordPath)
{
    wordPath.append(pos);
    if (index == word.length() - 1)
    {
        count++;
        if (count == 1)
        {
//            QString label;
//            QList<QString> words;
//            int score;
//            WordTable *wordTable;
//            QLabel *nameLabel;
//            QLabel *scoreLabel;
            me->addScore(word.length() - 3);
            me->addWord(word);
            wordFound.push_back(word.toUpper());
            console->write("good!");
            for (int i = 0; i < wordPath.length(); i++)
            {
                board->getCube(wordPath[i])->label->setStyleSheet("background-color: red; border-radius: 15px; border: 2px solid");
            }
            connect(timer, SIGNAL(timeout()), this, SLOT(changeColor()));
            timer->start(1000);
        }
        wordPath.clear();
        return;
    }
    if (board->getCube(pos)->letter == "Qu" && board->getCube(pos)->letter.toUpper() == word.mid(index, 2).toUpper() || board->getCube(pos)->letter != "Qu" && board->getCube(pos)->letter == word[index].toUpper())
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                int row = pos / 5;
                int col = pos % 5;
                if (row + i >= 0 && row + i < 5 && col + j >= 0 && col + j < 5 && isVisited[(row + i) * 5 + (col + j)] != 1 && !(i == 0 && j == 0) && board->getCube((row + i) * 5 + (col + j))->letter == word[index + 1].toUpper())
                {
                    isVisited[pos] = true;
                    searchBoard(word, (row + i) * 5 + (col + j), index + 1,
                                wordPath);
                    isVisited[pos] = 0;
                }
            }
        }
    }
    wordPath.clear();
    return;
}

void BoggleWindow::changeColor()
{
    timer->stop();
    //    QVector<int> num;
    disconnect(timer, SIGNAL(timeout()), this, SLOT(changeColor()));
    for (int i = 0; i < 25; i++)
    {

        board->getCube(i)->label->setStyleSheet("background-color: grey; border-radius: 15px; border: 2px solid");
    }
}

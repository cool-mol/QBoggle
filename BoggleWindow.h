#ifndef BOGGLEWINDOW_H
#define BOGGLEWINDOW_H

#include "Board.h"
#include "Console.h"
#include "WordListWidget.h"
#include "lexicon.h"
#include <QMainWindow>
#include <vector>
#include <QTimer>
class BoggleWindow : public QMainWindow
{
    Q_OBJECT

public:
    BoggleWindow(QWidget *parent = 0);
    ~BoggleWindow();

private:
    int count;
    QTimer *timer;
    WordListWidget *me;
    WordListWidget *computer;
    Board *board;
    Console *console;
    bool *isVisited;
    std::vector<QString> wordFound;
    //点击事件
    std::vector<int> clickIndex;
    QString clickLine;
    // 方便构造
    Lexicon *lexicon;
    // 判断单词是否包含在单词表里面
    bool wordContained(QString);
    void computerSearchWord(int, QString);
//    Board *getBoard(){return board;}
    void searchBoard(QString, int, int, QVector<int>);
    static const int BOGGLE_WINDOW_WIDTH = 800;
    static const int BOGGLE_WINDOW_HEIGHT = 600;
signals:

public slots:
    void personTurn(QString line);
    void computerTurn();
    void mouseClick(int, QString);
    void changeColor();
};

#endif // BOGGLEWINDOW_H

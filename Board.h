#ifndef BOARD_H
#define BOARD_H

#include "Cube.h"
#include <ctime>
//#include <random>
#include <QWidget>
#include <cstdlib>
// 定义随机数生成器

//typedef std::uniform_int_distribution<int> uni;
//typedef std::default_random_engine eng;
//uni uniform = uni(1, posMax)
class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr, int size = 5, const QString *cubeLetters = BIG_BOGGLE_CUBES);
    virtual ~Board();
    void shake();
    Cube *getCube(int i){return cubes[i];}
signals:

public slots:

private:
    int size;
    Cube **cubes;
    //QString *letters;
    std::vector<QString> letterCubes;
    inline int index(int i, int j) { return i * size + j; }
    static const QString STANDARD_CUBES[16];
    static const QString BIG_BOGGLE_CUBES[25];
};

#endif // BOARD_H

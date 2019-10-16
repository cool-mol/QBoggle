#include "Board.h"
#include "Cube.h"

#include <QGridLayout>
#include <QTime>
#include <qrandom.h>
const QString Board::STANDARD_CUBES[16]  = {
        "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
        "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
        "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
        "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const QString Board::BIG_BOGGLE_CUBES[25]  = {
        "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
        "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
        "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
        "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
        "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Board::Board(QWidget *parent, int size, const QString *cubeLetters) : QWidget(parent)
{
    this->size = size;
    this->cubes = new Cube*[size * size];
    //this->letters = new QString[size * size];
    for (int i = 0; i < size * size; ++i)
        letterCubes.push_back(cubeLetters[i]);
    //    this->letters[i] = cubeLetters[i];

    QGridLayout *layout = new QGridLayout();
    layout->setMargin(20);
    layout->setSpacing(10);

//    for(int i = 0;i < 25;i ++){
//        for(int j = 0;j < 5;j ++){
//            letterCubes[i].push_back(BIG_BOGGLE_CUBES[i].at(j));
//        }
//    }
    //开坑代填
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->cubes[index(i, j)] = new Cube(this);
            layout->addWidget(this->cubes[index(i, j)], i, j, Qt::AlignmentFlag::AlignCenter);
        }
    }
    setLayout(layout);
    shake();
    //吧Q换成QU
    for(int i = 0;i < size;i ++){
        for(int j = 0;j < size; j ++){
            if(cubes[index(i, j)]->letter == 'Q'){
                cubes[index(i, j)]->letter = "Qu";
            }
        }
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->cubes[index(i, j)]->setLetter(this->letterCubes[index(i, j)].at(0));
        }
    }

    this->setStyleSheet("background-color:grey; border: 3px solid");
}

Board::~Board()
{
    if (cubes) delete[] cubes;
//    if (letters) delete[] letters;
}

void Board::shake()
{
    // Shake Cubes
    // first step
//    for (int i = 0; i < vec.size(); i++) {
//    Choose a random index r between i and the
    // last element position, inclusive.
    //Swap the element at positions i and r.
//    }
    //随机数
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QChar tmp;
    int r = qrand() % 5;
    for(int i = 0;i < 25;i ++){
        r = qrand() % 5;
        tmp = letterCubes[i][0];
        letterCubes[i][0] = letterCubes[i][r];
        letterCubes[i][r] = tmp;
    }

    for(int i = 0;i < size;i ++){
        for(int j = 0;j < size;j ++){
            cubes[index(i, j)]->letter = letterCubes[index(i, j)][0];
            cubes[index(i, j)]->index = index(i, j);
        }
    }


}








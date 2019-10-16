#include "Cube.h"

#include <QHBoxLayout>

Cube::Cube(QWidget *parent) : QWidget(parent)
{
    label = new QLabel();
    label->setText("");
    label->setAlignment(Qt::AlignCenter);
    QFont font = label->font();
    font.setPointSize(20);
    label->setFont(font);

    this->setFixedSize(75, 75);
    this->setStyleSheet("background-color: grey; border-radius: 15px; border: 2px solid");
    //不是mac傻逼 是我傻逼

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    setLayout(layout);

    //鼠标玩玩
    //TODO
    //它lay了！！！
    letterButton = new QPushButton(this);
    letterButton->setGeometry(10, 10, 55, 55);
    letterButton->setStyleSheet("QPushButton{background: transparent; border-radius: 15px;border: 2px solid;} ");
    letterButton->setFlat(1);
    letterButton->raise();

    connect(letterButton, SIGNAL(released()), this, SLOT(transData()));
}

void Cube::setLetter(QString l)
{
    label->setText(l);
}

void Cube::transData()
{
    emit mouseClick(index, letter);
}

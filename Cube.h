#ifndef CUBE_H
#define CUBE_H

#include <QLabel>
#include <QWidget>
#include <QPushButton>
class Cube : public QWidget
{
    Q_OBJECT
public:
    explicit Cube(QWidget *parent = nullptr);
    void setLetter(QString l);
    QLabel *label;
    QString letter;
    int index;
    QPushButton *letterButton;

signals:
    void mouseClick(int, QString);
public slots:
    void transData();
private:

};

#endif // CUBE_H

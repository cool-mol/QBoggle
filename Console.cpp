#include "Console.h"
#include <QKeyEvent>
#include <QTextLine>
#include <QTextCursor>

Console::Console(QWidget *parent) : QTextEdit(parent)
{
    //connect(this,&Console::newLineWritten,this,&Console::write);
}

void Console::clear()
{
    this->clear();
}

void Console::write(QString msg)
{
    this->append(msg);
}

void Console::keyPressEvent(QKeyEvent *event)
{
    //退格和delete都是把这行清空
    if (event->key() == Qt::Key_Backspace){
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::End);
        cursor.select(QTextCursor::LineUnderCursor);
        cursor.removeSelectedText();
        return;
    }
    if (event->key() == Qt::Key_Delete){
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::End);
        cursor.select(QTextCursor::LineUnderCursor);
        cursor.removeSelectedText();
        return;
    }
    if (this->textCursor().hasSelection())
        return;
    if (event->key() == Qt::Key_Return) {
        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::End);
        cursor.select(QTextCursor::LineUnderCursor);
        QString lastLine = cursor.selectedText();
        //如果输入.的话 电脑跑一轮
        if(lastLine == ".")
            emit computerRound();
        else
            emit newLineWritten(lastLine);
        //newLineWritten(lastLine);
    }
    QTextEdit::keyPressEvent(event);
}

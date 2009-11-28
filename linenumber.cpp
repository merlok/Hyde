/*
 * This file is part of the Hyde code editor.
 *
 * Copyleft of The Hybris Dev Team <http://www.hybris-lang.org/>
 *
 * hybris is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * hybris is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with hybris.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "linenumber.h"

lineNumber::lineNumber(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);
    connect(this,SIGNAL(blockCountChanged(int)),this,SLOT(updateLineNumberAreaWidth(int)));
    connect(this,SIGNAL(updateRequest(QRect,int)),this,SLOT(updateLineNumberArea(const QRect &,int)));
    connect(this,SIGNAL(cursorPositionChanged()),this,SLOT(highlightLine()));
    connect(this,SIGNAL(textChanged()),this,SLOT(textChanged()));
    lineNumber::updateLineNumberAreaWidth(0);
    lineNumber::highlightLine();
    Syntax = new highlighter(document());
    this->setTabStopWidth(30);
    qDebug() << blockCount();
    changed = false;
    isNew = true;
    backspace=false;
}

lineNumber::~lineNumber()
{

}

int lineNumber::lineNumberAreaWidth()
{
    int digits=1;
    int max = qMax(1,blockCount());
    while (max>=10)
    {
        max /=10;
        digits++;
    }
    int space=3+ fontMetrics().width(QLatin1Char('9'))*digits;
    return space;
}

void lineNumber::updateLineNumberAreaWidth(int)
{
    setViewportMargins(lineNumber::lineNumberAreaWidth(),0,0,0);
}

void lineNumber::updateLineNumberArea(const QRect &rect,int dy)
{
    if (dy)
        lineNumberArea->scroll(0,dy);
    else
        lineNumberArea->update(0,rect.y(),lineNumberArea->width(),rect.height());
    if (rect.contains(viewport()->rect()))
        lineNumber::updateLineNumberAreaWidth(0);
}

void lineNumber::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(),cr.top(),lineNumber::lineNumberAreaWidth(),cr.height()));

}

void lineNumber::highlightLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if(!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(Qt::yellow).lighter(160);
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection,true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    setExtraSelections(extraSelections);
}

void lineNumber::lineNumberPaint(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(),Qt::lightGray);
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int)blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top+(int)blockBoundingRect(block).height();

    while(block.isValid() && top <= event->rect().bottom())
    {
        if(block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber+1);
            painter.setPen(Qt::black);
            painter.drawText(0,top,lineNumberArea->width(),fontMetrics().height(),Qt::AlignRight,number);
        }
        block=block.next();
        top=bottom;
        bottom=top+(int)blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void lineNumber::textChanged()
{
QTextCursor cursor= textCursor();
   QString tabbing="";
   QChar act='\0';

   changed = true;
   int col = 0;
   int pos = cursor.position();
   if (pos > 0)
       act = toPlainText()[pos -1];
   else
       act = toPlainText()[pos];

   cursor.movePosition(QTextCursor::Up,QTextCursor::MoveAnchor,1);
   cursor.movePosition(QTextCursor::EndOfLine);
   cursor.movePosition(QTextCursor::PreviousWord);
   //cursor.movePosition(QTextCursor::NextWord);
   if (!backspace)
   {
       if (act == '\n')
       {
           cursor.movePosition(QTextCursor::StartOfLine);
           if (!toPlainText()[cursor.position()].isPrint())
                cursor.movePosition(QTextCursor::NextWord);
           if (toPlainText()[cursor.position()] == '{')
               col=cursor.columnNumber() + 1;
           else
               col = cursor.columnNumber();
           if (col != 0)
           {
               tabbing = QString(col,'\t');
               cursor.movePosition(QTextCursor::Down);
               cursor.movePosition(QTextCursor::StartOfLine);
               cursor.insertText(tabbing);
               cursor.movePosition(QTextCursor::EndOfLine);
               setTextCursor(cursor);
           }
       }
       if (act == '}')
       {
            qDebug() << "closed";
            cursor.movePosition(QTextCursor::StartOfLine);
            if (!toPlainText()[cursor.position()].isPrint())
                cursor.movePosition(QTextCursor::NextWord);
            if (toPlainText()[cursor.position()] == '{')
               col=cursor.columnNumber();
           else
               col = cursor.columnNumber()-1;
           if (col >= 0)
           {
            cursor.setPosition(pos-1);
            cursor.deleteChar();
            cursor.movePosition(QTextCursor::StartOfLine);
            tabbing = QString(col,'\t');
            cursor.insertText(tabbing+"}");
            setTextCursor(cursor);
           }
       }
   }

}

int lineNumber::openFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return 0;
    }
    setPlainText(file.readAll());
    file.close();
    changed = false;
    isNew = false;
    return 1;
}

int lineNumber::saveFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return 0;
    }
    QTextStream sr(&file);
    sr << toPlainText();
    sr.flush();
    file.flush();
    file.close();
    changed = false;
    isNew = false;
    return 1;
}

void lineNumber::newFile()
{
    isNew = true;
    changed = false;
    setPlainText("");
}

void lineNumber::commentSelection(QTextCursor cursor)
{
    QTextCursor walk = cursor;
    walk.setPosition(cursor.selectionStart());
    walk.insertText("/*");
    walk.setPosition(cursor.selectionEnd());
    walk.insertText("*/");
    setTextCursor(walk);
}

void lineNumber::uncommentSelection(QTextCursor cursor)
{
    QTextCursor walk = cursor;
    QString selection = cursor.selectedText();
    if (selection.startsWith("/*") && selection[selection.length()-2] == '*' && selection[selection.length()-1] == '/')
    {
        walk.setPosition(cursor.selectionStart());
        walk.deleteChar();
        walk.deleteChar();
        walk.setPosition(cursor.selectionEnd()-2);
        walk.deleteChar();
        walk.deleteChar();
        setTextCursor(walk);
    }
}

void lineNumber::indentSelection(QTextCursor cursor)
{
    int pos = cursor.selectionStart();
    QStringList splitted = cursor.selectedText().split("\n");
    for (int i=0;i < splitted.count();i++)
    {
        splitted[i] = "\t" + splitted[i];
    }
    cursor.removeSelectedText();
    cursor.setPosition(pos);
    cursor.insertText(splitted.join("\n"));
    setTextCursor(cursor);
}

void lineNumber::keyPressEvent(QKeyEvent *e)
{

    switch(e->key())
    {
        case Qt::Key_Backspace:
            backspace=true;
            break;
        default:
            backspace=false;
    }
    QPlainTextEdit::keyPressEvent(e);
}

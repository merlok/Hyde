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
#ifndef LINENUMBER_H
#define LINENUMBER_H

#include <highlighter.h>
#include <QtGui/QWidget>
#include <QPlainTextEdit>
#include <QObject>
#include <QPainter>
#include <QTextBlock>
#include <QFile>
#include <QStringList>
#include <QKeyEvent>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class lineNumber : public QPlainTextEdit
{
    Q_OBJECT

public:
    lineNumber(QWidget *parent = 0);
    ~lineNumber();
    void lineNumberPaint(QPaintEvent *event);
    int lineNumberAreaWidth();
    int openFile(QString file);
    int saveFile(QString file);
    void newFile(void);
    bool changed;
    bool isNew;
    void commentSelection(QTextCursor cursor);
    void uncommentSelection(QTextCursor cursor);
    void indentSelection(QTextCursor cursor);

protected:
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *e);

private slots:
    void updateLineNumberArea(const QRect &,int);
    void updateLineNumberAreaWidth(int block);
    void highlightLine();
    void textChanged();

private:
    QWidget *lineNumberArea;
    highlighter *Syntax;
    bool backspace;
};


class LineNumberArea : public QWidget
{
public:
    LineNumberArea(lineNumber *editor) : QWidget(editor){
        codeEditor=editor;
    }

    QSize sizeHint() const {
        return QSize(codeEditor->lineNumberAreaWidth(),0);
    }
//TODO insert protected methods
protected:
    void paintEvent(QPaintEvent *event){
        codeEditor->lineNumberPaint(event);
    }
private:
    lineNumber *codeEditor;

};
#endif // LINENUMBER_H

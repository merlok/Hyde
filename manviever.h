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
#ifndef MANVIEVER_H
#define MANVIEVER_H

#include <QtGui/QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QProcess>
#include <QTextCursor>
#include <QDebug>

class manViever : public QWidget
{
    Q_OBJECT

public:
    manViever(QWidget *parent = 0);
    ~manViever();
private:
    QLineEdit *lneSearch;
    QTextEdit *txtMan;
    QVBoxLayout *Vlayout;
    QHBoxLayout *Hlayout;
    QPushButton *btnSearch;
    QProcess proc;
    QString out;

private slots:
    void startSearch();
    void stdOut();
    void stdErr();
    void procFinished(int code,QProcess::ExitStatus);
};

#endif // MANVIEVER_H

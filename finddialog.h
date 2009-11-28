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
#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QtGui/QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QFlags>
#include <QTextDocument>
#include <QTextCursor>
#include <QRegExp>
#include <QLabel>
#include "linenumber.h"

class findDialog : public QWidget
{
    Q_OBJECT

public:
    findDialog(QWidget *parent = 0);
    ~findDialog();
    QString getSearch();

private:
    QLabel *lblSearch;
    QLineEdit *txtSearch;
    QPushButton *btnNext;
    QPushButton *btnPrev;
    QCheckBox *caseSensitive;
    QCheckBox *completeWord;
    QCheckBox *regExp;
    QHBoxLayout *layout;
    QFlags<QTextDocument::FindFlag> checkFlags();

private slots:
    void nxtClicked();
    void prvClicked();

public slots:
    void findNext(lineNumber *editor);
    void findPrev(lineNumber *editor);
    void setFocusText();

signals:
    void nextClicked();
    void prevClicked();
};

#endif // FINDDIALOG_H

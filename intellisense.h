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
#ifndef Intellisense_H
#define Intellisense_H

#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QStringList>
#include <QTextCursor>
#include <QPlainTextEdit>
#include <QDir>

class Intellisense : public QWidget
{
    Q_OBJECT
public:
    Intellisense(QWidget *parent=0);
    void move(int x,int y);
    QString selected_match();
    void next_item();
    void prev_item();
    void onKeyPress( int key, QTextCursor& cursor, QPlainTextEdit *editor );
private:
    QString      word;
    QStringList  apis;
    QListWidget *matches;
    QHBoxLayout *mainLayout;
};

#endif // Intellisense_H

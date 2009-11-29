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

#include "intellisense.h"

#define WEIGHT 300
#define HEIGHT 100

Intellisense::Intellisense(QWidget *parent)
    : QWidget(parent)
{
    word       = "";
    matches    = new QListWidget;
    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(matches);
    setLayout(mainLayout);

    QDir dir("apis");
    QStringList files = dir.entryList( QStringList( "*.html" ), QDir::Files | QDir::NoSymLinks );

    foreach( QString file, files ){
        this->apis.append( file.left( file.indexOf('.') ) );
    }

    this->hide();
}

void Intellisense::prev_item()
{
    matches->setCurrentRow(matches->currentRow()-1);
}

void Intellisense::next_item()
{
    matches->setCurrentRow(matches->currentRow()+1);
}

void Intellisense::onKeyPress( int key, QTextCursor& cursor, QPlainTextEdit *editor ){
    QString strkey = QString(char(key));
    if( strkey.contains( QRegExp( "[a-zA-Z0-9_]+" ) ) ){
        this->word += char(key);
        if( this->word.size() >= 2 ){
            matches->clear();
            foreach( QString api, apis ){
                if( api.startsWith( this->word, Qt::CaseInsensitive ) ){
                    matches->addItem(api);
                }
            }
            matches->setCurrentRow(0);
            if( matches->count() ){
                this->show();
            }
        }
    }
    else{
        switch( key ){
            case Qt::Key_Space:
                this->word = "";
                setVisible(false);
                break;

            case Qt::Key_Backspace:
                this->word.chop(1);
                setVisible(false);
                break;

            case Qt::Key_Return:
                this->word = "";
                if( isVisible() ){
                    int         position = cursor.position() - 1;
                    QString     str      = QString( editor->toPlainText()[position] );

                    while( str.contains( QRegExp( "[a-zA-Z0-9_]+" ) ) && position-- >= 1 ){
                        cursor.movePosition( QTextCursor::Left );
                        cursor.deleteChar();
                        str = editor->toPlainText()[position];
                    }
                    cursor.insertText( this->selected_match() );
                    this->hide();
                }
                break;

            case Qt::Key_Escape:
                this->word = "";
                setVisible(false);
                break;

            case Qt::Key_Down:
                this->word = "";
                if( isVisible() ){
                    next_item();
                }
                break;

            case Qt::Key_Up:
                this->word = "";
                if( isVisible() ){
                    prev_item();
                }
                break;
        }
    }
}

void Intellisense::move(int x, int y)
{
    setGeometry(x,y,WEIGHT,HEIGHT);
}

QString Intellisense::selected_match()
{
    return matches->currentItem()->text();
}

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

#define WIDTH 300
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
    if( matches->currentRow() > 0)
        matches->setCurrentRow(matches->currentRow()-1);
}

void Intellisense::next_item()
{
    if( matches->currentRow() < matches->count()-1)
        matches->setCurrentRow(matches->currentRow()+1);
}

void Intellisense::onKeyPress( int key, QTextCursor& cursor, QPlainTextEdit *editor ){
    QString strkey = QString(char(key));

    // il tasto è una lettera, un numero o _ ?
    if( strkey.contains( QRegExp( "[a-zA-Z0-9_]+" ) ) ){
        this->word += char(key);
        // fa partire l'auto complete al secondo carattere
        if( this->word.size() >= 2 ){
            // resetto la lista dei match
            matches->clear();
            int maxlen = 0;
            // loopo tutte le api documentate
            foreach( QString api, apis ){
                // il nome dell'api inizia con i caratteri appena inseriti ?
                if( api.startsWith( this->word, Qt::CaseInsensitive ) ){
                    matches->addItem(api);
                    // determino la lunghezza massima del nome di un api per dimensionare il box
                    if( api.size() > maxlen ){
                        maxlen = api.size();
                    }
                }
            }
            // se ci sono stati match
            if( matches->count() ){
                matches->setCurrentRow(0);
                // imposto la nuova larghezza in base alla stringa più lunga inserita
                setGeometry( x(), y(),
                             50 + fontMetrics().width( QLatin1Char('9') ) * maxlen,
                             HEIGHT );
                this->show();
            }
        }
    }
    else{
        switch( key ){
            case Qt::Key_Space:
                // resetto il buffer
                this->word = "";
                setVisible(false);
                break;

            case Qt::Key_Backspace:
                // elimino l'ultimo carattere dal buffer
                this->word.chop(1);
                setVisible(false);
                break;

            case Qt::Key_Return:
                // resetto il buffer
                this->word = "";

                if( isVisible() ){
                    int         position = cursor.position() - 1;
                    QString     str      = QString( editor->toPlainText()[position] );
                    // se non siamo nella prima riga
                    if( position > 1 ){
                        // loopo all'indietro i caratteri rimuovendoli finchè
                        // non trovo l'inizio della parola digitata
                        while( str.contains( QRegExp( "[a-zA-Z0-9_]+" ) ) && position-- >= 1 ){
                            cursor.movePosition( QTextCursor::Left );
                            cursor.deleteChar();
                            str = editor->toPlainText()[position];
                        }
                    }
                    // la prima riga è un caso particolare, poichè dobbiamo ignorare gli indici
                    // e semplicemente cancellare a ritroso
                    else{
                        cursor.movePosition( QTextCursor::Left );
                        cursor.deleteChar();
                        cursor.movePosition( QTextCursor::Left );
                        cursor.deleteChar();
                    }
                    // inserisco il match selezionato
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
    setGeometry(x,y,WIDTH,HEIGHT);
}

QString Intellisense::selected_match()
{
    return matches->currentItem()->text();
}

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

#include "hybris_completer.h"
//É solo un esempio
#define WEIGHT 100
#define HEIGHT 100
//Se vogliamo ricreare l oggetto ogni volta basta aggingere i parametri x,y in ingresso
/*hybris_completer::hybris_completer(QWidget *parent,int x,int y)
    : QWidget(parent),x,y*/

hybris_completer::hybris_completer(QWidget *parent)
    : QWidget(parent)
{
    completer = new QListWidget;
    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(completer);
    setLayout(mainLayout);

    QStringList item ;
    item << "ciao" <<"bau"<< "miao";
    completer->addItems(item);
    this->hide();
}

void hybris_completer::move(int x, int y)
{
    setGeometry(x,y,WEIGHT,HEIGHT);
    show();
}

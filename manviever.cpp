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
#include "manviever.h"

manViever::manViever(QWidget *parent)
    : QWidget(parent)
{
    lneSearch = new QLineEdit;
    lneSearch->setText("");
    txtMan = new QTextEdit;
    txtMan->setText("");
    txtMan->setReadOnly(true);
    btnSearch = new QPushButton;
    btnSearch->setText("Search");

    Hlayout = new QHBoxLayout;
    Hlayout->addWidget(lneSearch);
    Hlayout->addWidget(btnSearch);

    Vlayout =  new QVBoxLayout;
    Vlayout->addLayout(Hlayout);
    Vlayout->addWidget(txtMan);

    setLayout(Vlayout);
    out="";

    connect(btnSearch,SIGNAL(clicked()),this,SLOT(startSearch()));
    connect(lneSearch,SIGNAL(returnPressed()),this,SLOT(startSearch()));
    connect(&proc,SIGNAL(readyReadStandardOutput()),this,SLOT(stdOut()));
    connect(&proc,SIGNAL(readyReadStandardError()),this,SLOT(stdErr()));
    connect(&proc,SIGNAL(finished(int ,QProcess::ExitStatus)),this,SLOT(procFinished(int,QProcess::ExitStatus)));
}

manViever::~manViever()
{

}

void manViever::startSearch()
{
   if (!lneSearch->text().isEmpty())
    {

        proc.start("man --ascii "+lneSearch->text());
    }
}

void manViever::stdOut()
{
    txtMan->setText("");
    out +=QString::fromLocal8Bit(proc.readAllStandardOutput());
}

void manViever::stdErr()
{
    txtMan->setText(QString::fromLocal8Bit(proc.readAllStandardError()));
}

void manViever::procFinished(int code,QProcess::ExitStatus)
{
    if (code == QProcess::NormalExit)
    {
        txtMan->setText(out);
        out = "";
    }
}

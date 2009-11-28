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
#include "finddialog.h"

findDialog::findDialog(QWidget *parent)
    : QWidget(parent)
{
    lblSearch = new QLabel;
    txtSearch = new QLineEdit;
    btnNext = new QPushButton;
    btnPrev = new QPushButton;
    layout = new QHBoxLayout;
    caseSensitive = new QCheckBox;
    completeWord = new QCheckBox;
    regExp = new QCheckBox;

    lblSearch->setText("Search:");
    btnNext->setText("Next");
    btnPrev->setText("Previous");
    caseSensitive->setText("Case\nsensitive");
    completeWord->setText("Complete\nword");
    regExp->setText("Regular\nexpression");

    layout->addWidget(lblSearch);
    layout->addWidget(txtSearch);
    layout->addWidget(btnNext);
    layout->addWidget(btnPrev);
    layout->addWidget(caseSensitive);
    layout->addWidget(completeWord);
    layout->addWidget(regExp);

    setLayout(layout);

    connect(btnNext,SIGNAL(clicked()),this,SLOT(nxtClicked()));
    connect(btnPrev,SIGNAL(clicked()),this,SLOT(prvClicked()));
}

findDialog::~findDialog()
{

}

void findDialog::nxtClicked()
{
    if (!txtSearch->text().isEmpty())
        emit nextClicked();
}

void findDialog::prvClicked()
{
    if (!txtSearch->text().isEmpty())
        emit prevClicked();
}

void findDialog::findNext(lineNumber *editor)
{
   //TODO search with Regular Expression
   editor->find(txtSearch->text(),findDialog::checkFlags());
}

void findDialog::findPrev(lineNumber *editor)
{
    editor->find(txtSearch->text(),findDialog::checkFlags());
}

void findDialog::setFocusText()
{
    txtSearch->setFocus(Qt::TabFocusReason);
}

QString findDialog::getSearch(){return txtSearch->text();}

QFlags<QTextDocument::FindFlag> findDialog::checkFlags()
{
    QFlags<QTextDocument::FindFlag> flags(0);
    if (caseSensitive->isChecked())
        flags |= QTextDocument::FindCaseSensitively;
    if (completeWord->isChecked())
        flags |= QTextDocument::FindWholeWords;
    return flags;
}

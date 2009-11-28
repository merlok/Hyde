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
#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QStringList>
#include <QFile>
#include <QRegExp>
#include <QTextStream>
#include <QDebug>
#include <QDomDocument>

class highlighter : public QSyntaxHighlighter
{
public:
    highlighter(QTextDocument *parent=0);
protected:
   void highlightBlock(const QString &text);
private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> rules;
    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat classFormat;
    QTextCharFormat methodFormat;
    QTextCharFormat commentFormat;
    QTextCharFormat statementFormat;
    QTextCharFormat typeFormat;
    QTextCharFormat includeFormat;
    QTextCharFormat pragmaFormat;
    QTextCharFormat stringFormat;
};

#endif // HIGHLIGHTER_H

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
#include "highlighter.h"

void highlighter::parseStyle( QDomElement& e, QTextCharFormat& format ){
    if( e.hasAttribute( "style" ) ){
        QStringList styles = e.attribute( "style", "" ).split( ',' );

        foreach( QString style, styles ){
            if( style == "bold" ){
                format.setFontWeight( QFont::Bold );
            }
            else if( style == "italic" ){
                format.setFontItalic(true);
            }
            else if( style == "underline" ){
                format.setFontUnderline(true);
            }
        }
    }
}

highlighter::highlighter(QTextDocument *parent)
        :QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    QDomDocument doc("");
    QFile file( "grammar.xml" );
    if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
        return;

    if( !doc.setContent( &file ) ){
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    if( root.tagName() != "grammar" )
      return;

    QDomNode n = root.firstChild();
    while( !n.isNull() ) {
        QDomElement e = n.toElement();
        if( !e.isNull() ) {
            if( e.tagName() == "keywords" ) {
                parseStyle( e, keywordFormat );
                keywordFormat.setForeground( QColor( e.attribute( "color", "" ).toAscii().constData() ) );

                QDomNode item = e.firstChild();
                while( !item.isNull() ) {
                    QDomElement item_e = item.toElement();
                    if( !item_e.isNull() ){
                        rule.pattern = QRegExp( item_e.text().toAscii().constData() );
                        rule.format  = keywordFormat;
                        rules.append(rule);
                    }
                    item = item.nextSibling();
                }
            }
            else if( e.tagName() == "strings" ){
                parseStyle( e, stringFormat );
                stringFormat.setForeground( QColor( e.attribute( "color", "" ).toAscii().constData() ) );
                rule.pattern = QRegExp( e.text().toAscii().constData() );
                rule.format  = stringFormat;
                rules.append(rule);
            }
            else if( e.tagName() == "methods" ){
                parseStyle( e, methodFormat );
                methodFormat.setForeground( QColor( e.attribute( "color", "" ).toAscii().constData() ) );
                rule.pattern = QRegExp( e.text().toAscii().constData() );
                rule.format  = methodFormat;
                rules.append(rule);
            }
            else if( e.tagName() == "comments" ){
                parseStyle( e, commentFormat );
                parseStyle( e, multiLineCommentFormat );

                commentFormat.setForeground( QColor( e.attribute( "color", "" ).toAscii().constData() ) );
                multiLineCommentFormat.setForeground( QColor( e.attribute( "color", "" ).toAscii().constData() ) );

                QDomNode item = e.firstChild();
                while( !item.isNull() ) {
                    QDomElement item_e = item.toElement();
                    if( !item_e.isNull() ){
                        if( item_e.tagName() == "single" ){
                            rule.pattern = QRegExp( item_e.text().toAscii().constData() );
                            rule.format  = commentFormat;
                            rules.append(rule);
                        }
                        else if( item_e.tagName() == "multi" ){
                            QDomNode comms = item_e.firstChild();
                            while( !comms.isNull() ) {
                                QDomElement comm_e = comms.toElement();
                                if( !comm_e.isNull() ){
                                    if( comm_e.tagName() == "start" ){
                                        commentStartExpression = QRegExp( comm_e.text().toAscii().constData() );
                                    }
                                    else{
                                        commentEndExpression   = QRegExp( comm_e.text().toAscii().constData() );
                                    }
                                }
                                comms = comms.nextSibling();
                            }
                        }
                    }
                    item = item.nextSibling();
                }
            }
        }
        n = n.nextSibling();
    }
}

void highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, rules) {
         QRegExp expression(rule.pattern);
         int index = expression.indexIn(text);
         while (index >= 0) {
             int length = expression.matchedLength();
             setFormat(index, length, rule.format);
             index = expression.indexIn(text, index + length);
         }
     }
     setCurrentBlockState(0);

     int startIndex = 0;
     if (previousBlockState() != 1)
         startIndex = commentStartExpression.indexIn(text);

     while (startIndex >= 0) {
         int endIndex = commentEndExpression.indexIn(text, startIndex);
         int commentLength;
         if (endIndex == -1) {
             setCurrentBlockState(1);
             commentLength = text.length() - startIndex;
         } else {
             commentLength = endIndex - startIndex + commentEndExpression.matchedLength();
         }
         setFormat(startIndex, commentLength, multiLineCommentFormat);
         startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
     }
}


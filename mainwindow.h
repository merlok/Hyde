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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextCursor>
#include "manviever.h"
#include "finddialog.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString fileName;
    QString filter;
    QMessageBox msgBox;
    void openDialog();
    manViever *man;
    findDialog *findTool;
    bool findVisible;

private slots:
    void on_actionIndent_triggered();
    void on_actionUncomment_triggered();
    void on_actionComment_triggered();
    void on_codeEditor_selectionChanged();
    void on_actionCut_triggered();
    void on_actionPaste_triggered();
    void on_actionCopy_triggered();
    void on_actionRedo_triggered();
    void on_actionUndo_triggered();
    void on_codeEditor_undoAvailable(bool b);
    void on_codeEditor_redoAvailable(bool b);
    void on_codeEditor_copyAvailable(bool b);
    void on_action_new_triggered();
    void on_actionSave_as_triggered();
    void on_action_Save_triggered();
    void on_action_open_triggered();
    void findNext();
    void findPrev();

protected:
    void keyPressEvent(QKeyEvent *e);
};

#endif // MAINWINDOW_H
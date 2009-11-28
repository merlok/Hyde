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
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    findVisible = false;
    man = new manViever;
    findTool = new findDialog;
    findTool->setVisible(findVisible);
    ui->statusBar->setVisible(findVisible);
    ui->actionCopy->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    ui->actionComment->setEnabled(false);
    ui->actionUncomment->setEnabled(false);
    ui->actionIndent->setEnabled(false);
    ui->actionUnindent->setEnabled(false);
    //ui->actionPaste->setEnabled(false);
    ui->statusBar->addWidget(findTool);
    ui->dockWidget->setWidget(man);

    fileName = "";
    filter = "All files (*.*);; Hybris Source (*.hs)";

    connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(close()));
    connect(findTool,SIGNAL(nextClicked()),this,SLOT(findNext()));
    connect(findTool,SIGNAL(prevClicked()),this,SLOT(findPrev()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_open_triggered()
{
    if (ui->codeEditor->changed)
    {
        msgBox.setWindowTitle("File changed");
        msgBox.setText("The file is changed do you want to save it?");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        switch(msgBox.exec())
        {
            case QMessageBox::Save:
                if (!ui->codeEditor->isNew)
                    MainWindow::on_action_Save_triggered();
                else
                    MainWindow::on_actionSave_as_triggered();
                    openDialog();
                break;
            case QMessageBox::Discard:
                 openDialog();
                 break;
            case QMessageBox::Cancel:
                 return;
        }
    }
    else openDialog();
}

void MainWindow::on_action_Save_triggered()
{
    if (ui->codeEditor->changed && ui->codeEditor->isNew)
    {
        MainWindow::on_actionSave_as_triggered();
        return;
    }
    int ret = ui->codeEditor->saveFile(fileName);
    if (!ret)
    {
        QMessageBox::warning(this,tr("warning"),"Cannot save the file...\nDo you have permission?",QMessageBox::Ok);
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    fileName = QFileDialog::getSaveFileName(this,tr("Save file as"),QDir::homePath(),filter);
    int ret = ui->codeEditor->saveFile(fileName);
    if (!ret)
    {
        QMessageBox::warning(this,tr("warning"),"Cannot save the file...\nDo you have permission?",QMessageBox::Ok);
    }
}

void MainWindow::on_action_new_triggered()
{
    if (ui->codeEditor->changed)
    {
        msgBox.setWindowTitle("File changed");
        msgBox.setText("The file is changed do you want to save it?");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        switch(msgBox.exec())
        {
            case QMessageBox::Save:
                MainWindow::on_action_Save_triggered();
                break;
            case QMessageBox::Discard:
                 ui->codeEditor->newFile();
                 break;
            case QMessageBox::Cancel:
                 return;
        }
    }
    else ui->codeEditor->newFile();
}

void MainWindow::openDialog()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Open File"),QDir::homePath(),filter);
    if (!fileName.isEmpty())
    {
        int ret = ui->codeEditor->openFile(fileName);
        if (!ret)
        {
            QMessageBox::warning(this,tr("warning"),"The selected file not exist",QMessageBox::Ok);
        }
    }
}

void MainWindow::on_codeEditor_copyAvailable(bool b)
{
    ui->actionCopy->setEnabled(b);
    ui->actionCut->setEnabled(b);
}

void MainWindow::on_codeEditor_redoAvailable(bool b)
{
    ui->actionRedo->setEnabled(b);
}

void MainWindow::on_codeEditor_undoAvailable(bool b)
{
    ui->actionUndo->setEnabled(b);
}

void MainWindow::on_actionUndo_triggered()
{
    ui->codeEditor->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->codeEditor->redo();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->codeEditor->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->codeEditor->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->codeEditor->cut();
}

void MainWindow::on_codeEditor_selectionChanged()
{
    QTextCursor cursor  = ui->codeEditor->textCursor();
    if (!cursor.selectedText().isEmpty())
    {
        ui->actionIndent->setEnabled(true);
        ui->actionUnindent->setEnabled(true);
        ui->actionComment->setEnabled(true);
        ui->actionUncomment->setEnabled(true);
    }
    else
    {
        ui->actionComment->setEnabled(false);
        ui->actionUncomment->setEnabled(false);
        ui->actionIndent->setEnabled(false);
        ui->actionUnindent->setEnabled(false);
    }
}

void MainWindow::on_actionComment_triggered()
{
    ui->codeEditor->commentSelection(ui->codeEditor->textCursor());
}

void MainWindow::on_actionUncomment_triggered()
{
    ui->codeEditor->uncommentSelection(ui->codeEditor->textCursor());
}

void MainWindow::on_actionIndent_triggered()
{
    ui->codeEditor->indentSelection(ui->codeEditor->textCursor());
}

void MainWindow::findNext()
{
    findTool->findNext(ui->codeEditor);
}

void MainWindow::findPrev()
{
    findTool->findPrev(ui->codeEditor);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
        case Qt::Key_F3:
            if (findVisible)
                MainWindow::findNext();
            break;
        case Qt::Key_F5:
            if (findVisible)
                MainWindow::findPrev();
            break;
        default:
            QMainWindow::keyPressEvent(e);
    }
    bool ctrlF = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_F);
    if (ctrlF)
    {
        findVisible = !findVisible;
        findTool->setVisible(findVisible);
        ui->statusBar->setVisible(findVisible);
        if (findVisible)
            findTool->setFocusText();
    }
}

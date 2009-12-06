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
    ownFile     = false;
    ownChanges  = false;
    man = new manViever;
    findTool = new findDialog;
    findTool->setVisible(findVisible);
    ui->statusBar->setVisible(findVisible);

   /* ui->actionComment->setEnabled(false);
    ui->actionUncomment->setEnabled(false);
    ui->actionIndent->setEnabled(false);
    ui->actionUnindent->setEnabled(false);*/
    //ui->actionPaste->setEnabled(false);
    ui->statusBar->addWidget(findTool);
    ui->dockWidget->setWidget(man);

    fileName = "";
    filter = "All files (*.*);; Hybris Source (*.hs)";

    ui->editor_tab->removeTab(0);
    ui->editor_tab->removeTab(0);
    //lineNumber *edit = new lineNumber();
    //ui->editor_tab->addTab(edit, "Docuement");

    connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(close()));
    connect(findTool,SIGNAL(nextClicked()),this,SLOT(findNext()));
    connect(findTool,SIGNAL(prevClicked()),this,SLOT(findPrev()));
    connect(ui->editor_tab, SIGNAL(currentChanged(int)), this, SLOT(currentTab(int)));
    connect(ui->editor_tab, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::currentTab(int index)
{
    codeEditor = (lineNumber *)ui->editor_tab->currentWidget();
}

void MainWindow::closeTab(int index)
{
    ui->editor_tab->removeTab(index);
}

void MainWindow::on_action_open_triggered()
{
    if( ownFile && ownChanges )
    {
        msgBox.setWindowTitle("File changed");
        msgBox.setText("The file is changed do you want to save it?");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        switch(msgBox.exec())
        {
            case QMessageBox::Save:
                if (!codeEditor->isNew)
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
    if (codeEditor->changed && codeEditor->isNew)
    {
        MainWindow::on_actionSave_as_triggered();
        return;
    }
    int ret = codeEditor->saveFile(codeEditor->fileName);
    if (!ret)
    {
        QMessageBox::warning(this,tr("warning"),"Cannot save the file...\nDo you have permission?",QMessageBox::Ok);
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    fileName = QFileDialog::getSaveFileName(this,tr("Save file as"),QDir::homePath(),filter);
    int ret = codeEditor->saveFile(fileName);
    if (!ret) {
        QMessageBox::warning(this,tr("warning"),"Cannot save the file...\nDo you have permission?",QMessageBox::Ok);
    }
    else{
        ownChanges = false;
    }
    ui->editor_tab->setTabText(ui->editor_tab->currentIndex(), QFileInfo(fileName).fileName());
    codeEditor->fileName = fileName;
}

void MainWindow::on_action_new_triggered()
{
    lineNumber *new_editor = new lineNumber();
    int index = ui->editor_tab->addTab(new_editor, "Document");
    ui->editor_tab->setCurrentIndex(index);
}

void MainWindow::openDialog()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Open File"),QDir::homePath(),filter);
    lineNumber *editor = new lineNumber();
    if (!fileName.isEmpty()) {
        int ret = editor->openFile(fileName);
        if (!ret) {
            QMessageBox::warning(this,tr("warning"),"The selected file not exist",QMessageBox::Ok);
        }
        else{
            int index = ui->editor_tab->addTab(editor, QFileInfo(fileName).fileName());
            ui->editor_tab->setCurrentIndex(index);
            codeEditor->fileName = fileName;
            ownFile    = true;
            ownChanges = false;
        }
    }
}

void MainWindow::on_actionComment_triggered()
{
    codeEditor->commentSelection(codeEditor->textCursor());
}

void MainWindow::on_actionUncomment_triggered()
{
    codeEditor->uncommentSelection(codeEditor->textCursor());
}

void MainWindow::on_actionIndent_triggered()
{
    codeEditor->indentSelection(codeEditor->textCursor());
}

void MainWindow::findNext()
{
    findTool->findNext(codeEditor);
}

void MainWindow::findPrev()
{
    findTool->findPrev(codeEditor);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    ownChanges = true;
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

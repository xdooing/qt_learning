#include "mainWindow.h"
#include <QSettings>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
                    : QMainWindow(parent)
{
    setGeometry(300, 300, 400, 300);
    edit_ = new QTextEdit;
    edit_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
    edit_->setObjectName("edit");
    setCentralWidget(edit_);

    // save config
    // saved in /home/xdoo/.config/xdoo/notepad.conf
    QSettings setting("xdoo", "notepad");

    // menuBar is the top row in mainWindow
    // menu is the obj in menuBar
    // action is the onj in menu
    QMenuBar* menuBar = new QMenuBar;
    setMenuBar(menuBar);
    QMenu* menu = nullptr;
    menu = menuBar->addMenu("file");
    {
        QAction* action = nullptr;
        // open
        action = menu->addAction("open");
        action->setObjectName("open");
        // qDebug() << "name: " << action->objectName();
        menu->addSeparator();
        
        // save
        action = menu->addAction("save");
        action->setObjectName("save");
        // save as
        action = menu->addAction("save as");
        action->setObjectName("saveAs");
    }

    menu = menuBar->addMenu("edit");
    {
        QAction* action = nullptr;
        // auto line warp
        action = menu->addAction("line warp");
        action->setCheckable(true);
        action->setObjectName("autoLineWarp");

        bool enableLineWarp = setting.value("enableLineWarp", true).toBool();
        action->setChecked(enableLineWarp);
    }

    QMetaObject::connectSlotsByName(this);
}

void MainWindow::on_edit_textChanged() {
    has_unsaved_modify_ = true;
}

bool MainWindow::checkUnSavedModify() {
    if(has_unsaved_modify_){
        auto btn = QMessageBox::question(this, "notepad", "you have unsaved file, save it or not?",
                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        switch (btn)
        {
        case QMessageBox::Save:
            on_save_triggered();
            // need to check if cancel int saveAs
            if(current_file_name_.isEmpty())
                return true;
            break;
        case QMessageBox::Discard:
            // close();
            break;
        case QMessageBox::Cancel:
            return true;
            break;
        default:
            break;
        }
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    if(checkUnSavedModify()){
        event->ignore();
        return;
    }else {
        QMainWindow::closeEvent(event);
    }
}

void MainWindow::openFile(const QString& path) {
    QFile file(path);
    if(!file.open(QFile::ReadOnly)) {
        qWarning() << "file open failed";
        return;
    }
    QString text = QString::fromUtf8(file.readAll());
    edit_->setPlainText(text);
    current_file_name_ = path;
    has_unsaved_modify_ = false;
}

void MainWindow::on_open_triggered() {
    if(checkUnSavedModify()){
        return;
    }
    QString path = QFileDialog::getOpenFileName(this, "open file", "", "");
    if(path == "")
        return;
    
    openFile(path);
}

void MainWindow::saveFile(const QString& path) {
    QFile file(path);
    if(!file.open(QFile::WriteOnly)) {
        qWarning() << "file open failed 3";
        return;
    }
    QString text = edit_->toPlainText();
    file.write(text.toUtf8());
    current_file_name_ = path;
    has_unsaved_modify_ = false;
}

void MainWindow::on_save_triggered() {
    if(current_file_name_.isEmpty()) {
        on_saveAs_triggered();
    }else {
        saveFile(current_file_name_);
    }
}

void MainWindow::on_saveAs_triggered() {
    QString path = QFileDialog::getSaveFileName(this, "save to", "", "");
    if(path == "")
        return;
    saveFile(path);
}

void MainWindow::on_autoLineWarp_triggered(bool checked) {
    qDebug() << "autoLineWarp triggered";
    auto mode = checked ? QTextEdit::WidgetWidth : QTextEdit::NoWrap;
    edit_->setLineWrapMode(mode);
    QSettings setting("xdoo", "notepad");
    setting.setValue("enableLineWarp", checked);
}
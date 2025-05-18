#include "mainWindow.h"
#include <QSettings>
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent)
                    : QMainWindow(parent)
{
    setGeometry(300, 300, 400, 300);
    edit_ = new QTextEdit;
    edit_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
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
        action->setObjectName("saveas");
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

void MainWindow::on_open_triggered() {
    QString path = QFileDialog::getOpenFileName(this, "open file", "", "");
    if(path == "")
        return;
    QFile file(path);
    if(!file.open(QFile::ReadOnly)) {
        qWarning() << "file open failed";
        return;
    }
    QString text = QString::fromUtf8(file.readAll());
    edit_->setPlainText(text);
}

void MainWindow::on_save_triggered() {
    QString path = QFileDialog::getSaveFileName(this, "save to", "", "");
    if(path == "")
        return;
    QFile file(path);
    if(!file.open(QFile::WriteOnly)) {
        qWarning() << "file open failed 2";
        return;
    }
    QString text = edit_->toPlainText();
    file.write(text.toUtf8());
}

void MainWindow::on_autoLineWarp_triggered(bool checked) {
    qDebug() << "autoLineWarp triggered";
    auto mode = checked ? QTextEdit::WidgetWidth : QTextEdit::NoWrap;
    edit_->setLineWrapMode(mode);
    QSettings setting("xdoo", "notepad");
    setting.setValue("enableLineWarp", checked);
}
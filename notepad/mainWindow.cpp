#include "mainWindow.h"

MainWindow::MainWindow(QWidget* parent)
                    : QMainWindow(parent)
{
    setGeometry(300, 300, 400, 300);
    auto* edit = new QTextEdit;
    edit->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
    setCentralWidget(edit);

    // menuBar is the top row in mainWindow
    // menu is the obj in menuBar
    // action is the onj in menu
    QMenuBar* menuBar = new QMenuBar;
    setMenuBar(menuBar);
    QMenu* menu = menuBar->addMenu("file");
    // open
    menu->addAction("open");
    menu->addSeparator();
    // save
    menu->addAction("save");
    // save as
    menu->addAction("save as");



}
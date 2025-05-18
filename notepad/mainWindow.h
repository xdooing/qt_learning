#pragma once

#include <QMainWindow>
#include <QDebug>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>

class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget* parent = nullptr);
};
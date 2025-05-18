#pragma once

#include <QMainWindow>
#include <QDebug>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

public Q_SLOTS: /*same as 'public slots'*/
    void on_open_triggered();
    void on_save_triggered();
    void on_autoLineWarp_triggered(bool checked);

private:
    QTextEdit* edit_;
};
#pragma once

#include <QMainWindow>
#include <QDebug>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QEvent>
#include <QCloseEvent>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

protected:
    void closeEvent(QCloseEvent* event) override;
private:
    bool checkUnSavedModify();
    void openFile(const QString& path);
    void saveFile(const QString& path);

public Q_SLOTS: /*same as 'public slots'*/
    void on_open_triggered();
    void on_edit_textChanged();
    void on_save_triggered();
    void on_saveAs_triggered();
    void on_autoLineWarp_triggered(bool checked);

private:
    QTextEdit* edit_;
    QString current_file_name_;
    bool has_unsaved_modify_ = false;
};
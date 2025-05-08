#include<QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QWidget>
#include <QGridLayout>

class Label : public QLabel {
public:
    // explicit: avoid -> Label label = minWin
    explicit Label(QWidget* parent = nullptr)
                    : QLabel(parent)
    {
        setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        // setStyleSheet(R"(
        //             QLabel {
        //             background-color: #333333;
        //             color: #66ccff;
        //             font-size: 40px;}
        // )");
        setStyleSheet(R"(
                    QLabel {
                    margin: 2-0px;
                    font-size: 30px;}
        )");
    }
};

class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget* parent = nullptr)
                        : QMainWindow(parent)
    {
        // qDebug() << "win is hidden: " << win.isHidden();
        setWindowTitle("XDOO PELL");
        setGeometry(300, 300, 500, 500);
        QWidget* central = new QWidget(this);
        setCentralWidget(central);
        QGridLayout* layout = new QGridLayout;
        central->setLayout(layout);

        for(int i = 1; i < 10; ++i) {
            for(int j = 1; j < 10; ++j) {
                Label* label = new Label;
                label->setText(QString("%1 * %2 = %3").arg(i).arg(j).arg(i*j));
                layout->addWidget(label, i-1, j-1);
            }
        }
        

    }
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    MainWindow win;
    win.show();
    return app.exec();
}
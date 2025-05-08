#include<QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QtGui/QIntValidator>
#include <QLineEdit>
#include <QList>


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

enum Operator{
    None,
    Add,
    Sub,
    Mult,
    Divid,
    Equal
};

class MainWindow : public QMainWindow {
private:

    QLineEdit* line_;
    double last_value_;
    Operator last_op_;

public:
    explicit MainWindow(QWidget* parent = nullptr)
                        : QMainWindow(parent)
    {
        setWindowTitle("CALCULATOR");
        setGeometry(300, 300, 400, 300);
        QWidget* central = new QWidget(this);
        setCentralWidget(central);
        QGridLayout* layout = new QGridLayout;
        central->setLayout(layout);

        line_ = new QLineEdit;
        line_->setValidator(new QDoubleValidator);
        layout->addWidget(line_, 0, 0, 1, 4);
        line_->setText("0");

        QList<QPair<Operator, QString>> operatorList = {
            {Add, "+"},
            {Sub, "-"},
            {Mult, "*"},
            {Divid, "/"},
            {Equal, "="},
        };
        QPushButton* button = nullptr;

        // number
        {
            for(int i = 1; i <= 9; ++i) {
                button = new QPushButton;
                button->setText(QString::number(i));
                int row = 1 + (i - 1) / 3;
                int col = (i - 1) % 3;
                layout->addWidget(button, row, col);
                connect(button, &QPushButton::clicked, this, [this, i](){
                    QString text = line_->text();
                    text += QString::number(i);
                    setLineText(text);
                });
            }
            
        }
        // dot
        {
            button = new QPushButton;
            button->setText(".");
            layout->addWidget(button, 4, 0);
            connect(button, &QPushButton::clicked, this, [this](){
                QString text = line_->text();
                text += ".";
                setLineText(text);
            });
        }
        // zero
        {
            button = new QPushButton;
            button->setText("0");
            layout->addWidget(button, 4, 1);
            connect(button, &QPushButton::clicked, this, [this](){
                QString text = line_->text();
                text += "0";
                setLineText(text);
            });
        }
        // space
        {
            button = new QPushButton;
            button->setText("X");
            layout->addWidget(button, 4, 2);
            connect(button, &QPushButton::clicked, this, [this](){
                QString text = line_->text();
                if(!text.isEmpty())
                    text.remove(text.size() - 1, 1);
                setLineText(text);
            });
        }
        
        // operator
        for(int i = 0; i < operatorList.size(); ++i) {
            Operator op = operatorList[i].first;
            QString str = operatorList[i].second;
            button = new QPushButton;
            button->setText(str);
            if(op != Equal)
                layout->addWidget(button, i + 1, 3);
            else
                layout->addWidget(button, 5, 0, 1, 4);
            
            connect(button, &QPushButton::clicked, this, [this, op](){
                if(op != Equal) {
                    last_op_ = op;
                    last_value_ = getValue();
                    setLineText("0");
                }else {
                    processEqual(last_op_);
                }
            });
        }
    }

    void processEqual(const Operator& op) {
        double value = getValue();
        switch (op)
        {
        case Add:
            last_value_ = last_value_ + value;
            break;
        case Sub:
            last_value_ = last_value_ - value;
            break;
        case Mult:
            last_value_ = last_value_ * value;
            break;
        case Divid:
            last_value_ = last_value_ / value;
            break;
        default:
            break;
        }
        last_op_ = None;
        setLineText(QString::number(last_value_));
    }

    double getValue() {
        bool ok;
        double value = line_->text().toDouble(&ok);
        if(!ok) {
            qDebug() << "Error format";
            return 0;
        }else {
            return value;
        }
        
    }

    void setLineText(QString text) {
        qDebug() << "text: " << text;
        int pos = 0;
        if(line_->validator()->validate(text, pos) != QValidator::Invalid) {
            while(text.size() >= 2 &&
                  text[0] == '0' &&
                  text[1] >= '0' &&
                  text[1] <= '9')
            {
                text.remove(0, 1);
            }
            if(text.size() == 0) {
                text = "0";
            }
            line_->setText(text);
        }
    }
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    MainWindow win;
    win.show();
    return app.exec();
}
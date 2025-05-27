#include "price_calc.h"
#include <QVBoxLayout>
#include <array>

std::array<QString, typeMaxLen> kTypeNames = {
    "goc_patch",
    "spicy_money",
    "dis_count",
    "tao_ness",
    "cus_name",
};

std::array<QString, typeMaxLen> kTypes = {
    "bool",
    "bool",
    "bool",
    "int",
    "string",
};

PriceCalc::PriceCalc(QWidget* parent)
                    :QWidget(parent)
{
    auto layout = new QVBoxLayout;
    setLayout(layout);

    for(int i = 0; i < kTypeNames.size(); ++i) {
        if(kTypes[i] == "bool") {
            editors_[i] = new BoolEditor();
        }else if(kTypes[i] == "int"){
            editors_[i] = new IntEditor(0, 5);
        }else if(kTypes[i] == "string") {
            editors_[i] = new StringEditor();
        }

        editors_[i]->setTitle(kTypeNames[i]);
        layout->addWidget(editors_[i]);
        connect(editors_[i], &Editor::valueChanged, this, &PriceCalc::computePrice);
    }

    price_label_ = new QLabel;
    layout->addWidget(price_label_);

    computePrice();
}

void PriceCalc::computePrice() {
    double price = 100;
    if(editors_[gocPatch]->getValue()->boolValue()) {
        price -= 10;
    }
    if(editors_[spicyMoney]->getValue()->boolValue()) {
        price -= 5;
    }
    if(editors_[disCount]->getValue()->boolValue()) {
        price -= 8;
    }
    
    price -= editors_[taoNess]->getValue()->intValue();

    price -= editors_[cusName]->getValue()->stringValue().size();

    price_label_->setText(QString("price: %1").arg(price));
}
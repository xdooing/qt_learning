#include "price_calc.h"
#include <QVBoxLayout>
#include <array>
#include <functional>

// factory mode
class EditorFactory {
    QString type_name_;
public:
    QString getTypeName() { return type_name_; }
    EditorFactory(QString name) : type_name_(name) {}
    virtual Editor* createEditor() = 0;
};

// variadic templates
template <typename EditorType, typename... Ts>
class EditorFactoryTemplate : public EditorFactory {
    std::tuple<Ts...> args_;
public:
    explicit EditorFactoryTemplate(QString name, Ts... args) :
                EditorFactory(name), args_(args...) {}
    Editor* createEditor() override {
        return std::apply([](auto&&... arg) -> Editor*{
            return new EditorType(arg...);
        }, args_);
    }
};

using BoolEditorFactory = EditorFactoryTemplate<BoolEditor>;
using IntEditorFactory = EditorFactoryTemplate<IntEditor, int, int>;
using StringEditorFactory = EditorFactoryTemplate<StringEditor>;

#if 0
class BoolEditorFactory : public EditorFactory {
public:
    // BoolEditorFactory(QString name) : EditorFactory(name) {}
    using EditorFactory::EditorFactory;
    Editor* createEditor() override {
        return new BoolEditor();
    }
};
class IntEditorFactory : public EditorFactory {
    int min_;
    int max_;
public:
    IntEditorFactory(QString name, int min, int max) 
                    : EditorFactory(name),
                      min_(min),
                      max_(max) {}
    Editor* createEditor() override {
        return new IntEditor(min_, max_);
    }
};
class StringEditorFactory : public EditorFactory {
public:
    using EditorFactory::EditorFactory;
    Editor* createEditor() override {
        return new StringEditor();
    }
};
#endif

std::array<EditorFactory*, typeMaxLen> kEditorFactory = {
    new BoolEditorFactory("goc_patch"),
    new BoolEditorFactory("spicy_money"),
    new BoolEditorFactory("dis_count"),
    new IntEditorFactory("tao_ness", 0, 5),
    new IntEditorFactory("kill_ness", 5, 10),
    new StringEditorFactory("cus_name"),
};

PriceCalc::PriceCalc(QWidget* parent)
                    :QWidget(parent)
{
    auto layout = new QVBoxLayout;
    setLayout(layout);

    for(int i = 0; i < kEditorFactory.size(); ++i) {
        editors_[i] = kEditorFactory[i]->createEditor();
        
        editors_[i]->setTitle(kEditorFactory[i]->getTypeName());
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

    price += editors_[killNess]->getValue()->intValue();

    price -= editors_[cusName]->getValue()->stringValue().size();

    price_label_->setText(QString("price: %1").arg(price));
}
#include "editor.h"
#include <QDebug>

// for slider
IntEditor::IntEditor(int min, int max) {
    h_layout_ = new QHBoxLayout;
    label_ = new QLabel;
    slider_ = new QSlider;
    slider_->setRange(min, max);
    slider_->setOrientation(Qt::Horizontal);
    h_layout_->addWidget(label_);
    h_layout_->addWidget(slider_);
    setLayout(h_layout_);

    connect(slider_, &QSlider::valueChanged, this, &Editor::valueChanged);
    // qDebug() << "new QSlider...";
}

void IntEditor::setTitle(const QString& name) {
    label_->setText(name);
}

Value* IntEditor::getValue() {
    return new IntValue(slider_->value());
}

// for checkBox
BoolEditor::BoolEditor() {
    auto layout = new QVBoxLayout;
    setLayout(layout);
    box_ = new QCheckBox;
    layout->addWidget(box_);
    connect(box_, &QCheckBox::stateChanged, this, &Editor::valueChanged);
    // qDebug() << "new QCheckBox...";
}

void BoolEditor::setTitle(const QString& name) {
    box_->setText(name);
}

Value* BoolEditor::getValue() {
    return new BoolValue(box_->isChecked());
}

StringEditor::StringEditor() {
    h_layout_ = new QHBoxLayout;
    label_ = new QLabel;
    line_ = new QLineEdit;
    h_layout_->addWidget(label_);
    h_layout_->addWidget(line_);
    setLayout(h_layout_);

    connect(line_, &QLineEdit::textEdited, this, &Editor::valueChanged);
}

void StringEditor::setTitle(const QString& name) {
    label_->setText(name);
}

Value* StringEditor::getValue() {
    return new StringValue(line_->text());
}

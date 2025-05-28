#pragma once

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QSlider>
#include "editor.h"

enum checkType {
    gocPatch,
    spicyMoney,
    disCount,
    taoNess,
    killNess,
    cusName,

    typeMaxLen, // for record max len of enum
};

class PriceCalc : public QWidget {
    Q_OBJECT

public:
    Editor* editors_[typeMaxLen];
    QLabel* price_label_;
public:
    explicit PriceCalc(QWidget* parent = nullptr);
    void computePrice();
};

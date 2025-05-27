#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QSlider>
#include <QLineEdit>

class Value : public QObject {
private:
    // Pure virtual functions avoid base class instantiation
    virtual void dummy() = 0; 
public:
    // The purpose is to prevent incorrect calls. eg-> IntEditor->boolValue()
    virtual int intValue() { throw; }
    virtual bool boolValue() { throw; }
    virtual QString stringValue() { throw; }
};

class IntValue : public Value {
private:
    void dummy() override {}
    int int_value_;
public:
    IntValue(int a) : int_value_(a) {}
    int intValue() override {
        return int_value_;
    }
};

class BoolValue : public Value {
private:
    void dummy() override {}
    bool bool_value_;
public:
    BoolValue(bool a) : bool_value_(a) {}
    bool boolValue() override {
        return bool_value_;
    }
};

class StringValue : public Value {
private:
    void dummy() override {}
    QString s_value_;
public:
    StringValue(QString a) : s_value_(a) {}
    QString stringValue() override {
        return s_value_;
    }
};


class Editor : public QWidget {
    Q_OBJECT
public:

Q_SIGNALS:
    void valueChanged();

public:
    virtual void setTitle(const QString& name) = 0;
    virtual Value* getValue() = 0;

};

// int for slider
class IntEditor : public Editor {
    Q_OBJECT
public:
    IntEditor(int min, int max);

    void setTitle(const QString& name) override;
    Value* getValue() override;
private:
    QLabel* label_;
    QHBoxLayout* h_layout_;
    QSlider* slider_;
};

// bool for checkbox
class BoolEditor : public Editor {
    Q_OBJECT
public:
    BoolEditor();

    void setTitle(const QString& name) override;
    Value* getValue() override;
private:
    QCheckBox* box_;
};

class StringEditor : public Editor {
    Q_OBJECT
public:
    StringEditor();

    void setTitle(const QString& name) override;
    Value* getValue() override;
private:
    QLineEdit* line_;
    QLabel* label_;
    QHBoxLayout* h_layout_;
};


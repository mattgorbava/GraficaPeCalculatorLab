#pragma once

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QComboBox>
#include <QTextEdit>
#include <QLabel>
#include "CurvedLine.h"
#include "Transformare.h"

class CurvedLineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CurvedLineWidget(QWidget* parent = nullptr);
    ~CurvedLineWidget();

protected:
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;

private:
    CurvedLine curvedLine;

    QComboBox* xFunctionComboBox;
    QComboBox* yFunctionComboBox;
    QTextEdit* intervalStartTextEdit;
    QTextEdit* intervalEndTextEdit;
    QTextEdit* resolutionTextEdit;

    QLabel* xFunctionLabel;
    QLabel* yFunctionLabel;
    QLabel* intervalLabel;
    QLabel* resolutionLabel;
};
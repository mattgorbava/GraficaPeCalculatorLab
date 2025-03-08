#pragma once

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QComboBox>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include "CurvedLine.h"
#include "Transformare.h"
#include "polygon.h"

class CurvedLineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CurvedLineWidget(QWidget* parent = nullptr);
    ~CurvedLineWidget();

private slots:
    void saveButtonClicked();
    void nextStepButtonClicked();

protected:
    virtual void paintEvent(QPaintEvent* event) override;
    //virtual void mousePressEvent(QMouseEvent* event) override;

private:
    CurvedLine curvedLine;
    Polygon polygon;

    QLabel* instructionalLabel;

    QComboBox* predefinedComboBox;
    QComboBox* xFunctionComboBox;
    QComboBox* yFunctionComboBox;
    QTextEdit* xCoefficientTextEdit;
    QTextEdit* yCoefficientTextEdit;
    QTextEdit* intervalStartTextEdit;
    QTextEdit* intervalEndTextEdit;
    QTextEdit* resolutionTextEdit;
    QPushButton* saveButton;
    QPushButton* nextStepButton;
    QLine* oXLine;
    QLine* oYLine;
    QLine* oXArrow1, *oxArrow2;
    QLine* oYArrow1, *oYArrow2;
    QLabel* xLabel;
    QLabel* yLabel;
    QLabel* OLabel;

    QLabel* predefinedLabel;
    QLabel* xFunctionLabel;
    QLabel* yFunctionLabel;
    QLabel* xCoefficientLabel;
    QLabel* yCoefficientLabel;
    QLabel* intervalLabel;
    QLabel* resolutionLabel;
    QLabel* titleLabel;

    double resolution = 100;
    bool curveSaved = false;
    int step = 0;
};
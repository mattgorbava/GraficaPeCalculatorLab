#pragma once

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QDebug>
#include "polygon.h"
#include "Transformare.h"

class CurvedLineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CurvedLineWidget(QWidget* parent = nullptr);
    ~CurvedLineWidget();

protected:

private:
};
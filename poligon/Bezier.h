#include <QWidget>
#include <QVector>
#include <QPointF>
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <QPainterPath>
#include <QLineF>
#include <QMessageBox>

class Bezier : public QWidget
{
    Q_OBJECT

public:
    Bezier(QWidget* parent = nullptr)
        : QWidget(parent),
        addingPoints(true),
        selectedPointIndex(-1),
        draggingPoint(false),
        pointRadius(5.0),
        curveStep(0.01)
    {
        setMouseTracking(true); // Enable mouse move events even when no button is pressed
    }
    ~Bezier() override = default;

protected:
    void paintEvent(QPaintEvent* event) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        drawControlPoints(painter);
        if (!controlPoints.isEmpty() && !addingPoints) {
            drawInterpolationCurve(painter);
        }
    }

    void mousePressEvent(QMouseEvent* event) override
    {
        if (addingPoints) {
            if (event->button() == Qt::LeftButton) {
                controlPoints.append(event->pos());
                lastPoint = event->pos();
                update();
            }
            else if (event->button() == Qt::RightButton) {
                if (controlPoints.isEmpty()) {
                    QMessageBox::warning(this, "Error", "Please input at least one point before finishing.");
                    return;
                }
                addingPoints = false;
                update(); // Redraw to show the curve
            }
        }
        else {
            if (event->button() == Qt::LeftButton) {
                selectedPointIndex = findNearsestPointIndex(event->pos());
                if (selectedPointIndex != -1) {
                    draggingPoint = true;
                }
            }
        }
    }

    void mouseMoveEvent(QMouseEvent* event) override
    {
        if (draggingPoint && selectedPointIndex != -1) {
            QPointF newPos = event->pos();
            controlPoints[selectedPointIndex] = newPos;
            update();
        }
    }

    void mouseReleaseEvent(QMouseEvent* event) override
    {
        if (event->button() == Qt::LeftButton) {
            draggingPoint = false;
            selectedPointIndex = -1;
        }
    }

private:
    QVector<QPointF> controlPoints;
    bool addingPoints;
    QPointF lastPoint;
    int selectedPointIndex;
    bool draggingPoint;
    double pointRadius;
    double curveStep; // Step for drawing the curve

    // Helper function to calculate binomial coefficient (n choose i)
    long long binomialCoeff(int n, int k) const {
        if (k < 0 || k > n) {
            return 0;
        }
        if (k == 0 || k == n) {
            return 1;
        }
        if (k > n / 2) {
            k = n - k;
        }
        long long res = 1;
        for (int i = 1; i <= k; ++i) {
            res = res * (n - i + 1) / i;
        }
        return res;
    }


    QPointF bezierPoint(double u, const QVector<QPointF>& p) const
    {
        double x = 0.0;
        double y = 0.0;
        int n = p.size() - 1;
        for (int i = 0; i <= n; ++i) {
            double b = binomialCoeff(n, i) * pow(u, i) * pow(1 - u, n - i);
            x += b * p[i].x();
            y += b * p[i].y();
        }
        return QPointF(x, y);
    }


    QVector<QPointF> calculateInterpolationPoints() const
    {
        QVector<QPointF> curvePoints;
        if (controlPoints.size() < 2) return curvePoints;

        int n = controlPoints.size() - 1;
        for (double u = 0; u <= 1.0; u += curveStep) {
            curvePoints.append(bezierPoint(u, controlPoints));
        }
        return curvePoints;
    }


    void drawControlPoints(QPainter& painter) const
    {
        QPen pointPen(Qt::blue);
        pointPen.setWidth(2);
        painter.setPen(pointPen);
        painter.setBrush(Qt::green);

        QPen linePen(Qt::lightGray);
        linePen.setWidth(1);
        painter.setPen(linePen);

        for (int i = 0; i < controlPoints.size(); ++i) {
            painter.drawEllipse(controlPoints[i], pointRadius, pointRadius);
            if (i > 0) {
                painter.drawLine(controlPoints[i - 1], controlPoints[i]);
            }
        }
    }

    void drawInterpolationCurve(QPainter& painter) const
    {
        QVector<QPointF> curvePoints = calculateInterpolationPoints();
        if (curvePoints.isEmpty()) return;

        QPen curvePen;
        curvePen.setColor(Qt::magenta); // Distinct color for Bezier
        curvePen.setWidth(2);
        painter.setPen(curvePen);

        painter.drawPoints(curvePoints.constData(), curvePoints.size()); // Draw points for Bezier
    }

    int findNearsestPointIndex(const QPointF& pos) const
    {
        for (int i = 0; i < controlPoints.size(); ++i) {
            if (QLineF(controlPoints[i], pos).length() <= 10) { // 10 pixels tolerance
                return i;
            }
        }
        return -1;
    }
};
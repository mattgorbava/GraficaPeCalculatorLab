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

class Hermite : public QWidget
{
    Q_OBJECT

public:
    Hermite(QWidget* parent = nullptr)
        : QWidget(parent),
        addingPoints(true),
        selectedPointIndex(-1),
        draggingPoint(false),
        pointRadius(5.0),
        curveStep(0.01)
    {
        setMouseTracking(true); // Enable mouse move events even when no button is pressed
    }
    ~Hermite() override = default;

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
                // Removed x-coordinate constraint for adding points
                controlPoints.append(event->pos());
                lastPoint = event->pos();
                update();

            }
            else if (event->button() == Qt::RightButton) {
                if (controlPoints.size() % 2 != 0) {
                    QMessageBox::warning(this, "Error", "Please input an even number of points before finishing.");
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
            // Removed x-coordinate constraints for point movement
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


    QPointF coonsHermiteInterpolation(const QPointF& p0, const QPointF& p1, const QPointF& t0, const QPointF& t1, double u) const
    {
        double h00 = (2.0 * pow(u, 3) - 3.0 * pow(u, 2) + 1.0);
        double h01 = (-2.0 * pow(u, 3) + 3.0 * pow(u, 2));
        double h10 = (pow(u, 3) - 2.0 * pow(u, 2) + u);
        double h11 = (pow(u, 3) - pow(u, 2));

        double x = h00 * p0.x() + h01 * p1.x() + h10 * t0.x() + h11 * t1.x();
        double y = h00 * p0.y() + h01 * p1.y() + h10 * t0.y() + h11 * t1.y();
        return QPointF(x, y);
    }


    QVector<QPointF> calculateInterpolationPoints() const
    {
        QVector<QPointF> curvePoints;
        if (controlPoints.size() < 4) return curvePoints; // Need at least 4 points for one segment

        for (int i = 0; i <= controlPoints.size() - 4; i += 2) { // Iterate by segments, 4 points per segment
            QPointF p0 = controlPoints[i];         // Start point of segment
            QPointF t0_point = controlPoints[i + 1]; // Tangent control point for p0
            QPointF p1 = controlPoints[i + 2];     // End point of segment (and start of next)
            QPointF t1_point = controlPoints[i + 3]; // Tangent control point for p1

            // Revised tangent calculation - Direct vectors from control points
            QPointF t0 = controlPoints[i + 1] - controlPoints[i]; // Tangent at p0 towards t0_point
            QPointF t1 = controlPoints[i + 3] - controlPoints[i + 2]; // Tangent at p1 towards t1_point


            int segmentsPerCurve = 50; // Adjust for curve smoothness
            for (int j = 0; j <= segmentsPerCurve; ++j) {
                double u = static_cast<double>(j) / segmentsPerCurve;
                curvePoints.append(coonsHermiteInterpolation(p0, p1, t0, t1, u));
            }
        }
        return curvePoints;
    }


    void drawControlPoints(QPainter& painter) const
    {
        QPen pointPen(Qt::green);
        pointPen.setWidth(2);
        painter.setPen(pointPen);
        painter.setBrush(Qt::green);

        QPen tangentPen(Qt::lightGray); // Pen for tangent lines
        tangentPen.setWidth(1);
        painter.setPen(tangentPen);
        painter.setBrush(Qt::NoBrush); // No fill for tangent control points

        for (int i = 0; i < controlPoints.size(); ++i) {
            if (i % 2 == 0) {
                painter.setPen(pointPen);
                painter.setBrush(Qt::green);
                painter.drawEllipse(controlPoints[i], pointRadius, pointRadius); // Curve points are blue and filled
                if (i + 1 < controlPoints.size()) {
                    painter.setPen(tangentPen); // Draw tangent line
                    painter.drawLine(controlPoints[i], controlPoints[i + 1]);
                }

            }
            else {
                painter.setPen(tangentPen);
                painter.setBrush(Qt::NoBrush); // No fill for tangent control points
                painter.drawEllipse(controlPoints[i], pointRadius * 0.7, pointRadius * 0.7); // Tangent points smaller and not filled
            }
        }
    }

    void drawInterpolationCurve(QPainter& painter) const
    {
        QVector<QPointF> curvePoints = calculateInterpolationPoints();
        if (curvePoints.isEmpty()) return;

        QPen curvePen;
        curvePen.setColor(Qt::magenta); // Distinct color for Coons-Hermite
        curvePen.setWidth(2);
        painter.setPen(curvePen);

        painter.drawPoints(curvePoints.constData(), curvePoints.size()); // Draw points for Coons-Hermite
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

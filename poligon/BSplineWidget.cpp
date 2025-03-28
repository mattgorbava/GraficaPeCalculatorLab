#include "BSplineWidget.h"

BSplineWidget::BSplineWidget(QWidget* parent)
	: QWidget(parent)
{
	setMouseTracking(true);
}

void BSplineWidget::paintEvent(QPaintEvent* e)
{
	QPainter painter(this);

	for (auto node : controlPoints)
	{
		painter.setBrush(Qt::black);
		painter.drawEllipse(node->getCoordinates(), 5, 5);
	}

	if (saved)
	{
		std::vector<QPointF> points = BSpline::computeBSplineCurve(controlPoints, k);
		painter.setPen(Qt::red);
		for (int i = 0; i < points.size() - 1; i++)
		{
			painter.drawLine(points[i], points[i + 1]);
		}
	}
}

void BSplineWidget::mouseMoveEvent(QMouseEvent* e)
{
	if (isDragging)
	{
		draggedNode->setCoordinates(e->pos());
		update();
	}
}

void BSplineWidget::mouseReleaseEvent(QMouseEvent* e)
{
	isDragging = false;
	draggedNode = aux;

	if (!saved)
	{
		if (e->button() == Qt::LeftButton)
		{
			bool addNode = true;
			for (auto& node : controlPoints)
				if (fabs(node->getCoordX() - e->pos().x()) < 20 && fabs(node->getCoordY() - e->pos().y()) < 20)
					addNode = false;

			if (addNode)
			{
				controlPoints.push_back(new Node(e->pos()));
				update();
			}
		}
		else if (e->button() == Qt::RightButton)
		{
			QInputDialog dialog;
			dialog.setLabelText("Introduceti gradul curbei B-Spline");
			dialog.setInputMode(QInputDialog::IntInput);
			dialog.setIntRange(1, controlPoints.size() - 1);
			if (dialog.exec() == QDialog::Accepted)
			{
				k = dialog.intValue();
				saved = true;
				update();
			}
		}
	}
}

void BSplineWidget::mousePressEvent(QMouseEvent* e)
{
	for (auto& node : controlPoints)
	{
		if (fabs(node->getCoordX() - e->pos().x()) < 10 && fabs(node->getCoordY() - e->pos().y()) < 10)
		{
			isDragging = true;
			draggedNode = node;
			aux = draggedNode;
			break;
		}
	}
}
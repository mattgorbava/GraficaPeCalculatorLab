#include "mainwindow.h"
#include <QPainter>
#include <QPalette>

mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->setFixedSize(1000, 600);

    xLabel.setParent(this);
    yLabel.setParent(this);
    oLabel.setParent(this);

    xLabel.setAlignment(Qt::AlignTop | Qt::AlignLeft);
    yLabel.setAlignment(Qt::AlignTop | Qt::AlignLeft);
    oLabel.setAlignment(Qt::AlignTop | Qt::AlignLeft);

    xLabel.move(785, 290); 
    yLabel.move(400, 570); 
    oLabel.move(380, 280);

    xLabel.show();
    yLabel.show();
    oLabel.show();

    /*clearButton.setParent(this);
    clearButton.setText("Clear");
    clearButton.move(800, 10);
    clearButton.show();*/

    int sliderWidth = 150;
    int sliderHeight = 20;
    int labelHeight = 20;
    int rightMargin = 20;
    int topMargin = 15;
    int spacing = 15;

    rotationLabel.setParent(this);
    translationXLabel.setParent(this);
    translationYLabel.setParent(this);
    scalingXLabel.setParent(this);
    scalingYLabel.setParent(this);

    rotationSlider.setParent(this);
    translationXSlider.setParent(this);
    translationYSlider.setParent(this);
    scalingXSlider.setParent(this);
    scalingYSlider.setParent(this);

    rotationLabel.setGeometry(width() - sliderWidth - rightMargin, topMargin, sliderWidth, labelHeight);
    rotationSlider.setGeometry(width() - sliderWidth - rightMargin, topMargin + labelHeight, sliderWidth, sliderHeight);
    rotationSlider.setOrientation(Qt::Horizontal);
    rotationSlider.setEnabled(false);

    translationXLabel.setGeometry(width() - sliderWidth - rightMargin, topMargin + labelHeight + sliderHeight + spacing, sliderWidth, labelHeight);
    translationXSlider.setGeometry(width() - sliderWidth - rightMargin, topMargin + labelHeight + 2 * (sliderHeight + spacing), sliderWidth, sliderHeight);
    translationXSlider.setOrientation(Qt::Horizontal);
    translationXSlider.setEnabled(false);

    translationYLabel.setGeometry(width() - sliderWidth - rightMargin, topMargin + labelHeight + 2 * (sliderHeight + spacing) + labelHeight + spacing, sliderWidth, labelHeight);
    translationYSlider.setGeometry(width() - sliderWidth - rightMargin, topMargin + labelHeight + 3 * (sliderHeight + spacing) + labelHeight + spacing, sliderWidth, sliderHeight);
    translationYSlider.setOrientation(Qt::Horizontal);
    translationYSlider.setEnabled(false);

    scalingXLabel.setGeometry(width() - sliderWidth - rightMargin, topMargin + labelHeight + 3 * (sliderHeight + spacing) + 2 * (labelHeight + spacing), sliderWidth, labelHeight);
    scalingXSlider.setGeometry(width() - sliderWidth - rightMargin, topMargin + labelHeight + 4 * (sliderHeight + spacing) + 2 * (labelHeight + spacing), sliderWidth, sliderHeight);
    scalingXSlider.setOrientation(Qt::Horizontal);
    scalingXSlider.setEnabled(false);

    scalingYLabel.setGeometry(width() - sliderWidth - rightMargin, topMargin + labelHeight + 4 * (sliderHeight + spacing) + 3 * (labelHeight + spacing), sliderWidth, labelHeight);
    scalingYSlider.setGeometry(width() - sliderWidth - rightMargin, topMargin + labelHeight + 5 * (sliderHeight + spacing) + 3 * (labelHeight + spacing), sliderWidth, sliderHeight);
    scalingYSlider.setOrientation(Qt::Horizontal);
    scalingYSlider.setEnabled(false);

    connect(&rotationSlider, &QSlider::valueChanged, this, &mainwindow::onRotationSliderChanged);
    connect(&translationXSlider, &QSlider::valueChanged, this, &mainwindow::onTranslationXSliderChanged);
    connect(&translationYSlider, &QSlider::valueChanged, this, &mainwindow::onTranslationYSliderChanged);
    connect(&scalingXSlider, &QSlider::valueChanged, this, &mainwindow::onScalingXSliderChanged);
    connect(&scalingYSlider, &QSlider::valueChanged, this, &mainwindow::onScalingYSliderChanged);

    rotationLabel.show();
    translationXLabel.show();
    translationYLabel.show();
    scalingXLabel.show();
    scalingYLabel.show();

    rotationSlider.show();
    translationXSlider.show();
    translationYSlider.show();
    scalingXSlider.show();
    scalingYSlider.show();
}

mainwindow::~mainwindow()
{}

void mainwindow::initializeSliders()
{
    rotationSlider.setEnabled(true);
    translationXSlider.setEnabled(true);
    translationYSlider.setEnabled(true);
    scalingXSlider.setEnabled(true);
    scalingYSlider.setEnabled(true);

    rotationSlider.setRange(0, 360);
    translationXSlider.setRange(-100, 100);
    translationYSlider.setRange(-100, 100);
    scalingXSlider.setRange(0, 200);
    scalingYSlider.setRange(0, 200);

    polygon.computeCenterOfMass();
    QPoint centerOfMass = polygon.getCenterOfMass();

    double normalizedX = (centerOfMass.x() - 400) / 400.0;
    double normalizedY = (centerOfMass.y() - 300) / 300.0;

    translationXSlider.setValue(static_cast<int>(normalizedX * 100));
    translationYSlider.setValue(static_cast<int>(normalizedY * 100));
    
    double angleRadians = atan2(centerOfMass.y() - 300, centerOfMass.x() - 400);
    int angleDegrees = static_cast<int>(angleRadians * 180.0 / M_PI);
    if (angleDegrees < 0) {
        angleDegrees += 360;
    }
    rotationSlider.setValue(angleDegrees);

    scalingXSlider.setValue(100); 
    scalingYSlider.setValue(100); 
}

void mainwindow::mouseReleaseEvent(QMouseEvent* e)
{
    if (!polygonSaved)
    {
        std::vector<Node*> nodes = polygon.getNodes();
        std::vector<Edge*> edges = polygon.getEdges();

        if (e->button() == Qt::RightButton)
        {
            bool addNode = true;
        
            for (auto& node : nodes)
                if (fabs(node->getCoordX() - e->pos().x()) < 20 && fabs(node->getCoordY() - e->pos().y()) < 20)
                    addNode = false;

            if (addNode)
            {
                polygon.addNode(e->pos());
                update();
            }
        }

        if (e->button() == Qt::LeftButton)
        {
            for (auto& node : nodes)
            {
                if (fabs(node->getCoordX() - e->pos().x()) < 10 && fabs(node->getCoordY() - e->pos().y()) < 10)
                {
                    if (firstNode->getValue() == -1)
                        firstNode = node;
                    else
                    {
                        QPoint point1 = firstNode->getCoordinates();
                        QPoint point2 = node->getCoordinates();
                        if (firstNode == node)
							break;
                        if (firstNode->getAdjacentNodesCounter() >= 2 || node->getAdjacentNodesCounter() >= 2)
                            break;
                        polygon.addEdge(firstNode, node);
                        if (isPolygonClosed())
                        {
                            polygonSaved = true;
                            initializeSliders();
                        }
                        firstNode = aux;
                    }
                    break;
                }
                else if (firstNode->getValue() != -1 && node->getValue() == nodes.size())
			    {
				    firstNode = aux;
			    }
            }
            update();
        }
    }
}

void mainwindow::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    //painter.fillRect(rect(), Qt::white);

    std::vector<Node*> nodes = polygon.getNodes();
    std::vector<Edge*> edges = polygon.getEdges();

    painter.drawLine(oX);
    painter.drawLine(oY);
    painter.drawLine(xArrow);
    painter.drawLine(yArrow);
    painter.drawLine(xArrow2);
    painter.drawLine(yArrow2);

    if (!polygonSaved)
    {
        for (auto& node : nodes)
        {
            QRect rectangle(node->getCoordX() - 10, node->getCoordY() - 10, 20, 20);
            painter.drawEllipse(rectangle);
            QString s;
            s.setNum(node->getValue());
            painter.drawText(rectangle, Qt::AlignCenter, s);
        }
    }

    for (auto& edge : edges)
    {
        
        if (!polygonSaved)
        {
            double unghiulDreptei{ atan2(edge->getSecondNode()->getCoordY() - edge->getFirstNode()->getCoordY(),
                                        edge->getSecondNode()->getCoordX() - edge->getFirstNode()->getCoordX()) };
            double lungimePeAxaX1{ cos(unghiulDreptei) * 10 };// pt muchie
            double lungimePeAxaY1{ sin(unghiulDreptei) * 10 };// pt muchie

            painter.drawLine(edge->getFirstNode()->getCoordX() + lungimePeAxaX1, edge->getFirstNode()->getCoordY() + lungimePeAxaY1,
                edge->getSecondNode()->getCoordX() - lungimePeAxaX1, edge->getSecondNode()->getCoordY() - lungimePeAxaY1);
        }
        else
        {
			painter.drawLine(edge->getFirstNode()->getCoordX(), edge->getFirstNode()->getCoordY(),
				edge->getSecondNode()->getCoordX(), edge->getSecondNode()->getCoordY());
        }
    }

    if (!polygonSaved)
    {
        if (firstNode->getValue() != -1)
        {
            QRect rectangle(firstNode->getCoordX() - 10, firstNode->getCoordY() - 10, 20, 20);
            QPen pen;
            pen.setColor(Qt::red);
            pen.setWidth(2);
            painter.setPen(pen);
            painter.drawEllipse(rectangle);
            QString s;
            s.setNum(firstNode->getValue());
            painter.drawText(rectangle, Qt::AlignCenter, s);
        }
    }
}

void mainwindow::onRotationSliderChanged(int value)
{
    double angle = value - rotationAngle;
    rotationAngle = value;
    polygon.computeCenterOfMass();
    QPoint centerOfMass = polygon.getCenterOfMass();
    for (auto& node : polygon.getNodes())
    {
        node->setCoordinates(Transformare::rotatePointAroundPoint(node->getCoordinates(), QPoint(400, 300), angle)) ;
    }
    update();
}

void mainwindow::onScalingXSliderChanged(int value)
{
	double scale = value / 100.0;
	for (auto& node : polygon.getNodes())
	{
        node->setCoordinates(Transformare::scalePointAroundPoint(node->getCoordinates(), QPoint(400, 300), scale, 1));
	}
	update();
}

void mainwindow::onScalingYSliderChanged(int value)
{
	double scale = value / 100.0;
	for (auto& node : polygon.getNodes())
	{
		node->setCoordinates(Transformare::scalePointAroundPoint(node->getCoordinates(), QPoint(400, 300), 1, scale));
	}
	update();
}

void mainwindow::onTranslationXSliderChanged(int value)
{
	double translationX = value / 100.0;
	double translationY = translationYSlider.value() / 100.0;
	for (auto& node : polygon.getNodes())
	{
		node->setCoordinates(Transformare::translatePoint(node->getCoordinates(), translationX, translationY));
	}
	update();
}

void mainwindow::onTranslationYSliderChanged(int value)
{
	double translationY = value / 100.0;
	double translationX = translationXSlider.value() / 100.0;
	for (auto& node : polygon.getNodes())
	{
		node->setCoordinates(Transformare::translatePoint(node->getCoordinates(), translationX, translationY));
	}
	update();
}

void mainwindow::mouseMoveEvent(QMouseEvent* e)
{
    if (!polygonSaved)
    {
        QPoint mousePos = e->pos();
        if (isDragging && draggedNode)
        {
            draggedNode->setCoordinates(mousePos);
            firstNode = aux;
            update();
        }
    }
}

void mainwindow::mousePressEvent(QMouseEvent* e)
{
    if (!polygonSaved)
    {
        std::vector<Node*> nodes = polygon.getNodes();
        for (auto& node : nodes)
        {
            if (fabs(node->getCoordX() - e->pos().x()) < 10 && fabs(node->getCoordY() - e->pos().y()) < 10)
            {
                draggedNode = node;
                isDragging = true;
                break;
            }
        }
    }
}

bool mainwindow::isPolygonClosed()
{
    for (auto& node : polygon.getNodes())
		if (node->getAdjacentNodesCounter() != 2)
			return false;
    return true;
}
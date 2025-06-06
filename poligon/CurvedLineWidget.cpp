#include "CurvedLineWidget.h"

CurvedLineWidget::CurvedLineWidget(QWidget* parent)
	: QWidget(parent)
{
	origin = new Node(QPointF(0, 0));
	oXLine = new QLineF(0, origin->getCoordY(), parent->size().width(), 0);
	oYLine = new QLineF(origin->getCoordX(), 0, 0, parent->size().height());
	oXArrow1 = new QLine(parent->size().width() - 10, 10, parent->size().width(), 0);
	oxArrow2 = new QLine(parent->size().width() - 10, -10, parent->size().width(), 0);
	oYArrow1 = new QLine(-10, parent->size().height() - 10, 0, parent->size().height());
	oYArrow2 = new QLine(10, parent->size().height() - 10, 0, parent->size().height());
	xLabel = new QLabel("X", this);
	xLabel->setGeometry(parent->size().width() - 20, 20, 20, 20);
	xLabel->setFont(QFont("Arial", 10, 10));
	yLabel = new QLabel("Y", this);
	yLabel->setGeometry(20, parent->size().height() - 20, 20, 20);
	OLabel = new QLabel("O", this);
	OLabel->setGeometry(origin->getCoordX(), origin->getCoordY(), 20, 20);
	titleLabel = new QLabel("Tema 2", this);
	titleLabel->setGeometry(685, 15, 100, 20);
	titleLabel->setFont(QFont("Arial", 20, 10));
	titleLabel->show();

	instructionalLabel = new QLabel("Select a predefined curve or select the undefined value for it and add parameters", this);
	instructionalLabel->setGeometry(10, 10, 500, 20);

	predefinedComboBox = new QComboBox(this);
	predefinedComboBox->addItem("Elipse");
	predefinedComboBox->addItem("Spiral2D");
	predefinedComboBox->addItem("XSquaredPlus1");
	predefinedComboBox->addItem("Undefined");
	predefinedComboBox->setGeometry(10, 160, 100, 20);

	predefinedLabel = new QLabel("Predefined", this);
	predefinedLabel->setGeometry(120, 160, 100, 20);

	xFunctionComboBox = new QComboBox(this);
	xFunctionComboBox->addItem("Linear");
	xFunctionComboBox->addItem("Quadratic");
	xFunctionComboBox->addItem("Exponential");
	xFunctionComboBox->addItem("Logarithmic");
	xFunctionComboBox->addItem("Sine");
	xFunctionComboBox->addItem("Cosine");
	xFunctionComboBox->addItem("Tangent");
	xFunctionComboBox->addItem("Cotangent");
	xFunctionComboBox->setGeometry(10, 40, 100, 20);

	yFunctionComboBox = new QComboBox(this);
	yFunctionComboBox->addItem("Linear");
	yFunctionComboBox->addItem("Quadratic");
	yFunctionComboBox->addItem("Exponential");
	yFunctionComboBox->addItem("Logarithmic");
	yFunctionComboBox->addItem("Sine");
	yFunctionComboBox->addItem("Cosine");
	yFunctionComboBox->addItem("Tangent");
	yFunctionComboBox->addItem("Cotangent");
	yFunctionComboBox->setGeometry(10, 70, 100, 20);

	xCoefficientTextEdit = new QTextEdit(this);
	xCoefficientTextEdit->setGeometry(230, 40, 100, 20);

	yCoefficientTextEdit = new QTextEdit(this);
	yCoefficientTextEdit->setGeometry(230, 70, 100, 20);

	intervalStartTextEdit = new QTextEdit(this);
	intervalStartTextEdit->setGeometry(10, 100, 100, 20);

	intervalEndTextEdit = new QTextEdit(this);
	intervalEndTextEdit->setGeometry(120, 100, 100, 20);

	resolutionTextEdit = new QTextEdit(this);
	resolutionTextEdit->setGeometry(10, 130, 100, 20);

	xFunctionLabel = new QLabel("X Function", this);
	xFunctionLabel->setGeometry(120, 40, 100, 20);

	yFunctionLabel = new QLabel("Y Function", this);
	yFunctionLabel->setGeometry(120, 70, 100, 20);

	xCoefficientLabel = new QLabel("X Coefficient", this);
	xCoefficientLabel->setGeometry(340, 40, 100, 20);

	yCoefficientLabel = new QLabel("Y Coefficient", this);
	yCoefficientLabel->setGeometry(340, 70, 100, 20);

	intervalLabel = new QLabel("Interval", this);
	intervalLabel->setGeometry(230, 100, 100, 20);

	resolutionLabel = new QLabel("Resolution", this);
	resolutionLabel->setGeometry(120, 130, 100, 20);

	saveButton = new QPushButton("Save", this);
	saveButton->setGeometry(10, 190, 100, 20);
	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked()));

	nextStepButton = new QPushButton("Next Step", this);
	nextStepButton->setGeometry(680, 160, 100, 20);
	connect(nextStepButton, SIGNAL(clicked()), this, SLOT(nextStepButtonClicked()));

	instructionalLabel->show();
	predefinedComboBox->show();
	xFunctionComboBox->show();
	yFunctionComboBox->show();
	xCoefficientTextEdit->show();
	yCoefficientTextEdit->show();
	intervalStartTextEdit->show();
	intervalEndTextEdit->show();
	resolutionTextEdit->show();
	xFunctionLabel->show();
	yFunctionLabel->show();
	xCoefficientLabel->show();
	yCoefficientLabel->show();
	intervalLabel->show();
	resolutionLabel->show();
	saveButton->show();
	
	nextStepButton->hide();
	xLabel->hide();
	yLabel->hide();
	OLabel->hide();
}

CurvedLineWidget::~CurvedLineWidget()
{ }

void CurvedLineWidget::saveButtonClicked()
{
	if (predefinedComboBox->currentIndex() != 3)
	{
		CurvedLine::Predefined predefined = CurvedLine::Predefined(predefinedComboBox->currentIndex());
		curvedLine = CurvedLine(predefined);
	}
	else
	{
		CurvedLine::Function xFunction = CurvedLine::Function(xFunctionComboBox->currentIndex());
		CurvedLine::Function yFunction = CurvedLine::Function(yFunctionComboBox->currentIndex());
		double xCoefficient = xCoefficientTextEdit->toPlainText().toDouble();
		double yCoefficient = yCoefficientTextEdit->toPlainText().toDouble();
		double intervalStart = intervalStartTextEdit->toPlainText().toDouble();
		double intervalEnd = intervalEndTextEdit->toPlainText().toDouble();
		resolution = resolutionTextEdit->toPlainText().toDouble();

		curvedLine = CurvedLine(xFunction, yFunction, { intervalStart, intervalEnd }, xCoefficient, yCoefficient);
	}

	instructionalLabel->hide();
	predefinedComboBox->hide();
	xFunctionComboBox->hide();
	yFunctionComboBox->hide();
	xCoefficientTextEdit->hide();
	yCoefficientTextEdit->hide();
	intervalStartTextEdit->hide();
	intervalEndTextEdit->hide();
	resolutionTextEdit->hide();
	xFunctionLabel->hide();
	yFunctionLabel->hide();
	xCoefficientLabel->hide();
	yCoefficientLabel->hide();
	intervalLabel->hide();
	resolutionLabel->hide();
	saveButton->hide();
	predefinedLabel->hide();

	nextStepButton->show();
	/*xLabel->show();
	yLabel->show();
	OLabel->show();*/

	curveSaved = true;
	update();
}

void CurvedLineWidget::nextStepButtonClicked()
{
	step++;
	switch (step)
	{
		case 1:
		{
			double xMin = 1000, yMin = 1000;
			for (Node* node : polygon.getNodes())
			{
				if (node->getCoordX() < xMin)
					xMin = node->getCoordX();
				if (node->getCoordY() < yMin)
					yMin = node->getCoordY();
			}
			polygon.computeCenterOfMass();
			for (Node* node : polygon.getNodes())
			{
				node->setCoordinates(Transformare::translatePoint(node->getCoordinates(), -xMin, -yMin));
			}
			origin->setCoordinates(Transformare::translatePoint(origin->getCoordinates(), -xMin, -yMin));
			updateLinesAndLabels();
			update();
			break;
		}
		case 2:
		{
			double xMax = 0, yMax = 0;
			for (Node* node : polygon.getNodes())
			{
				if (node->getCoordX() > xMax)
					xMax = node->getCoordX();
				if (node->getCoordY() > yMax)
					yMax = node->getCoordY();
			}
			double xScale = parentWidget()->size().width() / xMax;
			double yScale = parentWidget()->size().height() / yMax;
			double scale = xScale < yScale ? xScale : yScale;
			for (Node* node : polygon.getNodes())
			{
				node->setCoordinates(Transformare::scalePointAroundOrigin(node->getCoordinates(), scale, scale));
			}
			origin->setCoordinates(Transformare::scalePointAroundOrigin(origin->getCoordinates(), scale, scale));
			updateLinesAndLabels();
			update();
			break;
		}
		case 3:
		{
			double xMax = 0, yMax = 0;
			for (Node* node : polygon.getNodes())
			{
				if (node->getCoordX() > xMax)
					xMax = node->getCoordX();
				if (node->getCoordY() > yMax)
					yMax = node->getCoordY();
			}
			double xTranslation = (parentWidget()->size().width() - xMax) / 2;
			double yTranslation = (parentWidget()->size().height() - yMax) / 2;
			for (Node* node : polygon.getNodes())
			{
				node->setCoordinates(Transformare::translatePoint(node->getCoordinates(), xTranslation, yTranslation));
			}
			origin->setCoordinates(Transformare::translatePoint(origin->getCoordinates(), xTranslation, yTranslation));
			updateLinesAndLabels();
			update();
			break;
		}
		case 4:
		{
			for (Node* node : polygon.getNodes())
			{
				node->setCoordinates(Transformare::symmetricalPointByEdge(
					node->getCoordinates(), 
					QPointF(0, parentWidget()->size().height()/2),
					Transformare::Vector(1, 0, 0)));
			}
			origin->setCoordinates(Transformare::symmetricalPointByEdge(
				origin->getCoordinates(),
				QPointF(0, parentWidget()->size().height()/2),
				Transformare::Vector(1, 0, 0)));
			updateLinesAndLabels();
			update();
			break;
		}
	}
}

void CurvedLineWidget::updateLinesAndLabels()
{
	oXLine = new QLineF(0, origin->getCoordY(), size().width(), origin->getCoordY());
	oYLine = new QLineF(origin->getCoordX(), 0, origin->getCoordX(), size().height());
	oXArrow1 = new QLine(size().width() - 10, 10, size().width(), 0);
	oxArrow2 = new QLine(size().width() - 10, -10, size().width(), 0);
	oYArrow1 = new QLine(-10, size().height() - 10, 0, size().height());
	oYArrow2 = new QLine(10, size().height() - 10, 0, size().height());

	xLabel->setGeometry(size().width() - 20, 20, 20, 20);
	yLabel->setGeometry(20, size().height() - 20, 20, 20);
	OLabel->setGeometry(origin->getCoordX(), origin->getCoordY(), 20, 20);
}

void CurvedLineWidget::resizeEvent(QResizeEvent* event)
{
	if (curveSaved)
	{
		double xMax = 0, yMax = 0;
		for (Node* node : polygon.getNodes())
		{
			if (node->getCoordX() > xMax)
				xMax = node->getCoordX();
			if (node->getCoordY() > yMax)
				yMax = node->getCoordY();
		}
		double xScale = parentWidget()->size().width() / xMax;
		double yScale = parentWidget()->size().height() / yMax;
		double scale = xScale < yScale ? xScale : yScale;
		for (Node* node : polygon.getNodes())
		{
			node->setCoordinates(Transformare::scalePointAroundOrigin(node->getCoordinates(), scale, scale));
		}
		origin->setCoordinates(Transformare::scalePointAroundOrigin(origin->getCoordinates(), scale, scale));
		updateLinesAndLabels();
		qDebug() << "pos: " << this->pos();
		qDebug() << "size: " << this->size();
		update();
	}
	//QWidget::resizeEvent(event);
}

void CurvedLineWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	//painter.scale(10, 10);

	if (curveSaved)
	{
		painter.drawLine(*oXLine);
		painter.drawLine(*oYLine);
		painter.drawLine(*oXArrow1);
		painter.drawLine(*oxArrow2);
		painter.drawLine(*oYArrow1);
		painter.drawLine(*oYArrow2);
		if (step == 0)
		{
			CurvedLine::Interval interval = curvedLine.getInterval();
			double distanceBetweenPoints = (interval.end - interval.start) / resolution;
			QPointF point1 = curvedLine.getPoint(interval.start);
			polygon.addNode(point1);
			for (double u = interval.start + distanceBetweenPoints; u <= interval.end; u += distanceBetweenPoints)
			{
				QPointF point2 = curvedLine.getPoint(u);
				painter.drawLine(point1, point2);
				polygon.addNode(point2);
				polygon.addEdge(polygon.getNodes()[polygon.getNodes().size() - 1],
					polygon.getNodes()[polygon.getNodes().size() - 2]);
				point1 = point2;
			}
		}
		else
		{
			std::vector<Edge*> edges = polygon.getEdges();
			for (auto& edge : edges)
			{
				painter.drawLine(edge->getFirstNode()->getCoordinates(), edge->getSecondNode()->getCoordinates());
			}
		}
	}
}
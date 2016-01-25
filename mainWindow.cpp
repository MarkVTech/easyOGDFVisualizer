#include <QDebug>
#include <QPen>
#include <QLineF>
#include <QPointF>
#include <QRectF>
#include <QPainterPath>
#include <QGraphicsRectItem>

#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/planarity/PlanarizationLayout.h>
#include <ogdf/fileformats/GraphIO.h>

#include "mainWindow.h"

using namespace ogdf;

QRectF transformNode(const GraphAttributes& GA, node n)
{
    double x = GA.x(n);
    double y = GA.y(n);
    double w = GA.width(n);
    double h = GA.height(n);

    return QRectF(x-w/2, y-h/2, w, h);
}

MainWindow::
MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    ui_.setupUi(this);

    node n1 = ui_.graphView->addNode(QSize(60, 50));
    node n2 = ui_.graphView->addNode(QSize(60, 50));
    node n3 = ui_.graphView->addNode(QSize(60, 50));
    node n4 = ui_.graphView->addNode(QSize(60, 50));

    ui_.graphView->addEdge(n1, n3);
    ui_.graphView->addEdge(n3, n4);
    ui_.graphView->addEdge(n3, n2);
    ui_.graphView->addEdge(n2, n4);
    ui_.graphView->addEdge(n1, n2);
    ui_.graphView->addEdge(n1, n4);

    ui_.graphView->layout();

}

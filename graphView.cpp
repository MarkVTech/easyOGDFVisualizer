#include <QRectF>
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>
#include <QPointF>
#include <QPainterPath>
#include <QGraphicsEllipseItem>
#include <QGraphicsSimpleTextItem>
#include <QString>
#include <QLineF>
#include <QPolygonF>
#include <QDebug>

#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/planarity/PlanarizationLayout.h>                             
#include <ogdf/fileformats/GraphIO.h>

#include "graphView.h"

using namespace ogdf;

GraphView::GraphView(QWidget* parent) :
    QGraphicsView(parent)
{
    graph_ = new Graph();
    GA_ = new GraphAttributes(*graph_,
        GraphAttributes::nodeGraphics | GraphAttributes::edgeGraphics);

    scene_ = new QGraphicsScene(this);
    scene_->setBackgroundBrush(QBrush(QColor("black")));

    setScene(scene_);

    setRenderHint(QPainter::Antialiasing);

}

node GraphView::addNode(const QSize& size)
{
    node newNode = graph_->newNode();

    GA_->width(newNode) = size.width();
    GA_->height(newNode) = size.height();

    nodeList_.push_back(newNode);

    return newNode;
}

 void GraphView::addEdge(const ogdf::node& source,
         const ogdf::node& target)
{
    edge e = graph_->newEdge(source, target);

    edgeList_.push_back(e);
}

void GraphView::layout()
{

    PlanarizationLayout layout;
    layout.call(*GA_);

    //
    // Draw the nodes
    // 
    for ( int idx=0; idx<nodeList_.size(); ++idx)
    {
        node n = nodeList_[idx];

        double x = GA_->x(n);
        double y = GA_->y(n);
        double w = GA_->width(n);
        double h = GA_->height(n);

        QRectF rect(x-w/2, y-h/2, w, h);
        
        QGraphicsRectItem* ri = 
            scene_->addRect(rect, QPen(QColor("green")));


        QString ls = QString("N%1").arg(idx+1);

        QGraphicsSimpleTextItem* newLabel =
            new QGraphicsSimpleTextItem(ls);
        QRectF textRect = newLabel->boundingRect();
        double newx = (w - textRect.width())/2;
        double newy = (h - textRect.height())/2;

        newLabel->setBrush(QColor("white"));
        newLabel->setParentItem(ri);
        newLabel->setPos(x-w/2+newx, y-h/2+newy);
    }

    //
    // Draw the edges
    // 
    for ( int idx=0; idx<edgeList_.size(); ++idx)
    {
        edge e = edgeList_[idx];
        DPolyline& points = GA_->bends(e);

        List<DPoint>::const_iterator iter = points.begin();
        if ( iter != points.end() )
        {
            QPointF startPoint((*iter).m_x, (*iter).m_y);
            QPainterPath path(startPoint);

            for ( ; iter != points.end(); ++iter )
            {
                DPoint dp = *iter;
                QPointF nextPoint(dp.m_x, dp.m_y);
                path.lineTo(nextPoint);
            }

            scene_->addPath(path, QPen(QColor("green")));

            List<DPoint>::iterator arrowStartPoint =
                    points.get(points.size() - 2);
            List<DPoint>::iterator arrowEndPoint =
                points.get(points.size() - 1);

            //QPolygonF arrow = createArrow(
                    //QPointF((*arrowStartPoint).m_x, (*arrowStartPoint).m_y),
                    //QPointF((*arrowEndPoint).m_x, (*arrowEndPoint).m_y));
    

            //path.addPolygon(arrow);
            drawArrow(
                QPointF((*arrowStartPoint).m_x, (*arrowStartPoint).m_y),
                QPointF((*arrowEndPoint).m_x, (*arrowEndPoint).m_y),
                QColor("green")
            );
            
            //scene_->addPath(path, QPen(QColor("green")));

            /*
            QRectF epr(
               (*endPoint).m_x-3,
               (*endPoint).m_y-3,
               6, 6);

            scene_->addEllipse(epr, QPen(QColor("green")),
                    QBrush(QColor("green")));
            */

        }
    }

}

 QPolygonF GraphView::
 createArrow(const QPointF& start, const QPointF& end)
{
    qreal Pi = 3.14;
    qreal arrowSize = 10;

    QPolygonF arrowHead;

    QLineF line(end, start);

    double angle = ::acos(line.dx() / line.length());

    if ( line.dy() >= 0 )
        angle = (Pi * 2) - angle;

    QPointF arrowP1 = line.p1() + QPointF(sin(angle+Pi/3)*arrowSize,
            cos(angle+Pi/3)*arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle+Pi-Pi/3)*arrowSize,
            cos(angle+Pi-Pi/3)*arrowSize);


    arrowHead.clear();
    arrowHead << line.p1() << arrowP1 << arrowP2;

    return arrowHead;
}

void GraphView::
drawArrow(const QPointF& start, const QPointF& end, const QColor& color)
{
    qreal Pi = 3.14;
    qreal arrowSize = 10;

    QPolygonF arrowHead;

    QLineF line(end, start);

    double angle = ::acos(line.dx() / line.length());

    if ( line.dy() >= 0 )
        angle = (Pi * 2) - angle;

    QPointF arrowP1 = line.p1() + QPointF(sin(angle+Pi/3)*arrowSize,
            cos(angle+Pi/3)*arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle+Pi-Pi/3)*arrowSize,
            cos(angle+Pi-Pi/3)*arrowSize);


    arrowHead.clear();
    arrowHead << line.p1() << arrowP1 << arrowP2;

    scene_->addPolygon(arrowHead, QPen(color), QBrush(color));

    scene_->addLine(line, QPen(color));
}

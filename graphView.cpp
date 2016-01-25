#include <QRectF>
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>
#include <QPointF>
#include <QPainterPath>
#include <QGraphicsEllipseItem>
#include <QGraphicsSimpleTextItem>
#include <QString>
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

            List<DPoint>::iterator endPoint = points.get(points.size() - 1);
    
            QRectF epr(
               (*endPoint).m_x-3,
               (*endPoint).m_y-3,
               6, 6);

            scene_->addEllipse(epr, QPen(QColor("green")),
                    QBrush(QColor("green")));

        }
    }

}

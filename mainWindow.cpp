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


#if 0
    node n1 = G.newNode();
    GA.width(n1) = 56;
    GA.height(n1) = 30;
    //GA.x(n1) = 0;
    //GA.y(n1) = 0;

    node n2 = G.newNode();
    //GA.x(n2) = 20;
    //GA.y(n2) = 30;

    node n3 = G.newNode();
    GA.width(n3) = 30;
    GA.height(n3) = 56;

    node n4 = G.newNode();

    edge e1 = G.newEdge(n1, n3);
    edge e2 = G.newEdge(n3, n4);
    edge e3 = G.newEdge(n3, n2);
    edge e4 = G.newEdge(n3, n4);

    PlanarizationLayout layout;
    layout.call(GA);


    QRectF r1 = transformNode(GA, n1);
    QRectF r2 = transformNode(GA, n2);
    QRectF r3 = transformNode(GA, n3);
    QRectF r4 = transformNode(GA, n4);
    
    QGraphicsRectItem* ri;

    ri = scene_->addRect(r1, QPen(QColor("green")));
    ri->setFlag(QGraphicsItem::ItemIsSelectable);

    ri = scene_->addRect(r2, QPen(QColor("green")));
    ri->setFlag(QGraphicsItem::ItemIsSelectable);

    ri = scene_->addRect(r3, QPen(QColor("green")));
    ri->setFlag(QGraphicsItem::ItemIsSelectable);

    ri = scene_->addRect(r4, QPen(QColor("green")));
    ri->setFlag(QGraphicsItem::ItemIsSelectable);

    DPolyline& p1 = GA.bends(e1);
    DPolyline& p2 = GA.bends(e2);
    DPolyline& p3 = GA.bends(e3);
    DPolyline& p4 = GA.bends(e4);

    {
        List<DPoint>::const_iterator iter = p1.begin();
        if ( iter != p1.end() )
        {
            QPointF startPoint((*iter).m_x, (*iter).m_y);
            QPainterPath path(startPoint);

            for ( ; iter != p1.end(); ++iter )
            {
                DPoint dp = *iter;
                QPointF nextPoint(dp.m_x, dp.m_y);
                path.lineTo(nextPoint);
            }
        
            QGraphicsPathItem* pi =
                scene_->addPath(path, QPen(QColor("orange")));
            pi->setFlag(QGraphicsItem::ItemIsSelectable);
        }
    }

    {
        List<DPoint>::const_iterator iter = p2.begin();
        if ( iter != p2.end() )
        {
            QPointF startPoint((*iter).m_x, (*iter).m_y);
            QPainterPath path(startPoint);

            for ( ; iter != p2.end(); ++iter )
            {
                DPoint dp = *iter;
                QPointF nextPoint(dp.m_x, dp.m_y);
                path.lineTo(nextPoint);
            }
        
            QGraphicsPathItem* pi =
                scene_->addPath(path, QPen(QColor("purple")));
            pi->setFlag(QGraphicsItem::ItemIsSelectable);
        }
    }

    {
        List<DPoint>::const_iterator iter = p3.begin();
        if ( iter != p3.end() )
        {
            QPointF startPoint((*iter).m_x, (*iter).m_y);
            QPainterPath path(startPoint);

            for ( ; iter != p3.end(); ++iter )
            {
                DPoint dp = *iter;
                QPointF nextPoint(dp.m_x, dp.m_y);
                path.lineTo(nextPoint);
            }
        
            QGraphicsPathItem* pi =
                scene_->addPath(path, QPen(QColor("blue")));
            pi->setFlag(QGraphicsItem::ItemIsSelectable);
        }
    }

    {
        List<DPoint>::const_iterator iter = p4.begin();
        if ( iter != p4.end() )
        {
            QPointF startPoint((*iter).m_x, (*iter).m_y);
            QPainterPath path(startPoint);

            for ( ; iter != p4.end(); ++iter )
            {
                DPoint dp = *iter;
                QPointF nextPoint(dp.m_x, dp.m_y);
                path.lineTo(nextPoint);
            }
        
            QGraphicsPathItem* pi =
                scene_->addPath(path, QPen(QColor("green")));
            pi->setFlag(QGraphicsItem::ItemIsSelectable);
        }
    }

    GraphIO::drawSVG(GA, "planarGraph.svg"); 
#endif
}

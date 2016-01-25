#ifndef _GRAPH_VIEW_H_
#define _GRAPH_VIEW_H_

#include <QGraphicsView>
#include <QVector>

#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/planarity/PlanarizationLayout.h>                             
#include <ogdf/fileformats/GraphIO.h>

class QSize;
class QGraphicsScene;

class GraphView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphView(QWidget* parent=0);

    //ogdf::node addNode(const QSize& size, const ogdf::node& n);
    ogdf::node addNode(const QSize& size);
    void addEdge(const ogdf::node& source, const ogdf::node& target);

    void layout();

private:
    ogdf::Graph* graph_;
    ogdf::GraphAttributes* GA_;

    QVector<ogdf::node> nodeList_;
    QVector<ogdf::edge> edgeList_;

    QGraphicsScene* scene_;
};

#endif

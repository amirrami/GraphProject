/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "graphics.h"
#include "edge.h"
#include "node.h"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>

//! [0]
Graphics::Graphics(QWidget *parent)
     : QGraphicsView(new QGraphicsScene, parent), timerId(0)
{
    this->setMouseTracking(true);
    this->setBackgroundRole(QPalette::Base);
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0,800,800);
    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setScene(scene);
    this->setCacheMode(CacheBackground);
    this->setViewportUpdateMode(BoundingRectViewportUpdate);
    this->setRenderHint(QPainter::Antialiasing);
    this->setTransformationAnchor(AnchorUnderMouse);
    this->scale(qreal(0.8), qreal(0.8));
    this->setMinimumSize(650, 650);
//! [0]

//! [1]


}
//! [1]
//!
void Graphics::drawNodes(QVector<QList<QPair<int, float> > > adjacencyList, QVector<float> centrality, QString algorithm)
{
    // adjust graphical centrality

    float max=0;
    for(int i=0;i<centrality.size();i++){
        if(centrality[i]>max)
            max=centrality[i];
    }

    graphicsCentrality.resize(centrality.size());
    if(algorithm == "Degree Centrality"){
        for(int i=0;i<centrality.size();i++){
            if(centrality.size()<=10){
                graphicsCentrality[i] = centrality[i]* 10;
            }
            else if (centrality.size() >10 && centrality.size() <=20) {
                graphicsCentrality[i] = centrality[i]* 6;
            }
            else if (centrality.size() >20 && centrality.size() <=30) {
                graphicsCentrality[i] = centrality[i]* 5;
            }
            else {
                 graphicsCentrality[i] = centrality[i];
            }

        }

    }
    else if (algorithm == "Betweenness Centrality") {
        for(int i=0;i<centrality.size();i++){
            if(centrality[i]==0){
                graphicsCentrality[i]=20;
            }
            else {
                graphicsCentrality[i] = (centrality[i]+10) *3;
            }
        }
    }
    else{
        for(int i=0;i<centrality.size();i++){
            if(max <0.05)
                graphicsCentrality[i] =centrality[i]* 2500;
            else if(max < 0.1)
                graphicsCentrality[i] =centrality[i]* 400;
            else if(max < 0.2)
                graphicsCentrality[i] =centrality[i]* 300;
            else if(max < 0.3)
                graphicsCentrality[i] =centrality[i]* 200;
            else if(max <0.5)
                graphicsCentrality[i] =centrality[i]* 100;
            else if(max < 1)
                graphicsCentrality[i] =centrality[i]* 50;
            else if(max < 5)
                graphicsCentrality[i] =centrality[i]* 10;
            else if(max < 10)
                graphicsCentrality[i] =centrality[i]* 7;
            else if(max < 20)
                graphicsCentrality[i] =centrality[i]* 4;
            else if(max < 30)
                graphicsCentrality[i] =centrality[i]* 3;
            else
                graphicsCentrality[i] = centrality[i];
        }
    }

    //adding nodes


    for(int i=0;i<adjacencyList.size();i++){
        Node * node;
        QString tooltiptext;
        if(centrality[i]==max){
            node  = new Node(this,graphicsCentrality[i],true);
            tooltiptext = "<html><body><h4>Node No.:"+ QString::number(i)  +"</h4>"
                                 "<h4>Node Centerality:" + QString ::number(centrality[i]) + "</h4>"
                                  "<h4>Is Max: True </h4></body></html>";
        }

        else
        {
         node = new Node(this,graphicsCentrality[i],false);
         tooltiptext = "<html><body><h4>Node No.:"+ QString::number(i)  +"</h4>"
                              "<h4>Node Centerality:" + QString ::number(centrality[i]) + "</h4>"
                              "<h4>Is Max: False </h4></body></html>";
        }

        Nodes.push_back(node);
        scene->addItem(node);


        Nodes[i]->QGraphicsItem::setToolTip(tooltiptext);
    }

    //adding edges


    for(int i=0;i<adjacencyList.size();i++){
        QList<QPair<int, float>> ::iterator it;
        for(it=adjacencyList[i].begin(); it!=adjacencyList[i].end() ;it++){
            Edge * edge = new Edge(Nodes[i], Nodes[it->first]);
            scene->addItem(edge);
            Edges.push_back(edge);
        }
    }
    shuffle();

}

//! [2]
void Graphics::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}


//! [2]

//! [3]
void Graphics::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}
//! [3]

//! [4]
void Graphics::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<Node *> nodes;
    foreach (QGraphicsItem *item, scene->items()) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    foreach (Node *node, nodes)
        node->calculateForces();

    bool itemsMoved = false;
    foreach (Node *node, nodes) {
        if (node->advancePosition())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}
//! [4]

#if QT_CONFIG(wheelevent)
//! [5]
void Graphics::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
//! [5]
#endif

//! [6]
void Graphics::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Click and drag the nodes around, and zoom with the mouse "
                       "wheel or the '+' and '-' keys, Hover on Nodes to see its details"));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
}
//! [6]

//! [7]
void Graphics::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
//! [7]

void Graphics::shuffle()
{
    foreach (QGraphicsItem *item, scene->items()) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(1200), -150 + QRandomGenerator::global()->bounded(1200));
    }
}

void Graphics::zoomIn()
{
    scaleView(qreal(1.2));
}

void Graphics::zoomOut()
{
    scaleView(1 / qreal(1.2));
}


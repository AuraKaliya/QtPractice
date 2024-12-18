#ifndef NODEOBJECTITEM_H
#define NODEOBJECTITEM_H

#include <QObject>
#include<QList>
#include <QRect>
#include<QObject>
#include <QPointF>
#include <QVariant>
#include <QPainter>
#include <QGraphicsItem>
#include<QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>



#include "../Port/portobjectitem.h"

class NodeObjectItem : public QObject,public QGraphicsItem
{
public:
    enum NodeType{
        NoType,
        StartNode,
        EndNode,
        SolveNode
    };

private:
    Q_OBJECT

    Q_PROPERTY(unsigned int nodeId READ nodeId WRITE setNodeId NOTIFY idChanged)
    Q_PROPERTY(QString nodeTitle READ nodeTitle WRITE setNodeTitle NOTIFY nodeTitleChanged)
    Q_PROPERTY(NodeType nodeType READ nodeType WRITE setNodeType NOTIFY nodeTypeChanged)


public:
    explicit NodeObjectItem(QObject *parent = nullptr,QGraphicsItem* itemParent=nullptr);
    QRectF  boundingRect() const override;    //QRect绘制时除了topleft 都会往内部偏移1像素点，而QRectF是用浮点数表示区域，不会出现这个问题
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) override;


    void nodeRun();

    virtual void solute();

    //头节点初始化数据
    void initValue(const QVariant& value);
    //尾节点获取数据
    QVariant getValue();

    void addPort(PortObjectItem* port);

    // 初始化节点处理信息
    void initSolveInformation();
    // 检查端口的就绪状态
    bool checkReadyPort();
    // 重置输入端口的就绪状态
    void resetInPortReadyState();



    unsigned int getInPortCount()   const ;
    unsigned int getOutPortCount()  const ;

    PortObjectItem* getPortByPos(QPointF pos);

    unsigned int nodeId() const;
    void setNodeId(unsigned int newId);

    QVector<PortObjectItem *> portList() const;

    QString nodeTitle() const;
    void setNodeTitle(const QString &newNodeName);

    NodeType nodeType() const;
    void setNodeType(NodeType newNodeType);
    bool solveFlag() const;
    void setSolveFlag(bool newSolveFlag);

    bool readyFlag() const;
    void setReadyFlag(bool newReadyFlag);



    QVector<NodeObjectItem *> nextNodeList() const;
    void setNextNodeList(const QVector<NodeObjectItem *> &newNextNodeList);
    void addNextNode(NodeObjectItem* node);
    QSet<NodeObjectItem *> startNodeList() const;
    void addStartNode(NodeObjectItem * node);
protected:
    void updateNodeSize();
    void  mouseMoveEvent(QGraphicsSceneMouseEvent *e)override;

private:
    static QMap<NodeObjectItem::NodeType,QPair<QColor,QColor> > m_typeColorDictionary;
protected:
    unsigned int m_nodeId;
    QString m_nodeTitle;
    NodeType m_nodeType;

    QColor m_titleColor;
    QColor m_titleTextColor;

    unsigned int m_fixTitleHeight;
    unsigned int m_fixPortHeight;


    unsigned int m_nodeWidth;
    unsigned int m_nodeHeight;


    QVector<PortObjectItem*> m_portList;
    QVector<PortObjectItem*> m_inPortList;
    QVector<PortObjectItem*> m_outPortList;

    QSet<PortObjectItem*> m_waitDataPortSet;

    PortObjectItem* m_inLinkPort =nullptr;
    PortObjectItem* m_outLinkPort=nullptr;


    bool m_solveFlag;
    bool m_readyFlag;
    QSet<NodeObjectItem*> m_startNodeList;

    QVector<NodeObjectItem*> m_nextNodeList;

signals:

    void idChanged();
    void nodeTitleChanged();
    void nodeTypeChanged();
    void needUpdate(NodeObjectItem*);

    //停止处理控制信号
    void stopSolution();
};

#endif // NODEOBJECTITEM_H

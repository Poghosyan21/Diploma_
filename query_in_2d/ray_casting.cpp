#include "ray_casting.hpp"
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <QVBoxLayout>
#include <QDebug>


RayCastingAlgorithm::RayCastingAlgorithm(QWidget *parent) : QWidget(parent)
{
    setUI();
}

void RayCastingAlgorithm::openPolygonFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Polygon File", QString(), "Text Files (*.txt);;All Files (*.*)");
    if(!filePath.isEmpty())
    {
        loadPolygonFromFile(filePath);
        update();
    }
}

void RayCastingAlgorithm::openPointFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Points File", QString(), "Text Files (*.txt);;All Files (*.*)");
    if(!filePath.isEmpty())
    {
        loadPointsFromFile(filePath);
        update();
    }
}

void RayCastingAlgorithm::setUI()
{

}


void RayCastingAlgorithm::loadPolygonFromFile(const QString& filename)
{
    polygon.clear();

    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open polygon file:" << file.errorString();
        return;
    }

//    qDebug() << "Opened polygon file successfully";

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList coordinates = line.split(" ");
        if (coordinates.size() == 2)
        {
            qreal x = coordinates[0].toDouble();
            qreal y = coordinates[1].toDouble();
            polygon.append(QPoint(x, y));
        }
    }

    file.close();
}





void RayCastingAlgorithm::loadPointsFromFile(const QString& filename)
{
    points.clear();

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open points file:" << file.errorString();
        return;
    }

//    qDebug() << "Opened points file successfully";


    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList coordinates = line.split(" ");
        if(coordinates.size() == 2)
        {
            qreal x = coordinates[0].toDouble();
            qreal y = coordinates[1].toDouble();
            points.append(QPointF(x, y));
        }
    }

    file.close();
}




void RayCastingAlgorithm::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(QBrush(Qt::white));
    painter.drawPolygon(polygon);

    for(const QPointF& point : points)
    {
        if(isPointInsidePolygon(point, polygon))
            painter.setBrush(QBrush(Qt::green));
        else
            painter.setBrush(QBrush(Qt::red));

        painter.drawEllipse(point, 3, 3);
    }
}



bool RayCastingAlgorithm::isPointInsidePolygon(const QPointF &point, const QPolygonF &polygon)
{
    int intersectCount = 0;
    int numVertices = polygon.size();

    for (int i = 0; i < numVertices; ++i) {
        QPointF p1 = polygon.at(i);
        QPointF p2 = polygon.at((i + 1) % numVertices);

        if ((point.y() >= std::min(p1.y(), p2.y())) && (point.y() <= std::max(p1.y(), p2.y())) &&
            (point.x() <= std::max(p1.x(), p2.x())) && (p1.y() != p2.y())) {
            double xIntersection = (point.y() - p1.y()) * (p2.x() - p1.x()) / (p2.y() - p1.y()) + p1.x();
            if (p1.x() == p2.x() || point.x() <= xIntersection) {
                ++intersectCount;
            }
        }
    }

    return (intersectCount % 2 != 0);
}
































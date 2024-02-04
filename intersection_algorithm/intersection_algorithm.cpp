#include "intersection_algorithm.hpp"
#include <QtWidgets>
#include <QFile>
#include <QTextStream>

IntersectionAlgorithm::IntersectionAlgorithm(QWidget *parent) : QWidget(parent) {
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu("File");

    QAction *openAction = new QAction("Open", this);
    connect(openAction, &QAction::triggered, this, &IntersectionAlgorithm::openFile);
    fileMenu->addAction(openAction);
}

void IntersectionAlgorithm::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.setBrush(Qt::white);
    painter.drawPolygon(polygon1);

    painter.setBrush(Qt::white);
    painter.drawPolygon(polygon2);

    QPainterPath path1, path2;
    path1.addPolygon(QPolygonF(polygon1));
    path2.addPolygon(QPolygonF(polygon2));

    QPainterPath intersection;
    intersection.setFillRule(Qt::WindingFill);
    intersection.addPath(path1.intersected(path2));

    painter.setBrush(Qt::red);
    painter.drawPath(intersection);
}

void IntersectionAlgorithm::openFile() {
    QString file1 = QFileDialog::getOpenFileName(this, "Select File for Polygon 1", "", "Text Files (*.txt)");
    QString file2 = QFileDialog::getOpenFileName(this, "Select File for Polygon 2", "", "Text Files (*.txt)");

    loadPolygonFromFile(file1, polygon1);
    loadPolygonFromFile(file2, polygon2);

    update();
}

void IntersectionAlgorithm::loadPolygonFromFile(const QString &filename, QVector<QPointF> &polygon) {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        polygon.clear();
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList coordinates = line.split(" ");
            if (coordinates.size() == 2) {
                qreal x = coordinates[0].toDouble();
                qreal y = coordinates[1].toDouble();
                polygon.append(QPointF(x, y));
            }
        }
        file.close();
    }
}

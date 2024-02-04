#ifndef INTERSECTIONALGORITHM_H
#define INTERSECTIONALGORITHM_H

#include <QWidget>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QVector>
#include <QPointF>

class IntersectionAlgorithm : public QWidget {
    Q_OBJECT

public:
    IntersectionAlgorithm(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    QVector<QPointF> polygon1;
    QVector<QPointF> polygon2;
    QVBoxLayout *layout;

    void openFile();

    void loadPolygonFromFile(const QString &filename, QVector<QPointF> &polygon);
};

#endif // INTERSECTIONALGORITHM_H

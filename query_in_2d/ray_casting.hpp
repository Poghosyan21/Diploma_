#ifndef RAY_CASTING_HPP
#define RAY_CASTING_HPP

#include <QWidget>
#include <QPolygonF>
#include <QList>
#include <QPolygonF>
#include <QPushButton>

class RayCastingAlgorithm : public QWidget
{
    Q_OBJECT

public:
    RayCastingAlgorithm(QWidget* parent = nullptr);

private:
    bool isPointInsidePolygon(const QPointF &point, const QPolygonF &polygon);
    void setUI();
    void paintEvent(QPaintEvent* event) override;
    void loadPolygonFromFile(const QString& );
    void loadPointsFromFile(const QString&);



public slots:
    void openPolygonFile();
    void openPointFile();


private:
    QPolygonF polygon;
    QList<QPointF> points;

    QPushButton* addPointsButton;

    QPushButton* addPolygonButton;
};

#endif

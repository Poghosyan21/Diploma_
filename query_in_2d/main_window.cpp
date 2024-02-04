#include "main_window.hpp"

#include <QMenuBar>


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    rayCasting = new RayCastingAlgorithm(this);

    createToolBar();
    setWindowTitle("Query Algorithms");
}



void MainWindow::createToolBar()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    algorithmsMenu = menuBar()->addMenu(tr("&Algorithms"));

//    openMenu = menuBar()->addMenu(tr("&Open"));
    openMenu=fileMenu->addMenu("&Open");
//    fileMenu->addMenu(openMenu);
    polygonCoordinates = new QAction(tr("Polygon Coordinates"), this);
    pointsCoordinates = new QAction(tr("Points' Coordinates"), this);

    openMenu->addAction(polygonCoordinates);
    openMenu->addAction(pointsCoordinates);


    rayCastingAction = new QAction(tr("Ray casting"), this);

    algorithmsMenu->addAction(rayCastingAction);

    connect(rayCastingAction, &QAction::triggered, this, &MainWindow::onRayCastingClicked);
    connect(polygonCoordinates, &QAction::triggered, rayCasting, &RayCastingAlgorithm::openPolygonFile);
    connect(pointsCoordinates, &QAction::triggered, rayCasting, &RayCastingAlgorithm::openPointFile);
}


void MainWindow::onRayCastingClicked()
{
    setCentralWidget(rayCasting);
}

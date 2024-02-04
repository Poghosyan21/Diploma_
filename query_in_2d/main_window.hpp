#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include "ray_casting.hpp"
#include <QMainWindow>
#include <QMenu>
#include <QToolBar>
#include <QAction>


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

private:
    void createToolBar();
private:
    QMenu* fileMenu;
    QToolBar* toolBar;

    QMenu* algorithmsMenu;
    QMenu* openMenu;


    QAction* rayCastingAction;
    QAction* polygonCrossing;



    QAction* polygonCoordinates;
    QAction* pointsCoordinates;
    RayCastingAlgorithm* rayCasting;


private slots:
    void onRayCastingClicked();

};




#endif // MAIN_WINDOW_HPP

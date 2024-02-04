#include <QApplication>
#include "intersection_algorithm.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    IntersectionAlgorithm widget;
    widget.show();

    return app.exec();
}

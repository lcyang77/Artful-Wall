#include "mainwindow.h"
#include "dpiaware.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Initialize DPI awareness and scaling policies
    initializeDpiAwareness();
    
    QApplication a(argc, argv);
    
    // DPI-aware font initialization
    // This is disabled by default as Qt automatically scales fonts in most scenarios.
    // Uncomment the line below only if you need custom font scaling based on system DPI.
    // initializeDpiAwareFont(a);
    
    MainWindow w;
    w.show();
    return a.exec();
}

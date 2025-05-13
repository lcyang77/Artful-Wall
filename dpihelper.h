#ifndef DPIHELPER_H
#define DPIHELPER_H

#include <QPoint>
#include <QSize>

class QScreen;
class QWidget;

class DpiHelper
{
public:
    // Pixel conversion methods
    static QPoint fromNativePixels(const QPoint &nativePos, QScreen *screen = nullptr);
    static QPoint toNativePixels(const QPoint &logicalPos, QScreen *screen = nullptr);
    
    // DPI detection and calculation methods
    static qreal devicePixelRatio(QWidget *widget);
    static void detectWindowsDPI(int &horizontalDPI, int &verticalDPI);
    static void detectQtDPI(QScreen *screen, qreal &logicalDpiX, qreal &logicalDpiY, qreal &physicalDpiX, qreal &physicalDpiY);
    static void detectDisplaySizeCm(QScreen *screen, qreal &widthCm, qreal &heightCm);
    static QSize calculateDisplaySizeCm(int screenWidth, int screenHeight, int horizontalDPI, int verticalDPI);

private:
    // Helper method to find screen at position
    static QScreen* findScreenAtPosition(const QPoint &pos);
};

#endif // DPIHELPER_H 
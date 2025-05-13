#include "dpihelper.h"
#include "windows_helper.h"
#include <QGuiApplication>
#include <QScreen>
#include <QWidget>

QScreen* DpiHelper::findScreenAtPosition(const QPoint &pos)
{
    QScreen* screen = QGuiApplication::screenAt(pos);
    if (!screen) {
        screen = QGuiApplication::primaryScreen();
    }
    return screen;
}

QPoint DpiHelper::fromNativePixels(const QPoint &nativePos, QScreen *screen)
{
    if (!screen) {
        screen = findScreenAtPosition(nativePos);
    }
    
    // Get the screen's physical geometry
    QRect screenGeometry = screen->geometry();
    
    // Get device pixel ratio
    qreal dpr = screen->devicePixelRatio();
    
    // Convert from native pixels to logical pixels
    QPoint logicalPos;
    logicalPos = (nativePos - screenGeometry.topLeft()) / dpr;
    logicalPos += screenGeometry.topLeft();
    
    return logicalPos;
}

QPoint DpiHelper::toNativePixels(const QPoint &logicalPos, QScreen *screen)
{
    if (!screen) {
        screen = findScreenAtPosition(logicalPos);
    }
    
    // Get the screen's geometry
    QRect screenGeometry = screen->geometry();
    
    // Get device pixel ratio
    qreal dpr = screen->devicePixelRatio();
    
    // Convert from logical pixels to native pixels
    QPoint nativePos;
    nativePos = (logicalPos - screenGeometry.topLeft()) * dpr;
    nativePos += screenGeometry.topLeft();
    
    return nativePos;
}

qreal DpiHelper::devicePixelRatio(QWidget *widget)
{
    qreal dpr = 1.0;
    QScreen *screen = QGuiApplication::screenAt(widget->mapToGlobal(QPoint(0, 0)));
    if (screen) {
        dpr = screen->devicePixelRatio();
    } else {
        // During screen transitions, screenAt might return nullptr
        dpr = QGuiApplication::primaryScreen()->devicePixelRatio();
    }
    return dpr;
}

void DpiHelper::detectWindowsDPI(int &horizontalDPI, int &verticalDPI)
{
#if HAS_WINDOWS_API
    // Get desktop dc
    HDC desktopDc = GetDC(NULL);
    // Get native resolution
    horizontalDPI = GetDeviceCaps(desktopDc, LOGPIXELSX);
    verticalDPI = GetDeviceCaps(desktopDc, LOGPIXELSY);
    // Release DC
    ReleaseDC(NULL, desktopDc);
#else
    horizontalDPI = 96;
    verticalDPI = 96;
#endif
}

void DpiHelper::detectQtDPI(QScreen *screen, qreal &logicalDpiX, qreal &logicalDpiY, qreal &physicalDpiX, qreal &physicalDpiY)
{
    if (!screen) {
        screen = QGuiApplication::primaryScreen();
    }
    
    // Get logical DPI (affected by Windows scaling)
    logicalDpiX = screen->logicalDotsPerInchX();
    logicalDpiY = screen->logicalDotsPerInchY();
    
    // Get physical DPI (actual screen DPI)
    physicalDpiX = screen->physicalDotsPerInchX();
    physicalDpiY = screen->physicalDotsPerInchY();
}

void DpiHelper::detectDisplaySizeCm(QScreen *screen, qreal &widthCm, qreal &heightCm)
{
    if (!screen) {
        screen = QGuiApplication::primaryScreen();
    }
    
    // Get physical size in millimeters and convert to centimeters
    QSizeF physicalSize = screen->physicalSize(); // Returns size in millimeters
    widthCm = physicalSize.width() / 10.0;  // Convert mm to cm
    heightCm = physicalSize.height() / 10.0; // Convert mm to cm
}

QSize DpiHelper::calculateDisplaySizeCm(int screenWidth, int screenHeight, int horizontalDPI, int verticalDPI)
{
    // 1 inch = 2.54 cm
    const double inchToCm = 2.54;
    
    // Calculate width and height in centimeters
    double widthCm = (screenWidth / static_cast<double>(horizontalDPI)) * inchToCm;
    double heightCm = (screenHeight / static_cast<double>(verticalDPI)) * inchToCm;
    
    return QSize(widthCm, heightCm);
} 
#include "monitorinfomodel.h"
#include "dpihelper.h"
#include <QGuiApplication>
#include <QScreen>

MonitorInfoModel::MonitorInfoModel()
{
    refreshMonitorInfo();
}

void MonitorInfoModel::refreshMonitorInfo()
{
    // Clear cached data
    m_systemDpiInfo.clear();
    m_monitorInfoList.clear();
    m_dpiScalingExamples.clear();
    
    // Get system DPI information
    m_systemDpiInfo = getSystemDpiInfo();
    
    // Get information about all monitors
    m_monitorInfoList.clear();
    QList<QScreen*> screens = QGuiApplication::screens();
    for (int i = 0; i < screens.size(); ++i) {
        QScreen *screen = screens.at(i);
        bool isPrimary = (screen == QGuiApplication::primaryScreen());
        
        QString monitorHeader = QString("--- Monitor %1 %2 ---\n")
                               .arg(i+1)
                               .arg(isPrimary ? "(Primary)" : "");
        
        m_monitorInfoList.append(monitorHeader + getMonitorInfo(screen) + "\n");
    }
    
    // Get DPI scaling examples for the primary screen
    m_dpiScalingExamples = getDpiScalingExamples(QGuiApplication::primaryScreen());
}

QString MonitorInfoModel::getSystemDpiInfo()
{
    QString info;
    
    // Get Windows DPI
    int winHorizontalDpi, winVerticalDpi;
    DpiHelper::detectWindowsDPI(winHorizontalDpi, winVerticalDpi);
    
    // Build information string
    info += "--- Windows System DPI ---\n";
    info += QString("Windows Horizontal DPI: %1\n").arg(winHorizontalDpi);
    info += QString("Windows Vertical DPI: %1\n").arg(winVerticalDpi);
    info += QString("Windows Average DPI: %1\n").arg((winHorizontalDpi + winVerticalDpi) / 2.0);
    info += QString("Estimated Windows Scaling: %1%\n\n").arg(winHorizontalDpi * 100.0 / 96.0, 0, 'f', 0);
    
    return info;
}

QString MonitorInfoModel::getAllMonitorsInfo()
{
    QString info;
    QList<QScreen*> screens = QGuiApplication::screens();
    
    info += QString("Detected %1 monitor(s)\n").arg(screens.size());
    
    for (const QString &monitorInfo : m_monitorInfoList) {
        info += monitorInfo;
    }
    
    return info;
}

QString MonitorInfoModel::getDpiScalingExamples(QScreen *screen)
{
    if (!screen) {
        screen = QGuiApplication::primaryScreen();
    }
    
    QString info;
    qreal dpr = screen->devicePixelRatio();
    
    // Get Windows DPI
    int winHorizontalDpi, winVerticalDpi;
    DpiHelper::detectWindowsDPI(winHorizontalDpi, winVerticalDpi);
    
    info += "--- DPI Scaling Examples ---\n";
    info += QString("Current screen's DPR: %1\n").arg(dpr, 0, 'f', 3);
    
    // Example of coordinate conversion
    QPoint logicalPoint(100, 100);
    QPoint nativePoint = DpiHelper::toNativePixels(logicalPoint, screen);
    QPoint backToLogical = DpiHelper::fromNativePixels(nativePoint, screen);
    
    info += QString("Logical point (100,100) -> Native: (%1,%2) -> Back to logical: (%3,%4)\n")
            .arg(nativePoint.x()).arg(nativePoint.y())
            .arg(backToLogical.x()).arg(backToLogical.y());
            
    info += QString("Windows scaling %: %1%\n").arg(dpr * 100.0, 0, 'f', 1);
    
    // Font scaling example
    info += "\n--- Font Scaling Example ---\n";
    int dpi = (winHorizontalDpi + winVerticalDpi) / 2;
    int fontsize = 4 * dpi / 72; // 8pt at 144dpi is 4px
    fontsize = fontsize > 8 ? fontsize : 8;
    info += QString("Calculated font size for 8pt: %1px\n").arg(fontsize);
    
    return info;
}

QString MonitorInfoModel::getMonitorInfo(QScreen *screen)
{
    QString info;
    
    // Monitor name
    info += QString("Name: %1\n").arg(screen->name());
    
    // Screen geometry (resolution)
    QRect screenGeometry = screen->geometry();
    info += QString("Screen Geometry (Logical): %1x%2, Position: (%3,%4)\n")
                .arg(screenGeometry.width())
                .arg(screenGeometry.height())
                .arg(screenGeometry.x())
                .arg(screenGeometry.y());
                
    // Native geometry (not directly accessible in Qt6, calculated based on DPR)
    qreal dpr = screen->devicePixelRatio();
    QSize nativeSize = QSize(screenGeometry.width() * dpr, screenGeometry.height() * dpr);
    info += QString("Native Resolution: %1x%2 (DPR: %3)\n")
                .arg(nativeSize.width())
                .arg(nativeSize.height())
                .arg(dpr, 0, 'f', 3);
    
    // Available geometry
    QRect availableGeometry = screen->availableGeometry();
    info += QString("Available Geometry: %1x%2, Position: (%3,%4)\n")
                .arg(availableGeometry.width())
                .arg(availableGeometry.height())
                .arg(availableGeometry.x())
                .arg(availableGeometry.y());
    
    // Physical size
    QSizeF physicalSize = screen->physicalSize();
    info += QString("Physical Size: %1mm x %2mm\n")
                .arg(physicalSize.width(), 0, 'f', 1)
                .arg(physicalSize.height(), 0, 'f', 1);
    
    // Calculate size in centimeters
    qreal widthCm, heightCm;
    DpiHelper::detectDisplaySizeCm(screen, widthCm, heightCm);
    info += QString("Physical Size (cm): %1cm x %2cm\n")
                .arg(widthCm, 0, 'f', 2)
                .arg(heightCm, 0, 'f', 2);
    
    // DPI information
    qreal logicalDpiX, logicalDpiY, physicalDpiX, physicalDpiY;
    DpiHelper::detectQtDPI(screen, logicalDpiX, logicalDpiY, physicalDpiX, physicalDpiY);
    
    info += QString("Logical DPI: %1 x %2\n").arg(logicalDpiX, 0, 'f', 1).arg(logicalDpiY, 0, 'f', 1);
    info += QString("Physical DPI: %1 x %2\n").arg(physicalDpiX, 0, 'f', 1).arg(physicalDpiY, 0, 'f', 1);
    
    // Calculate display size using resolution and DPI
    QSize calculatedSizeCm = DpiHelper::calculateDisplaySizeCm(nativeSize.width(), nativeSize.height(), physicalDpiX, physicalDpiY);
    info += QString("Calculated Size (cm): %1cm x %2cm\n")
                .arg(static_cast<double>(calculatedSizeCm.width()), 0, 'f', 2)
                .arg(static_cast<double>(calculatedSizeCm.height()), 0, 'f', 2);
    
    // Calculate device pixel ratio based on DPI
    qreal calculatedDpr = logicalDpiX / 96.0;
    info += QString("Calculated DPR from logical DPI: %1\n").arg(calculatedDpr, 0, 'f', 2);
    
    // Refresh rate
    info += QString("Refresh Rate: %1 Hz\n").arg(screen->refreshRate(), 0, 'f', 1);
    
    // Screen orientation
    QString orientationStr;
    switch(screen->orientation()) {
        case Qt::PrimaryOrientation:
            orientationStr = "Primary";
            break;
        case Qt::LandscapeOrientation:
            orientationStr = "Landscape";
            break;
        case Qt::PortraitOrientation:
            orientationStr = "Portrait";
            break;
        case Qt::InvertedLandscapeOrientation:
            orientationStr = "Inverted Landscape";
            break;
        case Qt::InvertedPortraitOrientation:
            orientationStr = "Inverted Portrait";
            break;
        default:
            orientationStr = "Unknown";
    }
    info += QString("Orientation: %1\n").arg(orientationStr);
    
    // Device pixel ratio (Windows scaling %)
    info += QString("Device Pixel Ratio: %1 (Windows scaling: %2%)\n")
                .arg(screen->devicePixelRatio(), 0, 'f', 3)
                .arg(screen->devicePixelRatio() * 100.0, 0, 'f', 1);
    
    return info;
}

QString MonitorInfoModel::getCompleteMonitorInfoText()
{
    QString result;
    
    // System DPI information
    result += m_systemDpiInfo;
    
    // All monitors information
    result += getAllMonitorsInfo();
    
    // DPI scaling examples
    result += m_dpiScalingExamples;
    
    return result;
} 
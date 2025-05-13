#include "dpiaware.h"
#include "dpihelper.h"
#include "windows_helper.h"
#include <QApplication>
#include <QFont>

void initializeDpiAwareness()
{
#if HAS_WINDOWS_API
    // Implement proper Windows DPI awareness 
    // For Windows 10 version 1703 or higher:
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
#endif

    // Set proper scaling policies for the application
    // Note: Qt::AA_EnableHighDpiScaling is deprecated in Qt 6 as high-DPI scaling is always enabled
    QApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
}

void initializeDpiAwareFont(QApplication &app)
{
    // Get system DPI
    int horizontalDPI, verticalDPI;
    DpiHelper::detectWindowsDPI(horizontalDPI, verticalDPI);
    
    // Calculate font size based on DPI
    int dpi = (horizontalDPI + verticalDPI) / 2;
    int fontsize = 4 * dpi / 72; // 8pt at 144dpi is 4px
    fontsize = fontsize > 8 ? fontsize : 8;
    
    // Set font size
    QFont appFont = app.font();
    appFont.setPointSize(fontsize);
    app.setFont(appFont);
} 
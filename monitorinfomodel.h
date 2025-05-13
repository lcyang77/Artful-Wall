#ifndef MONITORINFOMODEL_H
#define MONITORINFOMODEL_H

#include <QString>
#include <QStringList>

class QScreen;

class MonitorInfoModel
{
public:
    MonitorInfoModel();
    
    // Get information about system DPI
    QString getSystemDpiInfo();
    
    // Get information about all monitors
    QString getAllMonitorsInfo();
    
    // Get DPI scaling examples for a specific screen
    QString getDpiScalingExamples(QScreen *screen);
    
    // Get information about a specific monitor
    QString getMonitorInfo(QScreen *screen);
    
    // Refresh all monitor information
    void refreshMonitorInfo();
    
    // Get the complete monitor information text
    QString getCompleteMonitorInfoText();

private:
    // Cached information
    QString m_systemDpiInfo;
    QStringList m_monitorInfoList;
    QString m_dpiScalingExamples;
};

#endif // MONITORINFOMODEL_H 
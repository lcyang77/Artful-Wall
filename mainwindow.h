#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>

// Forward declarations
class QTextEdit;
class QPushButton;
class QScreen;
class MonitorInfoModel;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void detectMonitors();

private:
    QScopedPointer<Ui::MainWindow> ui;
    QTextEdit *monitorInfoTextEdit;
    QPushButton *refreshButton;
    QScopedPointer<MonitorInfoModel> m_monitorInfoModel;

    void initializeUi();
};

#endif // MAINWINDOW_H

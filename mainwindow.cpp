#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "monitorinfomodel.h"
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QList>
#include <QDebug>
#include <QGuiApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_monitorInfoModel(new MonitorInfoModel)
{
    // Either use the UI file or create UI programmatically, but not both
    // Option 1: Use the UI file (comment out initializeUi if using this)
    // ui->setupUi(this);
    
    // Option 2: Initialize UI programmatically (preferred approach)
    initializeUi();
    
    // Detect monitors on startup
    detectMonitors();
}

MainWindow::~MainWindow()
{
    // QScopedPointer handles deletion automatically
}

void MainWindow::initializeUi()
{
    // Set window title
    setWindowTitle("ArtfulWall - Monitor Information");
    
    // Create central widget and layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    
    // Add title label
    QLabel *titleLabel = new QLabel("Monitor Information", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    layout->addWidget(titleLabel);
    
    // Create text edit for displaying monitor information
    monitorInfoTextEdit = new QTextEdit(this);
    monitorInfoTextEdit->setReadOnly(true);
    layout->addWidget(monitorInfoTextEdit);
    
    // Create refresh button
    refreshButton = new QPushButton("Refresh Monitor Info", this);
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::detectMonitors);
    layout->addWidget(refreshButton);
    
    // Set central widget
    setCentralWidget(centralWidget);
}

void MainWindow::detectMonitors()
{
    // Refresh the monitor info model
    m_monitorInfoModel->refreshMonitorInfo();
    
    // Update the text edit with all monitor information
    monitorInfoTextEdit->setPlainText(m_monitorInfoModel->getCompleteMonitorInfoText());
}

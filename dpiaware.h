#ifndef DPIAWARE_H
#define DPIAWARE_H

class QApplication;

// Initialize DPI awareness for the application
// This is required and should be called before creating QApplication
void initializeDpiAwareness();

// Set DPI-aware font scaling based on the system DPI
// This is optional and only needed for custom font scaling scenarios
// Qt handles font scaling automatically in most cases
void initializeDpiAwareFont(QApplication &app);

#endif // DPIAWARE_H 
#ifndef WINDOWS_HELPER_H
#define WINDOWS_HELPER_H

// Include this file whenever you need Windows API access
// It properly handles platform differences

#ifdef Q_OS_WIN
#include <windows.h>
#define HAS_WINDOWS_API 1

// Define Windows 10 DPI awareness constants if not already defined
#ifndef DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2
typedef HANDLE DPI_AWARENESS_CONTEXT;
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 ((DPI_AWARENESS_CONTEXT)-4)
#endif

#else
#define HAS_WINDOWS_API 0
// Define stub types/constants for non-Windows platforms if needed
typedef void* HDC;
#define NULL 0
typedef void* DPI_AWARENESS_CONTEXT;
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 ((DPI_AWARENESS_CONTEXT)-4)
#endif

#endif // WINDOWS_HELPER_H 
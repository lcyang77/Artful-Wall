# ArtfulWall

A Qt6 application for Windows that displays wallpapers in a grid pattern on your desktop.

## Features

- Monitor information detection (name, resolution, physical size, DPI, refresh rate, orientation, device pixel ratio)
- High DPI scaling support for crisp UI on 4K and high-resolution displays
- Comprehensive DPI detection and handling (both Windows API and Qt methods)
- More features coming soon...

## Requirements

- Qt 6.x
- CMake 3.16 or higher
- C++17 compatible compiler

## Building the Project

### Using Qt Creator

1. Open Qt Creator
2. Select "Open Project"
3. Navigate to the project directory and select the CMakeLists.txt file
4. Configure the project with a compatible kit
5. Build the project

### Using CMake from command line

```bash
# Create a build directory
mkdir build
cd build

# Configure the project
cmake ..

# Build the project
cmake --build .
```

## Running the Application

After building, run the executable from the build directory or directly from Qt Creator.

## Architecture

ArtfulWall has been designed with modularity and separation of concerns in mind:

### Key Components

1. **DpiHelper** (`dpihelper.h`, `dpihelper.cpp`)
   - Utility class containing static methods for DPI calculations
   - Handles coordinate conversions between logical and physical spaces
   - Detects system DPI using multiple methods (Qt and Windows API)
   - Calculates physical dimensions from resolution and DPI

2. **MonitorInfoModel** (`monitorinfomodel.h`, `monitorinfomodel.cpp`)
   - Manages monitor information collection
   - Formats information as readable text
   - Caches monitor data for efficient display updates
   - Uses batch string operations for improved performance

3. **DpiAware** (`dpiaware.h`, `dpiaware.cpp`)
   - Initializes DPI awareness for the application
   - Contains platform-specific DPI code
   - Provides font scaling based on system DPI

4. **WindowsHelper** (`windows_helper.h`)
   - Platform-specific abstraction layer
   - Contains Windows API includes with fallbacks for other platforms
   - Defines constants and types for cross-platform compatibility

5. **MainWindow** (`mainwindow.h`, `mainwindow.cpp`)
   - Main UI component
   - Displays monitor information from MonitorInfoModel
   - Focused solely on UI concerns, not DPI calculations

### Architectural Benefits

- **Separation of Concerns**: Each class has a single responsibility
- **Improved Maintainability**: Code is organized into logical modules
- **Performance Optimization**: String operations are batched for efficiency
- **Memory Management**: Smart pointers (QScopedPointer) used for automatic resource cleanup
- **Cross-Platform Compatibility**: Windows-specific code is isolated
- **Modern C++ Style**: Use of override, forward declarations, and other C++17 features

## High DPI Support

ArtfulWall includes full support for high DPI displays:

- Automatically adapts to Windows scaling settings
- Properly scales UI elements on high resolution displays (2K, 4K)
- Handles multi-monitor setups with different DPI settings
- Provides utility functions for converting between logical and physical coordinates

The application uses Qt6's built-in high DPI scaling features:

- High-DPI scaling is automatically enabled in Qt6
- Qt::HighDpiScaleFactorRoundingPolicy::PassThrough for non-integer scaling (125%, 150%, 175%)
- High-DPI pixmaps are automatically enabled in Qt6

### DPI Detection Methods

The application implements multiple methods for detecting and working with DPI:

1. **Qt Screen API**
   - `screen->logicalDotsPerInchX()` / `logicalDotsPerInchY()` - Logical DPI (affected by Windows scaling)
   - `screen->physicalDotsPerInchX()` / `physicalDotsPerInchY()` - Physical DPI (actual screen DPI)
   - `screen->devicePixelRatio()` - Windows scaling factor

2. **Windows API (Win32)**
   - `GetDeviceCaps(desktopDc, LOGPIXELSX)` / `LOGPIXELSY` - Get system DPI settings

3. **Coordinate Conversion Utilities**
   - `DpiHelper::fromNativePixels()` - Convert physical coordinates to logical coordinates
   - `DpiHelper::toNativePixels()` - Convert logical coordinates to physical coordinates
   - Functions to calculate physical screen size based on resolution and DPI

### Font Scaling Example

The application includes code to properly scale fonts based on DPI:

```cpp
// In dpiaware.cpp
void initializeDpiAwareFont(QApplication &app)
{
    int horizontalDPI, verticalDPI;
    DpiHelper::detectWindowsDPI(horizontalDPI, verticalDPI);
    
    int dpi = (horizontalDPI + verticalDPI) / 2;
    int fontsize = 4 * dpi / 72; // 8pt at 144dpi is 4px
    fontsize = fontsize > 8 ? fontsize : 8;
    
    QFont appFont = app.font();
    appFont.setPointSize(fontsize);
    app.setFont(appFont);
}
```

## Current Implementation

The current implementation can detect and display monitor information:
- Monitor name
- Screen geometry (both logical and native resolution)
- Available geometry
- Physical size in millimeters and centimeters
- DPI information (logical & physical, both Qt and Windows API methods)
- Refresh rate
- Screen orientation
- Device pixel ratio (Windows scaling percentage)
- Examples of coordinate conversion between logical and physical spaces
- Font scaling calculations

More features will be implemented in future updates. 
# QMLQuickDemo

## Overview

Video: http://renaudguezennec.eu/backup/2025/08/examples.mp4

**QML Quick Demo** is a Qt Creator plugin that provides an all-in-one environment for experimenting with and learning QML.

It brings everything you need into a single window:

- **QML Editor** — write and edit your QML code with syntax highlighting.
- **Live QML View** — see the result of your code immediately.
- **Log Panel** — monitor QML errors, warnings, and runtime messages.

The QML view is automatically refreshed whenever the source code is modified, making it easy to experiment with QML and instantly see the effect of your changes.

## QML Examples

The plugin also includes a collection of ready-to-use QML examples organized into different categories. They provide simple, focused examples that can be used to discover QML features, experiment with UI components, and understand how different concepts work.

Simply select an example, modify the code, and see the result live.

## Why QML Quick Demo?

QML Quick Demo is designed to make QML experimentation as simple and interactive as possible:

> **Write → See the result → Experiment**

There is no need to switch between multiple editors, applications, or preview windows. Everything is available directly inside Qt Creator.

## More information

For more information about QML Quick Demo, visit the [project page](http://renaudguezennec.eu/projects/plugin-qt-creator/).

The source code is available on [GitHub](https://github.com/obiwankennedy/QmlSampleEditor).

## Building

The plugin can be built as a standard Qt Creator plugin using CMake. See the build instructions below for more information.

## How to Build

Create a build directory and run

    cmake -DCMAKE_PREFIX_PATH=<path_to_qtcreator> -DCMAKE_BUILD_TYPE=RelWithDebInfo <path_to_plugin_source>
    cmake --build .

where `<path_to_qtcreator>` is the relative or absolute path to a Qt Creator build directory, or to a
combined binary and development package (Windows / Linux), or to the `Qt Creator.app/Contents/Resources/`
directory of a combined binary and development package (macOS), and `<path_to_plugin_source>` is the
relative or absolute path to this plugin directory.

## How to Run

From the command line run

    cmake --build . --target RunQtCreator

`RunQtCreator` is a custom CMake target that will use the <path to qtcreator> referenced above to
start the Qt Creator executable with the following parameters

    -pluginpath <path_to_plugin>

where `<path_to_plugin>` is the path to the resulting plugin library in the build directory
(`<plugin_build>/lib/qtcreator/plugins` on Windows and Linux,
`<plugin_build>/Qt Creator.app/Contents/PlugIns` on macOS).

You might want to add `-temporarycleansettings` (or `-tcs`) to ensure that the opened Qt Creator
instance cannot mess with your user-global Qt Creator settings.

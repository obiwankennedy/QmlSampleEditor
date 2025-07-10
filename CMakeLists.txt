cmake_minimum_required(VERSION 3.24)

# Remove when sharing with others.
list(APPEND CMAKE_PREFIX_PATH "/home/renaud/applications/mine/qt-creator/build/Desktop_Qt_6_8_3-release")

project(QMLQuickDemo)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(QtCreator REQUIRED COMPONENTS Core TextEditor QmlJS QmlJSEditor QmlJSTools LanguageClient)
find_package(Qt6 COMPONENTS Widgets QuickWidgets REQUIRED)

# Add a CMake option that enables building your plugin with tests.
# You don't want your released plugin binaries to contain tests,
# so make that default to 'NO'.
# Enable tests by passing -DWITH_TESTS=ON to CMake.
option(WITH_TESTS "Builds with tests" NO)

if(WITH_TESTS)
  # Look for QtTest
  find_package(Qt6 REQUIRED COMPONENTS Test)

  # Tell CMake functions like add_qtc_plugin about the QtTest component.
  set(IMPLICIT_DEPENDS Qt::Test)

  # Enable ctest for auto tests.
  enable_testing()
endif()



add_qtc_plugin(QMLQuickDemo
  PLUGIN_DEPENDS
    QtCreator::Core
    QtCreator::TextEditor
    QtCreator::QmlJSEditor
    QtCreator::QmlJSTools
    QtCreator::LanguageClient
  DEPENDS
    Qt::Widgets
    Qt::QuickWidgets
    QtCreator::ExtensionSystem
    QtCreator::Utils
    QtCreator::QmlJS
  SOURCES
    .github/workflows/build_cmake.yml
    .github/workflows/README.md
    README.md
    qmlquickdemo.cpp
    qmlquickdemoconstants.h
    qmlquickdemotr.h
    quickqmltester.h
    qmlhighlighter.cpp
    qmlhighlighter.h
    quickqmltester.cpp
    quickqmltester.ui
)

qt_add_resources(QMLQuickDemo "dico"
  PREFIX
      "dico"
  FILES
    assets/javascript.txt
    assets/keywords.txt
    assets/properties.txt
    assets/properties.txt
    assets/qml.txt)

target_sources(QMLQuickDemo
  PRIVATE
    qmleditor.h qmleditor.cpp
)

# Enable the Run button in Qt Creator
get_target_property(QtCreatorCorePath QtCreator::Core LOCATION)
find_program(QtCreatorExecutable
  NAMES
    qtcreator "Qt Creator"
  PATHS
    "${QtCreatorCorePath}/../../../bin"
    "${QtCreatorCorePath}/../../../MacOS"
  NO_DEFAULT_PATH
)
if (QtCreatorExecutable)
  add_custom_target(RunQtCreator
    COMMAND ${QtCreatorExecutable} -pluginpath $<TARGET_FILE_DIR:QMLQuickDemo>
    DEPENDS QMLQuickDemo
  )
  set_target_properties(RunQtCreator PROPERTIES FOLDER "qtc_runnable")
endif()

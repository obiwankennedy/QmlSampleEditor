#ifndef QUICKQMLTESTER_H
#define QUICKQMLTESTER_H

#include <QMainWindow>
#include <QSet>
#include <texteditor/textdocument.h>
#include "qmleditor.h"

namespace Ui {
class QuickQMLTester;
}

class QuickQMLTester : public QMainWindow
{
    Q_OBJECT

public:
    enum LogLevel {
      ErrorLevel,
        WarningLevel
    };
    explicit QuickQMLTester(QWidget *parent = nullptr);
    ~QuickQMLTester();

    void makeUiReady();


private slots:
    void writeLog(const QString& msg, LogLevel level = ErrorLevel);

private:
    Ui::QuickQMLTester *ui;
    QString m_oldFile;
    TextEditor::TextDocumentPtr m_document;
    QmlEditor* m_editor;
};

#endif // QUICKQMLTESTER_H

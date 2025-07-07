#ifndef QMLEDITOR_H
#define QMLEDITOR_H

#include <texteditor/texteditor.h>
#include <qmljseditor/qmljseditor.h>

class QmlEditor : public QmlJSEditor::QmlJSEditorWidget
{
public:
    QmlEditor();
};

#endif // QMLEDITOR_H

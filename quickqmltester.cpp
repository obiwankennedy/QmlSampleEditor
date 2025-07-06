#include "quickqmltester.h"
#include "ui_quickqmltester.h"
#include <qmljseditor/qmljseditordocument.h>
#include <qmljseditor/qmljshighlighter.h>
#include "qmleditor.h"

#include <QTemporaryFile>
#include <QDateTime>

QString getTime()
{
    QDateTime time = QDateTime::currentDateTime();
    return time.toString("hh:mm:ss");
}

QuickQMLTester::QuickQMLTester(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QuickQMLTester)
{
    ui->setupUi(this);

    auto document = new QmlJSEditor::QmlJSEditorDocument(Utils::Id());

    m_document.reset(document);
    document->resetSyntaxHighlighter([] { return new QmlJSEditor::QmlJSHighlighter(); });

    auto layout = new QVBoxLayout();
    m_editor = new QmlEditor();
    layout->addWidget(m_editor);
    m_editor->setTextDocument(m_document);

    ui->m_qmlCodeEdit->setLayout(layout);

    connect(ui->m_qmlViewer, &QQuickWidget::sceneGraphError, this, [this](QQuickWindow::SceneGraphError error, const QString &message)
    {
        writeLog(message);
    });

    connect(m_editor, &TextEditor::TextEditorWidget::textChanged, this, [this](){
        // run in qtConcurrent
        auto qmlCode = m_editor->toPlainText();

        QTemporaryFile file;
        file.setAutoRemove(false);
        if(file.open())
        {
            if(!m_oldFile.isEmpty())
                QFile::remove(m_oldFile);
            ui->m_consoleEdit->clear();
            auto fileName = file.fileName();
            m_oldFile = fileName;
            auto url = QUrl::fromLocalFile(fileName);
            file.write(qmlCode.toUtf8());
            file.flush();
            ui->m_qmlViewer->setSource(url);
            auto errors = ui->m_qmlViewer->errors();
            for(auto const & e : std::as_const(errors)) {
                static QHash<QtMsgType, LogLevel> level{{QtMsgType::QtCriticalMsg, LogLevel::ErrorLevel},
                                                        {QtMsgType::QtFatalMsg, LogLevel::ErrorLevel},
                                                        {QtMsgType::QtDebugMsg, LogLevel::WarningLevel},
                                                        {QtMsgType::QtWarningMsg, LogLevel::WarningLevel},
                                                        {QtMsgType::QtInfoMsg, LogLevel::WarningLevel}};
                writeLog(e.toString(),  level.value(e.messageType()));
            }

        }
    });
}

QuickQMLTester::~QuickQMLTester()
{
    delete ui;
}

void QuickQMLTester::writeLog(const QString &msg, LogLevel level)
{
    ui->m_consoleEdit->append(QStringLiteral("[%1]%2 - %3 ").arg(getTime(),level == LogLevel::ErrorLevel ? tr("Error") : tr("Warning") ,msg));
}

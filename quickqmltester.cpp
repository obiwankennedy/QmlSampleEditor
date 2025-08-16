#include "quickqmltester.h"
#include "ui_quickqmltester.h"
#include <qmljseditor/qmljseditordocument.h>
#include <qmljseditor/qmljshighlighter.h>
#include <qmljseditor/qmljsautocompleter.h>
#include <qmljseditor/qmljshoverhandler.h>
#include <qmljseditor/qmljscompletionassist.h>
#include <qmljstools/qmljsindenter.h>
#include <coreplugin/editormanager/editormanager.h>
#include "qmlhighlighter.h"

#include "qmleditor.h"

#include <QTemporaryFile>
#include <QDateTime>
#include <QQmlEngine>

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
}

QuickQMLTester::~QuickQMLTester()
{
    delete ui;
}

void QuickQMLTester::makeUiReady()
{
    auto document = new QmlJSEditor::QmlJSEditorDocument(Utils::Id());

    m_document.reset(document);
    document->resetSyntaxHighlighter([] { return new QmlJSEditor::QmlJSHighlighter(); });
    //document->resetSyntaxHighlighter([this] { return new QmlHighlighter(m_document->document())});
    new QmlHighlighter(m_document->document());

    auto layout = new QVBoxLayout();
    m_editor = new QmlEditor();
    auto clientManager = LanguageClient::LanguageClientManager::instance();
    clientManager->editorOpened(Core::EditorManager::currentEditor());
    clientManager->documentOpened(m_document.get());
    //clientManager->documentClosed(m_document.get());

    layout->addWidget(m_editor);
    m_editor->setTextDocument(m_document);

    m_editor->finalizeInitialization();
    m_editor->setAutoCompleter(new QmlJSEditor::AutoCompleter);
    m_editor->setParenthesesMatchingEnabled(true);
    m_editor->setCodeFoldingSupported(true);
    m_editor->addHoverHandler(new QmlJSEditor::QmlJSHoverHandler);
    m_document->setCompletionAssistProvider(new QmlJSEditor::QmlJSCompletionAssistProvider);
    m_document->setIndenter(QmlJSEditor::createQmlJsIndenter(m_document->document()));

    //QmlJSEditor::QmlJSEditorFactory::decorateEditor(m_editor);

    ui->m_qmlCodeEdit->setLayout(layout);

    ui->m_qmlViewer->engine()->setOutputWarningsToStandardError(false);

    connect(ui->m_qmlViewer->engine(), &QQmlEngine::warnings, this, [this](const QList<QQmlError>& warnings){
        qDebug() << "warinnigs @@@@@@@@@@@@@@@@@@";
        for(const auto &w : warnings)
        {
            writeLog(w.toString());
        }
    });

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

    ui->m_01Act->setData(":/dico/assets/qmlexamples/01_anchor_animation.qml");
    ui->m_02Act->setData(":/dico/assets/qmlexamples/02_anchor_changes.qml");
    ui->m_03Act->setData(":/dico/assets/qmlexamples/03_animated_image.qml");
    ui->m_04Act->setData(":/dico/assets/qmlexamples/04_animated_sprite.qml");
    ui->m_05Act->setData(":/dico/assets/qmlexamples/05_animated_easing_type.qml");
    ui->m_06Act->setData(":/dico/assets/qmlexamples/06_rotation_animation.qml");
    ui->m_07Act->setData(":/dico/assets/qmlexamples/07_sequential_animation.qml");
    ui->m_08Act->setData(":/dico/assets/qmlexamples/08_game_01.qml");
    ui->m_09Act->setData(":/dico/assets/qmlexamples/09_game_02.qml");
    ui->m_10Act->setData(":/dico/assets/qmlexamples/10_blend_image.qml");
    ui->m_11Act->setData(":/dico/assets/qmlexamples/11_brightness_and_conrtast.qml");
    ui->actionJSon_Model->setData(":/dico/assets/qmlexamples/12_json_model.qml");
    ui->actionListModel_ListElement->setData(":/dico/assets/qmlexamples/13_listmodel.qml");
    ui->actionBinding->setData(":/dico/assets/qmlexamples/14_binding.qml");
    ui->actionCanvas_Advanced->setData(":/dico/assets/qmlexamples/15_canvas.qml");
    ui->actionGridLayout->setData(":/dico/assets/qmlexamples/16_gridlayout.qml");
    ui->actionRepeater->setData(":/dico/assets/qmlexamples/17_repeater.qml");
    ui->actionSearch_Regex_match->setData(":/dico/assets/qmlexamples/18_search.qml");
    ui->actiontaphandler->setData(":/dico/assets/qmlexamples/19_taphandler.qml");
    ui->actionText_Format->setData(":/dico/assets/qmlexamples/20_text_format.qml");
    ui->actionShader_Effect_Pixelated->setData(":/dico/assets/qmlexamples/21_shader_effect_pixelated.qml");
    ui->actionShader_Effect->setData(":/dico/assets/qmlexamples/22_shader_effect.qml");
    ui->actionFooter->setData(":/dico/assets/qmlexamples/23_footer.qml");
    ui->actionPush_pop_clear->setData(":/dico/assets/qmlexamples/24_push.qml");
    ui->actionSimple_chat->setData(":/dico/assets/qmlexamples/25_simplechat.qml");


    auto func = [this](){
        auto act = qobject_cast<QAction*>(sender());

        if(!act)
            return;
        auto path = act->data().toString();

        QFile file(path);
        if(!file.open(QIODevice::ReadOnly))
        {
            qWarning() << "Can't read the file:" << path;
            return;
        }
        auto data = file.readAll();
        m_editor->document()->setPlainText(QString::fromUtf8(data));
    };

    connect(ui->m_01Act, &QAction::triggered,this, func);
    connect(ui->m_02Act, &QAction::triggered,this, func);
    connect(ui->m_03Act, &QAction::triggered,this, func);
    connect(ui->m_04Act, &QAction::triggered,this, func);
    connect(ui->m_05Act, &QAction::triggered,this, func);
    connect(ui->m_06Act, &QAction::triggered,this, func);
    connect(ui->m_07Act, &QAction::triggered,this, func);
    connect(ui->m_08Act, &QAction::triggered,this, func);
    connect(ui->m_09Act, &QAction::triggered,this, func);
    connect(ui->m_10Act, &QAction::triggered,this, func);
    connect(ui->m_11Act, &QAction::triggered,this, func);
    connect(ui->actionJSon_Model, &QAction::triggered,this, func);
    connect(ui->actionRepeater, &QAction::triggered,this, func);
    connect(ui->actionListModel_ListElement, &QAction::triggered,this, func);
    connect(ui->actionBinding, &QAction::triggered,this, func);
    connect(ui->actionCanvas_Advanced, &QAction::triggered,this, func);
    connect(ui->actionGridLayout, &QAction::triggered,this, func);
    connect(ui->actionPush_pop_clear, &QAction::triggered,this, func);
    connect(ui->actionSearch_Regex_match, &QAction::triggered,this, func);
    connect(ui->actionShader_Effect, &QAction::triggered,this, func);
    connect(ui->actionShader_Effect_Pixelated, &QAction::triggered,this, func);
    connect(ui->actionFooter, &QAction::triggered,this, func);
    connect(ui->actiontaphandler, &QAction::triggered,this, func);
    connect(ui->actionText_Format, &QAction::triggered,this, func);
    connect(ui->actionSimple_chat, &QAction::triggered,this, func);
}

void QuickQMLTester::writeLog(const QString &msg, LogLevel level)
{
    ui->m_consoleEdit->append(QStringLiteral("[%1]%2 - %3 ").arg(getTime(),level == LogLevel::ErrorLevel ? tr("Error") : tr("Warning") ,msg));
}

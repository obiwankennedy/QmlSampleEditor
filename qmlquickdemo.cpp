#include "qmlquickdemoconstants.h"
#include "qmlquickdemotr.h"

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/icontext.h>
#include <coreplugin/icore.h>
#include <coreplugin/themechooser.h>

#include <utils/theme/theme.h>
#include <utils/theme/theme_p.h>

#include <extensionsystem/iplugin.h>

#include <QAction>
#include <QMainWindow>
#include <QMenu>

#include "quickqmltester.h"

using namespace Core;

namespace QMLQuickDemo::Internal {

class QMLQuickDemoPlugin final : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "QMLQuickDemo.json")

public:
    QMLQuickDemoPlugin() = default;

    ~QMLQuickDemoPlugin() final
    {
        // Unregister objects from the plugin manager's object pool
        // Other cleanup, if needed.
    }

    void initialize() final
    {
        // Set up this plugin's factories, if needed.
        // Register objects in the plugin manager's object pool, if needed. (rare)
        // Load settings
        // Add actions to menus
        // Connect to other plugins' signals
        // In the initialize function, a plugin can be sure that the plugins it
        // depends on have passed their initialize() phase.

        // If you need access to command line arguments or to report errors, use the
        //    Utils::Result<> IPlugin::initialize(const QStringList &arguments)
        // overload.

        ActionContainer *menu = ActionManager::createMenu(Constants::MENU_ID);
        menu->menu()->setTitle(Tr::tr("QMLQuickDemo"));
        ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);

        ActionBuilder(this, Constants::ACTION_ID)
            .addToContainer(Constants::MENU_ID)
            .setText(Tr::tr("Show Quick Tester"))
            .setDefaultKeySequence(Tr::tr("Ctrl+Alt+Meta+A"))
            .addOnTriggered(this, &QMLQuickDemoPlugin::triggerAction);
    }

    void extensionsInitialized() final
    {
        // Retrieve objects from the plugin manager's object pool, if needed. (rare)
        // In the extensionsInitialized function, a plugin can be sure that all
        // plugins that depend on it have passed their initialize() and
        // extensionsInitialized() phase.

        //auto core = Core::Internal::CorePlugin::instance();
        //auto theme = Core::Internal::ThemeEntry::createTheme(Core::Internal::ThemeEntry::themeSetting());
        //Utils::setCreatorTheme(theme);
    }

    ShutdownFlag aboutToShutdown() final
    {
        // Save settings
        // Disconnect from signals that are not needed during shutdown
        // Hide UI (if you add UI that is not in the main window directly)
        return SynchronousShutdown;
    }

private:
    void triggerAction()
    {
        if(!m_window)
        {
            m_window.reset(new QuickQMLTester);
            m_window->makeUiReady();
        }
        m_window->show();
    }
private:
    std::unique_ptr<QuickQMLTester> m_window;
};

} // namespace QMLQuickDemo::Internal

#include <qmlquickdemo.moc>

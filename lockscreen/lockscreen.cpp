/****************************************************************************************
 * Copyright (C) 2011 Lucien XU <sfietkonstantin@free.fr>                               *
 *                                                                                      *
 * This program is free software; you can redistribute it and/or modify it under        *
 * the terms of the GNU General Public License as published by the Free Software        *
 * Foundation; either version 3 of the License, or (at your option) any later           *
 * version.                                                                             *
 *                                                                                      *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
 *                                                                                      *
 * You should have received a copy of the GNU General Public License along with         *
 * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
 ****************************************************************************************/

#include "lockscreen.h"
#include "lockscreenmanager.h"
#include "debughelper.h"
#include "global.h"
#include "oxygencolors.h"
#include "settings.h"
#include "settingswrapper.h"
/*#include "elementsettings.h"
#include "widgetbaseproperties.h"
#include "widgetproperties.h"
#include "dockbaseproperties.h"
#include "dockproperties.h"
#include "applicationinformations.h"
#include "viewmanager.h"
#include "displayedpagesmodel.h"
#include "displayedpagewidgetsmodel.h"
#include "displayeddocksmodel.h"
#include "availablewidgetsmodel.h"
#include "availabledocksmodel.h"
#include "packagemanager.h"
#include "applicationsmodel.h"
#include "launchermanager.h"*/

#include <QtDeclarative/QDeclarativeItem>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeComponent>
//#include <QtDeclarative/QtDeclarative>
//#include <QGraphicsLinearLayout>
#include <QtDeclarative/QDeclarativeView>
//#include <QFile>

namespace Widgets
{

class LockScreen::LockScreenPrivate
{
public:
    LockScreenPrivate(LockScreen *parent);
    ~LockScreenPrivate();
    static void registerQmlTypes();
    void initializeObjects();
    void setupEngine();
    void createItem();
    QDeclarativeView *view;
//    QDeclarativeEngine *engine;
//    QDeclarativeItem *item;
//    QGraphicsItem *item;
    OxygenColors *colors;
    Settings *settings;
    SettingsWrapper *settingsWrapper;
//    PackageManager *packageManager;
//    DisplayedPagesModel *displayedPagesModel;
//    DisplayedDocksModel *displayedDocksModel;
//    ViewManager *viewManager;
//    ApplicationsModel *applicationsModel;
//    LauncherManager *launcherManager;
private:
    LockScreen * const q;
};

LockScreen::LockScreenPrivate::LockScreenPrivate(LockScreen *parent):
    q(parent)
{
    // Delay objects initializations
    // (Settings needs application name first)
    // Initialization is done with initializeObjects()
    view = 0;
//    engine = 0;
//    item = 0;
    colors = 0;
    settings = 0;
    settingsWrapper = 0;
//    packageManager = 0;
//    displayedPagesModel = 0;
//    displayedDocksModel = 0;
//    viewManager = 0;
//    applicationsModel = 0;
//    launcherManager = 0;
}

LockScreen::LockScreenPrivate::~LockScreenPrivate()
{
    delete colors;
    view->deleteLater();
//    engine->deleteLater();
}

void LockScreen::LockScreenPrivate::registerQmlTypes()
{
//    qmlRegisterType<Widgets::ElementSettings>("org.sk.widgets", 1, 0, "ElementSettings");
//    qmlRegisterType<Widgets::WidgetBaseProperties>("org.sk.widgets", 1, 0, "WidgetBaseProperties");
//    qmlRegisterType<Widgets::WidgetProperties>("org.sk.widgets", 1, 0, "WidgetProperties");
//    qmlRegisterType<Widgets::DockBaseProperties>("org.sk.widgets", 1, 0, "DockBaseProperties");
//    qmlRegisterType<Widgets::DockProperties>("org.sk.widgets", 1, 0, "DockProperties");
//    qmlRegisterType<Widgets::ApplicationInformations>("org.sk.widgets", 1, 0,
//                                                      "ApplicationInformations");
//    qmlRegisterType<Widgets::FolderModel>("org.sk.widgets", 1, 0, "FolderModel");
//    qmlRegisterType<Widgets::DisplayedPageWidgetsModel>("org.sk.widgets", 1, 0,
//                                                        "DisplayedPageWidgetsModel");
//    qmlRegisterType<Widgets::Settings>("org.sk.widgets", 1, 0, "Settings");
}

void LockScreen::LockScreenPrivate::initializeObjects()
{
    // Initialize objects
//    engine = new QDeclarativeEngine();
    view = new QDeclarativeView();
    colors = new OxygenColors();
    settings = new Settings("sk", "Widgets", q);
    settingsWrapper = new SettingsWrapper(settings, q);
//    packageManager = new PackageManager("/opt/widgets/qml",
//                                        "/opt/widgets/widgets/", q);
//    displayedPagesModel = new DisplayedPagesModel(settings, packageManager, q);
//    displayedDocksModel = new DisplayedDocksModel(settings, packageManager, q);
//    viewManager = new ViewManager(settingsWrapper, displayedPagesModel, q);
//    applicationsModel = new ApplicationsModel(q);
//    launcherManager = new LauncherManager(q);

    // Load default settings
//    settings->setDefaultSettings();

    // Pages
//    displayedPagesModel->setPageCount(settings->value("view/pageCount").toInt());
}

void LockScreen::LockScreenPrivate::setupEngine()
{
    // Context properties
    QDeclarativeContext *context = //engine->rootContext();
            view->rootContext();
    context->setContextProperty("colors", colors);
    context->setContextProperty("settings", settings);
    context->setContextProperty("settingsWrapper", settingsWrapper);
//    context->setContextProperty("packageManager", packageManager);
//    context->setContextProperty("availableWidgetsModel", packageManager->availableWidgetsModel());
//    context->setContextProperty("availableDocksModel", packageManager->availableDocksModel());
//    context->setContextProperty("displayedPagesModel", displayedPagesModel);
//    context->setContextProperty("displayedDocksModel", displayedDocksModel);
//    context->setContextProperty("viewManager", viewManager);
//    context->setContextProperty("applicationsModel", applicationsModel);
//    context->setContextProperty("launcherManager", launcherManager);

    // Lock screen manager
    LockScreenManager *lockScreenManager = new LockScreenManager(q);
    context->setContextProperty("lockScreenManager", lockScreenManager);
    connect(lockScreenManager, SIGNAL(unlocked()), q , SIGNAL(unlocked()));

    // Debug helper
    DebugHelper *debugHelper = new DebugHelper(q);
    context->setContextProperty("debugHelper", debugHelper);


}

void LockScreen::LockScreenPrivate::createItem()
{
//    QDeclarativeComponent component (engine,
//                                     QUrl(QString(APPLICATION_QML_PATH) + "main-lockscreen.qml"));
//    QObject *object = component.create();
//    item = qobject_cast<QGraphicsItem *>(object);
//    item->setParentItem(q);

//    QDeclarativeItem *declarativeItem = qobject_cast<QDeclarativeItem *>(object);
//    declarativeItem->setSmooth(false);


//    view->setAttribute(Qt::WA_OpaquePaintEvent);
//    view->setAttribute(Qt::WA_NoSystemBackground);
//    view->viewport()->setAutoFillBackground(false);

    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    view->setSource(QUrl(QString(APPLICATION_QML_PATH) + "main-lockscreen.qml"));
    q->setWidget(view);
//    q->setGraphicsItem(item);
}

////// End of private class //////

LockScreen::LockScreen(QGraphicsWidget *parent):
//    QGraphicsObject(parent), QGraphicsLayoutItem(parent), d(new LockScreenPrivate(this))
    QGraphicsProxyWidget(parent), d(new LockScreenPrivate(this))
//    QGraphicsWidget(parent), d(new LockScreenPrivate(this))
{
    d->registerQmlTypes();
    d->initializeObjects();
    d->setupEngine();
    d->createItem();

    connect(this, SIGNAL(geometryChanged()) , this, SLOT(slotSetGeometry()));

//    setWidget(d->view);

}

//QRectF LockScreen::boundingRect() const
//{
//    return d->item->boundingRect();
//}

//void LockScreen::paint(QPainter *painter,
//                              const QStyleOptionGraphicsItem *option,
//                              QWidget *widget)
//{
//    Q_UNUSED(painter)
//    Q_UNUSED(option)
//    Q_UNUSED(widget)
//}

//QSizeF LockScreen::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
//{
//    Q_UNUSED(which)
//    Q_UNUSED(constraint)
//    return QSizeF(d->item->width(), d->item->height());
//}

void LockScreen::reset()
{
}

void LockScreen::setMode(ScreenLockExtensionInterface::ScreenLockMode mode)
{
    Q_UNUSED(mode)
}





//LockScreen::LockScreen(QGraphicsWidget *parent):
//    QGraphicsProxyWidget(parent)
//{
//    LockScreenManager *manager = new LockScreenManager(this);

//    view = new QDeclarativeView();
//    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
//    view->rootContext()->setContextProperty("lockScreenManager", manager);
//    view->setSource(QUrl("/opt/widgets/qml/main-lockscreen.qml"));

//    setWidget(view);

//    connect(manager, SIGNAL(unlocked()), this , SIGNAL(unlocked()));
//}

//void LockScreen::slotSetGeometry()
//{
//    QFile f("/home/developer/log2");
//    if(f.open(QIODevice::WriteOnly | QIODevice::Append)) {
//        f.write(QString("(%1,%2) %3x%4\n").arg(geometry().x()).arg(geometry().y()).arg(geometry().width()).arg(geometry().height()).toAscii());
//        f.write(QString("(%1,%2) %3x%4\n\n").arg(d->item->x()).arg(d->item->y()).arg(d->item->boundingRect().width()).arg(d->item->boundingRect().height()).toAscii());
//        f.close();
//    }
//}




}

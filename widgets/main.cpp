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

/**
 * @file widgets/main.cpp
 * @short Entry point of the application
 */

#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeView>
#include "qplatformdefs.h"

#ifdef MEEGO_EDITION_HARMATTAN
#include <MDeclarativeCache>
#endif

#ifdef QML_PLUGIN_PATH
#include <QtDeclarative/QDeclarativeEngine>
#endif

/**
 * @short Main
 *
 * Entry point of the application.
 *
 * @param argc argc
 * @param argv argv
 * @return exit code.
 */
Q_DECL_EXPORT int main(int argc, char *argv[])
{
#ifdef MEEGO_EDITION_HARMATTAN
    QScopedPointer<QApplication> app(MDeclarativeCache::qApplication(argc, argv));
    QScopedPointer<QDeclarativeView> view(MDeclarativeCache::qDeclarativeView());
#else
    QApplication *app = new QApplication(argc, argv);
    QDeclarativeView *view = new QDeclarativeView();
#endif

#ifdef QML_PLUGIN_PATH
    view->engine()->addImportPath(QML_PLUGIN_PATH);
#endif

    view->setSource(QUrl(MAIN_QML_PATH));

    QObject::connect(view->engine(), SIGNAL(quit()), view, SLOT(close()));
#ifdef MEEGO_EDITION_HARMATTAN
    view->showFullScreen();
#else
    view->show();
#endif

    return app->exec();
}

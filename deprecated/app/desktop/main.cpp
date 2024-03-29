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


#include <QtGui/QApplication>
#include <QtDeclarative/QtDeclarative>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeEngine>

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);
    QDeclarativeView view;
    app.setApplicationName("Widgets");
    app.setOrganizationName("SfietKonstantin");


    view.engine()->addImportPath(IMPORT_DIR);
    view.rootContext()->setContextProperty("ICON_DIR", DATA_DIR);
    view.setMinimumSize(480, 640);
    view.setResizeMode(QDeclarativeView::SizeRootObjectToView);
    view.setSource(QUrl(MAIN_QML_PATH));

    QObject::connect(view.engine(), SIGNAL(quit()), &view, SLOT(close()));
    view.show();

    return app.exec();
}

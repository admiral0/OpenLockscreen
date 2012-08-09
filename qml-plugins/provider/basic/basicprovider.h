/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
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

#ifndef WIDGETS_PROVIDER_BASIC_BASICPROVIDER_H
#define WIDGETS_PROVIDER_BASIC_BASICPROVIDER_H

#include "widgetproviderbase.h"

namespace Widgets
{

namespace Provider
{

namespace Basic
{

class BasicProviderPrivate;
class BasicProvider: public WidgetProviderBase
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
public:
    explicit BasicProvider(QObject *parent = 0);
    virtual ~BasicProvider();
    bool available() const;
    QString path() const;
    Q_INVOKABLE virtual QStringList registeredWidgets(const QVariantHash &disambiguation) const;
    Q_INVOKABLE virtual QString widgetFile(const QString &fileName,
                                           const QVariantHash &disambiguation) const;
    Q_INVOKABLE virtual QString widgetSettingsFile(const QString &fileName,
                                                   const QVariantHash &disambiguation) const;
    Q_INVOKABLE virtual Widgets::WidgetBaseProperties *
                        widget(const QString &fileName,
                               const QVariantHash &disambiguation);
public Q_SLOTS:
    void setPath(const QString &path);
Q_SIGNALS:
    void pathChanged();
protected:
    QScopedPointer<BasicProviderPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(BasicProvider)
};

}

}

}

#endif // BASICPROVIDER_H

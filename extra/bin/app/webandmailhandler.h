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

#ifndef WEBANDMAILHANDLER_H
#define WEBANDMAILHANDLER_H

#include <QtCore/QObject>

class WebAndMailHandler : public QObject
{
    Q_OBJECT
public:
    explicit WebAndMailHandler(QObject *parent = 0);
public Q_SLOTS:
    void openWebpage(const QString &webpage);
    void openMailEditor(const QString &mail);
};

#endif // WEBANDMAILHANDLER_H

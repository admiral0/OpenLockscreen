/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (directui@nokia.com)
**
** This file is part of libmeegotouch.
**
** If you have questions regarding the use of this file, please contact
** Nokia at directui@nokia.com.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#ifndef MAPPLICATIONEXTENSIONINTERFACE_H
#define MAPPLICATIONEXTENSIONINTERFACE_H

#include <QtPlugin>
#include "mexport.h"

class QGraphicsWidget;

class M_EXTENSIONS_EXPORT MApplicationExtensionInterface
{
public:
    virtual ~MApplicationExtensionInterface() {}

    virtual bool initialize(const QString &interface) = 0;

    virtual QGraphicsWidget *widget() { return NULL; }
};

Q_DECLARE_INTERFACE(MApplicationExtensionInterface, "com.meego.core.MApplicationExtensionInterface/1.0")

#endif // MAPPLICATIONEXTENSIONINTERFACE_H

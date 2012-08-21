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

#ifndef WIDGETS_BACKGROUND_SCROLLINGMANAGER_H
#define WIDGETS_BACKGROUND_SCROLLINGMANAGER_H

/**
 * @file parallaxmanager.h
 * @short Definition of Widgets::Background::ParallaxManager
 */

#include <QtCore/QObject>

namespace Widgets
{

namespace Background
{

class ParallaxManagerPrivate;

/**
 * @brief Parallax manager
 *
 * This class is used to compute a parallax effect, based
 * on a QML ListView. The list view in QML have a tendancy of
 * being a little bit buggy, or at least hard to use, this class
 * is used to wrap the list view scrolling with an unique parameter
 * that is used to compute the parallax effect.
 *
 * In order to compute the parallax effect, four parameters have to
 * be provided
 * - contentX(), that is the current x coordinate of the list view content.
 * - initialContentX(), that is the x coordinate when the list view were initialized.
 * - contentWidth(), that is the width of the list view content.
 * - viewWidth(), that is the width of the list view.
 *
 * The computed result is available with position(), that is a float
 * between 0 and 1. If the value is 0, then the view is at the left and
 * if the value is 1, at the right.
 */
class ParallaxManager : public QObject
{
    Q_OBJECT
    /**
     * @short Position
     */
    Q_PROPERTY(qreal position READ position NOTIFY positionChanged)
    /**
     * @short X coordinate of the content
     */
    Q_PROPERTY(qreal contentX READ contentX WRITE setContentX NOTIFY contentXChanged)
    /**
     * @short Initial x coordinate of the content
     */
    Q_PROPERTY(qreal initialContentX READ initialContentX WRITE setInitialContentX
               NOTIFY initialContentXChanged)
    /**
     * @short Width of the content
     */
    Q_PROPERTY(qreal contentWidth READ contentWidth WRITE setContentWidth
               NOTIFY contentWidthChanged)
    /**
     * @short Width of the view
     */
    Q_PROPERTY(qreal viewWidth READ viewWidth WRITE setViewWidth NOTIFY viewWidthChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit ParallaxManager(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~ParallaxManager();
    /**
     * @brief Position
     * @return position.
     */
    qreal position() const;
    /**
     * @brief X coordinate of the content
     * @return x coordinate of the content.
     */
    qreal contentX() const;
    /**
     * @brief Initial x coordinate of the content
     * @return initial x coordinate of the content.
     */
    qreal initialContentX() const;
    /**
     * @brief Width of the content
     * @return width of the content.
     */
    qreal contentWidth() const;
    /**
     * @brief Width of the view
     * @return width of the view.
     */
    qreal viewWidth() const;
Q_SIGNALS:
    /**
     * @brief Position changed
     */
    void positionChanged();
    /**
     * @brief Content x changed
     */
    void contentXChanged();
    /**
     * @brief Initial content x changed
     */
    void initialContentXChanged();
    /**
     * @brief Content width changed.
     */
    void contentWidthChanged();
    /**
     * @brief View width changed.
     */
    void viewWidthChanged();
public Q_SLOTS:
    /**
     * @brief Set content x
     * @param contentX content X.
     */
    void setContentX(qreal contentX);
    /**
     * @brief Set initial content x
     * @param initialContentX initial content x.
     */
    void setInitialContentX(qreal initialContentX);
    /**
     * @brief Set content width
     * @param contentWidth content width.
     */
    void setContentWidth(qreal contentWidth);
    /**
     * @brief Set view width
     * @param viewWidth view width.
     */
    void setViewWidth(qreal viewWidth);
protected:
    /**
     * @brief D-pointer
     */
    QScopedPointer<ParallaxManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(ParallaxManager)
};

}

}

#endif // WIDGETS_BACKGROUND_SCROLLINGMANAGER_H

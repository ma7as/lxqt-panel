/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Razor - a lightweight, Qt based, desktop toolset
 * http://razor-qt.org
 *
 * Copyright: 2010-2011 Razor team
 * Authors:
 *   Alexander Sokoloff <sokoloff.a@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */


#ifndef RAZOR_MAINMENU_H
#define RAZOR_MAINMENU_H

#include "../panel/irazorpanelplugin.h"
#include <qtxdg/xdgmenu.h>

#ifdef HAVE_MENU_CACHE
#include <menu-cache/menu-cache.h>
#endif

#include <QtGui/QLabel>
#include <QToolButton>
#include <QDomElement>
#include <QAction>

#include "menustyle.h"


class QMenu;
class RazorBar;

namespace LxQt {
class PowerManager;
class ScreenSaver;
}

namespace GlobalKeyShortcut
{
class Action;
}

class RazorMainMenu : public QObject, public IRazorPanelPlugin
{
    Q_OBJECT
public:
    RazorMainMenu(const IRazorPanelPluginStartupInfo &startupInfo);
    ~RazorMainMenu();

    QString themeId() const { return "MainMenu"; }
    virtual IRazorPanelPlugin::Flags flags() const { return HaveConfigDialog ; }

    QWidget *widget() { return &mButton; }
    QDialog *configureDialog();

    bool isSeparate() const { return true; }

private:
    QToolButton mButton;
    QString mLogDir;
    QMenu* mMenu;
    GlobalKeyShortcut::Action *mShortcut;
    MenuStyle mTopMenuStyle;
    MenuStyle mMenuStyle;
    LxQt::PowerManager* mPowerManager;
    LxQt::ScreenSaver* mScreenSaver;

#ifdef HAVE_MENU_CACHE
    MenuCache* mMenuCache;
    MenuCacheNotifyId mMenuCacheNotify;
    static void menuCacheReloadNotify(MenuCache* cache, gpointer user_data);
#else
    XdgMenu mXdgMenu;
#endif

    bool mLockCascadeChanges;

protected slots:

    virtual void settingsChanged();
    void buildMenu();

private slots:
    void showMenu();
    void showHideMenu();
    void shortcutChanged(const QString &oldShortcut, const QString &newShortcut);
};

class RazorMainMenuPluginLibrary: public QObject, public IRazorPanelPluginLibrary
{
    Q_OBJECT
    Q_INTERFACES(IRazorPanelPluginLibrary)
public:
    IRazorPanelPlugin *instance(const IRazorPanelPluginStartupInfo &startupInfo) { return new RazorMainMenu(startupInfo);}
};

#endif

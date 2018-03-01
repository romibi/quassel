/***************************************************************************
*   Copyright (C) 2005-2016 by the Quassel Project                        *
*   devel@quassel-irc.org                                                 *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) version 3.                                           *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
***************************************************************************/
#include "extraicon.h"
#include <QIcon>
#include <QDirIterator>
#include <qDebug>

QIcon ExtraIcon::load(const QString name) {
    qDebug() << "loading extra icon ...";
    QString theme = QIcon::themeName();
    if (theme == "breeze-dark") {
        theme = "breezedark";
    }
    else if (theme != "breeze" && theme != "breezedark" && theme != "oxygen") {
        if (QIcon::hasThemeIcon(name)) {
            return QIcon::fromTheme(name);
        }
        theme = "breeze";
    }

    QDirIterator it(":/icons/extra/"+theme, QDirIterator::Subdirectories);

    QList<QString> icons;

    while (it.hasNext()) {
        QString icon = it.next();
        if (icon.contains("/"+name+".")) {
            icons.push_back(icon);
        }
    }

    if (icons.length() == 0) {
        return QIcon(":/icons/" + name + ".png");
    }

    QList<QString>::Iterator filtered_it = icons.begin();
    QIcon qicon = QIcon(*filtered_it);
    filtered_it++;
    while (filtered_it!=icons.end()) {
        qicon.addFile(*filtered_it);
        filtered_it++;
    }

    return qicon;
}
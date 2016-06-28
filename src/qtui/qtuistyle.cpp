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

#include "chatviewsettings.h"
#include "qtuistyle.h"

#include <QFile>
#include <QTextStream>

QtUiStyle::QtUiStyle(QObject *parent) : UiStyle(parent)
{
    ChatViewSettings s;
    s.notify("TimestampFormat", this, SLOT(updateTimestampFormatString()));
    updateTimestampFormatString();
    s.notify("ShowSenderBrackets", this, SLOT(updateShowSenderBrackets()));
    updateShowSenderBrackets();
}


QtUiStyle::~QtUiStyle() {}

void QtUiStyle::updateTimestampFormatString()
{
    ChatViewSettings s;
    setTimestampFormatString(s.timestampFormatString());
}

void QtUiStyle::updateShowSenderBrackets()
{
    ChatViewSettings s;
    enableSenderBrackets(s.showSenderBrackets());
}


void QtUiStyle::generateSettingsQss() const
{
    QFile settingsQss(Quassel::configDirPath() + "settings.qss");
    if (!settingsQss.open(QFile::WriteOnly|QFile::Truncate)) {
        qWarning() << "Could not open" << settingsQss.fileName() << "for writing!";
        return;
    }
    QTextStream out(&settingsQss);

    out << "// Style settings made in Quassel's configuration dialog\n"
        << "// This file is automatically generated, do not edit\n";

    // ChatView
    ///////////
    QtUiStyleSettings fs("Fonts");
    if (fs.value("UseCustomChatViewFont").toBool())
        out << "\n// ChatView Font\n"
            << "ChatLine { " << fontDescription(fs.value("ChatView").value<QFont>()) << "; }\n";

    QtUiStyleSettings s("Colors");
    if (s.value("UseChatViewColors").toBool()) {
        out << "\n// Custom ChatView Colors\n"

        // markerline is special in that it always used to use a gradient, so we keep this behavior even with the new implementation
        << "Palette { marker-line: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 " << color("MarkerLine", s) << ", stop: 0.1 transparent); }\n"
        << "ChatView { background: " << color("ChatViewBackground", s) << "; }\n\n"
        << "ChatLine[label=\"highlight\"] {\n"
        << "  foreground: " << color("Highlight", s) << ";\n"
        << "  background: " << color("HighlightBackground", s) << ";\n"
        << "}\n\n"
        << "ChatLine::timestamp { foreground: " << color("Timestamp", s) << "; }\n\n"

        << msgTypeQss("plain", "ChannelMsg", s)
        << msgTypeQss("notice", "ServerMsg", s)
        << msgTypeQss("action", "ActionMsg", s)
        << msgTypeQss("nick", "CommandMsg", s)
        << msgTypeQss("mode", "CommandMsg", s)
        << msgTypeQss("join", "CommandMsg", s)
        << msgTypeQss("part", "CommandMsg", s)
        << msgTypeQss("quit", "CommandMsg", s)
        << msgTypeQss("kick", "CommandMsg", s)
        << msgTypeQss("kill", "CommandMsg", s)
        << msgTypeQss("server", "ServerMsg", s)
        << msgTypeQss("info", "ServerMsg", s)
        << msgTypeQss("error", "ErrorMsg", s)
        << msgTypeQss("daychange", "ServerMsg", s)
        << msgTypeQss("topic", "CommandMsg", s)
        << msgTypeQss("netsplit-join", "CommandMsg", s)
        << msgTypeQss("netsplit-quit", "CommandMsg", s)
        << msgTypeQss("invite", "CommandMsg", s)
        << "\n";
    }

    if (s.value("UseSenderColors").toBool()) {
        out << "\n// Sender Colors\n"
            << "ChatLine::sender#plain[sender=\"self\"] { foreground: " << color("SenderSelf", s) << "; }\n\n";

        for (int i = 0; i < 16; i++)
            out << senderQss(i, s);
    }

    // ItemViews
    ////////////

    UiStyleSettings uiFonts("Fonts");
    if (uiFonts.value("UseCustomItemViewFont").toBool()) {
        QString fontDesc = fontDescription(uiFonts.value("ItemView").value<QFont>());
        out << "\n// ItemView Font\n"
            << "ChatListItem { " << fontDesc << "; }\n"
            << "NickListItem { " << fontDesc << "; }\n\n";
    }

    UiStyleSettings uiColors("Colors");
    if (uiColors.value("UseBufferViewColors").toBool()) {
        out << "\n// BufferView Colors\n"
            << "ChatListItem { foreground: " << color("DefaultBuffer", uiColors) << "; }\n"
            << chatListItemQss("inactive", "InactiveBuffer", uiColors)
            << chatListItemQss("channel-event", "ActiveBuffer", uiColors)
            << chatListItemQss("unread-message", "UnreadBuffer", uiColors)
            << chatListItemQss("highlighted", "HighlightedBuffer", uiColors);
    }

    if (uiColors.value("UseNickViewColors").toBool()) {
        out << "\n// NickView Colors\n"
            << "NickListItem[type=\"category\"] { foreground: " << color("DefaultBuffer", uiColors) << "; }\n"
            << "NickListItem[type=\"user\"] { foreground: " << color("OnlineNick", uiColors) << "; }\n"
            << "NickListItem[type=\"user\", state=\"away\"] { foreground: " << color("AwayNick", uiColors) << "; }\n";
    }

    settingsQss.close();
}


QString QtUiStyle::color(const QString &key, UiSettings &settings) const
{
    return settings.value(key).value<QColor>().name();
}


QString QtUiStyle::fontDescription(const QFont &font) const
{
    QString desc = "font: ";
    if (font.italic())
        desc += "italic ";
    if (font.bold())
        desc += "bold ";
    if (!font.italic() && !font.bold())
        desc += "normal ";
    desc += QString("%1pt \"%2\"").arg(font.pointSize()).arg(font.family());
    return desc;
}


QString QtUiStyle::msgTypeQss(const QString &msgType, const QString &key, UiSettings &settings) const
{
    return QString("ChatLine#%1 { foreground: %2; }\n").arg(msgType, color(key, settings));
}


QString QtUiStyle::senderQss(int i, UiSettings &settings) const
{
    QString dez = QString::number(i);
    if (dez.length() == 1) dez.prepend('0');

    return QString("ChatLine::sender#plain[sender=\"0%1\"] { foreground: %2; }\n").arg(QString::number(i, 16), color("Sender"+dez, settings));
}


QString QtUiStyle::chatListItemQss(const QString &state, const QString &key, UiSettings &settings) const
{
    return QString("ChatListItem[state=\"%1\"] { foreground: %2; }\n").arg(state, color(key, settings));
}

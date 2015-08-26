//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#ifndef SCORING_HPP
#define SCORING_HPP

#define HUGGLE_EXTENSION
#include <iextension.hpp>
#include <collectable_smartptr.hpp>
#include <webserverquery.hpp>
#include <QAction>
#include <QDeclarativeItem>
#include <QHash>

class QTimer;

namespace Huggle
{
    class WikiPage;
    class WikiEdit;
    class WikiSite;
    class Query;
}

class scoring : public QDeclarativeItem, public Huggle::iExtension
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
        Q_PLUGIN_METADATA(IID "org.huggle.extension.qt" FILE "scoring_helper.json")
#endif
    Q_INTERFACES(Huggle::iExtension)
    public:
        scoring();
        ~scoring();
        bool Register();
        bool IsWorking();
        QString GetExtensionName() { return "Scoring Helper"; }
        QString GetExtensionAuthor() { return "Petr Bena"; }
        QString GetExtensionDescription() { return "Provides interface to external revision scoring mechanism on WMF labs"; }
        QString GetExtensionVersion() { return "1.0.0"; }
        //bool Hook_EditBeforeScore(void *edit);
        void Hook_Shutdown();
        void Hook_MainWindowOnLoad(void *window);
        bool Hook_EditIsReady(void *edit);
        bool Hook_EditBeforeScore(void *edit);
        void Hook_EditBeforePostProcessing(void *edit);
        void Hook_GoodEdit(void *edit);
        bool RequestCore() { return true; }
        bool RequestNetwork() { return true; }
        bool RequestConfiguration() { return true; }
        double GetAmplifier(Huggle::WikiSite *site);
    public slots:
        void Refresh();
    private:
        QString GetServer();
        QTimer *tm;
        QAction *System;
        QHash<void*, Huggle::Collectable_SmartPtr<Huggle::WebserverQuery>> Edits;
};

QML_DECLARE_TYPE(scoring)

#endif // SCORING_HPP
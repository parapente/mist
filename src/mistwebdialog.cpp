/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  Θεόφιλος Ιντζόγλου <int.teo@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "mistwebdialog.h"
#include <QSslError>
#include <QDebug>
#include <QNetworkReply>
#include <QHBoxLayout>
#include <QNetworkProxyFactory>

mistWebDialog::mistWebDialog( QWidget * parent, Qt::WindowFlags f )
{
    QNetworkProxyFactory::setUseSystemConfiguration(true);

    webView = new QWebView(this);
    QHBoxLayout *hblayout = new QHBoxLayout();
    hblayout->addWidget(webView);
    setLayout(hblayout);
    webView->show();
    connect(webView->page()->networkAccessManager(), SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
            this, SLOT(sslErrorHandler(QNetworkReply*, const QList<QSslError> & )));
    connect(webView, SIGNAL(loadStarted()), this, SLOT(loadStarted()));
    connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));
    connect(webView, SIGNAL(loadProgress(int)), this, SLOT(loadProgress(int)));
    connect(webView->page()->networkAccessManager(), SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
}

void mistWebDialog::finished(QNetworkReply* reply)
{
    qDebug() << "--NetworkReply:--" << reply->errorString();
}


void mistWebDialog::openUrl(QUrl url)
{
    //qDebug() << QString("Opening browser at: ") << url.toString();
    webView->load(url);
}

void mistWebDialog::sslErrorHandler(QNetworkReply* qnr, const QList< QSslError >& errlist)
{
    qDebug() << "---:sslErrorHandler: ";
    // show list of all ssl errors
    foreach (QSslError err, errlist)
        qDebug() << "ssl error: " << err;

    qnr->ignoreSslErrors();
}

void mistWebDialog::loadStarted()
{
    qDebug() << "Loading web page...";
}

void mistWebDialog::loadProgress(int progress)
{
    qDebug() << "Progress = " << progress;
}

void mistWebDialog::loadFinished(bool ok)
{
    qDebug() << "Ok = " << ok;
}

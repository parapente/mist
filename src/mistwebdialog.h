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

#ifndef MISTWEBDIALOG_H
#define MISTWEBDIALOG_H

#include <QDialog>
#include <QUrl>
#include <QWebView>

class mistWebDialog : public QDialog
{
    Q_OBJECT

public:
    mistWebDialog( QWidget * parent = 0, Qt::WindowFlags f = 0 );
    void openUrl(QUrl url);

private:
    QWebView *webView;
    
private slots:
    void sslErrorHandler(QNetworkReply*, const QList<QSslError> & );
    void loadStarted();
    void loadFinished(bool);
    void loadProgress(int);
    void finished(QNetworkReply*);
};

#endif // MISTWEBDIALOG_H

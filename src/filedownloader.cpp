#include "filedownloader.h"

FileDownloader::FileDownloader(QUrl url, QObject *parent) :
	QObject(parent),
	m_url(url)
{
	connect(
		&m_WebCtrl, SIGNAL (finished(QNetworkReply*)),
		this, SLOT (fileDownloaded(QNetworkReply*))
	);
}

FileDownloader::~FileDownloader() { }

void FileDownloader::launchDownload()
{
	QNetworkRequest request(m_url);
	m_WebCtrl.get(request);
}

void FileDownloader::fileDownloaded(QNetworkReply* pReply)
{
	if(pReply)
	{
		int errorCode = pReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		if(pReply->error() != QNetworkReply::NoError)
		{
			emit errorMsg(pReply->errorString());
		}
		else if(errorCode == 302)
		{
			QUrl newUrl = pReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
			qDebug() << "redirected to " + newUrl.toString();
			QNetworkRequest newRequest(newUrl);
			m_WebCtrl.get(newRequest);
		}
		else
		{
			m_DownloadedData = pReply->readAll();
			//emit a signal
			emit downloaded(m_url);
		}
		pReply->deleteLater();
	}
    return;
}

QByteArray FileDownloader::downloadedData() const
{
	return m_DownloadedData;
}

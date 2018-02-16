#ifndef SSLWEBSOCKETSERVER_H
#define SSLWEBSOCKETSERVER_H

#ifdef HAVE_SSL

//#include <QSslCertificate>
//#include <QSslKey>
#include "QtWebSockets/QWebSocketServer"
//#include <QLinkedList>

class SslWebSocketServer : public QWebSocketServer
{
	Q_OBJECT

public:
	SslWebSocketServer(QObject *parent = 0);

	//virtual inline bool hasPendingConnections() const { return !_pendingConnections.isEmpty(); }
	//virtual QWebSocket *nextPendingConnection();

	//virtual inline const QSslCertificate &certificate() const { return _cert; }
	//virtual inline const QSslKey &key() const { return _key; }
	//virtual inline bool isCertValid() const { return _isCertValid; }

	/**
	* Reloads SSL certificates used for connections
	*
	* If this command fails, it will try to maintain the most recent working certificate.  Error
	* conditions are automatically written to the log.
	*
	* @return True if certificates reloaded successfully, otherwise false.
	*/
	//bool reloadCerts();

protected:
	//virtual void incomingConnection(qintptr socketDescriptor);

	//virtual bool setCertificate(const QString &path, const QString &keyPath);

private:
	/**
	* Loads SSL certificates used for connections
	*
	* If this command fails, it will try to maintain the most recent working certificate.  Will log
	* specific failure points, but does not offer verbose guidance.
	*
	* @return True if certificates loaded successfully, otherwise false.
	*/
	//bool loadCerts();

	//QLinkedList<QWebSocket *> _pendingConnections;
	//QSslCertificate _cert;
	//QSslKey _key;
	//QList<QSslCertificate> _ca;
	//bool _isCertValid;

	// Used when reloading certificates later
	//QString _sslCertPath; /// Path to the certificate file
	//QString _sslKeyPath;  /// Path to the private key file (may be in same file as above)
};
#endif
#endif
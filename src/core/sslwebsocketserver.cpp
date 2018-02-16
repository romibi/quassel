#include "sslwebsocketserver.h"

#ifdef HAVE_SSL

//#include <QtWebSockets/QWebSocket>
//#include <QtCore/QFile>
//#include <QtNetwork/QSslCertificate>
//#include <QtNetwork/QSslKey>
//#include "logger.h"

SslWebSocketServer::SslWebSocketServer(QObject *parent)
	: QWebSocketServer(QStringLiteral("Quassel Websocket Server"), QWebSocketServer::SecureMode, parent) //,
	//_isCertValid(false)
{
	// Keep track if the SSL warning has been mentioned at least once before
	/* static bool sslWarningShown = false;

	if (Quassel::isOptionSet("ssl-cert")) {
		_sslCertPath = Quassel::optionValue("ssl-cert");
	}
	else {
		_sslCertPath = Quassel::configDirPath() + "quasselCert.pem";
	}

	if (Quassel::isOptionSet("ssl-key")) {
		_sslKeyPath = Quassel::optionValue("ssl-key");
	}
	else {
		_sslKeyPath = _sslCertPath;
	}

	// Initialize the certificates for first-time usage
	if (!loadCerts()) {
		if (!sslWarningShown) {
			quWarning()
				<< "SslServer: Unable to set certificate file\n"
				<< "          Quassel Core will still work, but cannot provide SSL for client connections.\n"
				<< "          Please see http://quassel-irc.org/faq/cert to learn how to enable SSL support.";
			sslWarningShown = true;
		}
	} */
}
/*
QWebSocket *SslWebSocketServer::nextPendingConnection()
{
	if (_pendingConnections.isEmpty())
		return 0;
	else
		return _pendingConnections.takeFirst();
}

void SslWebSocketServer::incomingConnection(qintptr socketDescriptor)
{
	QWebSocket *serverSocket = new QWebSocket(this);
	if (serverSocket->setSocketDescriptor(socketDescriptor)) {
		if (isCertValid()) {
			serverSocket->setLocalCertificate(_cert);
			serverSocket->setPrivateKey(_key);
			serverSocket->addCaCertificates(_ca);
		}
		_pendingConnections << serverSocket;
		emit newConnection();
	}
	else {
		delete serverSocket;
	}
}
*/
/*
bool SslWebSocketServer::loadCerts()
{
	// Load the certificates specified in the path.  If needed, other prep work can be done here.
	return setCertificate(_sslCertPath, _sslKeyPath);
}


bool SslWebSocketServer::reloadCerts()
{
	if (loadCerts()) {
		return true;
	}
	else {
		// Reloading certificates currently only occur in response to a request.  Always print an
		// error if something goes wrong, in order to simplify checking if it's working.
		if (isCertValid()) {
			quWarning()
				<< "SslServer: Unable to reload certificate file, reverting\n"
				<< "          Quassel Core will use the previous key to provide SSL for client connections.\n"
				<< "          Please see http://quassel-irc.org/faq/cert to learn how to enable SSL support.";
		}
		else {
			quWarning()
				<< "SslServer: Unable to reload certificate file\n"
				<< "          Quassel Core will still work, but cannot provide SSL for client connections.\n"
				<< "          Please see http://quassel-irc.org/faq/cert to learn how to enable SSL support.";
		}
		return false;
	}
}


bool SslWebSocketServer::setCertificate(const QString &path, const QString &keyPath)
{
	// Don't reset _isCertValid here, in case an older but valid certificate is still loaded.
	// Use temporary variables in order to avoid overwriting the existing certificates until
	// everything is confirmed good.
	QSslCertificate untestedCert;
	QList<QSslCertificate> untestedCA;
	QSslKey untestedKey;

	if (path.isEmpty())
		return false;

	QFile certFile(path);
	if (!certFile.exists()) {
		quWarning() << "SslServer: Certificate file" << qPrintable(path) << "does not exist";
		return false;
	}

	if (!certFile.open(QIODevice::ReadOnly)) {
		quWarning()
			<< "SslServer: Failed to open certificate file" << qPrintable(path)
			<< "error:" << certFile.error();
		return false;
	}

	QList<QSslCertificate> certList = QSslCertificate::fromDevice(&certFile);

	if (certList.isEmpty()) {
		quWarning() << "SslServer: Certificate file doesn't contain a certificate";
		return false;
	}

	untestedCert = certList[0];
	certList.removeFirst(); // remove server cert

							// store CA and intermediates certs
	untestedCA = certList;

	if (!certFile.reset()) {
		quWarning() << "SslServer: IO error reading certificate file";
		return false;
	}

	// load key from keyPath if it differs from path, otherwise load key from path
	if (path != keyPath) {
		QFile keyFile(keyPath);
		if (!keyFile.exists()) {
			quWarning() << "SslServer: Key file" << qPrintable(keyPath) << "does not exist";
			return false;
		}

		if (!keyFile.open(QIODevice::ReadOnly)) {
			quWarning()
				<< "SslServer: Failed to open key file" << qPrintable(keyPath)
				<< "error:" << keyFile.error();
			return false;
		}

		untestedKey = QSslKey(&keyFile, QSsl::Rsa);
		keyFile.close();
	}
	else {
		untestedKey = QSslKey(&certFile, QSsl::Rsa);
	}

	certFile.close();

	if (untestedCert.isNull()) {
		quWarning() << "SslServer:" << qPrintable(path) << "contains no certificate data";
		return false;
	}

	// We allow the core to offer SSL anyway, so no "return false" here. Client will warn about the cert being invalid.
	const QDateTime now = QDateTime::currentDateTime();
	if (now < untestedCert.effectiveDate())
		quWarning() << "SslServer: Certificate won't be valid before" << untestedCert.effectiveDate().toString();

	else if (now > untestedCert.expiryDate())
		quWarning() << "SslServer: Certificate expired on" << untestedCert.expiryDate().toString();

	else { // Qt4's isValid() checks for time range and blacklist; avoid a double warning, hence the else block
		if (untestedCert.isBlacklisted())
			quWarning() << "SslServer: Certificate blacklisted";
	}
	if (untestedKey.isNull()) {
		quWarning() << "SslServer:" << qPrintable(keyPath) << "contains no key data";
		return false;
	}

	_isCertValid = true;

	// All keys are valid, update the externally visible copy used for new connections.
	_cert = untestedCert;
	_ca = untestedCA;
	_key = untestedKey;

	return _isCertValid;
}
*/
#endif

#ifndef NCONNECTIONCONTROLLER_H
#define NCONNECTIONCONTROLLER_H

#include <QHostAddress>
#include <QList>
#include <QMap>
#include <QObject>
#include <QUrl>
#include <NCoreService.h>
#include <QVersionNumber>
#include <qhttpserver.h>

#include "ConnectorVersion.h"
//***#include <NResponse.h>

namespace NulstarNS {
  const QString cAdminServerLabel = "Nulstar Management";
  const QString cAdminServerName = "WebAdminServer";
  const QString cClientServerLabel = "Nulstar Client Channel";
  const QString cClientServerName = "WebClientServer";
  const QString cHttpServerName = "HttpServer";
  const QString cHttpError = QStringLiteral("__ERROR");
  const int cHttpServerTimeout = 3;


  class NWebSocketServer;
  class NConnectionController : public NCoreService {
    Q_OBJECT

    public:      
      explicit NConnectionController(QWebSocketServer::SslMode lSslMode, ELogLevel lLogLevel, const QHostAddress& lIP, const QUrl& lServiceManagerUrl, const QString& lMainPath,
                                     QList<QNetworkAddressEntry> lAllowedNetworks = QList<QNetworkAddressEntry> (), quint16 lCommPort = 0,
                                     quint16 lAdminPort = 0, quint16 lClientPort = 0, QHostAddress::SpecialAddress lBindAddress = QHostAddress::Null, const QString& lHttpServerPort = QString("0"), QObject* rParent = nullptr);
      ~NConnectionController() override {}

      QString fAbbreviation() const override { return "NCN"; }
      QString fName() const override { return QString(APP_NAME); }
      QString fVersion() const override { return QString(APP_VERSION); }
      QString fDomain() const override { return QString(APP_DOMAIN); }
      QVariantMap fDependencies() const override {  QVariantMap lDependencies; return lDependencies; }
      QVariantMap fApiRoles() const override;
      QList<QVersionNumber> fProtocolVersionsSupported() const override { QList<QVersionNumber> lApiVersionsSupported; QVersionNumber lMainVersion(QVersionNumber::fromString(APP_PROTOCOL_VERSIONS)); lApiVersionsSupported << lMainVersion; return lApiVersionsSupported; }
      void fSendMessage(const QString& lWebSocketsID, NMessage* rMessage, NWebSocket::EConnectionState lMinStateRequired = NWebSocket::EConnectionState::eConnectionActive) override;

    protected:
      void fFillMethodMetadata() override { }
      void fFillMethodDescriptions();
      void fFillMethodMinEventAndMinPeriod();
      void fInvokeMethod(TMessageRequestToProcess& lMessageRequestToProcess) override;

    private:
      quint64 mRequestID;
      quint8 mCompressionLevel;
      QString mHttpServerPort;
      QHttpServer mHttpServer;
      QVariantMap mAdminMethods;
      QVariantMap mPublicMethods;
      QVariantMap mPrivateMethods;
      QMap<QString, TMessageRequestToProcess> mForwardedMessages; // Forwarded MessageID, Data
      void fSendBadMethodResponse(const TMessageRequestToProcess& lMessageRequestToProcess);
      void fForwardMessage(const TMessageRequestToProcess& lMessageRequestToProcess);
      bool fMethodValid(const QString& lMethodName, const QVariantMap& lMethodList);
      QString fProcessHttpRequestTimeout(const QString &lMessage);
      QString fProcessHttpRequestError();

    public Q_SLOTS:
      API_PUBLIC_FUNCTION void ListAPI(const TMessageRequestToProcess& lMessageRequest);
  /***    API_ADMIN_FUNCTION NResponse setmaxconnections(int lMaxConnections) { return fSetMaxConnections(lClientServerName, lMaxConnections); }
      API_ADMIN_FUNCTION NResponse getmaxconnections() { return fMaxConnections(lClientServerName); }
      API_ADMIN_FUNCTION NResponse gettotalconnections() { return fTotalConnections(lClientServerName); }
      API_ADMIN_FUNCTION NResponse setcompressionlevel(quint8 lCompressionLevel);
      API_PUBLIC_FUNCTION NResponse getcompressionlevel();  ***/
    protected Q_SLOTS:
      void fProcessResponse(const QVariantMap& lMessageResponse) override;
      void fOnTextMessageReceived(const QString& lMessage);

    Q_SIGNALS:
      void sHttpResponseProcessed(const QString& lHttpResponse);
  };
}

#endif // NConnectionController_H

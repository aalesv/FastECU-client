// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "startup.h"

Startup::Startup(QObject *parent)
    : Startup("", parent)
{}

Startup::Startup(QString peerAddress,
                 QObject *parent)
    : QObject(parent)
    , peerAddress(peerAddress)
    , webSocketSerial(new QWebSocket("",QWebSocketProtocol::VersionLatest,this))
    , socket_serial(new WebSocketIoDevice(webSocketSerial, webSocketSerial))
    , node_serial(new QRemoteObjectHost(webSocketSerial))
    , webSocketUtility(new QWebSocket("",QWebSocketProtocol::VersionLatest,this))
    , socket_utility(new WebSocketIoDevice(webSocketUtility, webSocketUtility))
    , node_utility(new QRemoteObjectHost(webSocketUtility))
    , serial(new SerialPortActions(this))
    , utility(new RemoteUtility(this))
    , heartbeatIntervalSerial(0)
    , heartbeatIntervalUtility(0)
{
    //SerialPortActions
    QObject::connect(webSocketSerial, &QWebSocket::textMessageReceived, this,
                     [&](QString message)
                     {
                         //Run host node after connection is up
                         if (message == autodiscoveryMessage)
                         {
                             qDebug() << "SerialPortActions: Received autodiscovery message, starting host side connection";
                             node_serial->addHostSideConnection(socket_serial);
                         }
                     }
                     );
    QObject::connect(webSocketSerial, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
                     this, [=](QAbstractSocket::SocketError error)
                     {
                        qDebug() << this->metaObject()->className() << "startOverNetwok QWebSocket error:" << error;
                        QString e = QVariant::fromValue(error).toString();
                        emit log("Network error: " + e);
                      });
    QObject::connect(webSocketSerial, &QWebSocket::disconnected,
                     this, [=]()
                     {
                        QWebSocketProtocol::CloseCode code = this->webSocketSerial->closeCode();
                        QString reason = this->webSocketSerial->closeReason();
                        qDebug() << "webSocketSerial disconnected: " << code << reason;
                        emit disconnected();
                        emit log("Disconnected from "+this->peerAddress+" "+QString::number(code)+" "+reason);
                     });

    //RemoteUtility
    QObject::connect(webSocketUtility, &QWebSocket::textMessageReceived, this,
                     [&](QString message)
                     {
                         //Run host node after connection is up
                         if (message == autodiscoveryMessage)
                         {
                             qDebug() << "RemoteUtility: Received autodiscovery message, starting host side connection";
                             node_utility->addHostSideConnection(socket_utility);
                         }
                     }
                     );
    QObject::connect(webSocketUtility, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
                     this, [=](QAbstractSocket::SocketError error)
                     {
                         qDebug() << this->metaObject()->className() << "startOverNetwok QWebSocket error:" << error;
                         QString e = QVariant::fromValue(error).toString();
                         emit log("Network error: " + e);
                     });
    QObject::connect(webSocketUtility, &QWebSocket::disconnected,
                     this, [=]()
                     {
                         QWebSocketProtocol::CloseCode code = this->webSocketUtility->closeCode();
                         QString reason = this->webSocketUtility->closeReason();
                         qDebug() << "webSocketUtility disconnected: " << code << reason;
                         emit disconnected();
                         //emit log("Disconnected from "+this->peerAddress+" "+QString::number(code)+" "+reason);
                     });

    QObject::connect(utility, &RemoteUtility::signal_send_log_window_message,
                     this, &Startup::log);
    QObject::connect(utility, &RemoteUtility::signal_set_progressbar_value,
                     this, &Startup::set_progressbar_value);
}

Startup::~Startup()
{}

void Startup::setPeerAddress(QString address)
{
    peerAddress = address;
}

QString Startup::getPeerAddress()
{
    return peerAddress;
}

void Startup::setHostName(QString host)
{
    hostName = host;
}

void Startup::setPortNumber(int port)
{
    portNumber = port;
}

void Startup::setPassword(QString pw)
{
    password = pw;
}

void Startup::start()
{
    qDebug() << "Starting connection to " << peerAddress;
    if (this->peerAddress.startsWith("local:"))
    {
        startLocal();
    }
    else
    {
        startOverNetwok();
    }
}

void Startup::stop()
{
    qDebug() << "Disconnecting from" << peerAddress;
    node_serial->disableRemoting(serial);
    node_utility->disableRemoting(utility);
    if (webSocketSerial->isValid())
        webSocketSerial->close();
    if (webSocketUtility->isValid())
        webSocketUtility->close();
}

void Startup::startOverNetwok()
{
    bool ssl_is_supported = QSslSocket::supportsSsl();
    if (! ssl_is_supported)
    {
        qDebug() << "ERROR: SSL is NOT supported!";
        emit log("ERROR: SSL libaries not found! No further work possible. "
                 "Fix the error and restart the application.");
    }

    qDebug() << "Starting network connection";
    QSslConfiguration sslConfiguration;
    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    webSocketSerial->setSslConfiguration(sslConfiguration);
    webSocketUtility->setSslConfiguration(sslConfiguration);
    //Mandatory
    node_serial->setHostUrl(QUrl(nodeUrlSerial), QRemoteObjectHost::AllowExternalRegistration);
    node_serial->setHeartbeatInterval(heartbeatIntervalSerial);
    //Enable remote object access
    node_serial->enableRemoting(serial, remoteObjectNameSerial);
    //Mandatory
    node_utility->setHostUrl(QUrl(nodeUrlUtility), QRemoteObjectHost::AllowExternalRegistration);
    node_utility->setHeartbeatInterval(heartbeatIntervalUtility);
    //Enable remote object access
    node_utility->enableRemoting(utility, remoteObjectNameUtility);

    QUrl url;
    url.setScheme("wss");
    url.setHost(hostName);
    url.setPort(portNumber);
    QNetworkRequest req;
    req.setRawHeader(webSocketPasswordHeader.toUtf8(), password.toUtf8());

    url.setPath(wssSerialPath);
    req.setUrl(url);
    webSocketSerial->open(req);
    url.setPath(wssUtilityPath);
    req.setUrl(url);
    webSocketUtility->open(req);
}

void Startup::startLocal()
{
    qDebug() << "starting local connection";
    node_serial->setHostUrl(QUrl(peerAddress),
                    QRemoteObjectHost::BuiltInSchemasOnly);
    node_serial->enableRemoting(serial, remoteObjectNameSerial);

    node_utility->setHostUrl(QUrl(peerAddress+remoteObjectNameUtility),
                            QRemoteObjectHost::BuiltInSchemasOnly);
    node_utility->enableRemoting(utility, remoteObjectNameUtility);
}

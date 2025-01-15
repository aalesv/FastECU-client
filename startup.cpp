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
    , webSocket(new QWebSocket("",QWebSocketProtocol::VersionLatest,this))
    , socket_serial(new WebSocketIoDevice(webSocket, webSocket))
    , socket_utility(new WebSocketIoDevice(webSocket, webSocket))
    , node_serial(new QRemoteObjectHost(webSocket))
    , node_utility(new QRemoteObjectHost(webSocket))
    , serial(new SerialPortActions(this))
    , utility(new RemoteUtility(this))
    , heartbeatIntervalSerial(0)
    , heartbeatIntervalUtility(0)
{
    QObject::connect(webSocket, &QWebSocket::textMessageReceived, this,
                     [&](QString message)
                     {
                         //Run host node after connection is up
                         if (message == autodiscoveryMessage)
                         {
                             qDebug() << "Received autodiscovery message, starting host side connection";
                             node_serial->addHostSideConnection(socket_serial);
                             node_utility->addHostSideConnection(socket_utility);
                         }
                     }
                     );
    QObject::connect(webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
                     this, [=](QAbstractSocket::SocketError error)
                     {
                        qDebug() << this->metaObject()->className() << "startOverNetwok QWebSocket error:" << error;
                        QString e = QVariant::fromValue(error).toString();
                        emit log("Network error: " + e);
                      });
    QObject::connect(webSocket, &QWebSocket::disconnected,
                     this, [=]()
                     {
                        QWebSocketProtocol::CloseCode code = this->webSocket->closeCode();
                        QString reason = this->webSocket->closeReason();
                        qDebug() << "webSocket disconnected: " << code << reason;
                        emit disconnected();
                        emit log("Disconnected from "+this->peerAddress+" "+QString::number(code)+" "+reason);
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
    if (webSocket->isValid())
        webSocket->close();
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
    webSocket->setSslConfiguration(sslConfiguration);
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

    webSocket->open("wss://" + peerAddress);
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

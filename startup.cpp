// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "startup.h"

Startup::Startup(QObject *parent)
    : Startup("", parent)
{}

Startup::Startup(QString peerAddress, QObject *parent)
    : QObject(parent)
    , peerAddress(peerAddress)
    , webSocket(new QWebSocket("",QWebSocketProtocol::VersionLatest,this))
    , socket(new WebSocketIoDevice(webSocket, webSocket))
    , node(new QRemoteObjectHost(webSocket))
    , serial(new SerialPortActions(this))
{}

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
    node->disableRemoting(serial);
    webSocket->close(QWebSocketProtocol::CloseCodeGoingAway, "User request");
}

void Startup::startOverNetwok()
{
    qDebug() << "Starting network connection";
    QSslConfiguration sslConfiguration;
    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    webSocket->setSslConfiguration(sslConfiguration);
    //Mandatory
    node->setHostUrl(QUrl(nodeUrl), QRemoteObjectHost::AllowExternalRegistration);
    node->setHeartbeatInterval(heartbeatInterval);
    //Enable remote object access
    node->enableRemoting(serial, remoteObjectName);
    QObject::connect(webSocket, &QWebSocket::textMessageReceived, node,
                     [&](QString message)
                     {
                         //Run host node after connection is up
                         if (message == autodiscoveryMessage)
                         {
                             qDebug() << "Received autodiscovery message, starting host side connection";
                             node->addHostSideConnection(socket);
                         }
                     }
                     );
    QObject::connect(webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
                     this, [=](QAbstractSocket::SocketError error)
                     { qDebug() << this->metaObject()->className() << "startOverNetwok QWebSocket error:" << error; });

    webSocket->open("wss://" + peerAddress);
}

void Startup::startLocal()
{
    qDebug() << "starting local connection";
    node->setHostUrl(QUrl(peerAddress),
                    QRemoteObjectHost::BuiltInSchemasOnly);
    node->enableRemoting(serial, remoteObjectName);
}

#include "startup.h"

Startup::Startup(QString peerAddress, QObject *parent)
    : QObject{parent}
    , peerAddress(peerAddress)
    , webSocket(new QWebSocket("",QWebSocketProtocol::VersionLatest,this))
    , socket(new WebSocketIoDevice(webSocket, webSocket))
{
    qDebug() << "Startup: " << peerAddress;
    if (this->peerAddress.startsWith("local:"))
    {
        startLocal();
    }
    else
    {
        startOverNetwok();
    }
}

Startup::~Startup()
{}

void Startup::startOverNetwok(void)
{
    qDebug() << "Starting network connection";
    QSslConfiguration sslConfiguration;
    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    webSocket->setSslConfiguration(sslConfiguration);
    //Mandatory
    node.setHostUrl(QUrl(nodeUrl), QRemoteObjectHost::AllowExternalRegistration);
    node.setHeartbeatInterval(heartbeatInterval);
    //Enable remote object access
    node.enableRemoting(&serial, remoteObjectName);
    QObject::connect(webSocket, &QWebSocket::textMessageReceived, &node,
                     [&](QString message)
                     {
                         //Run host node after connection is up
                         if (message == autodiscoveryMessage)
                         {
                             qDebug() << "Received autodiscovery message, starting host side connection";
                             node.addHostSideConnection(socket);
                         }
                     }
                     );
    QObject::connect(webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
                     this, [=](QAbstractSocket::SocketError error)
                     { qDebug() << this->metaObject()->className() << "startOverNetwok QWebSocket error:" << error; });

    webSocket->open("wss://" + peerAddress);
}

void Startup::startLocal(void)
{
    qDebug() << "starting local connection";
    node.setHostUrl(QUrl(peerAddress),
                    QRemoteObjectHost::BuiltInSchemasOnly);
    node.enableRemoting(&serial, remoteObjectName);
}

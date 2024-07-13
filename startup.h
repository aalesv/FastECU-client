#ifndef STARTUP_H
#define STARTUP_H

#include <QObject>
#include <QSharedPointer>
#include <QWebSocket>
#include "websocketiodevice.h"
#include "serial_port/serial_port_actions.h"

class Startup : public QObject
{
    Q_OBJECT
public:
    explicit Startup(QObject *parent = nullptr);
    explicit Startup(QString peerAddress, QObject *parent = nullptr);
    ~Startup();
    const QString autodiscoveryMessage = "FastECU_PTP_Autodiscovery";
    const QString nodeUrl = "FastECU_node_url";
    const QString remoteObjectName = "FastECU";
    const int heartbeatInterval = 1000;

public slots:
    void start();
    void stop();
    void setPeerAddress(QString address);
    QString getPeerAddress();

signals:
private:
    QString peerAddress;
    QWebSocket *webSocket;
    WebSocketIoDevice *socket;
    QRemoteObjectHost *node;
    SerialPortActions *serial;
    void startOverNetwok();
    void startLocal();
};

#endif // STARTUP_H

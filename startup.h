#ifndef STARTUP_H
#define STARTUP_H

#include <QObject>
#include <QSharedPointer>
#include <QWebSocket>
#include "websocketiodevice.h"
#include "serial_port/serial_port_actions.h"
#include "remote_utility/remote_utility.h"

class Startup : public QObject
{
    Q_OBJECT
public:
    explicit Startup(QObject *parent = nullptr);
    explicit Startup(QString peerAddress,
                     QObject *parent = nullptr);
    ~Startup();
    const QString webSocketPasswordHeader = "fastecu-basic-password";
    const QString autodiscoveryMessage = "FastECU_PTP_Autodiscovery";
    const QString nodeUrlSerial = "FastECU_node_url";
    const QString nodeUrlUtility = "FastECU_Utility_node_url";
    const QString remoteObjectNameSerial = "FastECU";
    const QString remoteObjectNameUtility = "FastECU_Utility";
    const QString wssSerialPath = "/" + remoteObjectNameSerial;
    const QString wssUtilityPath = "/" + remoteObjectNameUtility;
    //Inited in constructor initializer list
    const int heartbeatIntervalSerial;
    const int heartbeatIntervalUtility;

public slots:
    void start();
    void stop();
    void setPeerAddress(QString address);
    QString getPeerAddress();
    void setHostName(QString host);
    void setPortNumber(int port);
    void setPassword(QString pw);

signals:
    void disconnected();
    void log(QString message);
    void set_progressbar_value(int value);

private:
    QString peerAddress;
    QString hostName;
    int portNumber;
    QString password;
    QWebSocket *webSocketSerial;
    QWebSocket *webSocketUtility;
    WebSocketIoDevice *socket_serial;
    WebSocketIoDevice *socket_utility;
    QRemoteObjectHost *node_serial;
    QRemoteObjectHost *node_utility;
    SerialPortActions *serial;
    RemoteUtility *utility;
    void startOverNetwok();
    void startLocal();
};

#endif // STARTUP_H

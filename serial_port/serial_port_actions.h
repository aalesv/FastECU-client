#ifndef SERIAL_PORT_ACTIONS_H
#define SERIAL_PORT_ACTIONS_H

#include <QObject>
#include "serial_port_actions_direct.h"
#include "rep_serial_port_actions_source.h"
#include "websocketiodevice.h"

class SerialPortActions : public SerialPortActionsRemoteSimpleSource
{
    Q_OBJECT
public:
    explicit SerialPortActions(QObject *parent=nullptr);
    ~SerialPortActions();

    bool get_serialPortAvailable() override ;
    bool set_serialPortAvailable(bool value) override ;
    bool get_setRequestToSend() override ;
    bool set_setRequestToSend(bool value) override ;
    bool get_setDataTerminalReady() override ;
    bool set_setDataTerminalReady(bool value) override ;

    bool get_add_iso14230_header() override ;
    bool set_add_iso14230_header(bool value) override ;
    bool get_is_iso14230_connection() override ;
    bool set_is_iso14230_connection(bool value) override ;
    bool get_is_can_connection() override ;
    bool set_is_can_connection(bool value) override ;
    bool get_is_iso15765_connection() override ;
    bool set_is_iso15765_connection(bool value) override ;
    bool get_is_29_bit_id() override ;
    bool set_is_29_bit_id(bool value) override ;

    bool get_use_openport2_adapter() override ;
    bool set_use_openport2_adapter(bool value) override ;

    int  get_requestToSendEnabled() override ;
    bool set_requestToSendEnabled(int value) override ;
    int  get_requestToSendDisabled() override ;
    bool set_requestToSendDisabled(int value) override ;
    int  get_dataTerminalEnabled() override ;
    bool set_dataTerminalEnabled(int value) override ;
    int  get_dataTerminalDisabled() override ;
    bool set_dataTerminalDisabled(int value) override ;

    uint8_t get_iso14230_startbyte() override ;
    bool    set_iso14230_startbyte(uint8_t value) override ;
    uint8_t get_iso14230_tester_id() override ;
    bool    set_iso14230_tester_id(uint8_t value) override ;
    uint8_t get_iso14230_target_id() override ;
    bool    set_iso14230_target_id(uint8_t value) override ;

    QByteArray get_ssm_receive_header_start() override ;
    bool       set_ssm_receive_header_start(QByteArray value) override ;

    QStringList get_serial_port_list() override ;
    bool        set_serial_port_list(QStringList value) override ;
    QString get_openedSerialPort() override ;
    bool    set_openedSerialPort(QString value) override ;
    QString get_subaru_02_16bit_bootloader_baudrate() override ;
    bool    set_subaru_02_16bit_bootloader_baudrate(QString value) override ;
    QString get_subaru_04_16bit_bootloader_baudrate() override ;
    bool    set_subaru_04_16bit_bootloader_baudrate(QString value) override ;
    QString get_subaru_02_32bit_bootloader_baudrate() override ;
    bool    set_subaru_02_32bit_bootloader_baudrate(QString value) override ;
    QString get_subaru_04_32bit_bootloader_baudrate() override ;
    bool    set_subaru_04_32bit_bootloader_baudrate(QString value) override ;
    QString get_subaru_05_32bit_bootloader_baudrate() override ;
    bool    set_subaru_05_32bit_bootloader_baudrate(QString value) override ;

    QString get_subaru_02_16bit_kernel_baudrate() override ;
    bool    set_subaru_02_16bit_kernel_baudrate(QString value) override ;
    QString get_subaru_04_16bit_kernel_baudrate() override ;
    bool    set_subaru_04_16bit_kernel_baudrate(QString value) override ;
    QString get_subaru_02_32bit_kernel_baudrate() override ;
    bool    set_subaru_02_32bit_kernel_baudrate(QString value) override ;
    QString get_subaru_04_32bit_kernel_baudrate() override ;
    bool    set_subaru_04_32bit_kernel_baudrate(QString value) override ;
    QString get_subaru_05_32bit_kernel_baudrate() override ;
    bool    set_subaru_05_32bit_kernel_baudrate(QString value) override ;

    QString get_can_speed() override ;
    bool    set_can_speed(QString value) override ;

    QString get_serial_port_baudrate() override ;
    bool    set_serial_port_baudrate(QString value) override ;
    QString get_serial_port_linux() override ;
    bool    set_serial_port_linux(QString value) override ;
    QString get_serial_port_windows() override ;
    bool    set_serial_port_windows(QString value) override ;
    QString get_serial_port() override ;
    bool    set_serial_port(QString value) override ;
    QString get_serial_port_prefix() override ;
    bool    set_serial_port_prefix(QString value) override ;
    QString get_serial_port_prefix_linux() override ;
    bool    set_serial_port_prefix_linux(QString value) override ;
    QString get_serial_port_prefix_win() override ;
    bool    set_serial_port_prefix_win(QString value) override ;

    uint32_t get_can_source_address() override ;
    bool     set_can_source_address(uint32_t value) override ;
    uint32_t get_can_destination_address() override ;
    bool     set_can_destination_address(uint32_t value) override ;
    uint32_t get_iso15765_source_address() override ;
    bool     set_iso15765_source_address(uint32_t value) override ;
    uint32_t get_iso15765_destination_address() override ;
    bool     set_iso15765_destination_address(uint32_t value) override ;

    bool is_serial_port_open(void) override ;
    int change_port_speed(QString portSpeed) override ;
    int fast_init(QByteArray output) override ;
    int set_lec_lines(int lec1, int lec2) override ;
    int pulse_lec_1_line(int timeout) override ;
    int pulse_lec_2_line(int timeout) override ;

    bool reset_connection(void) override ;

    QByteArray read_serial_data(uint32_t datalen, unsigned long timeout) override ;
    QByteArray write_serial_data(QByteArray output) override ;
    QByteArray write_serial_data_echo_check(QByteArray output) override ;

    int clear_rx_buffer(void) override ;
    int clear_tx_buffer(void) override ;

    int send_periodic_j2534_data(QByteArray output, int timeout) override ;
    int stop_periodic_j2534_data(void) override ;

    QStringList check_serial_ports(void) override ;
    QString open_serial_port(void) override ;

private:
    SerialPortActionsDirect        *serial_direct;
};

#endif // SERIAL_PORT_ACTIONS_H

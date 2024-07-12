# FastECU client

Designed to provide FastECU with remote serial port access. To work over WebSocket please use FastECU broker. To work over named pipes please set address of broker to `local`.

For correct work with OpenPort 2.0 FastECU client must be compiled as 32-bit application.

## Caveats:

Qt 5.15.14 has bug in `repc.exe` that incorrectly creates `read_serial_data` function declaration.
Go to `build\Desktop_blah-blah-blah-Debug\rep_serial_port_actions_source.h`, find
first occurence of `read_serial_data` and correct `longtimeout` to `long timeout` by inserting a space.
Then save and build.

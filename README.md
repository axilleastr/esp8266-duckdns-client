# esp8266-duckdns-client

[DuckDNS](https://www.duckdns.org/) DDNS update client running on esp8266 board

## How to use it

In order to use this DDNS update client, update:

1. the [wifi credentials](https://github.com/axilleastr/esp-ddns/blob/main/ddns.ino#L7-L8)
1. the [DucksDNS domain and token](https://github.com/axilleastr/esp-ddns/blob/main/ddns.ino#L17-L18)


## Troubleshooting

Check your serial monitor logs.

You can do that either from the Arduino IDE or (if you are a terminal guy) from your terminal, using `screen`:

```bash
screen -L /dev/ttyUSB0 9600
```

## TODOs

1. Cache the currentIP, so that we can compare with the previous one, and update the client only in case of mismatching. This way, we reduce the amount of redundant calls and updates
1. Update the timestamp to work in a desired timezone
1. Create a webserver interface, so that we can observe updates and changes easily


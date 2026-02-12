import network,time
sta_if = network.WLAN(network.STA_IF)
sta_if.active(True)
while not sta_if.isconnected():
    sta_if = network.WLAN(network.STA_IF)
    sta_if.active(True)
    try: sta_if.connect('Jorpakko', 'Juhannusyona')
    except:
         print("Erhe")
    time.sleep(1)
print('network config:', sta_if.ifconfig())






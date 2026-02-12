try:
  import usocket as socket
except:
  import socket
import network,time

import machine
import kello
import binascii

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

def tavut_tekstiksi(tavudata):
    # Muutetaan jokainen tavu (0-255) suoraan merkiksi chr()-funktiolla
    return "".join([chr(b) for b in tavudata])

def web_page():
    html="Kallo:"
    return html
    
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('', 80))
s.listen(5)

while True:
    s.settimeout(0.2)
    try:
        conn, addr = s.accept()
        request = conn.recv(1024)
        request = str(request)
        s.settimeout(5.0)
        if request.find('/nayta') == 6:
            jono=request[12:].split('$')[0]
            print(jono)
            auki=tavut_tekstiksi(binascii.unhexlify(jono))
            print(auki)
            kello.scroll(auki)
        response = web_page()
        conn.send('HTTP/1.1 200 OK\n')
        conn.send('Content-Type: text/html\n')
        conn.send('Connection: close\n\n')
        conn.sendall(response)
        conn.close()
    except:
        pass


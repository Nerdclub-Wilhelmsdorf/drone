def do_connect():
    import network
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        print('connecting to network...')
        wlan.connect('Italia', '84998774312187047978')
        while not wlan.isconnected():
            pass
    print('network config:', wlan.ifconfig())

do_connect()

from microdot import Microdot

app = Microdot()

@app.route('/')
async def index(request):
    return 'Hello, world!'

app.run()
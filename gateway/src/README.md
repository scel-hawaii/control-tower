# Notes on changes:
## fake_loop in fake_rx.py
Changed formatting for the byte strings to be compliant with python3 instead of python2, which was the main the fake functionality broke

The strings were formatted with b"bytestring" instead of just plain "bytestring"

With the "b" added, the os.write function can take on the plain input

## gateway_server.py
Wrong path in line 78, which is designed to disable fake mode, but since the if statement checked for the wrong path, disabled the fake gateway operation even when changes were made to fake_rx.py

import os
import errno
import threading
import time

def symlink_override(target, link_name):
    try:
        os.symlink(target, link_name)
    except OSError as e:
        if e.errno == errno.EEXIST:
            os.remove(link_name)
            os.symlink(target, link_name)
        else:
            raise e

def valid_packets():
    packets = {}
    packets['heartbeat'] = "\x7e\x00\x16\x90\x00\x7d\x33\xa2\x00\x40\xe6\x4b\x5e\x03\xfd\x01\x00\x00\xff\xff\xf0\xfa\x23\x00\x2b\x02\xb2"
    packets['apple'] = "\x7e\x00\x22\x90\x00\x7d\x33\xa2\x00\x40\x9f\x27\xa7\x29\x6c\x01\x01\x00\xff\xff\x80\x6f\x69\x3d\x06\x0f\x71\x7d\x33\x5a\x8a\x01\x00\x76\x01\x22\x00\x6e\x09\x55"
    packets['cranberry'] = "\x7e\x00\x22\x90\x00\x7d\x33\xa2\x00\x41\x25\xe5\x88\x0c\x83\x01\x02\x00\xff\xff\x7c\xf3\x05\x00\xba\x0f\x5c\x08\x05\x00\x20\x73\x3b\x00\xdd\x8b\x01\x00\x7a"
    return packets

def fake_loop(master_fd):
    packets = valid_packets()
    while True:
        for key in packets:
            os.write(master_fd, bytes(packets[key]))
            time.sleep(1)

def start_fake_serial(ptyPath):
    master_fd, slave_fd = os.openpty()
    symlink_override(os.ttyname(slave_fd), ptyPath)
    t = threading.Thread(target=fake_loop, args=[master_fd], daemon=True)
    t.start()

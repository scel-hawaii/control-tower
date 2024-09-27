import os
import threading
import errno


class MockSerialPTY:
    """
    Mocks a serial device using a pty on the filesystem.
    """

    def __init__(self, pty_path: str, write_loop=None, read_loop=None):
        self.write_loop = write_loop
        self.read_loop = read_loop
        self.pty_path = pty_path

    def start(self):
        master_fd, slave_fd = os.openpty()
        symlink_override(os.ttyname(slave_fd), self.pty_path)

        if self.write_loop:
            write_t = threading.Thread(
                target=self.write_loop, args=[master_fd], daemon=True
            )
            write_t.start()

        if self.read_loop:
            read_t = threading.Thread(
                target=self.read_loop, args=[master_fd], daemon=True
            )
            read_t.start()


def symlink_override(target, link_name):
    try:
        os.symlink(target, link_name)
    except OSError as e:
        if e.errno == errno.EEXIST:
            os.remove(link_name)
            os.symlink(target, link_name)
        else:
            raise e

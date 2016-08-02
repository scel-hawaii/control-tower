# Defines a fake xbee packet to use with testing

import pickle

class FakeXbeePacket:
    def get_rx(self):
        data_packet = pickle.load( open( "save.p", "rb" ) )
        return data_packet

if __name__ == "__main__":

    fake_xbee = FakeXbeePacket()
    d = fake_xbee.get_rx()
    print d

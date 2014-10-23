import prcessing.serial.*;
import java.util.concurrent.*;
import java.util.*;

XBee xbee;
Queue<XBeeResponse> queue = new ConcurrentLinkedQueue<XBeeResponse>();
boolean message;
XBeeResponse response;
  
void setup() {
    try { 
        //optional.  set up logging
        PropertyConfigurator.configure(dataPath("")+"log4j.properties");

        xbee = new XBee();
        // replace with your COM port
        xbee.open("/dev/ttyUSB0", 9600);

        xbee.addPacketListener(new PacketListener() {
          public void processResponse(XBeeResponse response) {
            queue.offer(response);
          }
        });
    } 
    catch (Exception e) {
        System.out.println("XBee failed to initialize");
        e.printStackTrace();
        System.exit(1);
    }

    AtCommand sleepmode = new AtCommand("SM", 4);
    AtCommand sleepperiod = new AtCommand("SP", 0x002);
    AtCommand waketime = new AtCommand("ST", 0x3E8);
    AtCommand sleepopt = new AtCommand("SO", 02);

    try {

        AtCommandResponse response = (AtCommandResponse) xbee.sendSynchronous(sleepmode, 5000); 
        if (response.isOk()) {
            // success
            System.out.println("The channel is " + response.getValue()[0]);
        }
        else {
            System.out.println("We didn't get a response");
        }

    }
    catch (Exception e) {
        e.printStackTrace();
      }

}

void draw() {
  try {
    readPackets();
  } 
  catch (Exception e) {
    e.printStackTrace();
  }
  
  
}

void readPackets() throws Exception {

  while ((response = queue.poll()) != null) {
    // we got something!
    try {
      RxResponseIoSample ioSample = (RxResponseIoSample) response;

      println("We received a sample from " + ioSample.getSourceAddress());

      if (ioSample.containsAnalog()) {
        println("10-bit temp reading (pin 19) is " +
          ioSample.getSamples()[0].getAnalog1());
      }
    } 
    catch (ClassCastException e) {
      // not an IO Sample
    }
  }
}

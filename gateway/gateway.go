package main

import (
	"encoding/hex"
	"encoding/json"
	"flag"
	"fmt"
	"github.com/gin-gonic/gin"
	"go.bug.st/serial.v1"
	"log"
	"net/http"
	"os"
	"time"
)

func ListPorts() {
	ports, err := serial.GetPortsList()
	if err != nil {
		log.Fatal(err)
	}
	if len(ports) == 0 {
		log.Fatal("No serial ports found!")
	}
	fmt.Printf("Found ports\n")
	for _, port := range ports {
		fmt.Printf("%v\n", port)
	}
}

type Listener struct {
	port            serial.Port
	passthroughPort serial.Port
	Packets         chan []byte
}

func (this *Listener) Init(portStr string, passthroughPortStr string) {
	mode := &serial.Mode{
		BaudRate: 9600,
	}

	port, err := serial.Open(portStr, mode)
	if err != nil {
		log.Fatal(err)
	}

	this.port = port

	if passthroughPortStr != "" {
		port, err := serial.Open(passthroughPortStr, mode)
		if err != nil {
			log.Fatal(err)
		}

		this.passthroughPort = port
	}
}

type EncodedFrame struct {
	EncodedBuffer string    `json:"encodedBuffer"`
	Timestamp     time.Time `json:"timestamp"`
}

func (this *EncodedFrame) ToJson() ([]byte, error) {
	buf, err := json.MarshalIndent(this, "", "    ")
	if err != nil {
		return nil, err
	}
	return buf, nil
}
func (this *Listener) Cleanup() {
	this.port.Close()
	this.passthroughPort.Close()
    fmt.Println()
    fmt.Println("Cleaned up listener")
}

func (this *Listener) Listen() {
	b := make([]byte, 1)
	buffer := []byte{}
	for {
		_, err := this.port.Read(b)
		if err != nil {
			fmt.Println("Serial Error Reading From Port")
			fmt.Println(err.Error())
		} else {
            this.passthroughPort.Write(b)
			if b[0] == 0x7E {
				this.Packets <- buffer
				buffer = []byte{}
			}
			buffer = append(buffer, b[0])
		}
	}
}

func main() {
	portFlag := flag.String("port", "", "The port to listen on")
	passthroughFlag := flag.String("passthrough-port", "", "The port to pass through messages.")
	listFlag := flag.Bool("list", false, "list ports")
	flag.Parse()
	fmt.Printf("%s\n", *portFlag)

	hub := newHub()
	go hub.run()

	// Serve webpage
	router := gin.Default()
	router.LoadHTMLGlob("templates/*")
	router.GET("/", func(c *gin.Context) {
		c.HTML(http.StatusOK, "index.tmpl", gin.H{
			"title": "Main website",
		})
	})
	router.GET("/ws", func(c *gin.Context) {
        serveWs(hub, c.Writer, c.Request)
	})

	go router.Run(":9090")

	if *listFlag {
		ListPorts()
		os.Exit(0)
	}

	if *portFlag != "" {
		packets := make(chan []byte)
		listener := Listener{Packets: packets}
		listener.Init(*portFlag, *passthroughFlag)
		go listener.Listen()
        defer listener.Cleanup()

		// Printer
		for packet := range packets {
			fmt.Printf("%s\t%s\n", time.Now().Format(time.RFC3339), hex.EncodeToString(packet))
			encodedFrame := EncodedFrame{
				EncodedBuffer: hex.EncodeToString(packet),
				Timestamp:     time.Now(),
			}
			buf, err := encodedFrame.ToJson()
			if err != nil {
				fmt.Println("There was an error converting to JSON")
			} else {
				hub.broadcast <- buf
			}

		}

	} else {
		fmt.Printf("Error, do you not specify a port")
	}
}

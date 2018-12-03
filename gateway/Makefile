.PHONY: build

build:
	mkdir -p build
	go build -o build/gateway
	cp scripts/run_gateway.sh build
	cp -r templates/ build/

deploy: build
	ssh -t -p 11144 scel@alpha.scel-hawaii.org 'sudo systemctl stop xbee-gateway.service'
	scp -P 11144 -r build/* scel@alpha.scel-hawaii.org:/home/scel/apps/gateway
	ssh -t -p 11144 scel@alpha.scel-hawaii.org 'sudo systemctl start xbee-gateway.service'

clean:
	rm -f gateway
	rm -rf build

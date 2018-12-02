build:
	mkdir build
	go build -o build/gateway
	cp scripts/run_gateway.sh build

deploy:
	scp -P 11144 -r build scel@alpha.scel-hawaii.org:/home/scel/apps/gateway

clean:
	rm gateway
	rm -rf build

#!/bin/bash

# Build the test container
docker build -t control-tower-test .
docker run -d --name ct-testinstance -p 16906:16906 -t control-tower-test

# Wait for the container to go up
sleep 5;

# Run a simple test
curl http://localhost:16906

# Run tests
# TODO: Run the other tests here

# Remove the container
docker kill ct-testinstance
docker rm ct-testinstance


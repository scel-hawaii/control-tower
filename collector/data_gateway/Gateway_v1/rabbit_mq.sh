# Commands to pull and run an instance of RabbitMQ via docker

# Pull the rabbitmq docker file
docker pull rabbitmq

# Run the instance
# Default port for the management GUI: 15672
# Default port for the rabbitmq instance: 5627
docker run -d --hostname my-rabbit --name some-rabbit -p 8081:15672 -p 8082:5672 rabbitmq:3-management

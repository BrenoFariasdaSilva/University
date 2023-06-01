client_run:
	clear;
	python3 client.py

classifier_run:
	clear;
	python3 classifier.py

collector_run:
	clear;
	python3 collector.py

docker_run:
	docker pull rabbitmq
	docker run -d --hostname 172.17.0.2:15691 --name 172.17.0.2:15691 rabbitmq:3

setup:
	pip install pika
	pip install colorama

remove:
	rm *.pyc
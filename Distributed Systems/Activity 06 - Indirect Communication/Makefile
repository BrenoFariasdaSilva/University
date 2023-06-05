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
	clear;
	docker pull rabbitmq
	docker run -d --hostname my-rabbit --name rabbitmq-tweets rabbitmq:3

setup:
	clear;
	pip install pika
	pip install colorama

remove:
	clear;
	rm *.pyc
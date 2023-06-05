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
	docker run -d --hostnamemy-rabbit --name rabbitmq-tweets rabbitmq:3

setup:
	pip install pika
	pip install colorama

remove:
	rm *.pyc
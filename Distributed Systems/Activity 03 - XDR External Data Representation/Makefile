client:
	clear; python3 client.py

server:
	clear; python3 server.py

protobuf:
	protoc -I=. --python_out=. ./protobufs/*.proto

setup:
	pip install pymongo

remove:
	rm *.pyc
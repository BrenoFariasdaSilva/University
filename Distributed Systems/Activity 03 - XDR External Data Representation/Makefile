client:
	clear; python3 client.py

server:
	clear; python3 server.py

protobuf:
	protoc --python_out=. movies.proto

setup:
	pip install pymongo
	pip install protobuf

remove:
	rm *.pyc
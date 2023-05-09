client:
	clear; python3 client.py

server:
	clear; python3 server.py

protobuf:
	protoc --python_out=. movies.proto

setup:
	sudo apt install -y protobuf-compiler -y
	pip install protobuf
	pip install pymongo

remove:
	rm *.pyc
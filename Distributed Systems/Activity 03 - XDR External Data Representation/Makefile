server:
	clear; python3 server/server.py

client:
	clear; javac client/Client.java; java client.Client

database:
	clear; python3 server/database.py

protoc:
	protoc --python_out=server/ movies.proto
	protoc --java_out=client/ movies.proto

setup:
	sudo apt install -y protobuf-compiler -y
	pip install protobuf
	pip install pymongo
	pip install python-dotenv
	pip install colorama

remove:
	rm *.pyc
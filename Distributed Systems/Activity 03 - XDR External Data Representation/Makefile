server:
	clear; python3 server/server.py

client:
	clear
	javac client/Client.java; java client

database:
	clear; python3 server/database.py

protoc:
	protoc --python_out=server/structs/ movies.proto
	protoc --java_out=client/External-Data-Representation/src/main/java movies.proto

setup:
	sudo apt install -y protobuf-compiler -y
	pip install protobuf
	pip install pymongo
	pip install python-dotenv
	pip install colorama

remove:
	rm *.pyc
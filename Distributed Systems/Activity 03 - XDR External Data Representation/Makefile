server:
	# Don't forget to check your .env file!
	clear; python3 server/server.py

client:
	clear; javac client/Client.java; java client.Client

database:
	clear; python3 database/database.py

protoc:
	protoc --python_out=. protocolbuffers/movies.proto
	protoc --java_out=protocolbuffers/ protocolbuffers/movies.proto

setup:
	sudo apt install -y protobuf-compiler -y
	pip install protobuf
	pip install pymongo
	pip install python-dotenv
	pip install colorama

remove:
	rm *.pyc
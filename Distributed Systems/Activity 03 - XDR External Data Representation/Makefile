make:
	# Don't forget to check your .env file!
	clear; python3 server/server.py

database:
	clear; python3 server/database.py

protoc:
	protoc --python_out=. server/movies.proto

setup:
	sudo apt install -y protobuf-compiler -y
	pip install protobuf
	pip install pymongo
	pip install python-dotenv
	pip install colorama

remove:
	rm *.pyc
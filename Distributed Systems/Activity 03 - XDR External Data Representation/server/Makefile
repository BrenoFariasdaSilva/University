make:
	clear; python3 server.py

database:
	clear; python3 database.py

protoc:
	# This generates the movies_pb2.py file
	protoc --python_out=. movies.proto

setup:
	sudo apt install -y protobuf-compiler -y
	pip install protobuf
	python -m pip install pymongo

remove:
	rm *.pyc
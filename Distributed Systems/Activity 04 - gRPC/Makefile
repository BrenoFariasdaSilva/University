server_run:
	clear; python3 server/server.py

client_run:
	clear
	javac client/Client.java; java client

database_run:
	clear; python3 server/database.py

protoc:
	python -m grpc_tools.protoc -I. --python_out=./server/structs --grpc_python_out=./server/structs movies.proto
	protoc -I=$SRC_DIR --java_out=$DST_DIR $SRC_DIR/HelloService.proto

setup:
	sudo pip install protobuf
	sudo pip install grpcio
	sudo pip install grpcio-tools
	sudo pip install pymongo
	sudo pip install python-dotenv
	sudo pip install colorama

remove:
	rm *.pyc
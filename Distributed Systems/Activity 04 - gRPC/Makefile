server_run:
	clear; python3 server/server.py

client_run:
	clear
	javac client/Client.java; java client

database_run:
	clear; python3 server/database.py

protoc:
	protoc --python_out=server/structs/ movies.proto
	protoc --java_out=client/External-Data-Representation/src/main/java movies.proto
	python3 -m grpc_tools . protoc -I . -- python_out = -- grpc_python_out =. helloworld . proto
	protoc -I=$SRC_DIR --java_out=$DST_DIR $SRC_DIR/HelloService.proto

setup:
	sudo pip3 install grpcio grpcio-tools protobuf
	sudo pip install protobuf
	sudo pip install pymongo
	sudo pip install python-dotenv
	sudo pip install colorama

remove:
	rm *.pyc
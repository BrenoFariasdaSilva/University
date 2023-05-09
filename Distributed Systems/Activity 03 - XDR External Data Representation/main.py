import socket
import threading 
import pymongo
from proto import movie_pb2

# Configuração do MongoDB
client = pymongo.MongoClient("mongodb://localhost:27017/")
db = client["mflix"]
movies = db["movies"]

# Configuração do servidor TCP
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('localhost', 8000))
server.listen(5)

# Configuração do Flask
app = Flask(__name__)

# Funções auxiliares para conversão de dados entre BSON e Protocol Buffers
def bson_to_proto(bson_data, message_type):
	message = message_type()
	message.ParseFromString(bson_data)
	return message

def proto_to_bson(proto_message):
	return proto_message.SerializeToString()

# Operações de CRUD
@app.route('/movie', methods=['POST'])
def create_movie():
	movie = movie_pb2.Movie()
	movie.ParseFromString(request.data)

	if movie.title == "":
		return jsonify({'error': 'title is empty'}), 400

	if movie.plot == "":
		return jsonify({'error': 'plot is empty'}), 400

	# Insere o novo filme na coleção movies
	movie_data = {
		'title': movie.title,
		'year': movie.year,
		'plot': movie.plot,
		'runtime': movie.runtime,
		'cast': movie.cast,
		'genres': movie.genres,
		'director': movie.director
	}
	result = movies.insert_one(movie_data)
	movie.id = str(result.inserted_id)

	return jsonify({'movie': MessageToJson(movie)}), 201

@app.route('/movie/<id>', methods=['GET'])
def read_movie(id):
	# Busca o filme pelo ID
	movie_data = movies.find_one({'_id': ObjectId(id)})
	if not movie_data:
		return jsonify({'error': 'movie not found'}), 404

	# Converte os dados BSON para um objeto Movie do Protocol Buffers
	movie = movie_pb2.Movie()
	movie.id = str(movie_data['_id'])
	movie.title = movie_data['title']
	movie.year = movie_data['year']
	movie.plot = movie_data['plot']
	movie.runtime = movie_data['runtime']
	movie.cast.extend(movie_data['cast'])
	movie.genres.extend(movie_data['genres'])
	movie.director = movie_data['director']

	return jsonify({'movie': MessageToJson(movie)})

# @app.route('/movie/<id>', methods=['PUT'])
# def update_movie(id):
	# Busca o filme pelo ID

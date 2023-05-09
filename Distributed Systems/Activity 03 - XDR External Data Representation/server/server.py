import movies_pb2

def main():
	movie = movies_pb2.Movie()
	movie.name = "The Shawshank Redemption"
	movie.year = 1994
	movie.genre = movies_pb2.Movie.DRAMA

	print(movie)

if __name__ == "__main__":
	main()
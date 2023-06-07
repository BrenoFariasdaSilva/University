package org.example;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;
import org.example.structs.*;

/*
 * gRPC - Google Remote Procedure Call
 * @author Breno Farias da Silva.
 * @subject Distributed Systems.
 * @date 27/05/2023.
 * @lastUpdate 29/05/2023.
 * This file is the client side of the application.
 * It's responsible for sending messages to the server.
 * It also receives messages from the server.
 * It also validates user input, so the server don't get loaded with invalid inputs
 */
public class Client {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_CYAN = "\u001B[36m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String CREATE = "CREATE";
    public static final String GET = "GET";
    public static final String UPDATE = "UPDATE";
    public static final String DELETE = "DELETE";
    public static final String LISTBYACTOR = "LISTBYACTOR";
    public static final String LISTBYGENRE = "LISTBYGENRE";
    public static final String HELP = "HELP";
    public static final String EXIT = "EXIT";
    public static final String SUCCESS = "1";
    public static final String input_movie_title = "Type the title of the movie: (String)";
    public static final String input_movie_actor = "Type the actor of the movie: (String)";
    public static final String input_movie_genre = "Type the genre of the movie: (String)";
    public static ManagedChannel channel;

    public static void main(String[] args) throws IOException {
        Scanner reader = new Scanner(System.in); // Read the user input
        // Create the variables to handle the user input
        String user_input = "";

        // Initialize the connection with the server
        channel = ManagedChannelBuilder
                .forAddress("localhost", 7070)
                .usePlaintext()
                .build();

        while (true) {
            System.out.println(ANSI_GREEN + "Type a message: " + ANSI_RED + "(String)" + ANSI_RESET);
            user_input = reader.nextLine(); // Read the user input

            // Convert the first word of the user input to uppercase
            user_input = stringToUpperCase(user_input);

            if (user_input.equals(EXIT)) {
                System.out.println(ANSI_GREEN + "Closing the connection..." + ANSI_RESET);
                break;
            }

            // Validate the user input for CREATE, GET, UPDATE, DELETE, LISTBYACTOR, LISTBYGENRE, HELP and Unknown commands.
            validateUserOperation(user_input);
        } // End of while
        channel.shutdown(); // Close the connection with the server
    } // End of main


    // START OF THE CRUD METHODS
    /*
    * @brief: This function creates a movie object and sends it to the server
    * @param: blockingStub - The MovieServiceBlockingStub object that is responsible for sending messages to the server
    * @return: None
    */
    public static void createMovie(MovieServiceGrpc.MovieServiceBlockingStub blockingStub) {
        System.out.println(ANSI_GREEN + "Creating a new movie..." + ANSI_RESET);
        Movie movie = userFillCreateMovieObject(false); // Create a movie object and fill it with the user input
        // System.out.println(ANSI_GREEN + "Movie: \n" + ANSI_RESET + movie);
        System.out.println(ANSI_GREEN + "Sending the movie to the server..." + ANSI_RESET);
        Message response = blockingStub.createMovie(movie); // Send the movie object to the server
        if (response.getMessage().equals(SUCCESS)) {
            System.out.println(ANSI_GREEN + "Movie " + ANSI_CYAN + movie.getTitle() + ANSI_GREEN + " created successfully!" + ANSI_RESET);
        } else {
            System.out.println(ANSI_RED + "Movie " + ANSI_CYAN + movie.getTitle() + ANSI_GREEN + " could not be created!" + ANSI_RESET);
        }
    } // End of createMovie

    /*
    * @brief: This function gets a movie object from the server
    * @param: blockingStub - The MovieServiceBlockingStub object that is responsible for sending messages to the server
    * @return: None
    */
    public static void getMovie(MovieServiceGrpc.MovieServiceBlockingStub blockingStub) {
        System.out.println(ANSI_GREEN + "Getting a movie..." + ANSI_RESET);
        Message movie_title = userFillMessageObject(input_movie_title); // Create a message object and fill it with the user input
        Movie movie = blockingStub.getMovie(movie_title); // Send the title to the server
        if (movie.getTitle().equals(movie_title.getMessage())) {
            System.out.println(ANSI_GREEN + "Movie " + ANSI_CYAN + movie.getTitle() + ANSI_GREEN + " found!" + ANSI_RESET);
            System.out.println(ANSI_GREEN + "Movie: " + ANSI_RESET + movie);
        } else {
            System.out.println(ANSI_RED + "Movie " + ANSI_CYAN + movie.getTitle() + ANSI_GREEN + " not found!" + ANSI_RESET);
        }
    } // End of getMovie

    /*
    * @brief: This function updates a movie object and sends it to the server
    * @param: blockingStub - The MovieServiceBlockingStub object that is responsible for sending messages to the server
    * @return: None
    */
    public static void updateMovie(MovieServiceGrpc.MovieServiceBlockingStub blockingStub) {
        System.out.println(ANSI_GREEN + "Updating a movie..." + ANSI_RESET);
        Movie movie = userFillCreateMovieObject(true); // Create a movie object and fill it with the user input
        System.out.println(ANSI_GREEN + "Sending the movie to the server..." + ANSI_RESET);
        Message response = blockingStub.updateMovie(movie); // Send the movie object to the server
        if (response.getMessage().equals(SUCCESS)) {
            System.out.println(ANSI_GREEN + "Movie " + ANSI_CYAN + movie.getTitle() + ANSI_GREEN + " updated successfully!" + ANSI_RESET);
        } else {
            System.out.println(ANSI_RED + "Movie " + ANSI_CYAN + movie.getTitle() + ANSI_GREEN + " could not be updated!" + ANSI_RESET);
        }
    } // End of updateMovie

    /*
    * @brief: This function deletes a movie object from the server
    * @param: blockingStub - The MovieServiceBlockingStub object that is responsible for sending messages to the server
    * @return: None
    */
    public static void deleteMovie(MovieServiceGrpc.MovieServiceBlockingStub blockingStub) {
        System.out.println(ANSI_GREEN + "Deleting a movie..." + ANSI_RESET);
        Message movie_title = userFillMessageObject(input_movie_title); // Create a message object and fill it with the user input
        Message response = blockingStub.deleteMovie(movie_title); // Send the title to the server
        if (response.getMessage().equals(SUCCESS)) {
            System.out.println(ANSI_GREEN + "Movie " + ANSI_CYAN + movie_title.getMessage() + ANSI_GREEN + " deleted successfully!" + ANSI_RESET);
        } else {
            System.out.println(ANSI_RED + "Movie " + ANSI_CYAN + movie_title.getMessage() + ANSI_GREEN + " could not be deleted!" + ANSI_RESET);
        }
    } // End of deleteMovie

    /*
    * @brief: This function lists all the movies that have a specific actor
    * @param: blockingStub - The MovieServiceBlockingStub object that is responsible for sending messages to the server
    * @return: None
    */
    public static void listByActor(MovieServiceGrpc.MovieServiceBlockingStub blockingStub) {
        System.out.println(ANSI_GREEN + "Listing movies by actor..." + ANSI_RESET);
        Message movie_actor = userFillMessageObject(input_movie_actor); // Create a message object and fill it with the user input
        MoviesList movie_list = blockingStub.listMoviesByActor(movie_actor); // Send the actor to the server
        if (movie_list.getMoviesCount() > 0) {
            System.out.println(ANSI_GREEN + "Movies of " + ANSI_CYAN + movie_actor.getMessage() + ANSI_GREEN + " found!" + ANSI_RESET);
            System.out.println(ANSI_GREEN + "Movies: " + ANSI_RESET + movie_list);
        } else {
            System.out.println(ANSI_RED + "Movies of " + ANSI_CYAN + movie_actor.getMessage() + ANSI_GREEN + " not found!" + ANSI_RESET);
        }
    } // End of listByActor

    /*
    * @brief: This function lists all the movies that have a specific genre
    * @param: blockingStub - The MovieServiceBlockingStub object that is responsible for sending messages to the server
    * @return: None
    */
    public static void listByGenre(MovieServiceGrpc.MovieServiceBlockingStub blockingStub) {
        System.out.println(ANSI_GREEN + "Listing movies by genre..." + ANSI_RESET);
        Message movie_genre = userFillMessageObject(input_movie_genre); // Create a message object and fill it with the user input
        MoviesList movie_list = blockingStub.listMoviesByGenre(movie_genre); // Send the genre to the server
        if (movie_list.getMoviesCount() > 0) {
            System.out.println(ANSI_GREEN + "Movies of " + ANSI_CYAN + movie_genre.getMessage() + ANSI_GREEN + " found!" + ANSI_RESET);
            System.out.println(ANSI_GREEN + "Movies: " + ANSI_RESET + movie_list);
        } else {
            System.out.println(ANSI_RED + "Movies of " + ANSI_CYAN + movie_genre.getMessage() + ANSI_GREEN + " not found!" + ANSI_RESET);
        }
    } // End of listByGenre

    // START OF AUXILIARY METHODS:
    /*
     * @brief: This function validates the user input for the operation to be performed
     * @param: in - The DataInputStream object
     * @param: out - The DataOutputStream object
     * @param: parts - The user input
     * @return: None
    */
    private static void validateUserOperation(String user_input) throws IOException {
        MovieServiceGrpc.MovieServiceBlockingStub blockingStub = MovieServiceGrpc.newBlockingStub(channel);
        switch (user_input) {
            case CREATE -> createMovie(blockingStub);
            case GET -> getMovie(blockingStub);
            case UPDATE -> updateMovie(blockingStub);
            case DELETE -> deleteMovie(blockingStub);
            case LISTBYACTOR -> listByActor(blockingStub);
            case LISTBYGENRE -> listByGenre(blockingStub);
            case HELP -> showHelp();
            default -> {
                System.out.println(ANSI_GREEN + "Invalid command. Try again." + ANSI_RESET);
                showHelp();
            } // End of default
        } // End of switch
    } // End of validateUserOperation

    /*
     @brief: This function shows the user how to use the program
     @param: None
     @return: None
    */
    public static void showHelp() {
        System.out.println(ANSI_GREEN + CREATE + ": Create a new movie" + ANSI_RESET);
        System.out.println(ANSI_GREEN + GET + ": Get a movie by title" + ANSI_RESET);
        System.out.println(ANSI_GREEN + UPDATE + ": Update a movie " + ANSI_RED + "(New ID must be the same as old ID!)" + ANSI_RESET);
        System.out.println(ANSI_GREEN + DELETE + ": Delete a movie by title" + ANSI_RESET);
        System.out.println(ANSI_GREEN + LISTBYACTOR + ": List all movies by an actor" + ANSI_RESET);
        System.out.println(ANSI_GREEN + LISTBYGENRE + ": List all movies by a genre" + ANSI_RESET);
        System.out.println(ANSI_GREEN + EXIT + ": Exit the program" + ANSI_RESET);
    } // End of showHelp

    /*
     @brief: This function asks the user to fill the fields with a movie object and returns it.
     @param: None
     @return: A movie object
    */
    public static Movie userFillCreateMovieObject(boolean allow_empty_fields) {
        Scanner reader = new Scanner(System.in); // Read the user input
        while (true) {
            // Ask for the user input: id, plot, genre, runtime, cast, num_mflix_comments, title, fullplot, countries, released, directors, rated, lastupdated, year, type
//            System.out.println(ANSI_GREEN + "Type the id of the movie:" + ANSI_RED + " (String)" + ANSI_RESET);
//            String id = reader.nextLine(); // Read the user input
//            System.out.println(ANSI_GREEN + "Type the plot of the movie:" + ANSI_RED + " (String)" + ANSI_RESET);
//            String plot = reader.nextLine(); // Read the user input
//            System.out.println(ANSI_GREEN + "Type the genre of the movie:" + ANSI_RED + " (String)" + ANSI_RESET);
//            String genre = reader.nextLine(); // Read the user input
//            System.out.println(ANSI_GREEN + "Type the runtime of the movie: (int)" + ANSI_RESET);
//            int runtime = reader.nextInt(); // Read the user input
//            System.out.println(ANSI_GREEN + "Type the number of casts in the movie: (int)" + ANSI_RESET);
//            int cast_number = reader.nextInt(); // Read the user input
//            // Create a list of casts
//            List<String> cast = new ArrayList<String>(cast_number);
//            reader.nextLine();
//            for (int i = 0; i < cast_number; i++) {
//                System.out.println(ANSI_GREEN + "Type the cast of the movie:" + ANSI_RED + " (String)" + ANSI_RESET);
//                cast.add(reader.nextLine()); // Read the user input
//            }
//            System.out.println(ANSI_GREEN + "Type the num_mflix_comments of the movie: (int)" + ANSI_RESET);
//            int num_mflix_comments = reader.nextInt(); // Read the user input
//            reader.nextLine();
            System.out.println(ANSI_GREEN + "Type the title of the movie:" + ANSI_RED + " (String)" + ANSI_RESET);
            String title = reader.nextLine(); // Read the user input
//            System.out.println(ANSI_GREEN + "Type the fullplot of the movie:" + ANSI_RED + " (String)" + ANSI_RESET);
//            String fullplot = reader.nextLine(); // Read the user input
//            System.out.println(ANSI_GREEN + "Type the number of countries of the movie: (int)" + ANSI_RESET);
//            int countries_number = reader.nextInt(); // Read the user input
//            reader.nextLine();
//            List<String> countries = new ArrayList<String>(countries_number);
//            for (int i = 0; i < countries_number; i++) {
//                System.out.println(ANSI_GREEN + "Type the countries of the movie:" + ANSI_RED + " (String)" + ANSI_RESET);
//                countries.add(reader.nextLine()); // Read the user input
//            }
//            System.out.println(ANSI_GREEN + "Type the released of the movie:" + ANSI_RED + " (String)" + ANSI_RESET);
//            String released = reader.nextLine(); // Read the user input
//            System.out.println(ANSI_GREEN + "Type the number of directors of the movie: (int)" + ANSI_RESET);
//            int directors_number = reader.nextInt(); // Read the user input
//            reader.nextLine();
//            List<String> directors = new ArrayList<String>(directors_number);
//            for (int i = 0; i < directors_number; i++) {
//                System.out.println(ANSI_GREEN + "Type the directors of the movie:" + ANSI_RED + " (String)" + ANSI_RESET);
//                directors.add(reader.nextLine()); // Read the user input
//            }
//            System.out.println(ANSI_GREEN + "Type the rated of the movie:" + ANSI_RED + " (String)" + ANSI_RESET);
//            String rated = reader.nextLine(); // Read the user input
//            System.out.println(ANSI_GREEN + "Type the last updated of the movie:" + ANSI_RED + " (String)" + ANSI_RESET);
//            String lastupdated = reader.nextLine(); // Read the user input
//            System.out.println(ANSI_GREEN + "Type the year of the movie: (int)" + ANSI_RESET);
//            int year = reader.nextInt(); // Read the user input
//            reader.nextLine();
//            System.out.println(ANSI_GREEN + "Type the type of the movie:" + ANSI_RED + " (String)" + ANSI_RESET);
//            String type = reader.nextLine(); // Read the user input

            // Initialize the variables id, plot, genre, runtime, cast, num_mflix_comments, title, fullplot, countries, released, directors, rated, lastupdated, year, type
            String id = "id";
            String plot = "plot";
            String genre = "genre";
            int runtime = 1;
            List<String> cast = new ArrayList<>();
            cast.add("actor1");
            int num_mflix_comments = 1;
//             String title = "title";
            String fullplot = "fullplot";
            List<String> countries = new ArrayList<>();
            countries.add("country1");
            String released = "released";
            List<String> directors = new ArrayList<>();
            directors.add("director1");
            String rated = "rated";
            String lastupdated = "lastupdated";
            int year = 2023;
            String type = "type";

            if (!allow_empty_fields) {
                if (id.equals("") || plot.equals("") || genre.equals("") || runtime == 0 || cast.size() == 0 || num_mflix_comments == 0 || title.equals("") || fullplot.equals("") || countries.size() == 0 || released.equals("") || directors.size() == 0 || rated.equals("") || lastupdated.equals("") || year == 0 || type.equals("")) {
                    System.out.println(ANSI_RED + "Error: You cannot have empty fields in a movie creation" + ANSI_RESET);
                    continue; // This will skip the rest of the code in the for loop and go to the next iteration
                }
            }
            if (id.equals("")) {
                System.out.println(ANSI_RED + "Error: ID cannot be empty in a Update operation" + ANSI_RESET);
            } else if (plot.equals("") && genre.equals("") && runtime == 0 && cast.size() == 0 && num_mflix_comments == 0 && title.equals("") && fullplot.equals("") && countries.size() == 0 && released.equals("") && directors.size() == 0 && rated.equals("") && lastupdated.equals("") && year == 0 && type.equals("")) {
                System.out.println(ANSI_RED + "Error: At least one field besides the ID must be filled in a Update operation" + ANSI_RESET);
            } else {
                // Create a movie protobuf object and return it
                return Movie.newBuilder()
                        .setId(id) // String
                        .setPlot(plot) // String
                        .setGenre(genre) // String
                        .setRuntime(runtime) // int
                        .addAllCast(cast) // String
                        .setNumMflixComments(num_mflix_comments) // int
                        .setTitle(title) // String
                        .setFullplot(fullplot) // String
                        .addAllCountries(countries) // String
                        .setReleased(released) // String
                        .addAllDirectors(directors) // String
                        .setRated(rated) // String
                        .setLastupdated(lastupdated) // String
                        .setYear(year) // int
                        .setType(type) // String
                        .build(); // Build the movie protobuf object
            } // End of if else statement
        } // End of for loop
    } // End of createMovie

    /*
     @brief: asks the user to fill the message field for a message object and returns it.
     @param: String user_input_message
     @return: Message object
     */
    public static Message userFillMessageObject(String user_input_message) {
        Scanner reader = new Scanner(System.in); // Reading from System.in
        System.out.println(ANSI_GREEN + user_input_message + ANSI_RESET);
        String message = reader.nextLine(); // Read the user input
        return Message.newBuilder()
                .setMessage(message) // String
                .build(); // Build the message protobuf object
    } // End of userFillMessageObject

    /*
     @brief: This function takes a string and returns it with the first word in uppercase
     @param: s - The string to be converted
     @return: The string with the first word in uppercase
    */
    public static String stringToUpperCase(String s) {
        if (s.contains(" ")) {
            String[] parts = s.split(" ");
            String firstWord = parts[0];
            StringBuilder restOfTheSentence = new StringBuilder();
            for (int i = 1; i < parts.length; i++) {
                restOfTheSentence.append(parts[i]).append(" ");
            }
            return firstWord.toUpperCase() + " " + restOfTheSentence;
        } else {
            return s.toUpperCase();
        }
    } // End of stringToUpperCase
    // END OF AUXILIARY METHODS
} // End of class
// END OF FILE
package org.example;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;
import org.example.structs.Message;
import org.example.structs.Movie;
import org.example.structs.Movies;

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
    public static final String SUCCESS = "SUCCESS";
    public static final String FAILURE = "FAILURE";
    public static final String SUCCESS_CODE = "1";

    private final ManagedChannel channel;

    public Client() {
        this.channel = ManagedChannelBuilder
            .forAddress("localhost", 7070)
            .usePlaintext()
            .build();
    }

    public static void main(String[] args) throws IOException {
        Scanner reader = new Scanner(System.in); // Read the user input
        // Create the variables to handle the user input
        String user_input = "";

        while (true) {
            System.out.println(ANSI_GREEN + "Type a message: " + ANSI_RED + "(String)" + ANSI_RESET);
            user_input = reader.nextLine(); // Read the user input

            // Convert the first word of the user input to uppercase
            user_input = stringToUpperCase(user_input);

            if (user_input.equals(EXIT)) {
                System.out.println(ANSI_GREEN + "Closing the connection..." + ANSI_RESET);
                break;
            }

            // Split the user input into an array of strings
            String[] parts = user_input.split(" ");

            // Validate the user input for CREATE, GET, UPDATE, DELETE, LISTBYACTOR, LISTBYGENRE, HELP and Unknown commands.
            validateUserOperation(parts);
        }

    }

    /*
    @brief: This function validates the user input for the operation to be performed
    @param: in - The DataInputStream object
    @param: out - The DataOutputStream object
    @param: parts - The user input
    @return: None
     */
    private static void validateUserOperation(String[] parts) throws IOException {
        switch (parts[0]) {
            case CREATE -> {}
            case GET -> {}
            case UPDATE -> {}
            case DELETE -> {}
            case LISTBYACTOR -> {}
            case LISTBYGENRE -> {}
            case HELP -> showHelp();
            default -> {
                System.out.println(ANSI_GREEN + "Invalid command. Try again." + ANSI_RESET);
                showHelp();
            }
        }
    }

    public static void createMovie() {
        System.out.println(ANSI_GREEN + "Creating a new movie..." + ANSI_RESET);
        Movie movie = userFillCreateMovieObject(false);
        System.out.println(ANSI_GREEN + "Sending the movie to the server..." + ANSI_RESET);
        // Send the movie to the server
        Client stub;
        String response = stub.createMovie(movie);
        System.out.println(ANSI_GREEN + "Response from the server: " + ANSI_RESET + response);
    }

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
            }
        }
    }

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
    }
    // End of auxiliary methods

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
    }
}

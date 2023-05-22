package org.example.client;
import org.example.client.structs.*;

import java.net.*;
import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Scanner;

/*
 * XDR - External Data Representation Activity
 * @author Breno Farias da Silva
 * @subject Distributed Systems
 * @date 15/05/2023
 * @lastUpdate 15/05/2023
 * This file is the client side of the application.
 * This file creates a TCP socket in order to communicate with the server.
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
    public static final String LISTBYACTORS = "LISTBYACTORS";
    public static final String LISTBYCATEGORY = "LISTBYCATEGORY";
    public static final String HELP = "HELP";
    public static final String EXIT = "EXIT";
    public static final String SUCCESS = "SUCCESS";
    public static final String FAILURE = "FAILURE";
    public static final String SUCCESS_CODE = "1";
    public static final String FAILURE_CODE = "0";
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in); // Read the user input

        // Address and port of the server
        int serverPort = 7001; // Later put it inside a env variable
        InetAddress serverAddr = null; // Create an instance of InetAddress
        try {
            serverAddr = InetAddress.getByName("localhost"); // Get the IP address of the server, which is localhost = 127.0.0.1
        } catch (UnknownHostException e) {
            System.out.println(ANSI_GREEN + "Unknown host: (String)" + ANSI_CYAN + e.getMessage() + ANSI_RESET);
            return;
        }

        try (var clientSocket = new Socket(serverAddr, serverPort)) { // Var inferes the type of the variable, which can only be used with local variables
            // Create the read and write objects for the socket
            DataInputStream in = new DataInputStream(clientSocket.getInputStream());
            DataOutputStream out = new DataOutputStream(clientSocket.getOutputStream());

            // Create the variables to handle the user input
            String user_input = "";

            // Show the user how to use the program
            // showHelp();
            while (true) {
                System.out.println(ANSI_GREEN + "Type a message: (String)" + ANSI_RESET);
                user_input = reader.nextLine(); // Read the user input

                // Convert the first word of the user input to uppercase
                user_input = stringToUpperCase(user_input);

                if (user_input.equals(EXIT)) {
                    System.out.println(ANSI_GREEN + "Closing the connection..." + ANSI_RESET);
                    clientSocket.close();
                    break;
                }

                // Split the user input into an array of strings
                String[] parts = user_input.split(" ");

                // Validate the user input for CREATE, GET, UPDATE, DELETE...
                switch (parts[0]) {
                    case CREATE -> {
                        createMovie(out);
                        validateResponseCode(Objects.requireNonNull(responseCodePacket(in)), CREATE);
                    }
                    case GET -> {
                        getMovie(out);
                        if (validateResponseCode(Objects.requireNonNull(responseCodePacket(in)), GET)) {
                            Movie movie = receiveMovie(in);
                            System.out.println(ANSI_GREEN + "Movie: \n" + ANSI_CYAN + movie + ANSI_RESET);
                        } else {
                            System.out.println(ANSI_GREEN + "Movie not found." + ANSI_RESET);
                        }
                    }
                    case UPDATE -> System.out.println(ANSI_GREEN + "Updating a movie..." + ANSI_RESET);
                    case DELETE -> System.out.println(ANSI_GREEN + "Deleting a movie..." + ANSI_RESET);
                    case LISTBYACTORS ->
                            System.out.println(ANSI_GREEN + "Listing all movies by an actor..." + ANSI_RESET);
                    case LISTBYCATEGORY ->
                            System.out.println(ANSI_GREEN + "Listing all movies by a category..." + ANSI_RESET);
                    case HELP -> showHelp();
                    default -> {
                        System.out.println(ANSI_GREEN + "Invalid command. Try again." + ANSI_RESET);
                        continue;
                    }
                }
            }
        } catch (EOFException eofe){
            System.out.println(ANSI_GREEN + "EOF:" + ANSI_CYAN + eofe.getMessage() + ANSI_RESET);
        } catch (IOException ioe){
            System.out.println(ANSI_CYAN + "IO:" + ANSI_CYAN + ioe.getMessage() + ANSI_RESET);
        }
    }

    private static Movie receiveMovie(DataInputStream in) {
        System.out.println(ANSI_GREEN + "Receiving a movie..." + ANSI_RESET);
        try {
            // Get the size of the movie
            int movieSize = in.readInt();
            System.out.println(ANSI_GREEN + "Movie size: " + ANSI_CYAN + movieSize + ANSI_RESET);

            // Create a byte array with the size of the movie
            byte[] movieBytes = new byte[movieSize];

            // Read the movie bytes from the socket
            in.readFully(movieBytes);

            // Deserialize the movie bytes into a Movie object and return it
            return Movie.parseFrom(movieBytes);
        } catch (IOException e) {
            System.out.println(ANSI_GREEN + "IO:" + ANSI_CYAN + e.getMessage() + ANSI_RESET);
        }
        return null;
    }

    private static void getMovie(DataOutputStream out) throws IOException {
        System.out.println(ANSI_GREEN + "Getting a movie..." + ANSI_RESET);

        // Create a new ClientRequest object for specifying the operation the server will execute
        ClientRequest request = ClientRequest.newBuilder()//.
                .setOperation(Operations.Read)
                .build();
        // Serialize the request
        byte[] serializedRequest = request.toByteArray();

        // Send the serialized request to the server
        sendPacket(out, serializedRequest);

        // Create a new Movie object and fill it with the user input
        GetMovieOperation get_movie = userFillGetMovieObject();
        System.out.println(ANSI_GREEN + "Movie title: " + ANSI_CYAN + get_movie.getMovieTitle() + ANSI_RESET);
        // Serialize the movie object
        byte[] serializedMovie = get_movie.toByteArray();

        // Send the serialized movie to the server
        sendPacket(out, serializedMovie);
    }

    private static GetMovieOperation userFillGetMovieObject() {
        Scanner reader = new Scanner(System.in); // Read the user input

        System.out.println(ANSI_GREEN + "Type the movie title: (String)" + ANSI_RESET);
        String title = reader.nextLine(); // Read the user input

        return GetMovieOperation.newBuilder()
                .setMovieTitle(title)
                .build();
    }

    private static void createMovie(DataOutputStream out) throws IOException {
        System.out.println(ANSI_GREEN + "Creating a new movie..." + ANSI_RESET);

        // Create a new ClientRequest object for specifying the operation the server will execute
        ClientRequest request = ClientRequest.newBuilder()//.
                .setOperation(Operations.Create)
                .build();
        // Serialize the request
        byte[] serializedRequest = request.toByteArray();

        // Send the serialized request to the server
        sendPacket(out, serializedRequest);

        // Create a new Movie object and fill it with the user input
        Movie movie = userFillMovieObject();
        // System.out.println(movie);
        // Serialize the movie object
        assert movie != null;
        byte[] serializedMovie = movie.toByteArray();

        // Send the serialized movie to the server
        sendPacket(out, serializedMovie);
    }

    private static ResponseCode responseCodePacket(DataInputStream in) throws IOException {
        // Wait for the server response packet, which will be two packets. The first one is the length of the second one
        try {
            System.out.println(ANSI_GREEN + "Waiting for the response packet..." + ANSI_RESET);
            int length = in.readInt();
            System.out.println(ANSI_GREEN + "Length of the response packet: " + ANSI_CYAN + length + ANSI_RESET);
            byte[] serializedResponse = new byte[length];
            in.readFully(serializedResponse, 0, length);
            System.out.println(ANSI_GREEN + "Serialized response: " + ANSI_CYAN + serializedResponse + ANSI_RESET);

            // Deserialize the response
            ResponseCode deserializedResponse = ResponseCode.parseFrom(serializedResponse);
            System.out.println(ANSI_GREEN + "Response: " + ANSI_CYAN + deserializedResponse.getResponse() + ANSI_RESET);
            System.out.println(ANSI_GREEN + "Response code sent!" + ANSI_RESET);
            return deserializedResponse;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    // Create a method that validates the response code. If is 1, then the operation was successful, otherwise it failed
    private static boolean validateResponseCode(ResponseCode responseCode, String operation) {
        if (responseCode.getResponse().equals(SUCCESS_CODE)) {
            System.out.println(ANSI_GREEN + "Operation " + ANSI_CYAN + operation + " " + ANSI_GREEN + SUCCESS + "!" + ANSI_RESET);
            return true;
        }
        System.out.println(ANSI_GREEN + "Operation " + ANSI_CYAN + operation + " " + ANSI_GREEN + FAILURE + "!" + ANSI_RESET);
        return false;
    }

    // create a method for sending packets to the server
    private static void sendPacket(DataOutputStream out, byte[] serializedPacket) throws IOException {
        out.writeInt(serializedPacket.length);
        System.out.println(ANSI_GREEN + "Serialized packet length: " + ANSI_CYAN + serializedPacket.length + ANSI_RESET);
        out.write(serializedPacket);
        System.out.println(ANSI_GREEN + "Serialized packet: " + ANSI_CYAN + serializedPacket + ANSI_RESET);
        out.flush();
    }

    /*
     @brief: This function shows the user how to use the program
     @param: None
     @return: None
     */
    public static void showHelp() {
        System.out.println(ANSI_GREEN + "CREATE: Create a new movie" + ANSI_RESET);
        System.out.println(ANSI_GREEN + "GET: Get a movie by title" + ANSI_RESET);
        System.out.println(ANSI_GREEN + "UPDATE: Update a movie" + ANSI_RESET);
        System.out.println(ANSI_GREEN + "DELETE: Delete a movie by title" + ANSI_RESET);
        System.out.println(ANSI_GREEN + "LISTACTORS: List all movies by an actor" + ANSI_RESET);
        System.out.println(ANSI_GREEN + "LISTCATEGORY: List all movies by a category" + ANSI_RESET);
        System.out.println(ANSI_GREEN + "EXIT: Exit the program" + ANSI_RESET);
    }

    /*
    @brief: This function asks for the user input to fill a movie object
    @param: None
    @return: A movie object
    */
    public static Movie userFillMovieObject() {
        Scanner reader = new Scanner(System.in); // Read the user input
        boolean empty_fields = true;
        while (empty_fields) {
            // Ask for the user input: id, plot, genre, runtime, cast, num_mflix_comments, title, fullplot, countries, released, directors, rated, lastupdated, year, type
            System.out.println(ANSI_GREEN + "Type the id of the movie: (String)" + ANSI_RESET);
            String id = reader.nextLine(); // Read the user input
            System.out.println(ANSI_GREEN + "Type the plot of the movie: (String)" + ANSI_RESET);
            String plot = reader.nextLine(); // Read the user input
            System.out.println(ANSI_GREEN + "Type the genre of the movie: (String)" + ANSI_RESET);
            String genre = reader.nextLine(); // Read the user input
            System.out.println(ANSI_GREEN + "Type the runtime of the movie: (int)" + ANSI_RESET);
            int runtime = reader.nextInt(); // Read the user input
            System.out.println(ANSI_GREEN + "Type the number of casts in the movie: (int)" + ANSI_RESET);
            int cast_number = reader.nextInt(); // Read the user input
            // Create a list of casts
            List<String> cast = new ArrayList<String>(cast_number);
            reader.nextLine();
            for (int i = 0; i < cast_number; i++) {
                System.out.println(ANSI_GREEN + "Type the cast of the movie: (String)" + ANSI_RESET);
                cast.add(reader.nextLine()); // Read the user input
            }
            System.out.println(ANSI_GREEN + "Type the num_mflix_comments of the movie: (int)" + ANSI_RESET);
            int num_mflix_comments = reader.nextInt(); // Read the user input
            reader.nextLine();
            System.out.println(ANSI_GREEN + "Type the title of the movie: (String)" + ANSI_RESET);
            String title = reader.nextLine(); // Read the user input
            System.out.println(ANSI_GREEN + "Type the fullplot of the movie: (String)" + ANSI_RESET);
            String fullplot = reader.nextLine(); // Read the user input
            System.out.println(ANSI_GREEN + "Type the number of countries of the movie: (int)" + ANSI_RESET);
            int countries_number = reader.nextInt(); // Read the user input
            reader.nextLine();
            List<String> countries = new ArrayList<String>(countries_number);
            for (int i = 0; i < countries_number; i++) {
                System.out.println(ANSI_GREEN + "Type the countries of the movie: (String)" + ANSI_RESET);
                countries.add(reader.nextLine()); // Read the user input
            }
            System.out.println(ANSI_GREEN + "Type the released of the movie: (String)" + ANSI_RESET);
            String released = reader.nextLine(); // Read the user input
            System.out.println(ANSI_GREEN + "Type the number of directors of the movie: (int)" + ANSI_RESET);
            int directors_number = reader.nextInt(); // Read the user input
            reader.nextLine();
            List<String> directors = new ArrayList<String>(directors_number);
            for (int i = 0; i < directors_number; i++) {
                System.out.println(ANSI_GREEN + "Type the directors of the movie: (String)" + ANSI_RESET);
                directors.add(reader.nextLine()); // Read the user input
            }
            System.out.println(ANSI_GREEN + "Type the rated of the movie: (String)" + ANSI_RESET);
            String rated = reader.nextLine(); // Read the user input
            System.out.println(ANSI_GREEN + "Type the last updated of the movie: (String)" + ANSI_RESET);
            String lastupdated = reader.nextLine(); // Read the user input
            System.out.println(ANSI_GREEN + "Type the year of the movie: (int)" + ANSI_RESET);
            int year = reader.nextInt(); // Read the user input
            reader.nextLine();
            System.out.println(ANSI_GREEN + "Type the type of the movie: (String)" + ANSI_RESET);
            String type = reader.nextLine(); // Read the user input

            // Initialize the variables id, plot, genre, runtime, cast, num_mflix_comments, title, fullplot, countries, released, directors, rated, lastupdated, year, type
            // String id = "id";
            // String plot = "plot";
            // String genre = "genre";
            // int runtime = 1;
            // List<String> cast = new ArrayList<>();
            // cast.add("cast1");
            // int num_mflix_comments = 1;
            // String title = "title";
            // String fullplot = "fullplot";
            // List<String> countries = new ArrayList<>();
            // countries.add("country1");
            // String released = "released";
            // List<String> directors = new ArrayList<>();
            // directors.add("director1");
            // String rated = "rated";
            // String lastupdated = "lastupdated";
            // int year = 2023;
            // String type = "type";

            // verify if there is no empty field
            if (id.equals("") || plot.equals("") || genre.equals("") || runtime == 0 || cast.size() == 0 || num_mflix_comments == 0 || title.equals("") || fullplot.equals("") || countries.size() == 0 || released.equals("") || directors.size() == 0 || rated.equals("") || lastupdated.equals("") || year == 0 || type.equals("")) {
                System.out.println(ANSI_RED + "Error: One or more fields are empty" + ANSI_RESET);
            } else {
                empty_fields = false;
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
        return null;
    }

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
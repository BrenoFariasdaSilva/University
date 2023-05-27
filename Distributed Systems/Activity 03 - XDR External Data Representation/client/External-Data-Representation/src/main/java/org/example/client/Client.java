package org.example.client;
import org.example.client.structs.*;

import java.net.*;
import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Scanner;

/*
 * XDR - External Data Representation Activity.
 * @author Breno Farias da Silva.
 * @subject Distributed Systems.
 * @date 15/05/2023.
 * @lastUpdate 24/05/2023.
 * This file is the client side of the application.
 * This file creates a TCP socket in order to communicate with the server.
 * It's responsible for sending messages to the server.
 * It also receives messages from the server.
 * It also validates user input, so the server don't get loaded with invalid inputs
 */

/**
 * This class is the client side of the application.
 * */
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
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in); // Read the user input

        // Address and port of the server
        int serverPort = 7070; // Later put it inside a env variable
        InetAddress serverAddr = null; // Create an instance of InetAddress
        try {
            serverAddr = InetAddress.getByName("localhost"); // Get the IP address of the server, which is localhost = 127.0.0.1
        } catch (UnknownHostException e) {
            System.out.println(ANSI_RED + "Unknown host!" + ANSI_CYAN + e.getMessage() + ANSI_RESET);
            return;
        }

        try (var clientSocket = new Socket(serverAddr, serverPort)) { // Var inferes the type of the variable, which can only be used with local variables
            // Create the read and write objects for the socket
            DataInputStream in = new DataInputStream(clientSocket.getInputStream());
            DataOutputStream out = new DataOutputStream(clientSocket.getOutputStream());

            // Create the variables to handle the user input
            String user_input = "";

            // Show the user how to use the program
            while (true) {
                System.out.println(ANSI_GREEN + "Type a message: " + ANSI_RED + "(String)" + ANSI_RESET);
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

                // Validate the user input for CREATE, GET, UPDATE, DELETE, LISTBYACTOR, LISTBYGENRE, HELP and Unknown commands.
                validateUserOperation(in, out, parts);
            }
        } catch (EOFException eofe){
            System.out.println(ANSI_GREEN + "EOF:" + ANSI_CYAN + eofe.getMessage() + ANSI_RESET);
        } catch (IOException ioe){
            System.out.println(ANSI_CYAN + "IO:" + ANSI_CYAN + ioe.getMessage() + ANSI_RESET);
        }
    }

    // End of main method
    // CRUD OPERATIONS: CREATE, READ (GET), UPDATE, DELETE, LISTBYACTOR, LISTBYGENRE

    /*
    * @brief This method creates a new movie object, fills it with the user input and sends it to the server.
    * @param out The DataOutputStream object to send the serialized movie object to the server.
    * @return void
    */
    private static void createMovie(DataOutputStream out) throws IOException {
        System.out.println(ANSI_GREEN + "Creating a new movie..." + ANSI_RESET);

        // Create a new ClientRequest object for specifying the operation the server will execute
        ClientRequest request = ClientRequest.newBuilder()//.
                .setOperation(Operations.Create) // Set the operation to CREATE
                .build(); // Build the object
        // Serialize the request
        byte[] serializedRequest = request.toByteArray();

        // Send the serialized request to the server
        sendPacket(out, serializedRequest);

        // Create a new Movie object and fill it with the user input
        createMovieObject(out);
    }

    /*
    * @brief This method gets a movie object according to the user input of the movie title and sends it to the server.
    * @param out The DataOutputStream object to send the serialized movie object to the server.
    * @return void
     */
    private static void getMovie(DataOutputStream out) throws IOException {
        System.out.println(ANSI_GREEN + "Getting a movie..." + ANSI_RESET);

        // Create a new ClientRequest object for specifying the operation the server will execute
        ClientRequest request = ClientRequest.newBuilder()//.
                .setOperation(Operations.Read) // Set the operation to READ
                .build(); // Build the object
        // Serialize the request
        byte[] serializedRequest = request.toByteArray();

        // Send the serialized request to the server
        sendPacket(out, serializedRequest);

        // Create a new Movie object and fill it with the user input
        GetMovieOperation get_movie = userFillGetMovieObject();
        // Serialize the movie object
        assert get_movie != null;
        byte[] serializedMovie = get_movie.toByteArray();

        // Send the serialized movie to the server
        sendPacket(out, serializedMovie);
    }

    /*
     * @brief This method updates a movie object according to the user input  and sends it to the server.
     * @param out The DataOutputStream object to send the serialized movie object to the server.
     * @return void
     */
    public static void updateMovie(DataInputStream in, DataOutputStream out) throws IOException {
        System.out.println(ANSI_GREEN + "Updating a movie..." + ANSI_RESET);
        // Create a new ClientRequest object for specifying the operation the server will execute
        ClientRequest request = ClientRequest.newBuilder()//.
                .setOperation(Operations.Update) // Set the operation to UPDATE
                .build(); // Build the object
        // Serialize the request
        byte[] serializedRequest = request.toByteArray();

        // Send the serialized request to the server
        sendPacket(out, serializedRequest);

        // Create a new Movie object and fill it with the user input
        GetMovieOperation get_movie = userFillGetMovieObject();
        // Serialize the movie object
        assert get_movie != null;
        byte[] serializedGetMovie = get_movie.toByteArray();

        // Send the serialized movie to the server
        sendPacket(out, serializedGetMovie);

        if (validateResponseCode(Objects.requireNonNull(responseCodePacket(in)), GET)) {
            Movie old_movie = receiveMovie(in);

            // Create a new Movie object and fill it with the user input
            Movie new_movie = userFillUpdateMovieObject(old_movie);
            // Serialize the movie object
            byte[] serializedMovie = new_movie.toByteArray();

            // Send the serialized movie to the server
            sendPacket(out, serializedMovie);
        }
    }

    /*
    * @brief This method deletes a movie object according to the user input of the movie title and sends it to the server.
    * @param out The DataOutputStream object to send the serialized movie object to the server.
    * @return void
     */
    private static void deleteMovie(DataOutputStream out) throws IOException {
        System.out.println(ANSI_GREEN + "Deleting a movie..." + ANSI_RESET);

        // Create a new ClientRequest object for specifying the operation the server will execute
        ClientRequest request = ClientRequest.newBuilder()//.
                .setOperation(Operations.Delete) // Set the operation to DELETE
                .build(); // Build the object
        // Serialize the request
        byte[] serializedRequest = request.toByteArray();

        // Send the serialized request to the server
        sendPacket(out, serializedRequest);

        // Create a new Movie object and fill it with the user input
        DeleteMovieOperation delete_movie = userFillDeleteMovieObject();
        // Serialize the movie object
        byte[] serializedMovie = delete_movie.toByteArray();

        // Send the serialized movie to the server
        sendPacket(out, serializedMovie);
    }

    /*
    * @brief This method lists all movies of a certain actor according to the user input and sends it to the server.
    * @param out The DataOutputStream object to send the serialized movie object to the server.
    * @return void
     */
    public static void listMoviesByActor(DataOutputStream out) throws IOException {
        System.out.println(ANSI_GREEN + "Listing all movies of a certain actor..." + ANSI_RESET);

        // Create a new ClientRequest object for specifying the operation the server will execute
        ClientRequest request = ClientRequest.newBuilder()//.
                .setOperation(Operations.ListByActor) // Set the operation to LISTBYACTOR
                .build(); // Build the object

        // Serialize the request
        byte[] serializedRequest = request.toByteArray();
        // Send the serialized request to the server
        sendPacket(out, serializedRequest);

        // Create a new ClientListOperation object and fill it with the user input
        createListByObject(out);
    }

    /*
    * @brief This method lists all movies of a certain genre according to the user input and sends it to the server.
    * @param out The DataOutputStream object to send the serialized movie object to the server.
    * @return void
     */
    private static void listMoviesByGenre(DataOutputStream out) throws IOException {
        System.out.println(ANSI_GREEN + "Listing all movies of a certain genre..." + ANSI_RESET);

        // Create a new ClientRequest object for specifying the request type
        ClientRequest request = ClientRequest.newBuilder()
                .setOperation(Operations.ListByGenre) // Set the operation to LISTBYGENRE
                .build(); // Build the object

        // Serialize the request
        byte[] serializedRequest = request.toByteArray();
        // Send the serialized request to the server
        sendPacket(out, serializedRequest);

        // Create a new ClientListOperation object and fill it with the user input
        createListByObject(out);
    }

    // End of CRUD operations
    // Start of Sending and Receiving methods

    /*
    * @brief This method sends a serialized packet to the server.
    * @param out The DataOutputStream object to send the serialized movie object to the server.
    * @param serializedPacket The serialized packet to send to the server.
    * @return void
     */
    private static void sendPacket(DataOutputStream out, byte[] serializedPacket) throws IOException {
        out.writeInt(serializedPacket.length);
        System.out.println(ANSI_GREEN + "Serialized packet length: " + ANSI_CYAN + serializedPacket.length + ANSI_RESET);
        out.write(serializedPacket);
        System.out.println(ANSI_GREEN + "Serialized packet: " + ANSI_CYAN + serializedPacket + ANSI_RESET);
        out.flush();
    }

    /*
    * @brief This method receives a serialized packet from the server.
    * @param in The DataInputStream object to receive the serialized movie object from the server.
    * @return byte[] The serialized packet received from the server.
     */
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

    /*
    * @brief This method receives a serialized packet from the server.
    * @param in The DataInputStream object to receive the serialized movie object from the server.
    * @return byte[] The serialized packet received from the server.
     */
    private static ListBy receiveMoviesList(DataInputStream in) {
        try {
            // Create a new ListBy object
            ListBy movies_list = null;

            // Receive the package size
            int package_size = in.readInt();
            // Create a byte array with the package size
            byte[] serialized_movies_list = new byte[package_size];

            // Receive the serialized movie list object from the server
            in.readFully(serialized_movies_list);
            return ListBy.parseFrom(serialized_movies_list);
        } catch (IOException e) {
            System.out.println(ANSI_GREEN + "IO:" + ANSI_CYAN + e.getMessage() + ANSI_RESET);
        }
        return null;
    }

    // End of Sending and Receiving methods
    // Start of create object methods: createMovieObject and createListByObject

    /*
    * @brief This method creates a new Movie object and fills it with the user input.
    * @param out the DataOutputStream object to send the serialized movie object to the server.
    * @return void
     */
    private static void createMovieObject(DataOutputStream out) throws IOException {
        // Create a new Movie object and fill it with the user input
        Movie movie = userFillCreateMovieObject(false);
        // System.out.println(movie);
        // Serialize the movie object
        assert movie != null;
        byte[] serializedMovie = movie.toByteArray();

        // Send the serialized movie to the server
        sendPacket(out, serializedMovie);
    }

    /*
    * @brief This method creates a new ClientListOperation object and fills it with the user input.
    * @param out the DataOutputStream object to send the serialized movie object to the server.
    * @return void
     */
    private static void createListByObject(DataOutputStream out) throws IOException {
        // Create a new ClientListOperation object and fill it with the user input
        ClientListOperation list_movies_by = userFillListByObject();

        // Serialize the movie object
        byte[] serializedMovie = list_movies_by.toByteArray();

        // Send the serialized movie to the server
        sendPacket(out, serializedMovie);
    }

    // End of create object methods: createMovieObject and createListByObject
    // Start of user fill objects methods: userFillCreateMovieObject, userFillGetMovieObject, userFillDeleteMovieObject, userFillListByObject

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
    * @brief This function is used to fill the GetMovieOperation object with user input
    * @param None
    * @return GetMovieOperation object
     */
    private static GetMovieOperation userFillGetMovieObject() {
        Scanner reader = new Scanner(System.in); // Read the user input
        boolean empty_field = true;

        while (empty_field) {
            System.out.println(ANSI_GREEN + "Type the movie title:" + ANSI_RED + " (String)" + ANSI_RESET);
            String title = reader.nextLine(); // Read the user input

            if (title.equals("")) {
                System.out.println(ANSI_RED + "Error: The title field is empty" + ANSI_RESET);
            } else {
                return GetMovieOperation.newBuilder()
                        .setMovieTitle(title) // Set the movie title
                        .build(); // Build the object
            }
        }
        return null;
    }

    /*
    * @brief This function is used to fill the Movie object with user input
    * @param Movie old_movie
    * return UpdateMovieOperation object
    */
    private static Movie userFillUpdateMovieObject (Movie old_movie) {
        Scanner reader = new Scanner(System.in); // Read the user input

        System.out.println(ANSI_GREEN + "Type the movie plot:" + ANSI_RED + " (String)" + ANSI_RESET);
        String plot = reader.nextLine(); // Read the user input
        if (plot.equals("")) plot = old_movie.getTitle();
        System.out.println(ANSI_GREEN + "Type the movie genre:" + ANSI_RED + " (String)" + ANSI_RESET);
        String genre = reader.nextLine(); // Read the user input
        if (genre.equals("")) genre = old_movie.getGenre();
        System.out.println(ANSI_GREEN + "Type the movie runtime:" + ANSI_RED + " (int)" + ANSI_RESET);
        int runtime = reader.nextInt(); // Read the user input
        reader.nextLine();
        if (runtime == 0) runtime = old_movie.getRuntime();
        System.out.println(ANSI_GREEN + "Type the movie cast:" + ANSI_RED + " (List<String>)" + ANSI_RESET);
        List<String> cast = new ArrayList<>();
        String cast_input = reader.nextLine(); // Read the user input
        if (cast_input.equals("")) cast = old_movie.getCastList();
        else {
            String[] cast_array = cast_input.split(",");
            for (String actor : cast_array) {
                cast.add(actor);
            }
        }
        System.out.println(ANSI_GREEN + "Type the movie num_mflix_comments:" + ANSI_RED + " (int)" + ANSI_RESET);
        int num_mflix_comments = reader.nextInt(); // Read the user input
        reader.nextLine();
        if (num_mflix_comments == 0) num_mflix_comments = old_movie.getNumMflixComments();
        System.out.println(ANSI_GREEN + "Type the movie title:" + ANSI_RED + " (String)" + ANSI_RESET);
        String title = reader.nextLine(); // Read the user input
        if (title.equals("")) title = old_movie.getTitle();
        System.out.println(ANSI_GREEN + "Type the movie fullplot:" + ANSI_RED + " (String)" + ANSI_RESET);
        String fullplot = reader.nextLine(); // Read the user input
        if (fullplot.equals("")) fullplot = old_movie.getFullplot();
        System.out.println(ANSI_GREEN + "Type the movie countries:" + ANSI_RED + " (List<String>)" + ANSI_RESET);
        List<String> countries = new ArrayList<>();
        String countries_input = reader.nextLine(); // Read the user input
        if (countries_input.equals("")) countries = old_movie.getCountriesList();
        else {
            String[] countries_array = countries_input.split(",");
            for (String country : countries_array) {
                countries.add(country);
            }
        }
        System.out.println(ANSI_GREEN + "Type the movie released:" + ANSI_RED + " (String)" + ANSI_RESET);
        String released = reader.nextLine(); // Read the user input
        if (released.equals("")) released = old_movie.getReleased();
        System.out.println(ANSI_GREEN + "Type the movie directors:" + ANSI_RED + " (List<String>)" + ANSI_RESET);
        List<String> directors = new ArrayList<>();
        String directors_input = reader.nextLine(); // Read the user input
        if (directors_input.equals("")) directors = old_movie.getDirectorsList();
        else {
            String[] directors_array = directors_input.split(",");
            for (String director : directors_array) {
                directors.add(director);
            }
        }
        System.out.println(ANSI_GREEN + "Type the movie rated:" + ANSI_RED + " (String)" + ANSI_RESET);
        String rated = reader.nextLine(); // Read the user input
        if (rated.equals("")) rated = old_movie.getRated();
        System.out.println(ANSI_GREEN + "Type the movie lastupdated:" + ANSI_RED + " (String)" + ANSI_RESET);
        String lastupdated = reader.nextLine(); // Read the user input
        if (lastupdated.equals("")) lastupdated = old_movie.getLastupdated();
        System.out.println(ANSI_GREEN + "Type the movie year:" + ANSI_RED + " (int)" + ANSI_RESET);
        int year = reader.nextInt(); // Read the user input
        reader.nextLine();
        if (year == 0) year = old_movie.getYear();
        System.out.println(ANSI_GREEN + "Type the movie type:" + ANSI_RED + " (String)" + ANSI_RESET);
        String type = reader.nextLine(); // Read the user input
        if (type.equals("")) type = old_movie.getType();

        // Create a movie protobuf object and return it
        return Movie.newBuilder()
                .setId(old_movie.getId()) // String
                .setPlot(old_movie.getPlot()) // String
                .setGenre(old_movie.getGenre()) // String
                .setRuntime(old_movie.getRuntime()) // int
                .addAllCast(old_movie.getCastList()) // String
                .setNumMflixComments(old_movie.getNumMflixComments()) // int
                .setTitle(title) // String
                .setFullplot(old_movie.getFullplot()) // String
                .addAllCountries(old_movie.getCountriesList()) // String
                .setReleased(old_movie.getReleased()) // String
                .addAllDirectors(old_movie.getDirectorsList()) // String
                .setRated(old_movie.getRated()) // String
                .setLastupdated(old_movie.getLastupdated()) // String
                .setYear(old_movie.getYear()) // int
                .setType(old_movie.getType()) // String
                .build(); // Build the movie protobuf object
    }

    /*
    * @brief This function is used to fill the DeleteMovieOperation object with user input
    * @param None
    * @return DeleteMovieOperation object
     */
    private static DeleteMovieOperation userFillDeleteMovieObject() {
        Scanner reader = new Scanner(System.in); // Read the user input
        boolean empty_field = true;

        while (empty_field) {
            System.out.println(ANSI_GREEN + "Type the movie title:" + ANSI_RED + " (String)" + ANSI_RESET);
            String title = reader.nextLine(); // Read the user input

            if (title.equals("")) {
                System.out.println(ANSI_RED + "Error: The title field is empty" + ANSI_RESET);
            } else {
                return DeleteMovieOperation.newBuilder()
                        .setMovieTitle(title) // Set the movie title
                        .build(); // Build the object
            }
        }
        return null;
    }

    /*
    * @brief This function is used to fill the ClientListOperation object with user input
    * @param None
    * @return ClientListOperation object
     */
    private static ClientListOperation userFillListByObject() {
        Scanner reader = new Scanner(System.in); // Read the user input
        boolean empty_field = true;

        while (empty_field) {
            System.out.println(ANSI_GREEN + "Type the listBy filter:" + ANSI_RED + " (String)" + ANSI_RESET);
            String filter = reader.nextLine(); // Read the user input

            // verify if there is no empty field
            if (filter.equals("")) {
                System.out.println(ANSI_RED + "Error: The filter field is empty" + ANSI_RESET);
            } else {
                return ClientListOperation.newBuilder()
                        .setFilter(filter) // Set the filter
                        .build(); // Build the object
            }
        }
        return null;
    }

    // End of User Input Methods: userFillCreateMovieObject, userFillGetMovieObject, userFillDeleteMovieObject, userFillListByObject
    // Start of Response Code Methods

    /*
    * @brief This function is used to send the CreateMovieOperation object to the server
    * @param out the DataOutputStream object
    * @return ResponseCode object
     */
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

    /*
    * @brief This function is used to send the CreateMovieOperation object to the server
    * @param ResponseCode object which contains the response code
    * @param operation the operation that was performed
    * @return true if the response code is 1, false otherwise
     */
    private static boolean validateResponseCode(ResponseCode responseCode, String operation) {
        if (responseCode.getResponse().equals(SUCCESS_CODE)) {
            System.out.println(ANSI_GREEN + "Operation " + ANSI_CYAN + operation + " " + ANSI_CYAN + SUCCESS + "!" + ANSI_RESET);
            return true;
        }
        System.out.println(ANSI_GREEN + "Operation " + ANSI_CYAN + operation + " " + ANSI_RED + FAILURE + "!" + ANSI_RESET);
        return false;
    }

    // End of response code methods
    // Start of auxiliary methods

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

    /*
    @brief: This function validates the user input for the operation to be performed
    @param: in - The DataInputStream object
    @param: out - The DataOutputStream object
    @param: parts - The user input
    @return: None
     */
    private static void validateUserOperation(DataInputStream in, DataOutputStream out, String[] parts) throws IOException {
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
                    System.out.println(ANSI_RED + "Movie not found." + ANSI_RESET);
                }
            }
            case UPDATE -> {
                updateMovie(in, out);
                validateResponseCode(Objects.requireNonNull(responseCodePacket(in)), UPDATE);
            }
            case DELETE -> {
                deleteMovie(out);
                validateResponseCode(Objects.requireNonNull(responseCodePacket(in)), DELETE);
            }
            case LISTBYACTOR -> {
                listMoviesByActor(out);
                if (validateResponseCode(Objects.requireNonNull(responseCodePacket(in)), LISTBYACTOR)) {
                    ListBy movies_list = receiveMoviesList(in);
                    System.out.println(ANSI_GREEN + "Movie(s): \n" + ANSI_CYAN + movies_list + ANSI_RESET);
                } else {
                    System.out.println(ANSI_GREEN + "Movie not found." + ANSI_RESET);
                }
            }
            case LISTBYGENRE -> {
                listMoviesByGenre(out);
                if (validateResponseCode(Objects.requireNonNull(responseCodePacket(in)), LISTBYGENRE)) {
                    ListBy movies_list = receiveMoviesList(in);
                    System.out.println(ANSI_GREEN + "Movie(s): \n" + ANSI_CYAN + movies_list + ANSI_RESET);
                } else {
                    System.out.println(ANSI_GREEN + "Movie not found." + ANSI_RESET);
                }
            }
            case HELP -> showHelp();
            default -> {
                System.out.println(ANSI_GREEN + "Invalid command. Try again." + ANSI_RESET);
                showHelp();
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
}
// End of class
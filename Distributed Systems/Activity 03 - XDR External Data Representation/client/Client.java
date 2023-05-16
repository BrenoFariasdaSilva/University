import java.net.*;
import java.io.*;
import java.util.Scanner;
import Movies;

/***
 *  XDR - eXternal Data Representation Activity
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

    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in); // Read the user input

        // Address and port of the server
        int serverPort = 7000; // Later put it inside a env variable
        InetAddress serverAddr = null; // Create an instance of InetAddress
        try {
            serverAddr = InetAddress.getByName("localhost"); // Get the IP address of the server, which is localhost = 127.0.0.1
        } catch (UnknownHostException e) {
            System.out.println(ANSI_GREEN + "Unknown host: " + ANSI_CYAN + e.getMessage() + ANSI_RESET);
            return;
        }

        try (var clientSocket = new Socket(serverAddr, serverPort)) { // Var inferes the type of the variable, which can only be used with local variables
            // Create the read and write objects for the socket
            DataInputStream in = new DataInputStream( clientSocket.getInputStream());
            DataOutputStream out = new DataOutputStream( clientSocket.getOutputStream());

            // Create the variables to handle the user input
            String user_input = "";

            while (true) {
                // Show the user how to use the program
                showHelp();
                System.out.println(ANSI_GREEN + "Type a message: " + ANSI_RESET);
                user_input = reader.nextLine(); // Read the user input

                // Convert the first word of the user input to uppercase
                user_input = stringToUpperCase(user_input);

                if (user_input.equals("EXIT")) {
                    System.out.println(ANSI_GREEN + "Closing the connection..." + ANSI_RESET);
                    clientSocket.close();
                    break;
                }

                // Split the user input into an array of strings
                String[] parts = user_input.split(" ");

                // Validate the user input for CREATE, GET, UPDATE, DELETE...
                if (parts[0].equals("CREATE")){
                    System.out.println(ANSI_GREEN + "Creating a new movie..." + ANSI_RESET);
                    // Create a movie protobuf object
                    Movies.Movie movie = Movies.Movie.newBuilder()
                            .setTitle(parts[1])
                            .setCategory(parts[2])
                            .setYear(Integer.parseInt(parts[3]))
                            .setActors(parts[4])
                            .build();
                } else if (parts[0].equals("GET")) {
                    System.out.println(ANSI_GREEN + "Getting a movie..." + ANSI_RESET);
                } else if (parts[0].equals("UPDATE")) {
                    System.out.println(ANSI_GREEN + "Updating a movie..." + ANSI_RESET);
                } else if (parts[0].equals("DELETE")) {
                    System.out.println(ANSI_GREEN + "Deleting a movie..." + ANSI_RESET);
                } else if (parts[0].equals("LISTBYACTORS")) {
                    System.out.println(ANSI_GREEN + "Listing all movies by an actor..." + ANSI_RESET);
                } else if (parts[0].equals("LISTBYCATEGORY")) {
                    System.out.println(ANSI_GREEN + "Listing all movies by a category..." + ANSI_RESET);
                } else {
                    System.out.println(ANSI_GREEN + "Invalid command. Try again." + ANSI_RESET);
                    continue;
                }

            }
        } catch (EOFException eofe){
            System.out.println(ANSI_GREEN + "EOF:" + ANSI_CYAN + eofe.getMessage() + ANSI_RESET);
        } catch (IOException ioe){
            System.out.println(ANSI_CYAN + "IO:" + ANSI_CYAN + ioe.getMessage() + ANSI_RESET);
        }
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
    public static Movies.Movie createMovie() {
        Scanner reader = new Scanner(System.in); // Read the user input

        // Create the variables to handle the user input: id, plot, genre, runtime, cast, num_mflix_comments, title, fullplot, countries, released, directors, rated, lastupdated, year, type
        String id = "";
        String plot = "";
        String genre = "";
        Integer runtime = -1;
        String cast = "";
        String num_mflix_comments = "";
        String title = "";  
        String fullplot = "";
        String countries = "";
        String released = "";
        String directors = "";
        String rated = "";  
        String lastupdated = "";
        Integer year = -1;
        String type = "";

        int cast_number = -1;

        // Ask for the user input: id, plot, genre, runtime, cast, num_mflix_comments, title, fullplot, countries, released, directors, rated, lastupdated, year, type
        System.out.println(ANSI_GREEN + "Type the id of the movie: " + ANSI_RESET);
        id = reader.nextLine(); // Read the user input
        System.out.println(ANSI_GREEN + "Type the plot of the movie: " + ANSI_RESET);
        plot = reader.nextLine(); // Read the user input
        System.out.println(ANSI_GREEN + "Type the genre of the movie: " + ANSI_RESET);
        genre = reader.nextLine(); // Read the user input
        System.out.println(ANSI_GREEN + "Type the runtime of the movie: " + ANSI_RESET);
        runtime = reader.nextInt(); // Read the user input
        System.out.print(ANSI_GREEN + "Type the number of casts in the movie");
        for (int i = 0; i < cast_number; i++) {
            System.out.print(ANSI_GREEN + "Type the cast of the movie: " + ANSI_RESET);
            cast = reader.nextLine(); // Read the user input
        }
        System.out.println(ANSI_GREEN + "Type the cast of the movie: " + ANSI_RESET);
        cast = reader.nextLine(); // Read the user input
        System.out.println(ANSI_GREEN + "Type the num_mflix_comments of the movie: " + ANSI_RESET);
        num_mflix_comments = reader.nextLine(); // Read the user input
        System.out.println(ANSI_GREEN + "Type the title of the movie: " + ANSI_RESET);
        title = reader.nextLine(); // Read the user input
        System.out.println(ANSI_GREEN + "Type the fullplot of the movie: " + ANSI_RESET);
        fullplot = reader.nextLine(); // Read the user input
        System.out.println(ANSI_GREEN + "Type the countries of the movie: " + ANSI_RESET);
        countries = reader.nextLine(); // Read the user input
        System.out.println(ANSI_GREEN + "Type the released of the movie: " + ANSI_RESET);
        released = reader.nextLine(); // Read the user input
        System.out.println(ANSI_GREEN + "Type the directors of the movie: " + ANSI_RESET);
        directors = reader.nextLine(); // Read the user input
        System.out.println(ANSI_GREEN + "Type the rated of the movie: " + ANSI_RESET);
        rated = reader.nextLine(); // Read the user input
        System.out.println(ANSI_GREEN + "Type the lastupdated of the movie: " + ANSI_RESET);
        lastupdated = reader.nextLine(); // Read the user input
        System.out.println(ANSI_GREEN + "Type the year of the movie: " + ANSI_RESET);
        year = reader.nextInt(); // Read the user input
        System.out.println(ANSI_GREEN + "Type the type of the movie: " + ANSI_RESET);
        type = reader.nextLine(); // Read the user input

        // Create a movie protobuf object
        Movies.Movie movie = Movies.Movie.newBuilder()
                .setId(id)
                .setPlot(plot)
                .setGenre(genre)
                .setRuntime(runtime)
                .setCast(cast,cast_number)
                .setNumMflixComments(num_mflix_comments)
                .setTitle(title)
                .setFullplot(fullplot)
                .setCountries(countries)
                .setReleased(released)
                .setDirectors(directors)
                .setRated(rated)
                .setLastupdated(lastupdated)
                .setYear(year)
                .setType(type)
                .build();
        return movie;
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
            String restOfTheSentence = "";
            for (int i = 1; i < parts.length; i++) {
                restOfTheSentence += parts[i] + " ";
            }
            return firstWord.toUpperCase() + " " + restOfTheSentence;
        } else {
            return s.toUpperCase();
        }
    }
}
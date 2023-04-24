import java.net.*;
import java.io.*;
import java.util.Scanner;
import java.math.BigInteger;
import java.security.MessageDigest;

/***
 *  TCP Socket Programming Activity.
 * @author Breno Farias
 * @subject Distributed Systems
 * @date 16/03/2022
 * @lastUpdate 24/04/2022
 * This file is the client side of the application.
 * This file creates a TCP socket in order to communicate with the server.
 * It's responsible for sending messages to the server.
 * It also receives messages from the server.
 * It's also responsible for encrypting the password into SHA512.
 * And validate user input, so the server don't get loaded with invalid inputs
 */

public class Client {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_CYAN = "\u001B[36m";

    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in); // ler mensagens via teclado

        // Address and port of the server
        int serverPort = 6666;
        InetAddress serverAddr = null; // Create an instance of InetAddress
        try {
            serverAddr = InetAddress.getByName("localhost"); // Get the IP address of the server, which is localhost = 127.0.0.1
        } catch (UnknownHostException e) {
            System.out.println(ANSI_GREEN + "Host desconhecido!" + ANSI_RESET);
            return;
        }

        try (var clientSocket = new Socket(serverAddr, serverPort)) { // Var inferes the type of the variable, which can only be used with local variables
            // Create the read and write objects for the socket
            DataInputStream in = new DataInputStream( clientSocket.getInputStream());
            DataOutputStream out = new DataOutputStream( clientSocket.getOutputStream());

            // Create the variables to handle the user input
            String buffer = "";
            String lastMessage = "";
            boolean loggedIn = false;

            while (true) {
                System.out.print(ANSI_GREEN + "Mensagem: " + ANSI_RESET);
                buffer = reader.nextLine(); // lRead the user input
                lastMessage = buffer;

                if (buffer.equals("EXIT")) { return; } // Close the socket and exit the program

                if (buffer.contains("CONNECT")) { // If the user is trying to connect, encrypt the password
                    String[] loginCredentials = buffer.substring(8).split(",");
                    buffer = "CONNECT " + loginCredentials[0] + "," + getSHA512(loginCredentials[1]);
                }

                out.writeUTF(buffer);      	// Send the message to the server
                buffer = in.readUTF();      // Wait for the server to respond

                if (buffer.equals(-1)) { buffer = in.readUTF(); } // If the server response is -1, it means 
                System.out.println(ANSI_GREEN + "Server disse: " + ANSI_CYAN + buffer + ANSI_RESET);

                if (lastMessage.contains("CONNECT") && buffer.equals("SUCCESS")) { loggedIn = true; } // If the user is logged in and the last message was CONNECT, set loggedIn to true
                if ((lastMessage.equals("GETFILES") || lastMessage.equals("GETDIRS")) && loggedIn) { // If the user is logged in and the last message was GETFILES or GETDIRS, print the server response
                    final int numberOfContent = Integer.parseInt(buffer);
                    if (numberOfContent != 0) { System.out.println(ANSI_CYAN + in.readUTF() + ANSI_RESET); } // If the server response is not 0, print the server response
                }
            }
        } catch (EOFException eofe){
            System.out.println(ANSI_GREEN + "EOF:" + ANSI_CYAN + eofe.getMessage() + ANSI_RESET);
        } catch (IOException ioe){
            System.out.println(ANSI_CYAN + "IO:" + ANSI_CYAN + ioe.getMessage() + ANSI_RESET);
        }
    }

    /**
     * This method is responsible for encrypting the password into SHA512.
     * @param password The password to be encrypted.
     * @return The encrypted password.
     */
    public static String getSHA512(String password) {
        String encryptedPassword = "";
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-512"); // Get the SHA-512 instance
            digest.reset(); // Reset the digest
            digest.update(password.getBytes("utf8")); // Update the digest with the password bytes in UTF-8
            encryptedPassword = String.format("%0128x", new BigInteger(1, digest.digest())); // Encrypt the password
        } catch (Exception e) { e.printStackTrace(); }
        return encryptedPassword;
    }
}
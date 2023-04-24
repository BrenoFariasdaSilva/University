import java.net.*;
import java.io.*;

/***
 *  TCP Socket Programming Activity.
 * @author Breno Farias
 * @subject Distributed Systems
 * @date 16/03/2022
 * @lastUpdate 24/04/2022
 * This file is the server side of the application.
 * It creates a socket and waits for connections.
 * It also creates a thread for each client that connects to the server.
 * The thread created is to allow multiple clients to connect to the server, due to TCP socket being a blocking socket.
 */

public class Server {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static void main(String[] args) {

        try {
            int serverPort = 6666; // porta do servidor

            try (/* cria um socket e mapeia a porta para aguardar conexao */
            ServerSocket listenSocket = new ServerSocket(serverPort)) {
                while (true) {
                    System.out.println(ANSI_GREEN + "Servidor aguardando conexao ..." + ANSI_RESET);

                    /* aguarda conexoes */
                    Socket clientSocket = listenSocket.accept(); // Chamada bloqueante

                    System.out.println(ANSI_GREEN + "Cliente conectado ... Criando thread ..." + ANSI_RESET);
                    ClientThread clientThread = new ClientThread(clientSocket); // cria uma thread para o cliente
                    Thread myThread = new Thread(clientThread); 

                    /* inicializa a thread */
                    myThread.start();
                }
            }

        } catch (IOException ioError) {
            throw new RuntimeException("Listen Error: " + ioError);
        }
    }
}
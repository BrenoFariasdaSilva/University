import java.net.*;
import java.io.*;

public class Server {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static void main(String[] args) {

        try {
            int serverPort = 6666; // porta do servidor

            /* cria um socket e mapeia a porta para aguardar conexao */
            ServerSocket listenSocket = new ServerSocket(serverPort);

            while (true) {
                System.out.println(ANSI_GREEN + "Servidor aguardando conexao ..." + ANSI_RESET);

                /* aguarda conexoes */
                Socket clientSocket = listenSocket.accept();

                System.out.println(ANSI_GREEN + "Cliente conectado ... Criando thread ..." + ANSI_RESET);
                ClientThread clientThread = new ClientThread(clientSocket);
                Thread myThread = new Thread(clientThread);

                /* inicializa a thread */
                myThread.start();
            }

        } catch (IOException ioError) {
            throw new RuntimeException("Listen Error: " + ioError);
        }
    }
}
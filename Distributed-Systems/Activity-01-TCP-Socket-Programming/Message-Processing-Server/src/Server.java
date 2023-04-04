import java.net.*;
import java.io.*;

public class Server {
    public static void main(String[] args) {
        try {
            int serverPort = 6666; // porta do servidor

            /* cria um socket e mapeia a porta para aguardar conexao */
            ServerSocket listenSocket = new ServerSocket(serverPort);

            while (true) {
                System.out.println("Servidor aguardando conexao ...");

                /* aguarda conexoes */
                Socket clientSocket = listenSocket.accept();

                System.out.println("Cliente conectado ... Criando thread ...");
                ClientThread clientThread = new ClientThread(clientSocket);
                Thread myThread = new Thread(clientThread);

                /* inicializa a thread */
                clientThread.run();
            }

        } catch (IOException ioError) {
            throw new RuntimeException("Listen Error: " + ioError);
        }
    }
}
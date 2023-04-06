import java.net.*;
import java.io.*;
import java.util.Scanner;

public class Client {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_CYAN = "\u001B[36m";

    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in); // ler mensagens via teclado

        // Endereço e porta do servidor
        int serverPort = 6666;
        InetAddress serverAddr = null; // Instância no localhost.
        try {
            serverAddr = InetAddress.getByName("127.0.0.1");
        } catch (UnknownHostException e) {
            System.out.println(ANSI_GREEN + "Host desconhecido!" + ANSI_RESET);
            return;
        }

        try (var clientSocket = new Socket(serverAddr, serverPort)) { // Var infere o tipo sozinho. Só se usa com variáveis locais.
            // cria objetos de leitura e escrita
            DataInputStream in = new DataInputStream( clientSocket.getInputStream());
            DataOutputStream out = new DataOutputStream( clientSocket.getOutputStream());

            // protocolo de comunicação
            String buffer = "";

            while (true) {
                System.out.print(ANSI_GREEN + "Mensagem: " + ANSI_RESET);
                buffer = reader.nextLine(); // lê mensagem via teclado

                if (buffer.equals("EXIT")) { return; }

                out.writeUTF(buffer);      	// envia a mensagem para o servidor
                buffer = in.readUTF();      // aguarda resposta do servidor
            }
        } catch (EOFException eofe){
            System.out.println(ANSI_GREEN + "EOF:" + ANSI_CYAN + eofe.getMessage() + ANSI_RESET);
        } catch (IOException ioe){
            System.out.println(ANSI_CYAN + "IO:" + ANSI_CYAN + ioe.getMessage() + ANSI_RESET);
        }
    }
}

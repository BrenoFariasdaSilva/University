import java.net.*;
import java.io.*;
import java.util.Scanner;
import java.math.BigInteger;
import java.security.MessageDigest;

/***
 *  TCP Socket Programming Activity.
 * @author Breno Farias
 * @date 24/09/2022
 * @subject Distributed Systems
 */

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
            serverAddr = InetAddress.getByName("localhost"); // 127.0.0.1
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
            String lastMessage = "";
            boolean loggedIn = false;

            while (true) {
                System.out.print(ANSI_GREEN + "Mensagem: " + ANSI_RESET);
                buffer = reader.nextLine(); // lê mensagem via teclado
                lastMessage = buffer;

                if (buffer.equals("EXIT")) { return; }

                if (buffer.contains("CONNECT")) {
                    String[] loginCredentials = buffer.substring(8).split(",");
                    buffer = "CONNECT " + loginCredentials[0] + "," + getSHA512(loginCredentials[1]);
                }

                out.writeUTF(buffer);      	// envia a mensagem para o servidor
                buffer = in.readUTF();      // aguarda resposta do servidor
                if (buffer.equals(-1)) { buffer = in.readUTF(); }
                System.out.println(ANSI_GREEN + "Server disse: " + ANSI_CYAN + buffer + ANSI_RESET);

                if (lastMessage.contains("CONNECT") && buffer.equals("SUCCESS")) { loggedIn = true; }
                if ((lastMessage.equals("GETFILES") || lastMessage.equals("GETDIRS")) && loggedIn) {
                    final int numberOfContent = Integer.parseInt(buffer);
                    if (numberOfContent != 0) { System.out.println(ANSI_CYAN + in.readUTF() + ANSI_RESET); }
                }
            }
        } catch (EOFException eofe){
            System.out.println(ANSI_GREEN + "EOF:" + ANSI_CYAN + eofe.getMessage() + ANSI_RESET);
        } catch (IOException ioe){
            System.out.println(ANSI_CYAN + "IO:" + ANSI_CYAN + ioe.getMessage() + ANSI_RESET);
        }
    }

    public static String getSHA512(String password) {
        String encryptedPassword = "";
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-512");
            digest.reset();
            digest.update(password.getBytes("utf8"));
            encryptedPassword = String.format("%0128x", new BigInteger(1, digest.digest()));
        } catch (Exception e) { e.printStackTrace(); }
        return encryptedPassword;
    }
}

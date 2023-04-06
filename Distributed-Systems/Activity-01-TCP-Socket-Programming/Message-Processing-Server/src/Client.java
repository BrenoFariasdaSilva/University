import java.net.*;
import java.io.*;
import java.util.Scanner;
import java.math.BigInteger;
import java.security.MessageDigest;

public class Client {
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in); // ler mensagens via teclado

        // Endereço e porta do servidor
        int serverPort = 6666;
        InetAddress serverAddr = null; // Instância no localhost.
        try {
            serverAddr = InetAddress.getByName("127.0.0.1");
        } catch (UnknownHostException e) {
            System.out.println("Host desconhecido!");
            return;
        }

        try (var clientSocket = new Socket(serverAddr, serverPort)) { // Var infere o tipo sozinho. Só se usa com variáveis locais.
            // cria objetos de leitura e escrita
            DataInputStream in = new DataInputStream( clientSocket.getInputStream());
            DataOutputStream out = new DataOutputStream( clientSocket.getOutputStream());

            // protocolo de comunicação
            String buffer = "";
            String lastMessage = "";

            while (!buffer.equals("EXIT")) {
                System.out.print("Mensagem: ");
                buffer = reader.nextLine(); // lê mensagem via teclado
                lastMessage = buffer;

                if (buffer.contains("CONNECT")) {
                    String[] loginCredentials = buffer.substring(8).split(",");
                    buffer = "CONNECT " + loginCredentials[0] + "," + getSHA512(loginCredentials[1]);
                }

                out.writeUTF(buffer);      	// envia a mensagem para o servidor
                buffer = in.readUTF();      // aguarda resposta do servidor
                System.out.println("Server disse: " + buffer);

                if (lastMessage.equals("GETFILES") || lastMessage.equals("GETDIRS")) {
                    final int numberOfContent = Integer.parseInt(buffer);
                    if (numberOfContent != 0) { System.out.println(in.readUTF()); }
                }
            }
        } catch (EOFException eofe){
            System.out.println("EOF:" + eofe.getMessage());
        } catch (IOException ioe){
            System.out.println("IO:" + ioe.getMessage());
        }
    }

    public static String getSHA512(String password) {
        String encryptedPassword = "";
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-512");
            digest.reset();
            digest.update(password.getBytes("utf8"));
            encryptedPassword = String.format("%0128x", new BigInteger(1, digest.digest()));
        } catch (Exception e) {
            e.printStackTrace();
        }
        return encryptedPassword;
    }
}

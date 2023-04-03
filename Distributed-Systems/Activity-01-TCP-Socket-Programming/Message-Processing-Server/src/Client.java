import java.net.*;
import java.io.*;
import java.util.Scanner;
import java.math.BigInteger;
import java.security.MessageDigest;

public class Client {
    public static void main(String[] args) {
        Socket clientSocket = null; // socket do cliente
        Scanner reader = new Scanner(System.in); // ler mensagens via teclado

        try{
            // Endereço e porta do servidor
            int serverPort = 6666;
            InetAddress serverAddr = InetAddress.getByName("127.0.0.1"); // Instância no localhost.

            // conecta com o servidor
            clientSocket = new Socket(serverAddr, serverPort);

            // cria objetos de leitura e escrita
            DataInputStream in = new DataInputStream( clientSocket.getInputStream());
            DataOutputStream out = new DataOutputStream( clientSocket.getOutputStream());

            // protocolo de comunicação
            String buffer = "";

            while (buffer != "EXIT") {
                System.out.print("Mensagem: ");
                buffer = reader.nextLine(); // lê mensagem via teclado

                out.writeUTF(buffer);      	// envia a mensagem para o servidor

                buffer = in.readUTF();      // aguarda resposta do servidor
                System.out.println("Server disse: " + buffer);
            }
        } catch (UnknownHostException ue){
            System.out.println("Socket:" + ue.getMessage());
        } catch (EOFException eofe){
            System.out.println("EOF:" + eofe.getMessage());
        } catch (IOException ioe){
            System.out.println("IO:" + ioe.getMessage());
        } finally {
            try {
                clientSocket.close(); // Fechar o socket para não haver problema de socket em uso.
            } catch (IOException ioe) {
                System.out.println("IO: " + ioe);;
            }
        }
    }

    public String getSHA512(String password) {
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

import java.net.*;
import java.io.*;
import java.nio.ByteBuffer;
import java.util.Scanner;

// TODO: Implement checksum.

public class Client {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_CYAN = "\u001B[36m";

    public static final String ADDFILE = "1";
    public static final String DELETE = "2";
    public static final String GETFILELIST = "3";
    public static final String GETFILE = "4";

    public static final int maxHeaderSize = 1 + 1 + 1 + 256;

    public static ByteBuffer byteIn;
    public static ByteBuffer byteOut;
    public static final byte request = 1;

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

            while (true) {
                System.out.println(ANSI_CYAN + "Insert the header information's: \n" + ANSI_RESET); // Operation name and filename (if exists);
                String[] headerInformation = reader.nextLine().split(" ");

                if (headerInformation[0].equals("EXIT")) { return; };

                switch (headerInformation[0]) {
                    case ADDFILE -> headerInformation[0] = ADDFILE;
                    case DELETE -> headerInformation[0] = DELETE;
                    case GETFILELIST -> {
                        headerInformation[0] = GETFILELIST;
                        headerInformation[2] = "";
                    }
                    case GETFILE -> headerInformation[0] = GETFILE;
                    case default -> System.out.println("Invalid command!");
                }
                byteOut = ByteBuffer.allocate(maxHeaderSize);
                byteOut.put(0, request); // Static because the client only send requests
                byteOut.put(1, headerInformation[0].getBytes());
                byte filenameLength = (byte) headerInformation[1].length();
                byteOut.put(2, filenameLength);
                byteOut.put(0, headerInformation[1].getBytes());

                out.write(byteOut.array());

            }
        } catch (EOFException eofe){
            System.out.println(ANSI_GREEN + "EOF:" + ANSI_CYAN + eofe.getMessage() + ANSI_RESET);
        } catch (IOException ioe){
            System.out.println(ANSI_CYAN + "IO:" + ANSI_CYAN + ioe.getMessage() + ANSI_RESET);
        }
    }
}

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

    public static final int headerSize = 1 + 1 + 1 + 256;

    public static ByteBuffer byteInput;
    public static ByteBuffer byteOutput;
    public static final byte request = 1;

    public void main(String[] args) {
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
                    case ADDFILE -> out.write(addFile(headerInformation[1]).array());
                    case DELETE -> out.write(deleteFile(headerInformation[1]).array());
                    case GETFILELIST -> out.write(getFileList().array());
                    case GETFILE -> out.write(getFile(headerInformation[1]).array());
                    case default -> System.out.println("Invalid command!");
                }
            }
        } catch (EOFException eofe){
            System.out.println(ANSI_GREEN + "EOF:" + ANSI_CYAN + eofe.getMessage() + ANSI_RESET);
        } catch (IOException ioe){
            System.out.println(ANSI_CYAN + "IO:" + ANSI_CYAN + ioe.getMessage() + ANSI_RESET);
        }
    }

    public ByteBuffer addFile (final String filename) {
        try {
            File file = new File(filename); // File to be sent
            byte[] fileContent = new byte[(int) file.length()]; // File content
            FileInputStream fileInputStream = new FileInputStream(file); // File input stream
            fileInputStream.read(fileContent); // Read file content
            fileInputStream.close(); // Close file input stream

            byteOutput = ByteBuffer.allocate(headerSize); // + fileContent.length?
            byteOutput.put(0, request); // Static because the client only send requests
            byteOutput.put(1, ADDFILE.getBytes()); // Value of ADDFILE (1) in position 1
            byte filenameLength = (byte) filename.length(); // Filename length
            byteOutput.put(2, filenameLength); // Filename length in position 2
            byteOutput.put(3, filename.getBytes()); // Filename in position 3
//            byteOutput.put(headerSize, fileContent); // File content in position 4

            return byteOutput;
        } catch (FileNotFoundException fnfe) {
            System.out.println(ANSI_GREEN + "File not found:" + ANSI_CYAN + fnfe.getMessage() + ANSI_RESET);
        } catch (IOException ioe) {
            System.out.println(ANSI_GREEN + "IO:" + ANSI_CYAN + ioe.getMessage() + ANSI_RESET);
        }
        return null;
    }

    public ByteBuffer deleteFile (final String filename) {
        byteOutput = ByteBuffer.allocate(headerSize);
        byteOutput.put(0, request); // Static because the client only send requests
        byteOutput.put(1, DELETE.getBytes()); // Value of DELETE (2) in position 1
        byte filenameLength = (byte) filename.length(); // Filename length
        byteOutput.put(2, filenameLength); // Filename length in position 2
        byteOutput.put(3, filename.getBytes()); // Filename in position 3

        return byteOutput;
    }

    public ByteBuffer getFileList () {
        byteOutput = ByteBuffer.allocate(headerSize);
        byteOutput.put(0, request); // Static because the client only send requests
        byteOutput.put(1, GETFILELIST.getBytes()); // Value of GETFILELIST (3) in position 1
        byteOutput.put(2, (byte) 0); // Filename length in position 2
        byteOutput.put(3, "".getBytes()); // Filename in position 3

        return byteOutput;
    }

    public ByteBuffer getFile (final String filename) {
        byteOutput = ByteBuffer.allocate(headerSize);
        byteOutput.put(0, request); // Static because the client only send requests
        byteOutput.put(1, GETFILE.getBytes()); // Value of GETFILE (4) in position 1
        byte filenameLength = (byte) filename.length(); // Filename length
        byteOutput.put(2, filenameLength); // Filename length in position 2
        byteOutput.put(3, filename.getBytes()); // Filename in position 3

        return byteOutput;
    }
}

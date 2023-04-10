import java.net.*;
import java.io.*;
import java.nio.ByteBuffer;
import java.util.Scanner;

import static java.lang.System.out;

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
            out.println(ANSI_GREEN + "Host desconhecido!" + ANSI_RESET);
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
                    case ADDFILE -> addFile(out, headerInformation[1]);
                    case DELETE -> deleteFile(out, headerInformation[1]);
                    case GETFILELIST -> getFileList(out);
                    case GETFILE -> getFile(out, headerInformation[1]);
                    case default -> System.out.println("Invalid command!");
                }

                // Wait for the response from server
                 // in.read(byteInput) // Blocking call

            }
        } catch (EOFException eofe){
            out.println(ANSI_GREEN + "EOF:" + ANSI_CYAN + eofe.getMessage() + ANSI_RESET);
        } catch (IOException ioe){
            out.println(ANSI_CYAN + "IO:" + ANSI_CYAN + ioe.getMessage() + ANSI_RESET);
        }
    }

    public ByteBuffer createHeader (final String operation, final String filename) {
        byteOutput = ByteBuffer.allocate(headerSize); // Order is already BIG_ENDIAN
        byteOutput.put(0, request); // Static because the client only send requests
        byteOutput.put(1, operation.getBytes()); // Value of operation in position 1
        byte filenameLength = (byte) filename.length(); // Filename length
        byteOutput.put(2, filenameLength); // Filename length in position 2
        byteOutput.put(3, filename.getBytes()); // Filename in position 3

        return byteOutput;
    }

    public boolean fileExists (final String filename) {
        File file = new File("resources/" + filename);
        return file.exists();
    }

    public void sendFileByPerByte (final String filename) {
        try {
            File file = new File("resources/" + filename); // File to be sent

            byte[] fileContent = new byte[(int) file.length()]; // File content
            FileInputStream fileInputStream = new FileInputStream(file); // File input stream

            // send file content byte by byte
            for (long sizeFile = fileContent.length; sizeFile > 0; sizeFile--) {
                byte b = (byte) fileInputStream.read();
                out.write(b);
            }
        } catch (FileNotFoundException fnfe) {
            out.println(ANSI_GREEN + "File not found:" + ANSI_CYAN + fnfe.getMessage() + ANSI_RESET);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void addFile (DataOutputStream out, final String filename) {
        try {
            if (!this.fileExists(filename)) { System.out.println("File \"" + filename + "\" does not exists!"); }

            out.write(createHeader(ADDFILE, filename).array());
            this.sendFileByPerByte(filename);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public void deleteFile (DataOutputStream out, final String filename) throws IOException {
        try {
            out.write(createHeader(DELETE, filename).array());
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public void getFileList (DataOutputStream out) {
        try {
            out.write(createHeader(GETFILELIST, "").array());
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public void getFile (DataOutputStream out, final String filename) {
        try {
            out.write(createHeader(GETFILE, filename).array());
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}

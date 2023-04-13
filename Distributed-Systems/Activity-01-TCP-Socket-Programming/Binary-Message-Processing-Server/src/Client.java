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

    public static final int successStatusCode = 1;
    public static final int errorStatusCode = 2;

    public static final int headerSize = 1 + 1 + 1 + 256;
    public static final int maxFilenameSize = 256;

    public static ByteBuffer byteInput;
    public static ByteBuffer byteOutput;
    public static final byte request = 1;
    public static String user = "user";

    public static void main(String[] args) throws IOException {
        Socket clientSocket = null;
        Scanner reader = new Scanner(System.in); // ler mensagens via teclado

        // Endereço e porta do servidor
        int serverPort = 6666;
        InetAddress serverAddr = null; // Instância no localhost.
        try {
            serverAddr = InetAddress.getByName("localhost"); // 127.0.0.1
            clientSocket = new Socket(serverAddr, serverPort);

            // cria objetos de leitura e escrita
            DataInputStream in = new DataInputStream( clientSocket.getInputStream());
            DataOutputStream out = new DataOutputStream( clientSocket.getOutputStream());

            while (true) {
                System.out.println(ANSI_CYAN + "Insert the header information's: \n" + ANSI_RESET); // Operation name and filename (if exists);
                String[] headerInformation = reader.nextLine().split(" ");

                if (headerInformation[0].equals("EXIT")) {
                    clientSocket.close();
                    return;
                }

                switch (headerInformation[0]) { // Operation name and filename (if exists);
                    case ADDFILE -> {
                        addFile(out, headerInformation[1]);
                        in.read(byteInput.array()); // Blocking call
                        if (byteInput.get(2) == successStatusCode) {
                            System.out.println(ANSI_GREEN + "File added successfully!" + ANSI_RESET);
                        } else {
                            System.out.println(ANSI_GREEN + "File already exists!" + ANSI_RESET);
                        }
                    }
                    case DELETE -> {
                        deleteFile(out, headerInformation[1]);
                        in.read(byteInput.array()); // Blocking call
                        if (byteInput.get(2) == successStatusCode) {
                            System.out.println(ANSI_GREEN + "File deleted successfully!" + ANSI_RESET);
                        } else {
                            System.out.println(ANSI_GREEN + "File does not exists!" + ANSI_RESET);
                        }
                    }
                    case GETFILELIST -> {
                        getFileList(out, in);
                        in.read(byteInput.array()); // Blocking call
                        if (byteInput.get(2) == successStatusCode) {
                            System.out.println(ANSI_GREEN + "File list received successfully!" + ANSI_RESET);
                            for (int i = 0; i < byteInput.get(4); i++) { // Print file list
                                byte filenameLength = in.readByte();
                                byte[] filename = new byte[filenameLength];
                            }
                        } else {
                            System.out.println(ANSI_GREEN + "File list is empty!" + ANSI_RESET);
                        }
                    }
                    case GETFILE -> {
                        getFile(out, in, headerInformation[1]);
                        in.read(byteInput.array()); // Blocking call
                        if (byteInput.get(2) == successStatusCode) {
                            System.out.println(ANSI_GREEN + "File received successfully!" + ANSI_RESET);
                        } else {
                            System.out.println(ANSI_GREEN + "File does not exists!" + ANSI_RESET);
                        }
                    }
                    default -> System.out.println("Invalid command!");
                }

                // Wait for the response from server
                in.read(byteInput.array()); // Blocking call

                byte response = byteInput.get(0);
                byte operation = byteInput.get(1);
                byte statusCode = byteInput.get(2);


            }
        } catch (EOFException eofe){
            out.println(ANSI_GREEN + "EOF:" + ANSI_CYAN + eofe.getMessage() + ANSI_RESET);
        } catch (IOException ioe){
            out.println(ANSI_CYAN + "IO:" + ANSI_CYAN + ioe.getMessage() + ANSI_RESET);
        } finally {
            clientSocket.close();
            reader.close();
        }
    }

    public static ByteBuffer createHeader(final String operation, final String filename) {
        byteOutput = ByteBuffer.allocate(headerSize); // Order is already BIG_ENDIAN
        byteOutput.put(0, request); // Static because the client only send requests
        byteOutput.put(1, operation.getBytes()); // Value of operation in position 1
        byte filenameLength = (byte) filename.length(); // Filename length
        byteOutput.put(2, filenameLength); // Filename length in position 2
        byteOutput.put(3, filename.getBytes()); // Filename in position 3

        return byteOutput;
    }

    public static void sendFileByPerByte(final String filename) { // Send file byte by byte
        try {
            File file = new File(user + "/" + filename); // File to be sent

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

    public static void addFile (DataOutputStream out, final String filename) {
        try {
            File file = new File(user + "/" + filename); // File to be sent
            if (!file.exists()) { // File does not exist
                System.out.println(ANSI_GREEN + "File does not exists!" + ANSI_RESET);
                return;
            }

            if (filename.length() <= maxFilenameSize) { // Filename size is valid
                ByteBuffer requestHeader = createHeader(ADDFILE, filename); // Create the header
                out.write(requestHeader.array(), 0, requestHeader.limit()); // Send the header
                sendFileByPerByte(filename); // Send the file
            }
            else { System.out.println(ANSI_GREEN + "Filename too long!" + ANSI_RESET); } // Filename too long
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public static void deleteFile (DataOutputStream out, final String filename) throws IOException {
        try {
            out.write(createHeader(DELETE, filename).array());
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public static void getFileList (DataOutputStream out, DataInputStream in) {
        try {
            out.write(createHeader(GETFILELIST, "").array());
            if (in.read(byteInput.array()) == successStatusCode) { // Blocking call
                System.out.println(ANSI_GREEN + "File list received successfully!" + ANSI_RESET);
                for (int i = 0; i < byteInput.get(4); i++) { // Print file list
                    byte filenameLength = in.readByte(); // Blocking call
                    byte[] filename = new byte[filenameLength]; // Filename
                    in.read(filename); // Blocking call
                    System.out.println(ANSI_GREEN + "File " + (i + 1) + ": " + ANSI_CYAN + new String(filename) + ANSI_RESET);
                }
            } else {
                System.out.println(ANSI_GREEN + "Error receiving file list!" + ANSI_RESET);
            }
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public static void getFile (DataOutputStream out, DataInputStream in, final String filename) {
        try {
            out.write(createHeader(GETFILE, filename).array());
            if (in.read(byteInput.array()) == successStatusCode) { // Blocking call
                System.out.println(ANSI_GREEN + "File received successfully!" + ANSI_RESET);
                byte filenameLength = in.readByte(); // Blocking call
                byte[] responseFilename = new byte[filenameLength]; // Filename
                in.read(responseFilename); // Blocking call
                System.out.println(ANSI_GREEN + "File name: " + ANSI_CYAN + new String(responseFilename) + ANSI_RESET);
                byte[] fileContent = new byte[byteInput.get(4)]; // File content
                in.read(fileContent); // Blocking call
                System.out.println(ANSI_GREEN + "File content: " + ANSI_CYAN + new String(fileContent) + ANSI_RESET);
            } else {
                System.out.println(ANSI_GREEN + "Error receiving file!" + ANSI_RESET);
            }
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}

import java.net.*;
import java.io.*;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.nio.file.Paths;
import java.util.*;

// TODO: Use JAVADOC.
// TODO: Create functions for repeated code.
// TODO: Simplify code.
// TODO: Implement log system with some library.

public class ClientThread implements Runnable {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_CYAN = "\u001B[36m";

    public static final int ADDFILE = 1;
    public static final int DELETE = 2;
    public static final int GETFILELIST = 3;
    public static final int GETFILE = 4;

    public static final int inputHeaderSize = 1 + 1 + 1 + 256;
    public static final int addFileResponseHeader = 1 + 1 + 1 + 4;
    public static final int getFileListResponseHeader = 1 + 1 + 1 + 2;
    public static final int getFileResponseHeader = 1 + 1 + 1 + 4;

    public static final int sucessStatusCode = 1;
    public static final int errorStatusCode = 2;

    public static ByteBuffer byteInput;
    public static ByteBuffer byteOutput;

    public static String user = "user";
    DataInputStream in;
    DataOutputStream out;
    Socket clientSocket;

    public ClientThread (Socket clientSocket) {
        try {
            this.clientSocket = clientSocket;
            in = new DataInputStream(clientSocket.getInputStream());
            out = new DataOutputStream(clientSocket.getOutputStream());
        } catch (IOException ioe) {
            System.out.println(ANSI_GREEN + "Connection:" + ANSI_CYAN + ioe.getMessage() + ANSI_RESET);
        }
    }

    @Override
    public void run() {
        try {
            StringBuilder currentRelativePath = new StringBuilder("/"); // Começa com / por ser um servidor linux
            this.createUserDirectory(user, currentRelativePath);

            while (true) {
                byteInput = ByteBuffer.allocateDirect(in.read());

                System.out.println(ANSI_GREEN + "Cliente disse: " + ANSI_RESET);

                int commandID = byteInput.get(0);
                byte filenameLength = byteInput.get(2);
                String filename = new String(byteInput.array(), 3, filenameLength, StandardCharsets.UTF_8);

                switch (commandID) {
                    case ADDFILE -> {
                        System.out.println(ANSI_CYAN + "ADD FILE" + ANSI_RESET);
                        byte[] fileContent = new byte[byteInput.capacity() - 3 - filenameLength];
                        byteInput.get(fileContent, 0, fileContent.length);
//                        this.addFile(filename, fileContent, currentRelativePath);
                    }
                    case DELETE -> {
                        System.out.println(ANSI_CYAN + "DELETE" + ANSI_RESET);
//                        this.deleteFile(filename, currentRelativePath);
                    }
                    case GETFILELIST -> {
                        System.out.println(ANSI_CYAN + "GET FILE LIST" + ANSI_RESET);
                        List<String> fileList = this.getFiles(currentRelativePath.toString());
                        byteOutput = ByteBuffer.allocateDirect(fileList.size() * 256);
                        for (String file : fileList) {
                            byteOutput.put(file.getBytes(StandardCharsets.UTF_8));
                        }
                        out.write(byteOutput.array());
                    }
                    case GETFILE -> {
                        System.out.println(ANSI_CYAN + "GET FILE" + ANSI_RESET);
//                        byte[] fileContent = this.getFile(filename, currentRelativePath);
//                        byteOutput = ByteBuffer.allocateDirect(fileContent.length + 3 + filenameLength);
//                        byteOutput.put((byte) GETFILE);
//                        byteOutput.put((byte) 0);
//                        byteOutput.put(filenameLength);
//                        byteOutput.put(filename.getBytes(StandardCharsets.UTF_8));
//                        byteOutput.put(fileContent);
//                        out.write(byteOutput.array());
                    }
                    default -> System.out.println(ANSI_CYAN + "Unknown command" + ANSI_RESET);
                }

            }

        } catch (IOException e) {
            throw new RuntimeException(e);
        } finally {
            try {
                clientSocket.close();
                System.out.println(ANSI_CYAN + "Thread de comunicação cliente finalizada." + ANSI_RESET);
            } catch (IOException ioe) {
                System.err.println("IOE: " + ioe);
            }
        }
    }

    private void responseHeader (int commandID, int status) {
        byteOutput = ByteBuffer.allocateDirect(inputHeaderSize);
        byteOutput.put((byte) commandID);
        byteOutput.put((byte) status);
        try {
            out.write(byteOutput.array());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    // Create a user folder in order to make all files operation inside that's folder:
    // Operations folder = absolutePath + /user
    public void createUserDirectory(final String user, StringBuilder currentRelativePath) {
        File userDirectory = new File("./".concat(user));
        System.out.println("userDirectory.getAbsolutePath(): " + userDirectory.getAbsolutePath());

        if (!userDirectory.exists()){
            userDirectory.mkdirs();
        }
        currentRelativePath.delete(0, currentRelativePath.length());
        currentRelativePath.append("/");
        currentRelativePath.append(user);
    }

    public String getAbsolutePath () {
        return Paths.get("").toAbsolutePath().toString();
    }
    
    public List<String> getFiles(final String currentRelativePath) throws IOException {
        File[] folder = new File(this.getAbsolutePath().concat(currentRelativePath)).listFiles();
        ArrayList<String> fileList = new ArrayList<>();

        if (folder == null) { return Collections.emptyList(); }

        for (File f : Objects.requireNonNull(folder)) {
            if (!f.isDirectory()) { fileList.add(f.getName()); } 
        }
        return fileList;
    }
}

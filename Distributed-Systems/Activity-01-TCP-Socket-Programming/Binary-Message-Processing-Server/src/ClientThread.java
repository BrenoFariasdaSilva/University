import java.net.*;
import java.io.*;
import java.nio.file.Paths;
import java.util.*;

// TODO: Use JAVADOC
// TODO: Create functions for repeated code
// TODO: Simplify code

public class ClientThread implements Runnable {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_CYAN = "\u001B[36m";
    Socket clientSocket;

    public ClientThread (Socket clientSocket) {
        this.clientSocket = clientSocket;
    }

    @Override
    public void run() {
        try {

        } finally {
            try {
                clientSocket.close();
            } catch (IOException ioe) {
                System.err.println("IOE: " + ioe);
            }
        }
        System.out.println(ANSI_CYAN + "Thread de comunicação cliente finalizada." + ANSI_RESET);
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

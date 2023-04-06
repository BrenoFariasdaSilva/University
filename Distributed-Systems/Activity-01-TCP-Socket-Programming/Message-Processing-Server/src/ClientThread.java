import java.net.*;
import java.io.*;
import java.nio.file.Paths;
import java.util.*;

// TODO: Use JAVADOC
// TODO: Create functions for repeated code
// TODO: Simplify code
// TODO: Put colors on terminal output for better legibility.

public class ClientThread implements Runnable {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_CYAN = "\u001B[36m";
    DataInputStream in;
    DataOutputStream out;
    Socket clientSocket;

    final static String[] preProcessedHashes = {
            "8871f959957ee6ebfd5d585aa03691e7affb6c5c4a2c31b648906ab235645358cd0efba62245f401aa38fddcf7db34169dcf655ae5631a79a5c4fcdf2f9f33df", // breno
            "7aa9c772629c40ccdd9061c0fcf46432c74b64c6ab6dcbda0959953a6f63c2c854b29df07ceaeb96c6034731b7a40db7a4645310c8814d7d8da8c1147e9f3691" // campiolo
    };

    final static String successMessage = "SUCCESS";
    final static String errorMessage = "ERROR";

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
            String buffer = "";
            StringBuilder currentRelativePath = new StringBuilder("/"); // Começa com / por ser um servidor linux
            boolean authenticated = false;

            while (true) {
                buffer = in.readUTF();   /* aguarda o envio de dados */

                System.out.println(ANSI_GREEN + "Cliente disse: " + ANSI_CYAN + buffer + ANSI_RESET);
                if (buffer.equals("EXIT")) { System.out.println(ANSI_GREEN + "CLIENTE FINALIZADO" + ANSI_RESET); break; }

                if (!authenticated) { // User is not authenticated
                    if (buffer.contains("CONNECT")) {
                        authenticated = this.connect(buffer.substring(8), currentRelativePath);
                    } else {
                        out.writeUTF("Forbidden Command! Please connect into your user!");
                    }
                } else { // User is authenticated.
                    if (buffer.contains("CONNECT") ) {
                        out.writeUTF("The user is already logged in!");
                    } else if (buffer.equals("PWD")) {
                        out.writeUTF(this.pwd(currentRelativePath.toString()));
                    } else if (buffer.contains("CHDIR")) {
                        String[] pathValue = buffer.split(" ", 2);
                         this.outputMessage(this.chdir(currentRelativePath, pathValue[1]));
                    } else if (buffer.equals("GETFILES")) {
                        List<String> files = this.getFiles(currentRelativePath.toString());
                        this.multipleOutput(files);
                    } else if (buffer.equals("GETDIRS")) {
                        List<String> folders = this.getDirs(currentRelativePath.toString());
                        this.multipleOutput(folders);
                    } else {
                        out.writeUTF("Invalid input!");
                    }
                }
            }

        } catch (EOFException eofe) {
            System.out.println(ANSI_CYAN + "EOF: " + ANSI_CYAN + eofe.getMessage() + ANSI_RESET);
        } catch (IOException ioe) {
            System.out.println(ANSI_CYAN + "IOE: " + ANSI_CYAN + ioe.getMessage() + ANSI_RESET);
        } finally {
            try {
                in.close();
                out.close();
                clientSocket.close();
            } catch (IOException ioe) {
                System.err.println("IOE: " + ioe);
            }
        }
        System.out.println(ANSI_CYAN + "Thread de comunicação cliente finalizada." + ANSI_RESET);
    }

    public void multipleOutput(List<String> files) throws IOException {
        out.writeUTF(String.valueOf(files.size()));
//        if (files.size() )
        if (files.size() > 0) {
            var builder = new StringBuilder();
            for (int i = 0; i < files.size(); i++) {
                builder.append(files.get(i));
                if (i < files.size() - 1) {
                    builder.append("\n");
                }
            }
            out.writeUTF(builder.toString());
        }
    }

    public void outputMessage (boolean validateConditional) throws IOException {
        if (validateConditional) {
            out.writeUTF(successMessage);
        } else {
            out.writeUTF(errorMessage);
        }
    }

    public boolean authenticate(final String password) {
        for (String preProcessedHash : preProcessedHashes) {
            if (preProcessedHash.equals(password)) { return true; }
        }
        return false;
    }

    public void createUserDirectory(final String user, StringBuilder currentRelativePath) {
        File userDirectory = new File("./" + user);
        if (!userDirectory.exists()){
            userDirectory.mkdirs();
        }
        currentRelativePath.delete(0, currentRelativePath.length());
        currentRelativePath.append("/");
        currentRelativePath.append(user);
//        currentRelativePath.append("/");
    }

    public String getAbsolutePath () {
        return Paths.get("").toAbsolutePath().toString();
    }

    public boolean connect(final String buffer, StringBuilder currentRelativePath) throws IOException {
        String[] loginCredentials = buffer.split(",");

        if (this.authenticate(loginCredentials[1])) {
            this.createUserDirectory(loginCredentials[0], currentRelativePath);
            this.outputMessage(true);
            return true;
        }
        this.outputMessage(false);
        return false;
    }

    public String pwd(String currentRelativePath) throws IOException {
        return currentRelativePath;
    }

    public boolean chdir(StringBuilder currentRelativePath, String folder) {
        File cdFolder = new File(this.getAbsolutePath());

        int lastChar = currentRelativePath.length();
        if (currentRelativePath.lastIndexOf("/") != lastChar) { currentRelativePath.append("/"); }

        if (cdFolder.isDirectory()) {
            currentRelativePath.append(folder);
//            currentRelativePath.append("/");
            return true;
        }

        return false;
    }

    public List<String> getFiles(final String currentRelativePath) throws IOException {
        return this.getAllFiles(currentRelativePath, false);
    }

    public List<String> getDirs(final String currentRelativePath) throws IOException {
        return this.getAllFiles(currentRelativePath, true);
    }

    public List<String> getAllFiles (final String currentRelativePath, final boolean wantDirectory) {
        File[] folder = new File(this.getAbsolutePath().concat(currentRelativePath)).listFiles();
        ArrayList<String> fileList = new ArrayList<>();

        if (folder == null) { return Collections.emptyList(); }

        for (File f : Objects.requireNonNull(folder)) {
            if (f.isDirectory() && wantDirectory) { // True && false ->
                fileList.add(f.getName());
            }
        }

        return fileList;
    }
}

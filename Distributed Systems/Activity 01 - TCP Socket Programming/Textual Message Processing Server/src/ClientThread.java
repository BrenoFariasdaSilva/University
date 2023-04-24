import java.net.*;
import java.io.*;
import java.nio.file.Paths;
import java.util.*;

/***
 *  TCP Socket Programming Activity.
 * @author Breno Farias
 * @subject Distributed Systems
 * @date 16/03/2022
 * @lastUpdate 24/04/2022
 * This file is the server side of the application, which is called by the Server.java file.
 * Here is the implementation of the thread that is created for each client that connects to the server.
 * It's responsible for receiving messages from the client and sending messages to the client.
 * It also validates the user input, just like the Client.java file does, but it also validates the user's password.
 * It's main purpose is to receive commands from the client and execute them.
 */

// TODO: Use JAVADOC
// TODO: Create functions for repeated code
// TODO: Simplify code

public class ClientThread implements Runnable {
    public static final String ANSI_RESET = "\u001B[0m"; // Variavel for reseting terminal output color
    public static final String ANSI_GREEN = "\u001B[32m"; // Variable for changing terminal output color to green
    public static final String ANSI_CYAN = "\u001B[36m"; // Variable for changing terminal output color to cyan
    DataInputStream in;
    DataOutputStream out;
    Socket clientSocket;

    final static String[] preProcessedHashes = { // pre processed hashed for authenticate user in CONNECT command
            "8871f959957ee6ebfd5d585aa03691e7affb6c5c4a2c31b648906ab235645358cd0efba62245f401aa38fddcf7db34169dcf655ae5631a79a5c4fcdf2f9f33df", // breno
            "7aa9c772629c40ccdd9061c0fcf46432c74b64c6ab6dcbda0959953a6f63c2c854b29df07ceaeb96c6034731b7a40db7a4645310c8814d7d8da8c1147e9f3691", // campiolo
            "b0e0ec7fa0a89577c9341c16cff870789221b310a02cc465f464789407f83f377a87a97d635cac2666147a8fb5fd27d56dea3d4ceba1fc7d02f422dda6794e3c" // guest
    };

    final static String successMessage = "SUCCESS";
    final static String errorMessage = "ERROR";

    static String user = "";

    public ClientThread (Socket clientSocket) {
        try {
            this.clientSocket = clientSocket;
            in = new DataInputStream(clientSocket.getInputStream());
            out = new DataOutputStream(clientSocket.getOutputStream());
        } catch (IOException ioe) {
            System.out.println(ANSI_GREEN + "Connection:" + ANSI_CYAN + ioe.getMessage() + ANSI_RESET);
        }
    }

    /*
     * This function is responsible for executing the thread that was created for each client that connects to the server.
     */
    @Override
    public void run() {
        try {
            String buffer = "";
            StringBuilder currentRelativePath = new StringBuilder("/"); // Starts at root directory
            boolean authenticated = false;

            while (true) {
                buffer = in.readUTF();   // Waits for client to send a message

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
                        out.writeUTF("The user is already logged in!"); // User is already logged in
                    } else if (buffer.equals("PWD")) {
                        out.writeUTF(this.pwd(currentRelativePath.toString())); // Prints current directory
                    } else if (buffer.contains("CHDIR")) {
                        String[] pathValue = buffer.split(" ", 2);
                         this.outputMessage(this.chdir(currentRelativePath, pathValue[1])); // Changes directory
                    } else if (buffer.equals("GETFILES")) {
                        List<String> files = this.getFiles(currentRelativePath.toString()); // Gets files from current directory
                        this.multipleOutput(files); // Sends files to client
                    } else if (buffer.equals("GETDIRS")) {
                        List<String> folders = this.getDirs(currentRelativePath.toString()); // Gets folders from current directory
                        this.multipleOutput(folders); // Sends folders to client
                    } else {
                        out.writeUTF("Invalid input!"); // Invalid input
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

    /*
     * This function is responsible for sending multiple messages to the client using the DataOutputStream.
     * @param files - List of files or folders to be sent to the client.
     * @return void
     */
    public void multipleOutput(List<String> files) throws IOException {
        out.writeUTF(String.valueOf(files.size()));

        if (files.size() > 0) {
            var builder = new StringBuilder();
            for (int i = 0; i < files.size(); i++) {
                builder.append(files.get(i));
                if (i < files.size() - 1) { builder.append("\n"); }
            }
            out.writeUTF(builder.toString());
        }
    }

    /*
     * This function is responsible for sending a success or error message to the client using the DataOutputStream.
     * @param validateConditional - Boolean value that determines if the message will be sent or not.
     * @return void
     */
    public void outputMessage (boolean validateConditional) throws IOException {
        if (validateConditional) {
            out.writeUTF(successMessage);
        } else {
            out.writeUTF(errorMessage);
        }
    }

    /*
     * This function is responsible for authenticating the user credentials using the pre-processed hashes.
     * @param password - Password to be authenticated.
     * @return boolean - Returns true if the password is valid, false otherwise.
     */
    public boolean authenticate(final String password) {
        for (String preProcessedHash : preProcessedHashes) {
            if (preProcessedHash.equals(password)) { return true; }
        }
        return false;
    }

    /*
     * This function is responsible for creating a user directory in the server when the user logs in.
     * @param user - User to be created.
     * @param currentRelativePath - Current directory path.
     * @return void
     */
    public void createUserDirectory(final String user, StringBuilder currentRelativePath) {
        File userDirectory = new File("./".concat(user));

        if (!userDirectory.exists()){
            userDirectory.mkdirs();
        }
        currentRelativePath.delete(0, currentRelativePath.length());
        currentRelativePath.append("/");
        currentRelativePath.append(user);
    }

    /*
     * This function is responsible for getting the absolute path of the server.
     * @return String - Returns the absolute path of the server.
     */
    public String getAbsolutePath () {
        return Paths.get("").toAbsolutePath().toString();
    }

    /*
     * This function is responsible for connecting the user to the server.
     * @param buffer - Buffer containing the user credentials, which are separated by a comma.
     * @param currentRelativePath - Current directory path.
     * @return boolean - Returns true if the user is connected, false otherwise.
     * @comment - The user credentials is like this: user,password
     */
    public boolean connect(final String buffer, StringBuilder currentRelativePath) throws IOException {
        String[] loginCredentials = buffer.split(",");

        if (this.authenticate(loginCredentials[1])) {
            user = loginCredentials[0];
            this.createUserDirectory(loginCredentials[0], currentRelativePath);
            this.outputMessage(true);
            return true;
        }
        this.outputMessage(false);
        return false;
    }

    /*
     * This function is responsible for returning the working directory (PWD).
     * @param currentRelativePath - Current directory path.
     * @return String - Returns the current directory path.
     */
    public String pwd(String currentRelativePath) throws IOException {
        return currentRelativePath;
    }

    /*
     * This function is responsible for changing the working directory (CHDIR).
     * @param currentRelativePath - Current directory path.
     * @param folder - Folder to be changed.
     * @return boolean - Returns true if the folder is changed, false otherwise.
     * @comment - The folder can be ".", ".." or a folder name.
     * @comment - The folder "." is the current directory.
     * @comment - The folder ".." is the parent directory.
     * @comment - The folder name is a folder inside the current directory.
     * @comment - currentRelativePath is a StringBuilder object, which stores something like this: /user/folder
     */
    public boolean chdir(StringBuilder currentRelativePath, String folder) throws IOException {
        if (folder.equals(".")) { return true; }
        else if (folder.equals("..")) {
            if (currentRelativePath.toString().equals("/" + user)) { return false; } else {
                currentRelativePath.replace(currentRelativePath.lastIndexOf("/"), currentRelativePath.length(), "");
                return true;
            }
        }

        if (currentRelativePath.lastIndexOf("/") != currentRelativePath.length()) { currentRelativePath.append("/"); }

        if (this.getDirs(currentRelativePath.toString()).contains(folder)) {
            currentRelativePath.append(folder);
            return true;
        }

        return false;
    }

    /*
     * This function is responsible for returning the list of files or folders in the current directory (DIR).
     * @param currentRelativePath - Current directory path.
     * @return List<String> - Returns a list of files or folders in the current directory.
     */
    public List<String> getFiles(final String currentRelativePath) throws IOException {
        return this.getAllFiles(currentRelativePath, false);
    }

    /*
     * This function is responsible for returning the list of folders in the current directory (DIR).
     * @param currentRelativePath - Current directory path.
     * @return List<String> - Returns a list of folders in the current directory.
     */
    public List<String> getDirs(final String currentRelativePath) throws IOException {
        ArrayList<String> dirsList = (ArrayList<String>) this.getAllFiles(currentRelativePath, true);
        dirsList.add(".");
        dirsList.add("..");
        return dirsList;
    }

    /*
     * This function is responsible for returning the list of files or folders in the current directory.
     * @param currentRelativePath - Current directory path.
     * @param wantDirectory - Boolean value that determines if the list will contain folders or files.
     * @return List<String> - Returns a list of files or folders in the current directory.
     */
    public List<String> getAllFiles (final String currentRelativePath, final boolean wantDirectory) {
        File[] folder = new File(this.getAbsolutePath().concat(currentRelativePath)).listFiles();
        ArrayList<String> fileList = new ArrayList<>();

        if (folder == null) { return Collections.emptyList(); }

        for (File f : Objects.requireNonNull(folder)) {
            if (f.isDirectory() && wantDirectory) {
                fileList.add(f.getName());
            } else if (!f.isDirectory() && !wantDirectory) {
                fileList.add(f.getName());
            }
        }
        return fileList;
    }
}
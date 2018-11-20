
import javax.swing.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;


/**
 * Trivial client for the date server.
 */
public class Client {
    private String serverAddress;
    private Socket socket;
    private BufferedReader in;
    private PrintWriter out;
    /**
     * Runs the client as an application.  First it displays a dialog
     * box asking for the IP address or hostname of a host running
     * the date server, then connects to it and displays the date that
     * it serves.
     */
    public Client(String address, int port) throws IOException {
        // Make connection and initialize streams
        serverAddress = address;
        socket = new Socket(serverAddress, port);
        out = new PrintWriter(socket.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(
                socket.getInputStream()));

    }

    public String getData() {
        /*
        String answer = "no answer";
        try {
            BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            answer = input.readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return answer;
        */
        try {
            return in.readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return "failed to get a message";
    }

    public void sendData(String msg){
        out.println(msg);
    }

}

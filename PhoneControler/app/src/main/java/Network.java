import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class Network {

    private String serverAddress;
    private Socket socket;
    private BufferedReader in;
    private PrintWriter out;

    private Network(String address, int port){
        serverAddress = address;
        try {
            socket = new Socket(serverAddress, port);
            out = new PrintWriter(socket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(
                    socket.getInputStream()));
        } catch (IOException e) {
            e.printStackTrace();
        }

    }


    public String getData() {
        try {
            return in.readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return "failed to get a message";
    }




}

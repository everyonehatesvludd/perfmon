import java.io.DataInputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * @author vregi, 1/8/2025
 */
public class MetricsServer {

    public static void main(String[] args) {
        if (args.length < 1){
            System.err.println("Usage: java <Class> <port>");
            System.exit(1);
        }

        try (
                ServerSocket server = new ServerSocket(Integer.parseInt(args[0]));
                Socket socket = server.accept();
                // TODO: Issue with input stream
                DataInputStream in = new DataInputStream(socket.getInputStream());
        ){
            long clientInput;
            while (in.available() > 0) {
                clientInput = in.read();
                System.out.println("Processes: " + clientInput);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }


}

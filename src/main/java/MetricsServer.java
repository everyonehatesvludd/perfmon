import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
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
                BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()))
        ){
            String clientInput;
            while ((clientInput = in.readLine()) != null){
                System.out.println(clientInput);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }


}

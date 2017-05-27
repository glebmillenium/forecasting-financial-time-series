package repo;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;

/**
 * run Метод запускающий реализацию сокет соединения по протоколу TCP в
 * параллельном треде
 *
 * @author glebmillenium
 */
public class ConnectWithRemoteManagerSocket extends Thread {

    private int serverPort;
    private String address;
    private Socket socket;
    private DataInputStream in;
    private DataOutputStream out;

    public ConnectWithRemoteManagerSocket() throws IOException {
        this.serverPort = 3425;
        this.address = "127.0.0.1";
        this.socket = new Socket(InetAddress.getByName(address), serverPort);
        InputStream sin = socket.getInputStream();
        OutputStream sout = socket.getOutputStream();
        in = new DataInputStream(sin);
        out = new DataOutputStream(sout);
    }

    public ConnectWithRemoteManagerSocket(String ip, int port) throws IOException {
        this.serverPort = port;
        this.address = ip;
        socket = new Socket(InetAddress.getByName(address), serverPort);
        InputStream sin = socket.getInputStream();
        OutputStream sout = socket.getOutputStream();
        in = new DataInputStream(sin);
        out = new DataOutputStream(sout);
    }

    public ConnectWithRemoteManagerSocket(String ip, int port, boolean check) throws IOException {
        this.serverPort = port;
        this.address = ip;
        socket = new Socket(InetAddress.getByName(address), serverPort);
        InputStream sin = socket.getInputStream();
        OutputStream sout = socket.getOutputStream();
        in = new DataInputStream(sin);
        out = new DataOutputStream(sout);
    }

    /**
     * run Метод запускающий реализацию сокет соединения по протоколу TCP в
     * параллельном треде
     *
     */
    @Override
    public void run() {
        try {
            String answer;
            while (true) {
                answer = sendMessage("--opcode", in, out);
                Integer.parseInt(CppToJavaString(answer));
                Thread.sleep(2500);
            }
        } catch (Exception x) {
            System.out.println(x.toString());
        }
    }

    private String CppToJavaString(String strcpp) {
        String result = "";
        for (int i = 0; i < strcpp.length(); i++) {
            if (strcpp.charAt(i) == '\0') {
                break;
            }
            result += strcpp.charAt(i);
        }
        return result;
    }

    public static String sendMessage(String text, DataInputStream in,
            DataOutputStream out) throws IOException, InterruptedException {

        out.write((text + '\0').getBytes("UTF-8"));
        out.flush();
        byte[] b = new byte[1024];
        in.read(b);
        String answer = new String(b, "UTF-8");
        return answer;
    }

    /**
     * sendMessage - отправка сообщения серверу
     *
     * @param text
     * @param in
     * @param out
     * @param sizeByte
     * @return
     * @throws IOException
     * @throws InterruptedException
     */
    public static String sendMessage(String text, DataInputStream in,
            DataOutputStream out, int sizeByte) throws IOException, InterruptedException {
        out.write((text + '\0').getBytes("UTF-8"));
        out.flush();
        byte[] b = new byte[sizeByte];
        in.read(b);
        String answer = new String(b, "UTF-8");
        return answer;
    }

    public void stopping() {
        this.stop();
    }

    public DataInputStream getDataInputStream() {
        return this.in;
    }

    public DataOutputStream getDataOutputStream() {
        return this.out;
    }
}

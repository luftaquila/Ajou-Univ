package external_input;
import java.util.HashMap;

public class machine {
	private machine() { }

	public static final HashMap<Integer, String> machine_port = new HashMap<Integer, String>();
	static {
		machine_port.put(1,"VGA");
		machine_port.put(2,"VGA");
		machine_port.put(3,"DVI");
		machine_port.put(4,"DVI");
		machine_port.put(5,"HDMI");
		machine_port.put(6,"HDMI");
		machine_port.put(7,"HDMI");
		machine_port.put(8,"DP");
		machine_port.put(9,"DP");
	}
}

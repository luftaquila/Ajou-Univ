package external_input;
import static external_input.machine.machine_port;
import external_input.module;

public class external_input implements module {
	private int port_number;
	private String input_type;

	public int getPort_number() {
		return port_number;
	}
	public void setPort_number(int port_number) {
		this.port_number = port_number;
	}
	public String getInput_type() {
		return input_type;
	}
	public void setInput_type(String input_type) {
		this.input_type = input_type;
	}
	public void checkInput_type(int port_number, String input_type) {
		if(machine_port.get(port_number).toString() == input_type) {
			System.out.println("Port "  + port_number + " is Successfully Connected");
		}
		else System.out.println("Port "  + port_number + " is a different type");
	}
	public void print() {
		if(machine_port.get(port_number).toString() == input_type) {
			System.out.println("Port "  + port_number + " is working correctly");
		}
		else if(port_number >= 5 && port_number <= 9) {
			System.out.println("Port "  + port_number + " is not working");
		}
	}
}

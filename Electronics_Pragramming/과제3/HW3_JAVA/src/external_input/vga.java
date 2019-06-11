package external_input;
import external_input.external_input;

public class vga extends external_input {
	public vga(int port_number, String input_type) {
		checkInput_type(port_number, input_type);
		setPort_number(port_number);
		setInput_type(input_type);
	}
}

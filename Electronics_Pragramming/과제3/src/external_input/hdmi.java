package external_input;
import external_input.external_input;

public class hdmi extends external_input{
  public hdmi(int port_number, String input_type) {
		setPort_number(port_number);
		setInput_type(input_type);
    checkInput_type();
	}
}

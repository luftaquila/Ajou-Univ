import java.util.ArrayList;
import external_input.*;

public class main {

	public static void main(String[] args) {
		ArrayList<external_input> inputs = new ArrayList<external_input>();

		vga input1 = new vga(1, "VGA");
		dvi input2 = new dvi(5, "DVI");
		dvi input3 = new dvi(3, "DVI");
		hdmi input4 = new hdmi(7, "HDMI");
		dp input5 = new dp(8, "VGA");
		dp input6 = new dp(9, "DP");

		inputs.add(input1);
		inputs.add(input2);
		inputs.add(input3);
		inputs.add(input4);
		inputs.add(input5);
		inputs.add(input6);

		System.out.print("\n\n");
		for (external_input input: inputs) {
			input.print();
		}
	};
}

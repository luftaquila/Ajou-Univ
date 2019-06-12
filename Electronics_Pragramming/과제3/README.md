전자공학프로그래밍 과제 3 보고서
=============================
> 전자공학과  
201820908 오병준  
개발 환경 : IJava Jupyter Kernel with JDK 11.0.2

## 1. 개발 요구 사항  
외부입력 통제 프로그램 개발

### 1. 사양
* 포트에 외부 입력을 연결
  * 외부입력 타입 `VGA`, `DVI`, `HDMI`, `DP`
  * 포트 9개

### 2. 프로그램 구조
#### 1. 인터페이스
1. module.java  
    * checkInput_type(int, String) : 해당 포트와 연결된 외부 입력의 종류가 일치하는지 확인.
    * print() : 해당 포트가 정상 작동중인지 확인.

#### 2. 클래스
1. main.java  
메인 메소드를 포함하는 클래스
    <br>
1. machine.java  
각 포트의 정상 입력 타입 정의
    <br>
1. external_input.java  
각 포트 타입 클래스가 상속할 외부 입력 클래스 정의
    * getPort_number(), getInput_type() : 해당 인스턴스의 포트 번호 및 입력 타입을 받아오는 메소드
    * setPort_number(), setInput_type() : 해당 인스턴스의 포트 번호 및 입력 번호를 설정하는 메소드
    * checkInput_type() : 해당 인스턴스가 올바른 포트에 연결되었는지 확인하는 메소드
    * print() : 해당 인스턴스가 올바른 포트에 연결되어 정상 작동하는지 확인하는 메소드
    <br>
1. dp.java, dvi.java, hdmi.java, vga.java  
`external_input` 클래스를 상속받아 지정된 포트 번호와 입력 타입 정의

## 2. 코드 분석


```JAVA
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
```
machine.java에서 `machine_port` 해쉬맵에 1 ~ 9번 포트와 정상 입력 타입을 정의한다.

* * * * *

```JAVA
import static external_input.machine.machine_port;
import external_input.module;
public class external_input implements module {
	private int port_number;
	private String input_type;

	public int getPort_number() { ... }
	public void setPort_number(int port_number) { ... }
	public String getInput_type() { ... }
	public void setInput_type(String input_type) { ... }
	public void checkInput_type() { ... }
	public void print() { ... }
}
```
external_input.java에서 인터페이스 `module`을 상속한 external_input 클래스를 정의하고, 속성 및 메소드를 정의한다.  
추상 메소드 `checkInput_type()`과 `print()`를 구현한다.
```JAVA
public void checkInput_type() {
  int port_number = getPort_number();
  String input_type = getInput_type();

  if(machine_port.get(port_number).toString() == input_type) {
    System.out.println("Port "  + port_number + " is Successfully Connected");
  }
  else System.out.println("Port "  + port_number + " is a different type");
}
```
1. getPort_number()와 getInput_type()을 이용해 인스턴스의 포트 번호 및 입력 타입 정보를 얻어와 저장한다.
1. machine_port.get(port_number).toString()를 통해 해당 포트의 정상 입력 타입이 무엇인지 확인하고, 해당 인스턴스의 입력 타입 속성과 같다면 정상적으로 연결되었음을 알린다.
1. 다르다면, 입력 타입이 다름을 알린다.

```JAVA
public void print() {
  int port_number = getPort_number();
  String input_type = getInput_type();

  if(machine_port.get(port_number).toString() == input_type) {
    System.out.println("Port "  + port_number + " is working correctly");
  }
  else if(port_number >= 5 && port_number <= 9) {
    System.out.println("Port "  + port_number + " is not working");
  }
}
```
1. `getPort_number()`와 `getInput_type()`을 이용해 인스턴스의 포트 번호 및 입력 타입 정보를 얻어와 저장한다.
1. *machine_port.get(port_number).toString()* 를 통해 해당 포트의 정상 입력 타입이 무엇인지 확인하고, 해당 인스턴스의 입력 타입 속성과 같다면 정상적으로 작동 중임을 알린다.
1. 포트 연결이 잘못된 경우, 5 ~ 9번 HDMI와 DP 포트일 때만 작동하지 않음을 알린다.

* * * * *
```JAVA
vga input1 = new vga(1, "VGA");
dvi input2 = new dvi(5, "DVI");
dvi input3 = new dvi(3, "DVI");
hdmi input4 = new hdmi(7, "HDMI");
dp input5 = new dp(8, "VGA");
dp input6 = new dp(9, "DP");
```
main.java에서 input1부터 input6까지 총 6개의 외부 입력에 대해 연결 포트 및 종류를 결정하고 인스턴스를 생성한다.

* * * * *
```JAVA
package external_input;
import external_input.external_input;

public class vga extends external_input {
	public vga(int port_number, String input_type) {
		setPort_number(port_number);
		setInput_type(input_type);
		checkInput_type();
	}
}
```
1. vga.java에서 `external_input` 클래스를 상속해 `vga` 클래스를 정의한다.
1. `vga` 클래스의 생성자를 정의하고, 파라미터로 포트 번호와 입력 타입을 받아 저장한다.
1. `external_input` 에서 상속한 `setPort_number()`와 `setInput_type()` 메소드를 이용해 생성한 인스턴스의 포트 번호 및 입력 타입을 지정한다.
1. `checkInput_type()` 메소드를 이용해 입력이 올바르게 이루어졌는지를 검증한다.
<br><br>
1. dp, dvi, hdmi 클래스 또한 마찬가지로 `external_input` 클래스를 상속해 생성자를 정의한다.

* * * * *
```JAVA
ArrayList<external_input> inputs = new ArrayList<external_input>();

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
```
1. 배열 `inputs`를 생성해 input1 ~ input6의 입력 인스턴스를 각 요소에 저장한다.
1. 각 인스턴스에 대해 `print()` 메소드를 호출해 동작 상태를 점검한다.

## 3. 실행 결과 분석
### I. 출력
![output](/Electronics_Pragramming/과제3/images/output.png)  

생성자를 통해 각 인스턴스를 생성하면서 호출된 `checkInput_type()` 메소드의 출력이 해당 인스턴스의 입력 유효성을 점검한다.  
HDMI 포트인 5번에 연결된 DVI, DP 포트인 8번에 연결된 VGA가 잘못 연결되었음을 알 수 있다.  

main 메소드에서 호출된
```JAVA
for (external_input input: inputs) {
  input.print();
```
에서 각 포트의 동작 상태를 점검한다.
잘못 연결된 5번, 8번 포트가 작동하지 않음을 확인할 수 있다. 두 포트 모두 잘못 연결됐을 시 이를 알려야 하는 HDMI, DP 포트이므로, 출력이 발생한다.

## 4. 전체 코드
![main](/Electronics_Pragramming/과제3/images/main.png)  
![machine](/Electronics_Pragramming/과제3/images/machine.png)  
![external_input](/Electronics_Pragramming/과제3/images/external_input.png)  
![instances](/Electronics_Pragramming/과제3/images/instances.png)  
![module](/Electronics_Pragramming/과제3/images/module.png)  

# RTOS (Real Time OS)

## RTOS와 NON-OS의 차이

지금까지 코딩한 방식은 single thread (main 하나에 while문 돈다)

OS로 넘어오게 되면 multi-thread 방식이며, thread가 독립적으로 동작하는 것 처럼 보이게 된다.


## Program vs Process vs Thread

### Program
메모리에 실행을 위해 load 되지 않은 *.exe 파일 그 자체

### Process
프로그램을 실행한 순간 *.exe file은 메모리에 공간을 할당받음. 이상태의 프로그램을 프로세스라고 한다.  
![](image.png)  
위 그림은 프로세스들이 운영체제로부터 별도의 메모리 공간을 할당받은 모습이다.  

### Thread
프로세스를 여러단위로 나눈 것

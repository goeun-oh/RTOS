# RTOS (Real Time OS)

## RTOS와 NON-OS의 차이

지금까지 코딩한 방식은 single thread (main 하나에 while문 돈다)

OS로 넘어오게 되면 multi-thread 방식이며, thread가 독립적으로 동작하는 것 처럼 보이게 된다.

| non OS | RTOS |
|-------|------|
|thread가 없다 | thread가 있다.|
|signle thread | multi thread|
|super Loop 형태의 programming 구조 | 각 thread에서 독립적인 programming 방식|

---

**non-RTOS**  

![]({D9876EE0-2E75-4DE6-86EB-54413F1378BB}.png)
```c
int main(){
    while(1){
        listner()
        controller()
        presenter()
    }
}
```

**RTOS**  

![]({DC113C62-9107-44C7-860C-A6D5AA34FBC8}.png)  

```c
int main(){
    thread1_start(); //listener
    thread2_start(); //controller
    thread3_start(); //presenter
}
```

timer interrupt가 tick을 발생시켜 thread를 전환하는 역할을 한다.
FND 동작하는 방식과 비슷


**RTOS는 시간적으로 우선순위가 있는 할당방식**  
우선순위가 높은 thread가 있다면 우선 순위가 있는 thread를 먼저 동작시킨다.

***stm32CubeIDE에 free RTOS가 내장되어있다***

![]({652BF389-7417-4854-8976-75C140A3F407}.png)

CMSIS OS는 ARM 사에서 제공해준다.

Free RTOS는 Kernel.

>회사에서 Free RTOS를 사용할지 어떤 OS를 사용할지 모른다.  
하지만 **RTOS 동작 개념, 특성, 주의사항**은 같다.  
단지 안의 Kernel 동작방식이 다를 뿐이다.

## Program vs Process vs Thread

### Program
메모리에 실행을 위해 load 되지 않은 `*.exe` 파일 그 자체

### Process
프로그램을 실행한 순간 `*.exe` file은 메모리에 공간을 할당받음. 이상태의 프로그램을 프로세스라고 한다. 

![](image.png)  

위 그림은 프로세스들이 운영체제로부터 별도의 메모리 공간을 할당받은 모습이다.  

### Thread
프로세스를 여러단위로 나눈 것

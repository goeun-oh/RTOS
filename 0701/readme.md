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

## Word
Register Size  
Register가 한 번에 처리할 수 있는 양

64bit 컴퓨터: Register가 한 번에 처리할 수 있는 양이 64bit

# 초기 설정

## Free RTOS 선택  

![]({05D00F4E-C384-419B-93B5-6C655E602F4C}.png)

## CMSIS V1 선택  

![]({BF75D103-58DB-4DE2-8551-D62AEF6D6799}.png)

## ADD Task 하기
![]({56937CB8-1451-4A3D-B555-79DDB7E6F173}.png)

### 스택 사이즈
![]({F122D4C9-3656-4304-93E0-6E0344125A39}.png)

해당 thread가 차지하는 STACK 사이즈.
현재 ARM Core는 4byte 이므로 STACK 은 128X4byte가 된다.

### 우선순위

![]({52F46B01-1445-4B83-96FE-9B13A643D840}.png)  

위에서 아래로 갈수록 우선순위가 높아짐

### 함수이름
![]({F3B40E71-B6A2-42AD-B946-E27E9B2A11F2}.png)

이렇게 설정하기!
![]({DCE7E220-02F8-42A3-9038-312D35AA688B}.png)


이렇게 생성하면 WARNING이 하나 뜬다.  

![]({83EFF147-65D7-4DC6-AD30-A1A1005FB1E0}.png)

1.RTOS도 SysTick을 사용하여 interrupt를 발생시키게 되는데, Systick은 HAL이 사용중임
따라서 HAL이 Systick을 사용하지 않게 바꿔야함

따라서 다시 돌아와서 SYS의 Timebase Source를 TIM11로 변경하자.  

![]({9F03DAFE-E9D5-4198-B600-199DA2D7CE0E}.png)


2.USE_NEWLIB_REENTRANT 설정 필요  
현재: newlib는 STM32에서 사용하는 C 라이브러리, 기본적으로 비재진입성 (non-reentrant)

문제: RTOS를 쓰면 여러 쓰레드가 동시에 printf 같은 C 라이브러리 함수를 사용할 수 있는데, 이때 충돌이 날 수 있음

해결: USE_NEWLIB_REENTRANT 옵션을 활성화하면, 라이브러리를 재진입 가능하게 만들어줌


![]({0966B239-7AB8-428A-8E8D-9CF9AED75E94}.png)


# Thread

```c
osThreadId defaultTaskHandle;
osThreadId myLed1Handle;
osThreadId myLed2Handle;
osThreadId myLed3Handle;
```

thread를 만들면 메모리에 STACK memory 공간이 생긴다. (각각 독립적인)

![]({A5967BCD-1BC4-4A6D-B6DE-C0D3337273A9}.png)

non-OS프로그램에서는 메모리 공간 맨 위에서 stack pointer가 내려와서 다 공유했었음.  
이제는 thread별로 stack pointer가 내려와서 독립적으로 자신만의 stack 공간을 사용  
각 Thread가 자신만의 Stack을 가지게 되어 안정적인 멀티태스킹이 가능해짐

thread가 돌아가며 CPU를 점유함 -> `스케줄링`

스케줄을 정해주는 애 -> `스케줄러`


Thread를 Context라고 함

context가 CPU 점유 변경 -> context switching

***context switching을 scheduler가 해준다!!***

FSM 상태 변화도 context switching 의 한 종류


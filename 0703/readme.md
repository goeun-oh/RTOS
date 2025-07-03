# Process와 Thread 차이

![]({52FD29E2-AF01-4528-8668-6E0A080FE1A8}.png)  

한 Thread가 다른 Thread의 stack에 접근 불가 (접근하면 해킹임)


1Process와 2Process의 메모리 공간은 별개로 존재.(독립적인 메모리 공간)  

![]({5D948B06-61DC-4D69-B32C-7A0894071872}.png)  

Process1에서 Process2로 접근하는 것을 허용해주는 합법적인 방법이 `디버거툴`임  

> 임베디드 시스템은 보통 single Process에 multi-thread.
여기에 linux를 올린다하면 보통 multi-Process에 multi-thread


## IPC

Inter Process Communication (프로세스간 통신)
Process 1에서 Process 2에 메시지를 보내는 방법이 IPC가 되겠다.

예시) TCP, UDP..

프로토콜은 데이터를 주고받을 때 어떤 순서, 어떤 형식, 어떤 의미를 가질지 약속하는 것




## UI와 Processing 코드 분리해야한다.

스파게티 코드를 피할 것

### "UI와 Processing을 분리한다"는 뜻

- UI (User Interface): 화면에 보여지는 것 + 사용자가 직접 조작하는 부분
- Processing (처리 로직): 실제로 일을 처리하는 코드

만약 UI와 처리 로직이 한 코드에 섞여 있으면
UI를 바꾸려고 해도 로직이 엉켜서 수정하기 어렵다.
재사용이 어렵다.
테스트가 힘들다.
유지보수가 복잡해진다.

> 따라서 UI는 UI만, 처리 로직은 처리 로직만 담당하도록 역할을 구분하는 것이 좋다.


# 기존 모델을 Listener, Controller, Presenter로 확장하자


# message Queue와 Mail Queue의 차이

![]({94BEFA42-F3B8-4912-8DCC-6D8003CCDC7D}.png)

동적할당이 계속 유지되는 현상을 "메모리 leak"이라고 한다. (메모리 다 사용하고 반환안해서 생기는 일)

- Message Queue는 값을 집어넣을때 사용
- Mail Queue는 포인터 집어넣을때 사용


![]({2EDA04DF-F603-49C0-8D31-BEDA1AA524C6}.png)


![]({D5C9668B-0625-4997-9FCF-C036BECBC5B0}.png)  

![]({895DBE8F-1AEE-43A9-AD96-6C8B3F4A3C2C}.png)  

![]({A66ED62A-E189-4C76-901C-E05B24662388}.png)  


osMailGet을 하면 스택의 head, tail 포인터만 관리하게 된다. (실제로 tail pointer가 +1 증가하며 pop)

![]({B70DA561-FDEE-426D-B8EC-C0F0F30A7910}.png)

osMailFree를 하게되면 동적할당한 메모리 반납.



# Watch 추가

![]({1ABA3F3E-A126-463F-8D04-33AED9953E3C}.png)



# 시간 조정기능 추가

![]({9F84614D-65D6-4035-841A-2E6DFA647753}.png)

Normal 상태와 Modify 상태로 나뉜다.

# 숙제
![]({3E42EE75-829A-46C1-99A3-8979D2109AF5}.png)
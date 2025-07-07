
![]({AC5216FE-7D24-42AE-AC13-A40E2C3B110D}.png)  

새로운 보드

CPU가 처리하는 속도는 `480Mhz`

캐시메모리가 있어서 좀 더 빠르다. (d cache(data cache), i cache(instruction cache))  

16 Kbytes of data and 16 Kbytes of instruction cache  

![](image.png)  

# DCMI

Data Camera Interface  

Camera 영상처리를 위한 카메라 모듈이 HW 적으로 탑재되어있다.  
DCMI의 CLK은 AHB2 bus에 연동되어 `240MHz`로 동작한다.  
APB는 `120MHz`로 동작.  

![]({E6BE337B-BA04-4B04-9B19-27598493AAC3}.png)  

# MPU (Memory Protection Unit)

MPU 설정이 필요함

AXI-SRAM 사이즈가 512KB  
RAM Area는 나누어져 있다.  

![]({EA5ED18A-FE49-44C0-9360-2DA0343A2E0D}.png)

CPU가 480MHz 인데 나머지 버스들 클럭이 훨씬 느리다.
따라서 캐시가 중간 버퍼 역할을 해주어 480MHz 로 무사히 동작할 수 있도록 해준다.

# DMA (Direct Memory Access)

D Cache는 CPU 전용 고속 임시 저장소.
DMA는 CPU를 대신해서 메모리에 접근하여 메모리 read/write을 수행한다. 
DMA는 Data Cache에 접근이 불가하고 오직 RAM에만 접근한다.

# FMC

DRAM 연동하는 모듈

# LCD 추가
SPI 로 나가는 clk 속도 100MHz로 변경
![](image-1.png)
# Maze-Project
본 프로젝트는 출발점부터 도착점까지의 경로가 하나 뿐인 완전미로를 Eller`s Algorithm 을 이용해 구현하고
OpenFrameWorks 를 이용해 GUI를 구축한다. 또한 DFS 방식과 BFS 방식으로 미로를 탐색하여 최적 경로를 구하여 비교해본다.

# 실행환경
1. OS : Windows 10
2. OpenFrameWorks 필요
3. Visual studio 2019 버전 이상에서 빌드 하길 추천
4. *.maz(미로 파일 필요)

# How to run
VisualStudio 환경에서 빌드하여 실행한다. *.maz 미로 파일은 make_maze 프로젝트를 이용해 만들 수 있다. 
프로그램 실행 후 .maz 파일을 열어 완전미로를 그래픽으로 구현할 수 있다. 

# 실행예시

![image](https://user-images.githubusercontent.com/70252973/124463970-9358bd80-ddce-11eb-8cd4-d1c676acce38.png)

maze.maz 파일을 이용해 그래픽으로 구현한 완전미로

![image](https://user-images.githubusercontent.com/70252973/124465752-bc7a4d80-ddd0-11eb-89d0-18764997000a.png)

D 키를 누르면 DFS 방식으로 경로를 탐색하고, B 키를 누르면 BFS 방식으로 경로를 탐색한다.
초록색경로가 탐색한 모든 경로이고, 빨간색이 출발점부터 도착점까지의 경로이다.
완전미로의 경로 찾기에는 DFS 방식이 유리한 것을 확인 할 수 있다.


![image](https://user-images.githubusercontent.com/70252973/124465880-e9c6fb80-ddd0-11eb-953c-2c9200be5c14.png)

미로의 크기를 매우 크게 만들어 비교하면 성능 차이를 더 확실하게 확인 할 수 있다.






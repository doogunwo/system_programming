system 함수는 쉘 명령이 실행되도록 하는데, 예를 들면, system("ls -la") 을
호출하면, 현재 디렉토리의 파일들을 나열해 준다. 이와 같은 기능을 수행하는
함수를 직접 구현하여 보자. 또, 이 함수를 이용하는 예제 프로그램을 통해서
“a.out ls -la" 와 같이 명령이 잘 동작하도록 해 보자.
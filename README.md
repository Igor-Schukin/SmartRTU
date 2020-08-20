# SmartRTU project  
- [About](#about)
- [How to run project](#how-to-run-project)
- [License](#license)  
- [Contributors](#contributors)  
# About project  
Student bulletin board for displaying lectures, weather, time and real-time announcements. Written in C/C++ using the OpenVG graphics library, working machine is Raspberry Pi on Raspbian OS.  
Maintained mostly by DF RTU students.
# How to run project  
How to run:  
0)IMPORTANT!!! check if you did [THIS](https://github.com/RazdolbayOne/GuidesPull)   
1)enter into ${PROJECT_DIR}/build   
```shell  
$ cd build
```  
2)run in ${PROJECT_DIR}/build   
```shell  
$ cmake ..
```  
3)run in ${PROJECT_DIR}/build  
```shell  
$ make
```  
4)back to ${PROJECT_DIR} dir  
```shell
$ cd ..
```  
5)Run exe  
```shell  
$ ./infoboard
```  
inf)if needed "reliese" build ,uncomment  in ${PROJECT_DIR}/CMakeLists.txt line 14 by default it is in reliese mode  
# License  
UNDER MIT [license](LICENSE)  

# Contributors  
year when left project...............Name...............deserts  
2020 - RazdolbayOne - Check v1.1.0 reliese to see its work 
2020 - Alfred.L - Creator of REST server (now server on toddler state)  
# Project_structure  
<img src="https://imgur.com/b63PIkS.png" ></img> 

# DEPENDECY lib GRAPH  
<img src="https://imgur.com/Ofp4oJY.png" ></img> 
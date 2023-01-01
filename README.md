# Chess Engine



## Setup
I chose to dockerize this project, so we use the docker container to build and run the project.
You may need to download Eigen headers, so the language server does not scream at you. The added bonus is that the docker container manages the deps and libraries!

C++ Eigen library for matrix and vector math: https://eigen.tuxfamily.org/index.php?title=Main_Page.

### Build Docker Image 
Use whatever image name and tag I choose to use nnue:latest
```
DOCKER_BUILDKIT=1 docker build . -t nnue:latest
```
### Launch Docker Container
if 'pwd' is the project root:
```
docker run -it -v $(pwd):/engine_nnue/ nnue <COMMAND> 
```
I like to use 'bash' to launch an interactive bash. 'make' works as well 

**TODO**: add wrapping script, so there will be no need to type long docker run command
#include "messenger.hpp"
#include "dummy/blank_scenegraph.hpp"
#include <chrono>
#include <iostream>

std::chrono::duration<double> benchmark_time(void *(*function)()) {
	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
	(*function)();
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

	return std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
}

int s2cpipe[2];
int c2spipe[2];

void client(int readFD, int writeFD) {
	printf("Client Started\n");

	StardustXR::BlankScenegraph blankScenegraph;
	StardustXR::Messenger messenger(readFD, writeFD, &blankScenegraph);

	flexbuffers::Builder fbb;
	fbb.String("Echo test");
	fbb.Finish();
	std::vector<uint8_t> flexbuffer = fbb.GetBuffer();

	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
	messenger.executeRemoteMethod("/test", "echo", flexbuffer);
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

	printf("Method took %f seconds round trip\n",
				 std::chrono::duration_cast<std::chrono::duration<double, std::micro>>(
						 t2 - t1)
						 .count());

	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}

void server(int readFD, int writeFD) {
	printf("Server Started\n");

	StardustXR::BlankScenegraph blankScenegraph;
	StardustXR::Messenger messenger(readFD, writeFD, &blankScenegraph);
	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}

int main(int argc, char **argv) {
	if (pipe(s2cpipe) == -1) {
		perror("s2cpipe");
		exit(EXIT_FAILURE);
	}
	if (pipe(c2spipe) == -1) {
		perror("c2spipe");
		exit(EXIT_FAILURE);
	}

	pid_t cpid;
	cpid = fork();
	if (cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) {
		close(s2cpipe[1]);
		close(c2spipe[0]);
		client(s2cpipe[0], c2spipe[1]);
	} else {
		close(s2cpipe[0]);
		close(c2spipe[1]);
		server(c2spipe[0], s2cpipe[1]);
	}

	return 0;
}

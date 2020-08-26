#include "client/clientconnector.hpp"

namespace StardustXR {

void SendFD(int socket, int fd) {
	struct msghdr msg = {0};
	char buf[CMSG_SPACE(sizeof(fd))];
	memset(buf, '\0', sizeof(buf));
	struct iovec io;
	io.iov_base = (void *)"ABC";
	io.iov_len = 3;
	msg.msg_iov = &io;
	msg.msg_iovlen = 1;
	msg.msg_control = buf;
	msg.msg_controllen = sizeof(buf);

	struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	cmsg->cmsg_len = CMSG_LEN(sizeof(fd));

	*((int *)CMSG_DATA(cmsg)) = fd; // CMSG_DATA() returns a pointer to the data portion of a cmsghdr.

	msg.msg_controllen = CMSG_SPACE(sizeof(fd));

	if (sendmsg(socket, &msg, 0) < 0)
		printf("Failed to send message\n");
}

bool ConnectClient(std::string path, int &read, int &write) {
	int s2c[2];
	pipe(s2c);
	int c2s[2];
	pipe(c2s);
	int s, len;
	struct sockaddr_un remote;

	if ((s = socket(AF_UNIX, SOCK_SEQPACKET, 0)) == -1) {
		perror("socket");
		return false;
	}

	printf("Trying to connect to Stardust's server at %s...\n", path.c_str());

	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, path.c_str());
	len = strlen(remote.sun_path) + sizeof(remote.sun_family);
	if (connect(s, (struct sockaddr *)&remote, len) == -1) {
		perror("connect");
		return false;
	}

	printf("Connected.\n");

	SendFD(s, c2s[0]);
	SendFD(s, s2c[1]);

	read = s2c[0];
	write = c2s[1];
	return true;
}

} // namespace StardustXR

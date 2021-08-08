#include "messengermanager.hpp"

namespace StardustXR {

MessengerManager::MessengerManager(const char *socketPath) {
  this->socketPath = socketPath;
  this->socketThread = std::thread(&StardustXR::MessengerManager::socketLoop, this);
}
MessengerManager::~MessengerManager() {}

MessengerManager::RecieveFDReturn MessengerManager::recieveFD(int socket) {
  struct msghdr msg = {0};

  char m_buffer[256];
  struct iovec io = {.iov_base = m_buffer, .iov_len = sizeof(m_buffer)};
  msg.msg_iov = &io;
  msg.msg_iovlen = 1;

  char c_buffer[256];
  msg.msg_control = c_buffer;
  msg.msg_controllen = sizeof(c_buffer);

  RecieveFDReturn ret = {0};
  strcpy(ret.buf, m_buffer); // should be ret.buf = m_buffer, but not modifiable l-value :(
  if (recvmsg(socket, &msg, 0) < 0) {
	// printf("Didn't get a FD\n");
	ret.fd = -1;
	return ret;
  }
  struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);

  unsigned char *data = CMSG_DATA(cmsg);

  // printf("About to extract fd\n");
  int fd = *((int *)data);
  // printf("Extracted fd %d\n", fd);
  ret.fd = fd;
  return ret;
}

void MessengerManager::socketLoop() {
  printf("socketLoop: loop starting, trying to make a socket at %s .\n", socketPath);
  int s, s2;
  struct sockaddr_un local, remote;
  if ((s = socket(AF_UNIX, SOCK_SEQPACKET, 0)) == -1) {
	perror("socket");
	exit(1);
  };

  local.sun_family = AF_UNIX; /* local is declared before socket() ^ */
  strcpy(local.sun_path, socketPath);
  unlink(local.sun_path);
  int len1 = strlen(local.sun_path) + sizeof(local.sun_family);

  if (bind(s, (struct sockaddr *)&local, len1) == -1) {
	perror("bind");
	exit(1);
  }
  if (listen(s, 5) == -1) {
	perror("listen");
	exit(1);
  }
  unsigned int len = sizeof(struct sockaddr_un);
  while (1) {
	// Mainloop for now.
	// Badly made, just fyi.
	printf("socketLoop: waiting for a connection...\n");
	// This accept() call blocks indefinitely when no clients are trying to
	// connect. So, this is a problem when we want to shutdown, because how do
	// we stop this thread? There are two solutions. One, use poll() or epoll()
	// with a timeout, so this thread can check if it's supposed to shutdown
	// within a reasonable amount of time (say 200ms). But what I'll do for now
	// is just let it block forever, and instead do raise(SIGKILL) when we want
	// to shutdown. This is silly, and any future contributors should FIX. THIS.
	// No good reason to do it this way.
	// --Moses
	if ((s2 = accept(s, (struct sockaddr *)&remote, &len)) ==
		-1) { // Usually blocking. Not a problem.
	  perror("accept");
	  continue; // Probably should be replaced with exit() or something. This is a very fatal condition
	}
	printf("socketLoop: client connected on %s .\n", socketPath);
	usleep(1000);
	MessengerManager::RecieveFDReturn in = {-1, 0};
	MessengerManager::RecieveFDReturn out = {-1, 0};
	int i = 0;
	while (1) {
	  if (i == 100) {
		break;
	  }
	  in = recieveFD(s2);
	  out = recieveFD(s2);
	  if ((in.fd != -1) && (out.fd != -1)) {

		break;
	  }
	  i++;
	  printf("%d\n", i);
	}
	close(s2);
	usleep(1000);
	// std::queue <int> q = *fd_queue;
	if (i != 100) {
	  printf("socketLoop: Client provided fd's. in: %d, out: %d\n", in.fd,
			 out.fd);
	  clientConnected(in.fd, out.fd);
	} else {
	  printf("socketLoop: Client failed to provide fd's\n");
	}
  }
}

} // namespace StardustXR

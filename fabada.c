//Este codigo mola 
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  void* addr = (void*) (0xfabada >> 12 << 12);
  void *r = mmap(addr, 1 << 12, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

  if (r == MAP_FAILED) {
    perror("mmap");
    return -1;
  }

  if (r != addr) {
    fprintf(stderr, "mmap returned address %p, but expected %p\n", r, addr);
    return -1;
  }

  *((char**)0xfabada) = "chorizo";

  printf("%s\n", *(char**)0xfabada);
  pause();
  return 0;
}

//Este codigo mola 
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  long pagesz = sysconf(_SC_PAGESIZE);

  void* addr = (void*) ((long)0xfabada & (~(pagesz - 1)));
  void *r = mmap(addr, pagesz, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

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

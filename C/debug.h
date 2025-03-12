#define TALKS3_ON_ONE_CHAN

void PFATAL(const char* msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}


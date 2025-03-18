void PFATAL(const char* msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}
